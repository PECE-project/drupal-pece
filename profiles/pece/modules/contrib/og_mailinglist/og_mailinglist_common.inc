<?php
/**
 * @file
 * This file holds functions common to both transport and phpmailer code.
 */

/**
 * Create the mailer object and send out the email.
 *
 * @param $headers
 *   An associative array of header names and values.
 * @param $recipients
 *   Array with 'from', 'to', 'cc' and 'bcc' keys which all may contain another
 *   array of 'email' => 'Display name'
 * @param $body
 *   Plain text version of the body of email. Might contain encoded MIME.
 */
function _og_mailinglist_send_email($headers, $recipients, $body, $html = NULL) {
  $mailer = og_mailinglist_create_mailer();
  $mailer->ClearAddresses();

  try {

  foreach ($recipients as $key => $value) {
    switch ($key) {
      case 'from':
        // Even if array in 'from' contains more values we use only the first.
        $mailer->From = key($value);
        $mailer->FromName = _og_mailinglist_encode(reset($value));
        break;
      case 'to':
        foreach ($value as $email => $name) {
          if ($name)
            $mailer->AddAddress($email, _og_mailinglist_encode($name));
          else
            $mailer->AddAddress($email);
        }
        break;
      case 'cc':
        foreach ($value as $email => $name) {
          if ($name)
            $mailer->AddCC($email, _og_mailinglist_encode($name));
          else
            $mailer->AddCC($email);
        }
        break;
      case 'bcc':
        foreach ($value as $email => $name) {
          $mailer->AddBCC($email);
        }
        break;
    }
  }

  foreach ($headers as $key => $value) {
    if (empty($value)) {
      continue;
    }
    switch (strtolower($key)) {
      case 'date':
        $mailer->MessageDate = $value;
        break;
      case 'message-id':
        $mailer->MessageID = $value;
        break;
      case 'subject':
        $mailer->Subject = _og_mailinglist_encode($value);
        break;
      case 'content-type':
        $mailer->ContentType = $value;

        // Parse out the charset if one is set.
        if (preg_match("/charset=(.*)/s", $value, $matches)) {
          $mailer->CharSet = $matches[1];
        }
        break;
      case 'received':
        // An array of lines of where the email has been.
        // I think it is okay to drop it.
        break;
      default:
        $mailer->AddCustomHeader(capitalize_headers($key, " -") . ':' . $value);
    }
  }

  if ($html) {
    $mailer->Body = trim($html);
    $mailer->isHTML = TRUE;
    $mailer->AltBody = trim($body);
  }
  else {
    $mailer->Body = trim($body);
  }

  $success = $mailer->Send();
  return $success;

  }
  catch (phpmailerException $e) {
    watchdog('og_mailinglist', 'PHPMailer error: !error',
      array('!error' => $e->errorMessage()), WATCHDOG_ERROR);
  }
  catch (Exception $e) {
    watchdog('og_mailinglist', $e->getMessage(), NULL, WATCHDOG_ERROR);
  }
}

/**
 * Compose email headers for outgoing emails.
 */
function _og_mailinglist_list_headers($group_node, $digest = FALSE) {
  $headers = array();

  $group_name = _og_mailinglist_get_group_name($group_node);
  $server = og_mailinglist_server();
  $group_email = $group_name . '@' . $server;

  // Add a reply-to header directed to the group if enabled.
  if (!$digest && variable_get('og_mailinglist_reply_to_group', FALSE)) {
    $headers['reply-to'] = $group_email;
  }

  // Group node URL
  $url = url("node/" . $group_node->nid, array('absolute' => TRUE));

  // Add list headers.
  if (!$digest) {
    $headers['precedence'] = 'list';
  }
  $headers['list-id'] = '<' . $group_email . '>';
  $headers['list-post'] = '<mailto:' . $group_email . '>';
  $headers['list-archive'] = $url;
#  $headers['list-help'] = '<' . ;
#  $headers['list-owner'] = '<' . ;
#  $headers['list-subscribe'] = '<' . ;
#  $headers['list-unsubscribe'] = '<' . ;

  if (!$digest) {
    $headers['x-thread-url'] = $url;
  }
  $headers['x-beenthere'] = $group_email;

  return $headers;
}

/**
 * Compose references list for emails which are in the thread before this email.
 *
 * @param $nid
 *   Integer, node ID.
 * @param $pid
 *   Integer, current comment parent's ID or 0 if first comment in thread.
 * @param $pid
 *   Parent message's email ID, something like <node-3-comment-4@example.com>
 */
function _og_mailinglist_references_headers($nid, $pid, $parent_message_id) {
  $headers = array();

  if ($pid != 0) {
    $result = db_select('og_mailinglist_source', 'ogms')
      ->fields('ogms', array('message_id', 'references_header'))
      ->condition('ogms.nid', $nid)
      ->condition('ogms.cid', $pid)
      ->execute();

    foreach ($result as $data) {
      $headers['in-reply-to'] = $data->message_id;
      $headers['references'] = $data->references_header . " " . $data->message_id;
    }
  }
  elseif (!empty($parent_message_id)) {
    $headers['in-reply-to'] = $parent_message_id;
    $headers['references'] = $parent_message_id;
  }

  return $headers;
}

/**
 * Build group names list for email subject line.
 *
 * @param $group_nodes
 *   An array of group nodes of which the subject is to be compiled.
 * @return
 *   A string containing group names for mail subject line, eg [group][new].
 */
function _og_mailinglist_build_subject($group_nodes) {
  $title_groups = '';
  foreach ($group_nodes as $group_node) {
    $group_name = _og_mailinglist_get_group_name($group_node);
    $title_groups .= '[' . $group_name . ']';
  }
  return $title_groups;
}

/**
 * Returns HTML for possible files links.
 *
 * @param $variables
 *   An array containing 'node' => $node or 'comment' => $comment object.
 * @return
 *   HTML code for files links or an empty string.
 */
function theme_og_mailinglist_attached_files($variables) {
  if (!empty($variables['comment'])) {
    $entity = $variables['comment'];
    $entity_type = 'comment';
  }
  elseif (!empty($variables['node'])) {
    $entity = $variables['node'];
    $entity_type = 'node';
  }
  else {
    return;
  }

  $image_field = variable_get('og_mailinglist_' . $entity_type . '_image_field', '');
  $file_field = variable_get('og_mailinglist_' . $entity_type . '_file_field', '');

  $html = '';

  if ($image_field) {
    $images = field_get_items($entity_type, $entity, $image_field);
    if (!empty($images)) {
      $html .= "<br />\n";
      $html .= "Attached images:<br />\n";
      foreach ($images as $file_info) {
        $file = file_load($file_info['fid']);
        $html .= l($file->filename, file_create_url($file->uri)) . "<br />\n";
      }
    }
  }

  if ($file_field) {
    $files = field_get_items($entity_type, $entity, $file_field);
    if (!empty($files)) {
      $html .= "<br />\n";
      $html .= "Attached files:<br />\n";
      foreach ($files as $file_info) {
        $file = file_load($file_info['fid']);
        $html .= l($file->filename, file_create_url($file->uri)) . "<br />\n";
      }
    }
  }

  return $html;
}

/**
 * Returns HTML for user signature.
 *
 * @param $variables
 *   An array containing 'user' => $user object.
 * @return
 *   HTML code for user signature or an empty string.
 */
function theme_og_mailinglist_user_signature($variables) {
  $user = $variables['user'];
  if (!$user) {
    return;
  }

  if (variable_get('og_mailinglist_add_signatures', 1)) {
    if (!empty($user->signature)) {
      return check_markup($user->signature, $user->signature_format);
    }
  }
  return '';
}

/**
 * Returns HTML for email footer.
 *
 * @param $variables
 *   An array containing 'node' => $node object.
 * @return
 *   HTML code for footer.
 */
function theme_og_mailinglist_mail_footer($variables) {
  $node = $variables['node'];
  if (!$node) {
    return;
  }

  $absolute = array('absolute' => TRUE);
  $full = url("node/" . $node->nid, $absolute);
  $subscriptions = url("mailinglist", $absolute);
  $unsubscribe = url("mailinglist/unsubscribe/" . $node->nid, $absolute);

  $footer = '--<br />'
    . t('Full post: @link', array('@link' => $full))
    . '<br />'
    . t('Manage my subscriptions: @link', array('@link' => $subscriptions))
    . '<br />'
    . t('Stop emails for this post: @link', array('@link' => $unsubscribe))
    . '<br />';
  return $footer;
}

/**
 * Compose an array of sender information.
 */
function _og_mailinglist_sender($user) {
  if ($user->uid == 0) {
    $server = og_mailinglist_server();
    return array('anonymous@' . $server => t('Anonymous'));
  }

  $name = isset($user->realname) ? $user->realname : $user->name;
  return array($user->mail => $name);
}

/**
 * Compose an array of reciever information.
 */
function _og_mailinglist_reciever($group_node) {
  $group_name = _og_mailinglist_get_group_name($group_node);
  $server = og_mailinglist_server();
  $group_email = $group_name . '@' . $server;
  return array($group_email => $group_node->title);
}

/**
 * Compose a string of recipients.
 */
function _og_mailinglist_recipient_string() {
  $out = '';
  foreach (func_get_args() as $email => $name) {
    $out .= $name . ' <' . $email . '>, ';
  }
  return substr($out, 0, -2);
}

/**
 * Encode $value to be used in email header if it contains non-ASCII characters.
 *
 * @param $value
 *   $value is a string which may or may not contain non-ASCII characters.
 *
 * @return
 *   Returns UTF-8 base64 string or plain ASCII string as it suits.
 */
function _og_mailinglist_encode($value) {
  if (!mb_detect_encoding($value, 'ASCII', true)) {
    return "=?UTF-8?B?".base64_encode($value)."?=";
  }
  return $value;
}

/**
 * A helper function to decide which variable to use for server name.
 */
function og_mailinglist_server() {
  $server = variable_get("og_mailinglist_server_string", "");
  if (strlen($server) != 0) {
    return $server;
  }
  if (strlen($_SERVER['SERVER_NAME']) != 0) {
    return $_SERVER['SERVER_NAME'];
  }
  return $_SERVER['HTTP_HOST'];
}
