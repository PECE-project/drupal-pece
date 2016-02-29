<?php
/**
 * @file
 * Handles sending digest emails. Digest emails are handled as cron jobs.
 *
 */

require_once 'og_mailinglist_common.inc';
require_once 'og_mailinglist_utilities.inc';

define("EMAIL_HEADER", 'background-color: #D1DCFF; font-family: helvetica;
       font-size: 160%; border-top: 1px solid #262c40; padding: 2px');
define("DISCUSSION_HEADER", 'background-color: #D1DCFF; font-family: helvetica;
       font-size: 140%; border-top: 1px solid #262c40; padding: 2px');
define("MESSAGE_HEADER", 'background-color: #E6ECFF; font-family: helvetica;
       border-top: 1px solid #262c40; padding: 2px');
// TODO -- make email from list address

function _og_mailinglist_send_digest_emails() {
  $digest_days = variable_get('og_mailinglist_digest_interval_days', 1);
  $digest_start = time() - $digest_days * 86400;

  // Get list of groups where at least one person has subscribed to a digest
  // node and which had a new post or comment in the last 24 hours.
  $query = db_select('og_mailinglist_group_subscription', 'ogms');
  $query->join('og_membership', 'om', 'om.gid = ogms.nid');
  $query->join('node', 'n', 'n.nid = om.etid');
  $query->condition('ogms.subscription_type', 'digest email');
  $query->condition('om.group_type', 'node');
  $query->condition('om.entity_type', 'node');
  $query->condition('n.created', $digest_start, '>');
  $query->condition('n.status', 1);
  $query->fields('om', array('gid', 'etid'));
  $groups_with_new_nodes = $query->execute();

  $query = db_select('og_mailinglist_group_subscription', 'ogms');
  $query->join('og_membership', 'om', 'om.gid = ogms.nid');
  $query->join('comment', 'c', 'c.nid = om.etid');
  $query->condition('ogms.subscription_type', 'digest email');
  $query->condition('om.group_type', 'node');
  $query->condition('om.entity_type', 'node');
  $query->condition('c.created', $digest_start, '>');
  $query->condition('c.status', 1);
  $query->fields('om', array('gid', 'etid'));
  $query->addField('c', 'cid');
  $groups_with_new_comments = $query->execute();

  $groups = array();
  foreach ($groups_with_new_comments as $data) {
    $groups[$data->gid][$data->etid]['status'] = 'old';
    $groups[$data->gid][$data->etid]['comments'][$data->cid] = $data->cid;
  }
  foreach ($groups_with_new_nodes as $data) {
    $groups[$data->gid][$data->etid]['status'] = 'new';
  }

  foreach ($groups as $gid => $nodes) {
    // Prepare some values.
    $group_node = node_load($gid);
    $group_title = $group_node->title;
    $group_name = _og_mailinglist_get_group_name($group_node);
    $server = og_mailinglist_server();
    $group_email = $group_name . '@' . $server;
    $group_request = $group_name . '-request@' . $server;

    // Let's sort node array to make sure these appear in right order.
    ksort($nodes);

    // Count number of new messages.
    $message_count = 0;

    foreach ($nodes as $nid => $object) {
      if ($object['status'] == 'new') {
        $nodes[$nid]['node_obj'] = node_load($nid);
      }
      else {
        $nodes[$nid]['node_obj'] = node_load($nid);
      }

      $new_messages = og_mailinglist_count_new_messages($nodes[$nid]);
      $message_count += $new_messages;
      $nodes[$nid]['new_messages'] = $new_messages;
    }

    $themed = theme('og_mailinglist_digest', array(
      'group' => $group_node,
      'nodes' => $nodes,
      'message_count' => $message_count)
    );

    // Prepare sender/reciever addresses.
    $recipients['from'] = array($group_title => $group_name . "+no-reply@" . $server);
    $recipients['to'] = array($group_email => $group_title);

    // For each person, send out an email.
    $query = db_select('og_mailinglist_group_subscription', 'ogms');
    $query->join('users', 'u', 'ogms.uid = u.uid');
    $query->condition('ogms.nid', $gid);
    $query->condition('ogms.subscription_type', 'digest email');
    $query->addField('u', 'mail');
    $emails = $query->execute();

    foreach ($emails as $email) {
      $recipients['bcc'][$email->mail] = '';
    }

    $debug_emails = variable_get('og_mailinglist_test_email_addresses', '');
    if (!empty($debug_emails)) {
      $debug_emails = explode(",", $debug_emails);
      foreach ($debug_emails as $email) {
        $recipients['bcc'][trim($email)] = '';
      }
    }

    // Get headers for digest email.
    $headers = _og_mailinglist_list_headers($group_node, TRUE);
    $headers['subject'] = $themed['subject'];

    $success = _og_mailinglist_send_email($headers, $recipients, $themed['text'], $themed['html']);

    if ($success) {
      watchdog('og_mailinglist', 'Sent digest email to @email for group @group',
                array('@email' => $group_email, '@group' => $group_title), WATCHDOG_INFO);
    }
    else {
      watchdog('og_mailinglist', 'Failed sending digest email to @email for group @group',
                array('@email' => $group_email, '@group' => $group_title), WATCHDOG_ERROR);
    }
  }
}

/**
 * Returns HTML for digest email.
 *
 * @param $variables
 *   An array containing 'group_node', 'nodes' and 'message_count'.
 * @return
 *   Array with 'subject', 'text' and 'html' with HTML code for digest email.
 */
function theme_og_mailinglist_digest($variables) {
  $absolute = array('absolute' => TRUE);

  $group = $variables['group'];
  $group_title = $group->title;
  $group_name = _og_mailinglist_get_group_name($group);
  $server = og_mailinglist_server();
  $group_email = $group_name . '@' . $server;
  $group_url = url("node/" . $group->nid, $absolute);

  $subject = t('[@group_name] Digest for @group_title - @messages_plural in @discussions_plural',
    array(
      '@group_name' => $group_name,
      '@group_title' => $group_title,
      '@messages_plural' => format_plural($variables['message_count'], '1 message', '@count messages'),
      '@discussions_plural' => format_plural(count($variables['nodes']), '1 discussion', '@count discussions'),
  ));

  $html = t("Group: @url", array('@url' => $group_url)) . "\n";
  $text = $html . "\n";
  $html .= "<ul>\n";
  $text .= t('Summary') . ":\n";

  foreach ($variables['nodes'] as $nid => $node) {
    $link_to_anchor = l($node['node_obj']->title, '',
      array(
        'fragment' => "digest-" . $nid,
        'external' => TRUE
      ));
    $messages = format_plural($node['new_messages'], "1 new", "@count new");
    $html .= '<li>' . $link_to_anchor . ' (' . $messages . ')</li>';
    $text .= $node['node_obj']->title . ' (' . $messages . ")\n";
  }
  $html .= "</ul>\n";
  $text .= "\n";

  $html .= "<hr />\n";

  // Add individual posts.
  foreach ($variables['nodes'] as $nid => $node) {
    $html .= '<a name="digest-' . $nid . '"></a>';
    $html .= '<div style="' . DISCUSSION_HEADER . '">';
    $html .= "\n" . t("Discussion: !link",
      array('!link' => l($node['node_obj']->title, "node/" . $nid, $absolute)));
    $html .= "\n</div>";

    $text .= $node['node_obj']->title . ': ' . url('node/' . $nid, $absolute) . "\n";

    $html .= "<blockquote>\n";
    // If new node created today.
    if ($node['status'] === "new") {
      $themed = theme('og_mailinglist_digest_node', array('node' => $node['node_obj']));
      $html .= $themed['html'];
      $text .= $themed['text'];
    }

    if (isset($node['comments'])) {
      $comments = comment_load_multiple($node['comments']);
        foreach ($comments as $cid => $comment) {
        $themed = theme('og_mailinglist_digest_comment', array('node' => $node['node_obj'], 'comment' => $comment));
        $html .= $themed['html'];
        $text .= $themed['text'];
      }
    }
    $html .= "</blockquote>\n";
    $text .= "\n";
  }

  // Add footer.
  $unsubscribe = url("mailinglist", array("absolute" => TRUE));

  $html .= "__<br />\n";
  $html .= t("You received this message because you are a member of the \"@group\" group on !server",
    array('@group' => $group_title, '!server' => l($server, '', $absolute))) . "<br />\n";
  $html .= t("To unsubscribe from this group, visit !url",
    array('!url' => l($unsubscribe, $unsubscribe))) . "<br />\n";
  $html .= t("To post a new message to this group, email to !email",
    array('!email' =>  l($group_email, 'mailto: ' . $group_email))) . "<br />\n";

  $text .= "--\n";
  $text .= t("You received this message because you are a member of the \"@group\" group on !server",
    array('@group' => $group_title, '!server' => url('', $absolute))) . "\n";
  $text .= t("To unsubscribe from this group, visit !url",
    array('!url' => $unsubscribe)) . "\n";
  $text .= t("To post a new message to this group, email to !email",
    array('!email' => $group_email)) . "\n";

  return array('subject' => $subject, 'text' => $text, 'html' => $html);
}

/**
 * Wrap node body for including in the digest.
 */
function theme_og_mailinglist_digest_node($variables) {
  $node = $variables['node'];

  $user = user_load($node->uid);
  $name = isset($user->realname) ? $user->realname : $user->name;
  $user_link = '<strong>' . l($name, "user/" . $user->uid, array('absolute' => True)) . '</strong>';
  $user_email_link = l($user->mail, 'mailto:' . $user->mail);
  $medium_date = format_date($node->created, 'medium');

  $html = "<div style=\"" . MESSAGE_HEADER . "\">" .
    $user_link . " " . $user_email_link . " " . $medium_date . "</div>\n";
  $text = $name . ' ' . $user->mail . ' ' . $medium_date . ":\n";

  // Prepare node body for viewing.
  $body = _og_mailinglist_remove_quotes($node->body[LANGUAGE_NONE][0]['value']);
  $html .= $body . "<br />\n";
  $text .= drupal_html_to_text($body);

  return array('text' => $text, 'html' => $html);
}

/**
 * Wrap comment body for including in the digest.
 */
function theme_og_mailinglist_digest_comment($variables) {
  $comment = $variables['comment'];
  $node = $variables['node'];
  $user = user_load($comment->uid);
  $name = isset($user->realname) ? $user->realname : $user->name;
  $user_link = '<strong>' . l($name, "user/" . $user->uid, array('absolute' => True)) . '</strong>';
  $user_email_link = l($user->mail, 'mailto:' . $user->mail);
  $medium_date = format_date($comment->created, 'medium');

  $html = '<div style="' . MESSAGE_HEADER . '">' .
    $user_link . ' ' . $user_email_link . ' ' . $medium_date . "</div>\n";
  $text = $name . ' ' . $user->mail . ' ' . $medium_date . ":\n";

  // Filter out quoted sections of emails.
  $body = _og_mailinglist_remove_quotes($comment->comment_body[LANGUAGE_NONE][0]['value']);
  $html .= $body . "<br />\n";

  $text .= drupal_html_to_text($body);

  return array('text' => $text, 'html' => $html);
}

/**
 * Count total new messages for a node since the previous digest.
 */
function og_mailinglist_count_new_messages($message) {
  $count = 0;
  if ($message['status'] === "new") {
    $count++;
  }

  if (isset($message['comments'])) {
    $count += count($message['comments']);
  }

  return $count;
}
