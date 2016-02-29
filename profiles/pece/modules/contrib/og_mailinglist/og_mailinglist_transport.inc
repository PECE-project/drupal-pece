<?php
/**
 * @file
 *  Recieves group email, posts as node or comment and sends it out again.
 */

require_once 'og_mailinglist_api.inc';
require_once 'og_mailinglist_common.inc';
require_once 'og_mailinglist_utilities.inc';

og_mailinglist_mimeDecode_load_library();
og_mailinglist_phpmailer_load_library();

/**
 * Receive messages POSTed from an external source.
 *
 * This function enables messages to be sent to a Drupal site via POST or some
 * other RFC822 source input (e.g. directly from a mail server).
 *
 * Original version written by Conan Albrecht in March 2009.
 */
function og_mailinglist_post() {
  // Check if posting emails over HTTP is disabled.
  if (variable_get('og_mailinglist_address_open', '1') != '1') {
    drupal_access_denied();
  }

  $group_name = isset($_POST['group_name']) ? $_POST['group_name'] : NULL;
  $message = isset($_POST['message']) ? $_POST['message'] : '';
  $token = isset($_POST['token']) ? $_POST['token'] : '';
  $hash = md5(variable_get('og_mailinglist_incoming_key', '**') . $message);

  if ($hash != $token) {
    watchdog('access denied', 'Authentication error for POST e-mail. Check that you\'ve set the validation string in /admin/config/group/mailinglist and in site_info.php', array(), WATCHDOG_WARNING);
    return drupal_access_denied();
  }

  // If the Maillog module has been set to turn off emails, return.
  if (!variable_get('maillog_send', TRUE)) {
    watchdog('WATCHDOG_INFO', 'Maillog has disabled this site from sending emails. An incoming email was left unprocessed.', array(), WATCHDOG_INFO);
    return;
  }

  _og_mailinglist_process_email($message, $group_name);
}

function _og_mailinglist_process_email($raw_email, $group_name = NULL) {
  try {
    // Extract all the needed info from the email into a simple array.
    $email = _og_mailinglist_parse_email($raw_email);

    // If the x-BeenThere header is set, this email looped back to the server
    // or if there is not a message-id (happens with spam), reject it.
    if (!empty($email['headers']['x-beenthere'])
      or empty($email['headers']['message-id'])) {
      exit();
    }

    // Let's double check if this message has been here.
    // https://drupal.org/node/2181049
    $result = db_query('SELECT ogms.nid FROM {og_mailinglist_source} ogms
        WHERE ogms.message_id = :msgid',
        array(':msgid' => $email['headers']['message-id']));
    if ($result->rowCount() > 0) {
        exit();
    }

    // Let's set the message subject in case it's missing.
    if (empty($email['headers']['subject'])) {
      $email['headers']['subject'] = t('(no subject)');
    }

    // Did we actually get email text back? If not, throw an exception.
    if ($email['text'] == "") {
      throw new Exception(t("Could not parse message body from the email."));
    }

    // Check the size of the body and kick out if too large (for security).
    $max_size = variable_get('og_mailinglist_max_message_size', 200); // 200kb
    if (strlen($email['text']) > $max_size * 1024 && $max_size != 0) {
      throw new Exception(t("Discussion items sent via email must be less than !max_size Kb. For security reasons, please post larger messages through the web interface.", array("!max_size" => $max_size)));
    }

    // Get the user.
    $author = _og_mailinglist_user_load_by_mail(key($email['from']));

    // Check how many posts have been made by this user (for security).
    if ($max_posts = variable_get('og_mailinglist_max_posts_per_hour', 20) > 0) {
      $one_hour_ago = REQUEST_TIME - 3600;
      $num_recent_posts = db_select('node', 'n')
        ->condition('n.uid', $author->uid)
        ->condition('n.created', $one_hour_ago, '>')
        ->countQuery()
        ->execute()
        ->fetchField();
      if ($num_recent_posts > $max_posts) {
        throw new Exception(t("You have posted via email too many times in the last hour. For security reasons, please wait a while or post through the regular web interface."));
      }
    }

    // Initialize group_names array.
    $group_names = $group_name ? array($group_name => '') : array();
    $group_names += _og_mailinglist_extract_group_names($email['to']);
    $group_names += _og_mailinglist_extract_group_names($email['cc']);

    // This email hit this code accidentally, since it does not contain
    // an email with this servers domain as a recipient.
    if (!count($group_names)) {
      $sender = _og_mailinglist_recipient_string($email['from']);
      $recipients = _og_mailinglist_recipient_string($email['to'], $email['cc']);
      watchdog('og_mailinglist', "Email from %sender to %recipients was dropped since no recipients are on this domain.",
        array('%sender' => $sender, '%recipients' => $recipients),
        WATCHDOG_NOTICE);
      exit(0);
    }

    // Get the group IDs.
    // We are safe since the group_email field is required to be lowercase.
    $group_names_list = array();
    foreach ($group_names as $group_name => $group_email) {
      $group_names_list[] = strtolower($group_name);
    }
    $query = new EntityFieldQuery;
    $query->entityCondition('entity_type', 'node')
      ->fieldCondition(OG_MAILINGLIST_EMAIL_FIELD, 'value', $group_names_list, 'IN')
      ->addMetaData('account', $author);
    $result = $query->execute();

    if (empty($result)) {
      throw new Exception(t("Could not locate groups with names !group_names",
        array('!group_names' => '"' . implode('", "', $group_names_list) . '"')));
    }
    $to_gids = array_keys($result['node']);

    // Check if this user is member of at least one of these groups
    // (for security).
    foreach ($to_gids as $key => $gid) {
      if (!og_is_member('node', $gid, 'user', $author)) {
        unset($to_gids[$key]);
      }
    }

    // See if the email is a comment to an existing node or a new node.
    // If the email is a comment to a node, we should be able to get the
    // node ID of the original node.
    $email['nid'] = og_mailinglist_parse_nid($email);

    // User might be subscribed to the thread.
    if (empty($to_gids) and $email['nid']) {
      // See also og_mailinglist_get_thread_subscriptions()
      $query = db_select('og_mailinglist_thread_subscription', 'ogmt');
      $query->condition('ogmt.uid', $author->uid);
      $query->addField('ogmt', 'uid');
      $result = $query->execute();

      if (empty($result)) {
        throw new Exception(t("You are not a member of any of the groups you tried to post to and you are not subscribed to the thread either."));
      }
    }
    elseif (empty($to_gids)) {
        throw new Exception(t("You are not a member of any of the groups you tried to post to."));
    }

    if ($email['nid']) {
      $node = node_load($email['nid']);
      $group_refs = field_get_items('node', $node, 'og_group_ref');

      // Check if the user is a member of at least one group.
      $gids = array();
      foreach ($group_refs as $ref) {
        $gids[] = $ref['target_id'];
      }
      // Mark groups to be added to node.
      $new_gids = array();
      foreach ($to_gids as $gid) {
        if (!in_array($gid, $gids)) {
          $new_gids[] = $gid;
          $gids[] = $gid;
        }
      }
    }
    else {
      $new_gids = $to_gids;
      $gids = $to_gids;
    }

    // Load group nodes.
    sort($gids);
    $group_nodes = node_load_multiple($gids);
    $email['group_nodes'] = $group_nodes;

    // Check if groups are published.
    // If a group is not published, it's effectively not there.
    foreach ($group_nodes as $gid => $group_node) {
      if ($group_node->status === 0) {
        unset($group_nodes[$gid]);
      }
    }
    if (empty($group_nodes)) {
      throw new Exception(t("None of the group nodes you were trying to post to are published."));
    }

    // Let's decide whether it's node or comment.
    if (empty($email['nid'])) {
      $type = 'node';
    }
    else {
      $type = 'comment';
      $node = node_load($email['nid']);

      // Remove the group identifier (e.g. [a-group]) from the subject line.
      $treated_subject = preg_replace("/^[RrEe:]{3}\s\[[\w-]*\]/", "", $email['headers']['subject']);

      // Email is forwarded, if it is addressed to other groups only.
      $members = array();
      $not_members = array();
      foreach ($group_nodes as $gid => $group_node) {
        if (og_is_member('node', $group_node->nid, 'node', $email['nid']))
          $members[$gid] = $group_node;
        else
          $not_members[$gid] = $group_node;
      }
      // If there are no direct members, then it is definitely a new post
      // or the thread might be forked by changing the subject line.
      // The levenshtein distance between a reply and node title
      // should be 4 (e.g. "a subject" and "Re: a subject").
      // Let's use 7 for oddness of foreign languages.
      if ((empty($members) and count($not_members))
        or (variable_get('og_mailinglist_new_thread_from_subject', TRUE) and levenshtein($node->title, $treated_subject) > 7)) {
        $type = 'node';
      }
    }

    // Let's save either node or comment and send the emails.
    if ($type == 'node') {
      // Check if user has permission to publish.
      $node_type = variable_get('og_mailinglist_default_content_type', 'article');
      foreach ($group_nodes as $gid => $group_node) {
        // Note: don't skip alter, but ignore admin (see og_user_access()).
        if (!og_user_access('node', $gid, 'create ' . $node_type . ' content', $author, FALSE, TRUE)) {
          unset($group_nodes[$gid]);
        }
      }
      if (empty($group_nodes)) {
        throw new Exception(t("You do not have permission to post to any of the group nodes you were trying to. Please contact the site administrator."));
      }
      og_mailinglist_save_node($email, $group_nodes, $author);
    }
    elseif ($type == 'comment') {
      og_mailinglist_save_comment($email, $group_nodes, $node, $new_gids, $author);
    }

    // Tell MTA we had success!
    exit(0);
  }
  catch (Exception $e) {
    try {
      watchdog('og_mailinglist', "Error processing email from %email: %message",
        array('%email' => reset($email['from']) . ' <' . key($email['from']) . '>', '%message' => $e->getMessage()), WATCHDOG_WARNING);
      _og_mailinglist_send_error_email($email, $e->getMessage());

      // Print error message to log, then quit.
      echo "Error: " . $e->getMessage() . "\n";
      exit(0);
    }
    catch (Exception $e2) {
      // If we got here, we couldn't even send an email back to the sender, so
      // just have MTA compose an error message and send it back.
      echo "Error: " . $e2->getMessage() . " ::: Embedded Error: " . $e->getMessage() . "\n";
      exit(1);
    }
  }
}

/**
 * Save new comment that came through email.
 */
function og_mailinglist_save_comment(&$email, $group_nodes, $node, $new_gids, $author) {
  $email['node'] = $node;

  // Let other modules alter the new comment or delay posting for another time
  // (e.g. a moderation module might want to delay posting for a time).
  drupal_alter('og_mailinglist_new_email_comment', $email);

  // Other modules can unset certain emails to stop them from being saved and sent.
  // If they do, we'll just exit out.
  if (empty($email)) {
    return;
  }

  // Check that this user has rights to post comments.
  foreach ($group_nodes as $gid => $group_node) {
    // Note: don't skip alter, but ignore admin (see og_user_access()).
    if (!og_user_access('node', $gid, 'post comments by mail', $author, FALSE, TRUE)) {
      unset($group_nodes);
    }
  }
  if (empty($group_nodes)) {
    throw new Exception(t("You do not have rights to post comments to any of the group nodes you were trying to. Please contact the site administrator."));
  }

  // Check that this post has comments enabled.
  if ($node->comment != COMMENT_NODE_OPEN) {
    throw new Exception(t("Comments (replies) have been disabled for this post."));
  }

  // If there are new groups add these to the thread.
  if (!empty($new_gids)) {
    foreach ($new_gids as $gid) {
      $node->og_group_ref[LANGUAGE_NONE][]['target_id'] = $gid;
    }
    node_save($node);
  }

  $mailbody = $email['text'];

  // Create an object representing the comment.
  $comment = new stdClass();
  $comment->cid = 0;
  $comment->nid = $node->nid;
  $comment->uid = $author->uid;
  $comment->name = $author->name;
  $comment->language = LANGUAGE_NONE;
  $comment->is_anonymous = 0;
  $comment->node_type = 'comment_node_' . $node->type;
  $comment->status = user_access('skip comment approval', $author) ? COMMENT_PUBLISHED : COMMENT_NOT_PUBLISHED;

  // A custom variable to keep phpmailer from sending double email.
  $comment->og_mailinglist_from_email = TRUE;

  if (preg_match("/re:\s*\[.*?\]\s*(.*)/i", $email['headers']['subject'], $matches)) {
    $comment->subject = $matches[1];
  }
  elseif (preg_match("/re: +(.*)/i", $email['headers']['subject'], $matches)) {
    $comment->subject = $matches[1];
  }
  else {
    $comment->subject = $email['headers']['subject'];
  }
  // Subject can be at most 64 chars long.
  $comment->subject = truncate_utf8($comment->subject, 64, TRUE, TRUE, 54);

  $comment->comment_body[$comment->language][0]['value'] = $mailbody;
  $filter = variable_get('og_mailinglist_default_filter_format', 'plain_text');
  $comment->comment_body[$comment->language][0]['format'] = $filter;

  // Log that comment came from email so og_mailinglist_phpmailer doesn't send an email as well.
  $parent_message = _og_mailinglist_get_thread_parent($email['headers']);
  $parent_message_id = isset($parent_message->message_id) ? $parent_message->message_id : 0;

  // If enabled, set comment parent = cid of in-reply-to for comment threading.
  if (variable_get('og_mailinglist_thread_comments', FALSE)
    and isset($parent_message->cid)) {
    $comment->pid = $parent_message->cid;
  }
  else {
    $comment->pid = 0;
  }

  // Add attachments if any.
  if (!empty($email['attachments'])) {
    _og_mailinglist_save_files('comment', $comment, $email['attachments']);
  }

  // Let other modules alter the comment object before saving.
  drupal_alter('og_mailinglist_save_comment', $comment);

  // Save the new comment.
  comment_submit($comment);
  comment_save($comment);

  // Send off the email.
  _og_mailinglist_email_comment_email($email, $node, $group_nodes, $comment, $author);

  // Log that this comment came by email.
  og_mailinglist_log_email_sent('email', $node->nid, $comment->cid, $parent_message_id, $email['headers']);

  // Report activity to watchdog.
  $group_list = array();
  foreach ($group_nodes as $gid => $group_node) {
    $group_list[] = $group_node->title . ' (gid' . $gid . ')';
  }
  watchdog('og_mailinglist', "Posted comment: %subject to groups: %group_list",
    array(
      '%subject' => $comment->subject,
      '%group_list' => implode($group_list, ', '),
    ),
    WATCHDOG_INFO, l(t('view'), 'comment/' . $comment->cid, array('fragment' => 'comment-' . $comment->cid)));
}

/**
 * Save new nodes that came through email.
 */
function og_mailinglist_save_node(&$email, $group_nodes, $author) {
  // Let other modules alter the new node or delay posting for another time
  // (e.g. a moderation module might want to delay posting for a time).
  drupal_alter('og_mailinglist_new_email_node', $email);

  // Other modules can unset certain emails to stop them from being saved and sent.
  // If they do, we'll just exit out.
  if (empty($email)) {
    exit(0);
  }

  // Unset the in-reply-to and references headers so this new thread
  // doesn't get merged with the old thread if the email isn't brand new.
  unset($email['headers']['in-reply-to']);
  unset($email['structure']->headers['in-reply-to']);
  unset($email['headers']['references']);
  unset($email['structure']->headers['references']);

  $mailbody = $email['text'];

  // Create the new node
  $node = new stdClass();
  $node->type = variable_get('og_mailinglist_default_content_type', 'article');
  node_object_prepare($node);

  $node->title = $email['headers']['subject'];
  $node->uid = $author->uid;
  $node->language = LANGUAGE_NONE;
  $node->body[$node->language][0]['value'] = $mailbody;
  $filter = variable_get('og_mailinglist_default_filter_format', 'plain_text');
  $node->body[$node->language][0]['format'] = $filter;

  // Custom value to keep the e-mail from being sent twice.
  $node->og_mailinglist_from_email = TRUE;

  foreach ($group_nodes as $gid => $group_node) {
    $node->og_group_ref[$node->language][]['target_id'] = $gid;
  }

  // Add attachments if any.
  if (!empty($email['attachments'])) {
    _og_mailinglist_save_files('node', $node, $email['attachments']);
  }

  // Let other modules alter the node object before saving.
  drupal_alter('og_mailinglist_save_node', $node);

  node_save($node);

  // Send off email.
  _og_mailinglist_email_node_email($email, $node, $group_nodes, $author);

  // Log that this node came from email.
  og_mailinglist_log_email_sent('email', $node->nid, 0, $email['headers']['message-id'], $email['headers']);

  $group_list = array();
  foreach ($group_nodes as $gid => $group_node) {
    $group_list[] = $group_node->title . ' (gid' . $gid . ')';
  }
  // Report activity to watchdog.
  watchdog('og_mailinglist', 'Posted node: %title to groups: %group_list.',
    array(
      '%title' => $node->title,
      '%group_list' => implode($group_list, ', '),
    ),
    WATCHDOG_INFO, l(t('view'), 'node/' . $node->nid));
}

function _og_mailinglist_email_node_email(&$email, $node, $group_nodes, $author) {
  // Build new email.
  _og_mailinglist_remove_some_headers($email);

  // Remove two more header fields when thread is forked.
  unset($email['headers']['in-reply-to']);
  unset($email['headers']['references']);

  // Recipients.
  $recipients = array();
  $recipients['from'] = _og_mailinglist_sender($author);
  $recipients['to'] = $email['to'];
  $recipients['cc'] = $email['cc'];
  $recipients['bcc'] = array();

  foreach ($group_nodes as $group_node) {
    $recipients['to'] += _og_mailinglist_reciever($group_node);
  }

  // Users who already got this email since they are members of other groups
  // or were emailed directly.
  $already_mailed = array();
  $already_mailed += $recipients['from'];
  $already_mailed += $recipients['to'];
  $already_mailed += $recipients['cc'];

  // Decorate subject.
  $groups_list = _og_mailinglist_build_subject($group_nodes);
  $email['headers']['subject'] = $groups_list . ' ' . $node->title;

  // Set footer.
  $footer = theme('og_mailinglist_attached_files', array('node' => $node));
  $footer .= theme('og_mailinglist_user_signature', array('user' => $author));
  $footer .= theme('og_mailinglist_mail_footer', array('node' => $node));
  _og_mailinglist_add_footer($email, $footer);

  // Encode email.
  unset($email['structure']->headers);
  $body = _og_mailinglist_encode_email(array($email['structure']));

  // Check if entire body should be encoded as base64
  $body = _og_mailinglist_check_base64($body, $email['headers']);

  foreach ($group_nodes as $group_node) {
    $recipients['bcc'] = _og_mailinglist_get_subscribers($node, $group_node, TRUE);

    // Remove possible double entries.
    foreach ($already_mailed as $address => $name) {
      unset($recipients['bcc'][$address]);
    }
    $already_mailed += $recipients['bcc'];

    // Add list headers.
    $list_headers = _og_mailinglist_list_headers($group_node);
    foreach ($list_headers as $key => $value) {
      $email['headers'][$key] = $value;
    }

    // Send off the email.
    $success = _og_mailinglist_send_email($email['headers'], $recipients, $body);
  }

  // If the sender's subscription type isn't email, give him a thread subscription.
  if (og_mailinglist_get_group_subscription_type($node->og_group_ref[LANGUAGE_NONE][0], $node->uid) != "email") {
    og_mailinglist_save_thread_subscriptions($node->nid, array($node->uid));
  }
}

function _og_mailinglist_email_comment_email($email, $node, $group_nodes, $comment, $author) {
  _og_mailinglist_remove_some_headers($email);

  // Recipients.
  $recipients = array();
  $recipients['from'] = _og_mailinglist_sender($author);
  $recipients['to'] = $email['to'];
  $recipients['cc'] = $email['cc'];
  $recipients['bcc'] = array();

  foreach ($group_nodes as $group_node) {
    $recipients['to'] += _og_mailinglist_reciever($group_node);
  }

  // Users who already got this email since they are members of other groups
  // or were emailed directly.
  $already_mailed = array();
  $already_mailed += $recipients['from'];
  $already_mailed += $recipients['to'];
  $already_mailed += $recipients['cc'];

  // Decorate subject.
  $groups_list = _og_mailinglist_build_subject($group_nodes);
  $email['headers']['subject'] = 'Re: ' . $groups_list . ' ' . $comment->subject;

  // Set footer.
  $footer = theme('og_mailinglist_attached_files', array('comment' => $comment));
  $footer .= theme('og_mailinglist_user_signature', array('user' => $author));
  $footer .= theme('og_mailinglist_mail_footer', array('node' => $node, 'comment' => $comment));
  _og_mailinglist_add_footer($email, $footer);

  // Encode email.
  unset($email['structure']->headers);
  $body = _og_mailinglist_encode_email(array($email['structure']));

  // Check if entire body should be encoded as base64
  $body = _og_mailinglist_check_base64($body, $email['headers']);

  foreach ($group_nodes as $group_node) {
    $recipients['bcc'] = _og_mailinglist_get_subscribers($node, $group_node, TRUE);

    // Remove possible double entries.
    foreach ($already_mailed as $address => $name) {
      unset($recipients['bcc'][$address]);
    }
    $already_mailed += $recipients['bcc'];

    // Add list headers.
    $list_headers = _og_mailinglist_list_headers($group_node);
    foreach ($list_headers as $key => $value) {
      $email['headers'][$key] = $value;
    }

    // Send off the email.
    $success = _og_mailinglist_send_email($email['headers'], $recipients, $body);
  }
}

function _og_mailinglist_parse_email($raw_email) {
  $params = array(
    'include_bodies' => TRUE,
    'decode_bodies' => TRUE,
  );
  $email = array();
  $email['attachments'] = array();

  // Decode the email message.
  $decoder = new Mail_mimeDecode($raw_email);
  $structure = $decoder->decode($params);
  $email['structure'] = clone $structure;

  // Copy headers to the $email array.
  $email['headers'] = array_copy($structure->headers);

  if (!empty($structure->parts)) {
    foreach ($structure->parts as $i => $part) {
      if (!empty($part->parts)) {
        $sub_part = $part->parts;

        foreach ($sub_part as $j => $sub_part_part) {
          if (isset($sub_part_part->disposition) and ($sub_part_part->disposition === 'attachment')) {
            $email['attachments'][] = _og_mailinglist_parse_attachment($sub_part_part);
          }
          elseif ($sub_part_part->ctype_secondary == 'plain') {
            $email['text'] = _og_mailinglist_parse_content($sub_part_part);
          }
          elseif ($sub_part_part->ctype_secondary == 'html') {
            $email['html'] = _og_mailinglist_parse_content($sub_part_part);
          }
        }
      }

      if (isset($part->disposition) and ($part->disposition === 'attachment')) {
        $email['attachments'][] = _og_mailinglist_parse_attachment($part);
      }
      elseif (($part->ctype_secondary == 'plain') && empty($email['text'])) {
        $email['text'] = _og_mailinglist_parse_content($part);
      }
      elseif (($part->ctype_secondary == 'html') && empty($email['html'])) {
        $email['html'] = _og_mailinglist_parse_content($part);
      }
    }
  }
  // Make sure we always have text.
  if (isset($email['html']) && !isset($email['text'])) {
    $email['text'] = preg_replace('|<style.*</style>|mis', '', $email['html']);
    $email['text'] = drupal_html_to_text($email['text']);
  }

  // Set the default character encoding.
  $charset = 'iso-8859-1';

  if (!empty($structure->ctype_parameters['charset'])) {
    $charset = $structure->ctype_parameters['charset'];
  }

  // Last ditch attempt - use the body as-is.
  if (!isset($email['text'])) {
    // Try to convert to UTF-8.
    $email['text'] = drupal_convert_to_utf8($structure->body, $charset);
  }

  // Convert the subject and recipient fields to UTF-8.
  if (isset($email['headers']['subject'])) {
    $email['headers']['subject'] = _og_mailinglist_decode_header_utf8($email['headers']['subject']);
  }

  $raw_emails = _og_mailinglist_decode_header_utf8($email['headers']['from']);
  $email['from'] = _og_mailinglist_extract_emails($raw_emails);
  unset($email['headers']['from']);

  $raw_emails = _og_mailinglist_decode_header_utf8($email['headers']['to']);
  $email['to'] = _og_mailinglist_extract_emails($raw_emails);
  unset($email['headers']['to']);

  $email['cc'] = array();
  if (isset($email['headers']['cc'])) {
    $raw_emails = _og_mailinglist_decode_header_utf8($email['headers']['cc']);
    $email['cc'] = _og_mailinglist_extract_emails($raw_emails);
    unset($email['headers']['cc']);
  }

  return $email;
}

function _og_mailinglist_parse_attachment($part) {
  $info['data'] = $part->body;
  $info['filemime'] = $part->ctype_primary . "/" . $part->ctype_secondary;
  $info['filename'] = mb_decode_mimeheader($part->ctype_parameters['name']);

  return $info;
}

function _og_mailinglist_parse_content($part) {
  $content = $part->body;

  // Try to convert character set to UTF-8.
  if (!empty($part->ctype_parameters['charset'])) {
    $content = drupal_convert_to_utf8($content, $part->ctype_parameters['charset']);
  }

  return $content;
}

function _og_mailinglist_save_files($entity_type, &$entity, $attachments) {
  $image_field = _og_mailinglist_get_field($entity_type, 'image');
  $file_field = _og_mailinglist_get_field($entity_type, 'file');

  if (!$image_field and !$file_field) {
    return;
  }

  foreach ($attachments as $attachment) {
    $filename = _og_mailinglist_sanitise_filename($attachment['filename']);

    // Save the data to a temporary file.
    $file = file_save_data($attachment['data'], 'temporary://' . $filename);

    // If file is an image and image field is present.
    $image_errors = file_validate_is_image($file);
    if ($image_field and count($image_errors) == 0) {
      $field = $image_field;
    }
    else {
      $field = $file_field;
    }
    
    $errors = file_validate($file, $field->validators);
    if (count($errors)) {
      $error = reset($errors);
      // Find a better way to report these errors.
      drupal_set_message($error, NULL, 'error');
      file_delete($file);
      continue;
    }

    $filename = file_munge_filename($file->filename, $field->extensions);
    // TODO: decide whether to use private:// based on group privacy.
    $path = 'public://';
    if ($field->directory) {
      $dir = $path . $field->directory;
      $path = $dir . '/' . $filename;
      
      if (!file_prepare_directory($dir, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS))  {
        watchdog('og_mailinglist', 'Directory @dir cannot be made writable', array('@dir' => $dir), WATCHDOG_ERROR);
        return;
      }
    }
    else {
      $path .= $filename;
    }

    $file = file_move($file, $path);
    
    if (!$file) {
      watchdog('og_mailinglist', 'OG Mailinglist failed to attach file @file to entity', array('@file ' => $filename), WATCHDOG_ERROR);
      return;
    }
    $file->display = 1;

    if ($entity_type == $field->type) {
      $entity->{$field->name}[LANGUAGE_NONE][$file->fid] = (array) $file;
    }
    elseif ($entity_type == 'comment' and $field->type == 'node') {
      $node = node_load($entity->nid);
      $node->{$field->name}[LANGUAGE_NONE][$file->fid] = (array) $file;
    }
  }

  if (isset($node)) {
    node_save($node);
  }
}

/**
 * Get file or image field object.
 *
 * @param string $entity_type
 *   Either 'node' or 'comment'.
 * @param string $file_type
 *   Either 'image' or 'file'.
 * @return
 *   A customized object containing field properties.
 */
function _og_mailinglist_get_field($entity_type, $file_type) {
  $field = new stdClass();
  $field->name = variable_get('og_mailinglist_' . $entity_type . '_' . $file_type . '_field', 'no^field');

  if ($field->name == 'no^field') {
    return;
  }

  if ($field->name == 'attach^to^node') {
    $entity_type = 'node';
    $field->name = variable_get('og_mailinglist_' . $entity_type . '_' . $file_type . '_field', 'no^field');
  }

  $bundle = $entity_type == 'comment' ? 'comment_node_' : '';
  $bundle .= variable_get('og_mailinglist_default_content_type', 'article');

  $field->type = $entity_type;
  $field->info = field_info_field($field->name);
  $field->instance = field_info_instance($entity_type, $field->name, $bundle);
  $field->validators = file_field_widget_upload_validators($field->info, $field->instance);
  $field->extensions = $field->instance['settings']['file_extensions'];
  $field->directory = $field->instance['settings']['file_directory'];

  return $field;
}

/**
 * Take a raw attachment filename and strip out invalid characters.
 *
 * Replaces all characters up through space and all past - along with the
 * above reserved characters to sanitise filename from
 * http://php.net/manual/en/function.preg-replace.php#80431
 *
 * @param $filename
 *   A filename to be sanitised.
 * @return
 *   A sanitised filename that should be ok for use by modules that want
 *   to save the file.
 */
function _og_mailinglist_sanitise_filename($filename) {
  // Define characters that are illegal on any of the 3 major OS's
  $reserved = preg_quote('\/:*?"<>|', '/');

  // Perform cleanup.
  $filename = preg_replace("/([\\x00-\\x20\\x7f-\\xff{$reserved}])/e", "_", $filename);

  // Return the cleaned up filename.
  return $filename;
}

// Turn structure back into a plain text email using recursion.
function _og_mailinglist_encode_email($structure, $boundary = NULL) {
  $email = '';

  // Set the boundary if empty.
  if (empty($boundary) and isset($part->ctype_parameters['boundary'])) {
    $boundary = $part->ctype_parameters['boundary'];
  }

  foreach ($structure as $key => $part) {
    // Start with the boundary, if one is present.
    if ($boundary) {
      $email .= "--" . $boundary . "\n";
    }

    // Add headers when present.
    if (isset($part->headers)) {
      $email .= _og_mailinglist_encode_email_headers($part->headers) . "\n";
    }

    if (isset($part->parts)) {
      // Add nested parts.
      $email .= _og_mailinglist_encode_email($part->parts, $part->ctype_parameters['boundary']);
    }
    elseif (isset($part->body)) {
      // Encode the body as base64 if necessary.
      if (isset($part->headers['content-transfer-encoding']) and
        $part->headers['content-transfer-encoding'] == "base64") {
        $email .= wordwrap(base64_encode($part->body), 76, "\n", TRUE);
        $email .= "\n";
      }
      else {
        $email .= $part->body . "\n\n";
      }
    }
  }

  // Add the ending boundary only to the last part.
  if ($boundary) {
    $email .= "--" . $boundary . "--\n";
  }

  return $email;
}

function _og_mailinglist_encode_email_headers($array) {
  $header = "";
  if (empty($array)) {
    return $header;
  }
  foreach ($array as $key => $value) {
    // We remove quoted-printable as content-transfer-encoding
    // because mime_decode decodes that and PHP doesn't have a function
    // AFAIK to reencode the text as quoted-printable.
    if ($value && $value !== "quoted-printable") {
      $header .= capitalize_headers($key, " -") . ": " . $value . "\n";
    }
  }

  return $header;
}

// Keep mime-version, date, subject, from, to, and content-type
function _og_mailinglist_remove_some_headers(&$email) {
  // Header values which we want to keep. All lowercase here.
  $copy_headers = array('content-type', 'date', 'in-reply-to', 'message-id',
    'mime-version', 'references', 'subject');

  // Let's delete unnecessary header fields.
  foreach ($email['headers'] as $key => $value) {
    if (!in_array(strtolower($key), $copy_headers)) {
      unset($email['headers'][$key]);
    }
  }
}

function _og_mailinglist_check_base64($body, $headers) {
  // If text/plain + base64
  if (isset($headers['content-transfer-encoding']) and
    $headers['content-transfer-encoding'] == 'base64') {
    return wordwrap(base64_encode($body), 76, "\n", TRUE) . "\n";
  }
  return $body;
}

function _og_mailinglist_add_footer(&$email, $footer) {
  $structure = $email['structure'];

  if (isset($email['headers']['content-type'])) {
    $content_type = $email['headers']['content-type'];
  }
  else {
    $content_type = '';
  }

  // If message is 7/8bit text/plain and uses utf-8 character set, just
  // append the footer.
  if (isset($structure->body)
    and preg_match('/^text\/plain.*utf-8/i', $content_type)) {
    $structure->body .= "\n\n" . drupal_html_to_text($footer);
  }
  // If message is already multipart, append a new part with footer to the end.
  elseif (isset($structure->parts)
    and preg_match('/^multipart\/(mixed|related)/i', $content_type)) {
    $structure->parts[] = (object) array(
      "headers" => array(
        "content-type" => 'text/html; charset="utf-8"',
        "mime-version" => '1.0',
        "content-transfer-encoding" => '8bit',
        "content-disposition" => 'inline',
      ),
      "ctype_primary" => 'text',
      "ctype_secondary" => 'plain',
      "ctype_parameters" => array(
        "charset" => 'utf-8',
      ),
      "disposition" => 'inline',
      "body" => $footer,
    );
  }
  else {
    // Else, move existing fields into new MIME entity surrounded by new multipart
    // and append footer field to the end.
    // Copy email, remove headers from copy, rewrite the content-type, add
    // email copy as parts.
    $str_clone = clone $structure;
    if (isset($structure->headers['content-type'])) {
      $str_clone->headers = array('content-type' => $structure->headers['content-type']);
    }
    else {
      $str_clone->headers = array();
    }

    // Set correct MIME version and content type to headers.
    $email['headers']['mime-version'] = "1.0";
    $boundary = "Drupal-OG-Mailinglist--" . rand(100000000, 9999999999999);
    $content_type = "multipart/mixed; boundary=\"" . $boundary . "\"";
    $email['headers']['content-type'] = $content_type;

    $structure->ctype_primary = "multipart";
    $structure->ctype_secondary = "mixed";
    $structure->ctype_parameters = array('boundary' => $boundary);
    $structure->parts = array($str_clone);
    $structure->parts[] = (object) array(
      "headers" => array(
        "content-type" => 'text/html; charset="utf-8"',
        "mime-version" => '1.0',
        "content-transfer-encoding" => '8bit',
        "content-disposition" => 'inline',
      ),
      "ctype_primary" => 'text',
      "ctype_secondary" => 'html',
      "ctype_parameters" => array(
        "charset" => 'utf-8',
      ),
      "disposition" => 'inline',
      "body" => $footer,
    );
  }

  $email['structure'] = $structure;
}

/**
 * Try to parse nid from the email.
 *
 * @param $headers
 *  Headers of the email to be parsed.
 */
function og_mailinglist_parse_nid($email) {
  // Check the in-reply-to header.
  $parent_message = _og_mailinglist_get_thread_parent($email['headers']);
  if (!empty($parent_message->nid)) {
    return $parent_message->nid;
  }

  return _og_mailinglist_get_nid_from_subject($email['headers']['subject']);
}

function _og_mailinglist_get_nid_from_subject($subject) {
  $nid = NULL;
  preg_match("/(Re:\s\[.*?\])?\s(.+)/si", $subject, $matches);
  if (isset($matches[2])) {
    $nid = db_query("SELECT nid
      FROM {node}
      WHERE title LIKE :title
      ORDER BY created desc
      LIMIT 1",
      array(':title' => '%' . $matches[2] . '%')
    )->fetchField();
  }
  return $nid;
}

/**
 * Extract email addresses and names from a comma separated string.
 *
 * @param $addresses
 *   "@param" is a comma separated string of email addresses as it is found in
 *   email TO or CC fields, e.g John Smith <john@example.com>, joe@example.com
 *
 * @return
 *   "@return" return an associative array of emails as keys and names as
 *   values. Using keys makes it impossible to have duplicates.
 */
function _og_mailinglist_extract_emails($addresses) {
  $emails = array();
  $server = og_mailinglist_server();
  foreach (imap_rfc822_parse_adrlist($addresses, $server) as $email) {
    $emails[$email->mailbox . '@' . $email->host] = isset($email->personal) ? $email->personal : '';
  }
  return $emails;
}

/**
 * Extract group names from an array of email addresses as keys.
 *
 * @param $addresses
 *   "@param" is an array of email addresses, where addresses are held as keys.
 *   This is what is returned from _og_mailinglist_extract_emails().
 *   E.g array('john@example.com' => 'John Smith', 'joe@example.com' => '')
 *
 * @return
 *   "@return" return an associative array of usernames as keys and emails as
 *   values.
 */
function _og_mailinglist_extract_group_names($addresses) {
  // Regex borrowed from valid_email_address().
  // Case insensitivity is needed because in domain names case does not matter.
  $server = og_mailinglist_server();
  $regex = "/([a-z0-9_\-\.\+\^!#\$%&*+\/\=\?\`\|\{\}~\']+)@" . $server . "/i";

  $out = array();
  foreach ($addresses as $email => $name) {
    // Parse the group name from the email.
    if (preg_match($regex, $email, $matches)) {
      $out[$matches[1]] = $email;
    }
  }
  return $out;
}

/**
 * Get user account by e-mail.
 *
 * @param $email
 *   E-mail address of the user.
 * @return
 *   User object, if user is found. Exception is raised otherwise.
 */
function _og_mailinglist_user_load_by_mail($email) {
  // Let's find the user by the e-mail address.
  $user = user_load_by_mail($email);

  // If site is using multiple_email, check for alternative emails.
  if (!$user && module_exists('multiple_email') && $multiple = multiple_email_find_address($email)) {
    $user = user_load($multiple->uid);
  }

  if (!$user) {
    $exception = t("Could not locate the user account for @mailfrom. For security reasons, please post from the email account you are registered with.", array('@mailfrom' => $email));
    throw new Exception($exception);
  }

  // Check if user is blocked.
  if ($user->status != 1) {
    $exception = t("Your user account has been blocked, therefore you are unable to post or reply. If you believe this is a mistake, please contact a moderator.");
    throw new Exception($exception);
  }

  return $user;
}

/**
 * Compose an error message and send it off.
 */
function _og_mailinglist_send_error_email($email, $errormsg) {
  $server = og_mailinglist_server();
  $noreply = variable_get("og_mailinglist_noreply_email", t("no-reply@") . $server);

  // Compose an email back to the sender informing them of the problem.
  $head = array();
  $head[] = 'From: ' . $noreply;
  $head[] = 'References: ' . $email['headers']['message-id'];
  $head[] = 'In-Reply-To: ' . $email['headers']['message-id'];
  $head[] = 'X-Beenthere: ' . $server;
  $head[] = 'MIME-Version: 1.0';
  $head[] = 'Content-Type: text/plain; charset="utf-8"';
  $head[] = 'Content-Transfer-Encoding: 8bit';

  $body = t("Hi, sorry about this but we were unable to handle your email correctly for the following reason:")
    . "\n\n"
    . $errormsg
    . "\n\n"
    . t("Please correct this error and try again, or contact the system administrator.  Thank you.")
    . "\n\n---- " . t("Below this line is a copy of the message") . " ----\n";

  $body .= '> ' . str_replace("\n", "\n> ", $email['text']);

  // Send it off.
  $from = reset($email['from']) . ' <' . key($email['from']) . '>';
  if (!mail($from, t("Error processing message"), $body, implode("\n", $head))) {
    throw new Exception("Mail error");
  }
}

/**
 * This function is a copy from mimeDecode function _decodeHeader(), which
 * now always returns utf-8 encoded string.
 *
 * @param string $input Header field to be decoded.
 * @return string Already decoded value in utf-8 encoding.
 */
function _og_mailinglist_decode_header_utf8($input) {
  // Remove white space between encoded-words
  $input = preg_replace('/(=\?[^?]+\?(q|b)\?[^?]*\?=)(\s)+=\?/i', '\1=?', $input);

  // For each encoded-word...
  while (preg_match('/(=\?([^?]+)\?(q|b)\?([^?]*)\?=)/i', $input, $matches)) {
    $encoded = $matches[1];
    $charset = $matches[2];
    $encoding = $matches[3];
    $text = $matches[4];

    switch (strtolower($encoding)) {
      case 'b':
        $text = drupal_convert_to_utf8(base64_decode($text), $charset);
        break;
      case 'q':
        $text = str_replace('_', ' ', $text);
        preg_match_all('/=([a-f0-9]{2})/i', $text, $matches);
        foreach($matches[1] as $value) {
          $char = chr(hexdec($value));
          $text = str_replace('=' . $value, $char, $text);
        }
        $text = drupal_convert_to_utf8($text, $charset);
        break;
    }
    $input = str_replace($encoded, $text, $input);
  }
  return $input;
}
