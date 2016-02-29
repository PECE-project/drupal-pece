<?php
/**
 * @file
 *  Sending mail using PHPMailer class.
 */

require_once 'og_mailinglist_api.inc';
require_once 'og_mailinglist_common.inc';
require_once 'og_mailinglist_utilities.inc';

/**
 * Sends emails for comments.
 *
 * @param $comment
 *  Comment object, for which to send the email.
 *
 * @param $node
 *  Node of the comment.
 *
 * @param $gids
 *  Group IDs of groups where $node belongs.
 */
function og_mailinglist_send_comment_email($comment, $node, $gids) {
  // Check if comment arrived via email so it's already sent.
  if (_og_mailinglist_email_already_sent($comment->nid, $comment->cid)) {
    return;
  }
  
  // Load user.
  $author = user_load($comment->uid);

  // Load parent group nodes.
  $group_nodes = node_load_multiple($gids);

  // Add default values.
  $headers = array();
  $recipients = array('to' => array(), 'cc' => array(), 'bcc' => array());
  $recipients['from'] = _og_mailinglist_sender($author);

  // Set Message-ID.
  $server = og_mailinglist_server();
  $headers['message-id'] = format_string('<node-@nid-comment-@cid@@server>',
    array('@nid' => $node->nid, '@cid' => $comment->cid, '@server' => $server));

  // If the comment is in reply to another comment, set the in-reply-to header
  // to that comment's message-id, else to the parent post's message-id.
  $parent_message_id = _og_mailinglist_get_messageid_from_nid($node->nid);
  $headers += _og_mailinglist_references_headers($node->nid, $comment->pid, $parent_message_id);

  // Decorate subject.
  $groups_list = _og_mailinglist_build_subject($group_nodes);
  $headers['subject'] = 'Re: ' . $groups_list . ' ' . $node->title;

  // Decorate body.
  $rendered_body = comment_view($comment, $node);
  $html = $rendered_body['comment_body']['0']['#markup'];

  // Add the user's signature and footer.
  $html .= theme('og_mailinglist_attached_files', array('comment' => $comment));
  $html .= theme('og_mailinglist_user_signature', array('user' => $author));
  $html .= theme('og_mailinglist_mail_footer', array('node' => $node));

  $text = drupal_html_to_text($html);

  foreach ($group_nodes as $group_node) {
    $recipients['to'] += _og_mailinglist_reciever($group_node);
  }

  // Users who already got this email since they are members of other groups.
  $already_mailed = array();

  foreach ($group_nodes as $group_node) {
    $recipients['bcc'] = _og_mailinglist_get_subscribers($node, $group_node, TRUE);

    // Remove possible double entries.
    foreach ($already_mailed as $email => $name) {
      unset($recipients['bcc'][$email]);
    }
    $already_mailed += $recipients['bcc'];

    // Add list headers.
    $list_headers = _og_mailinglist_list_headers($group_node);
    foreach ($list_headers as $key => $value) {
      $headers[$key] = $value;
    }

    // Send off the email.
    $success = _og_mailinglist_send_email($headers, $recipients, $text, $html);
  }

  // We log the message only once.
  if ($success) {
    // In case of multiple groups and emails log it only once.
    og_mailinglist_log_email_sent('web', $node->nid, $comment->cid,
      $parent_message_id, $headers);
  }
  else {
    watchdog('og_mailinglist', "OG_Mailinglist couldn't send a new comment email.", NULL, WATCHDOG_ERROR);
  }
}

/**
 * Master function for sending an email for a new node.
 */
function og_mailinglist_send_node_email($node, $gids) {
  // Check if node arrived via email so already sent.
  if (_og_mailinglist_email_already_sent($node->nid)) {
    return;
  }
  
  // Load user.
  $author = user_load($node->uid);

  // Load parent group nodes.
  $group_nodes = node_load_multiple($gids);

  // Add default values.
  $headers = array();
  $recipients = array('to' => array(), 'cc' => array(), 'bcc' => array());

  // Set Message-ID.
  $server = og_mailinglist_server();
  $headers['message-id'] = format_string('<node-@nid-comment-0@@server>',
    array('@nid' => $node->nid, '@server' => $server));

  // Decorate subject.
  $groups_list = _og_mailinglist_build_subject($group_nodes);
  $subject = $groups_list . ' ' . $node->title;

  // Prepare node body for viewing.
  $rendered_body = node_view($node);

  // If body is empty, we will send no e-mail.
  if (empty($rendered_body['body'])) {
    drupal_set_message(t('Message body is empty. Node was created but no e-mail was sent.'), 'error');
    return;
  }

  $html = $rendered_body['body'][0]['#markup'];

  // Add the user's signature and footer.
  $html .= theme('og_mailinglist_attached_files', array('node' => $node));
  $html .= theme('og_mailinglist_user_signature', array('user' => $author));
  $html .= theme('og_mailinglist_mail_footer', array('node' => $node));

  // Let other modules alter outgoing node emails.
  $data = array(
    'subject' => $subject,
    'body' => $html,
    'group_nodes' => $group_nodes,
    'title' => $node->title,
    'nid' => $node->nid,
    'node' => $node,
  );

  drupal_alter('og_mailinglist_new_node', $data);
  $headers['subject'] = $data['subject'];
  $html = $data['body'];
  $text = drupal_html_to_text($html);
  $group_nodes = $data['group_nodes'];

  $recipients['from'] = _og_mailinglist_sender($author);
  foreach ($group_nodes as $group_node) {
    $recipients['to'] += _og_mailinglist_reciever($group_node);
  }

  // Users who already got this email since they are members of other groups.
  $already_mailed = array();

  foreach ($group_nodes as $group_node) {
    $recipients['bcc'] = _og_mailinglist_get_subscribers($node, $group_node, TRUE);

    // Remove possible double entries.
    foreach ($already_mailed as $email => $name) {
      unset($recipients['bcc'][$email]);
    }
    $already_mailed += $recipients['bcc'];

    // Add list headers.
    $list_headers = _og_mailinglist_list_headers($group_node);
    foreach ($list_headers as $key => $value) {
      $headers[$key] = $value;
    }

    // Send off the email.
    $success = _og_mailinglist_send_email($headers, $recipients, $text, $html);
  }

  if ($success) {
    og_mailinglist_log_email_sent('web', $node->nid, 0, $headers['message-id'], $headers);
  }
  else {
    watchdog('og_mailinglist', "OG_Mailinglist couldn't send a new node email for node.", NULL, WATCHDOG_ERROR);
  }
}

