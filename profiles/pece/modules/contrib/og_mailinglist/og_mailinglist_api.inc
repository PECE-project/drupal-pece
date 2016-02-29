<?php
/**
 * @file
 *  API functions for OG Mailinglist.
 */

/**
 * Saves new thread subscriptions for members of a group.
 *
 * @param int $gid Group ID
 * @param int $nid Node ID
 */
function og_mailinglist_save_group_thread_subscriptions($gid, $nid) {
  $subscribers = og_mailinglist_get_group_subscriptions($gid);
  // Clean bad email addresses from the array.
  foreach ($subscribers as $uid => $email) {
    if (!valid_email_address($email)) {
      unset($subscribers[$uid]);
    }
  }
  og_mailinglist_save_thread_subscriptions($nid, array_keys($subscribers));
}
/**
 * Returns users who are active email subscribers in a group.
 *
 * @param int $gid
 *   Group id to query for subscriptions.
 * @return array
 *   Array of UIDs and email addresses that are subscribed to this group.
 *   Format: [$uid] => $email
 */
function og_mailinglist_get_group_subscriptions($gid) {
  $query = db_select('og_mailinglist_group_subscription', 's');
  $query->join('users', 'u', 's.uid = u.uid');
  $query->condition('s.nid', $gid);
  $query->condition('s.subscription_type', 'email');
  $query->fields('u', array('uid', 'mail'));
  $emails = $query->execute()->fetchAllKeyed();

  return $emails;
}

/**
 * Get all subscribers of the thread.
 *
 * @param int $nid
 *   Node Id of the thread.
 * @param boolean $email_as_key
 *   Changes the format of returned array.
 * @return array
 *   UIDs and email addresses that are subscribed to this thread.
 *   If $email_as_key is TRUE, then the format is [$email] => ''
 *   else it is [$uid] => $email.
 */
function og_mailinglist_get_thread_subscriptions($nid, $email_as_key = FALSE) {
  $query = db_select('og_mailinglist_thread_subscription', 'ogmt');
  $query->join('users', 'u', 'ogmt.uid = u.uid');
  $query->condition('ogmt.nid', $nid);
  $query->condition('u.status', 1);
  $query->fields('u', array('uid', 'mail'));
  $result = $query->execute();

  $emails = array();
 
  // For easier use later we might want the list with email as array key.
  if ($email_as_key) {
    foreach ($result as $user) {
      $emails[$user->mail] = '';
    }
  }
  else {
    foreach ($result as $user) {
      $emails[$user->uid] = $user->mail;
    }
  }

  return $emails;
}

/**
 * Check if a user is subscribed to a thread.
 *
 * @param int $nid
 *   Node ID of the thread.
 * @param int $uid
 *   User ID.
 * @return int
 *   Return 0 if user is not subscribed to the thread, otherwise
 *   return a positive number, supposedly 1.
 */
function og_mailinglist_check_user_subscribed_to_thread($nid, $uid) {
  $query = db_select('og_mailinglist_thread_subscription', 'ogmt');
  $query->condition('ogmt.nid', $nid);
  $query->condition('ogmt.uid', $uid);
  $query->countQuery();
  return $query->execute()->fetchField();
}

/**
 * Subscribe multiple users to a thread.
 *
 * @param int $nid
 *   Node id for the thread.
 * @param array $uids
 *   Array of User IDs that need to be subscribed to this thread.
 */
function og_mailinglist_save_thread_subscriptions($nid, $uids) {
  static $saved = array();
  foreach ($uids as $uid) {
    // Check that this subscription hasn't already been saved on this page load.
    if (in_array($nid . "_" . $uid, $saved)) {
      continue;
    }
    $saved[] = $nid . "_" . $uid;

    if ($uid != 0) { // Ignore anonymous users.
      $data = array(
        "nid" => $nid,
        "uid" => $uid,
      );

      $result = db_merge('og_mailinglist_thread_subscription')
        ->key(array('nid' => $nid, 'uid' => $uid))
        ->execute();

      if ($result) {
        // Invoke hook
        module_invoke_all('og_mailinglist_save_thread_subscription', $nid, $uid);
      }
    }
  }
}

/**
 * Get subscription user subscription type to the group's mailinglist.
 *
 * @param int $gid
 *   Node ID of the group.
 * @param int $uid
 *   User ID whose subscription type we need.
 * @return string
 *   Subscription type for the given group and user, could be 'email',
 *   'digest' or 'no email'.
 */
function og_mailinglist_get_group_subscription_type($gid, $uid) {
  $query = db_select('og_mailinglist_group_subscription', 'ogms');
  $query->fields('ogms', array('subscription_type'));
  $query->condition('ogms.nid', $gid);
  $query->condition('ogms.uid', $uid);
  return $query->execute()->fetchField();
}

/**
 * Update a user's subscription type for one of their groups.
 *
 * @param int $gid
 *   Node ID of the group.
 * @param int $uid
 *   User ID.
 * @param string $subscription_type
 *   Subscription type to be set, could be 'email', 'digest' or 'no email'.
 */
function og_mailinglist_update_group_subcription_type($gid, $uid, $subscription_type) {
  db_update('og_mailinglist_group_subscription')
    ->fields(array('subscription_type' => $subscription_type))
    ->condition('uid', $uid)
    ->condition('nid', $gid)
    ->execute();
}

/**
 * Save group subscriptions.
 *
 * @param int $gid
 *   Group id.
 * @param array $uids
 *   Array of User IDs to add group subscriptions.
 */
function og_mailinglist_save_group_subscriptions($gid, $uids) {
  $subscription_type = variable_get('og_mailinglist_default_group_subscription_type', 'email');
  foreach ($uids as $uid) {
    db_merge('og_mailinglist_group_subscription')
      ->key(array('nid' => $gid, 'uid' => $uid))
      ->fields(array('subscription_type' => $subscription_type))
      ->execute();
  }
}

/**
 * Delete group subscription for all user IDs in $uids.
 *
 * @param int $gid
 *   Node ID of the group.
 * @param array $uids
 *   Array of User IDs to remove from the group.
 */
function og_mailinglist_delete_group_subscriptions($gid, $uids) {
  db_delete('og_mailinglist_group_subscription')
    ->condition('nid', $gid)
    ->condition('uid', $uids, 'IN')
    ->execute();
  foreach ($uids as $uid) {
    og_mailinglist_delete_group_threads($gid, $uid);
  }
}

/**
 * Unsubscribe a user from all group threads when they leave that group.
 *
 * @param int $gid
 *   Node ID of the group.
 * @param int $uid
 *   User ID.
 */
function og_mailinglist_delete_group_threads($gid, $uid) {
  // Delete threads.  See http://drupal.org/node/1079620
  $subquery = db_select('og_membership', 'o');
  $subquery->addField('o', 'etid');
  $subquery->condition('entity_type', 'node');
  $subquery->condition('gid', $gid);

  return db_delete('og_mailinglist_thread_subscription')
    ->condition('uid', $uid)
    ->condition('nid', $subquery, 'IN')
    ->execute();
}

/**
 * Remove a user from a thread.
 *
 * @param int $nid
 *   Node ID of the thread which subscription is to be removed.
 * @param int $uid
 *   User ID of the user whose subscription is to be removed.
 * @return boolean
 *   Whether the operation succeeded.
 */
function og_mailinglist_delete_thread_subscription($nid, $uid) {
  static $deleted = array();
  // Check that this subscription hasn't already been deleted.
  if (in_array($nid . "_" . $uid, $deleted)) {
    return;
  }
  $deleted[] = $nid . "_" . $uid;

  $result = db_delete('og_mailinglist_thread_subscription')
    ->condition('nid', $nid)
    ->condition('uid', $uid)
    ->execute();

  if ($result) {
    // Invoke hook
    module_invoke_all('og_mailinglist_delete_thread_subscription', $nid, $uid);
  }

  return $result;
}

/**
 * Log when email has been successfully sent.
 *
 * @param string $source
 *   Indicates where the email came from, could be 'web' or 'email'.
 * @param int $nid
 *   Node ID.
 * @param int $cid
 *   Comment ID.
 * @param string $parent_message_id
 *   Parent email's message ID, could be something like <123.431@example.org>
 * @param array $headers
 *   Email headers as used in e.g _og_mailinglist_email_node_email()
 * @return boolean
 *   Indicates whether the logging was successful.
 */
function og_mailinglist_log_email_sent($source, $nid, $cid = 0, $parent_message_id = 0, $headers = array()) {
  $message_id = isset($headers['message-id']) ? $headers['message-id'] : 0;
  $references = isset($headers['references']) ? $headers['references'] : 0;

  if (isset($headers['in-reply-to'])) {
    $in_reply_to = $headers['in-reply-to'];
    $len = strlen($in_reply_to);
    // If references string exceeds 512 characters we will cut it from left
    // to fit the database column.
    if ($len > 512) {
      $start = strpos($in_reply_to, '<', $len - 512);
      $in_reply_to = substr($in_reply_to, $start);
      // If no < found, just drop it entirely.
      if (strlen($in_reply_to) > 512) {
        watchdog('og_mailinglist', 'An email with nid=@nid, cid=@cid came in which had too long and unsplittable reference list: %refs', array('@nid' => $nid, '@cid' => $cid, '%refs' => $in_reply_to), WATCHDOG_ERROR);
        $in_reply_to = 0;
      }
    }
  }
  else {
    $in_reply_to = 0;
  }

  $data = array(
    'nid' => $nid,
    'cid' => $cid,
    'source' => $source,
    'message_id' => $message_id,
    'in_reply_to' => $in_reply_to,
    'references_header' => $references,
    'parent_message_id' => $parent_message_id,
  );
  return drupal_write_record('og_mailinglist_source', $data);
}

/**
 * A helper function to create a PHPMailer object.
 *
 * @return object
 *   PHPMailer object.
 */
function og_mailinglist_create_mailer() {
  if (og_mailinglist_phpmailer_load_library()) {
    // TRUE makes it throw exceptions on errors, which we need to catch.
    $mailer = new PHPMailer(TRUE);
    $mailer->PluginDir = og_mailinglist_get_phpmailer_plugin_dir();
    $mailer->CharSet = 'UTF-8';
    drupal_alter('og_mailinglist_new_phpmailer', $mailer);

    if ($mailer) {
      return $mailer;
    }
  }

  drupal_set_message(t('E-mail cannot be sent. PHPMailer library is missing.'
    . ' See <a href=@link>status report</a> for more information.',
    array('@link' => '/admin/reports/status')), 'error');
}

/**
 * Delete group subscriptions from og_mailinglist_group_subscription.
 *
 * @param int $nid
 *   The node ID.
 */
function og_mailinglist_delete_group($nid) {
  db_delete('og_mailinglist_group_subscription')
    ->condition('nid', $nid)
    ->execute();
}

/**
 * Try to get the parent message nid and cid from the references header.
 *
 * Parent message ID is the message id of the node which starts the thread.
 * References are apparently a more reliable header than in-reply-to
 * http://cr.yp.to/immhf/thread.html
 *
 * @param array $headers
 *  Email headers as used in e.g _og_mailinglist_email_node_email()
 *
 * @return object with properties $object->nid and $object->cid or NULL.
 */
function _og_mailinglist_get_thread_parent($headers) {
  $references = isset($headers['references']) ? $headers['references'] : '';
  $refs = str_replace(array("\r\n", "\n"), "", $references);
  $refs_array = explode(" ", $refs);

  foreach ($refs_array as $reference) {
    if (!empty($reference)) {
      return db_query("SELECT parent_message_id AS message_id, nid, cid
        FROM {og_mailinglist_source}
        WHERE message_id = :message_id",
        array(':message_id' => $reference))
        ->fetchObject();
    }
  }

  // If references don't find anything, try the in-reply-to header.
  if (empty($headers['in-reply-to'])) {
    return;
  }
  return db_query("SELECT parent_message_id ΑS message_id, nid, cid
    FROM {og_mailinglist_source}
    WHERE message_id = :message_id",
    array(':message_id' => $headers['in-reply-to']))
    ->fetchObject();
}

/**
 * Get the email's message ID from the node id.
 *
 * @param int $nid
 *   Node ID to get the message id for.
 * @return string
 *   Email's message ID for that node/thread parent message.
 */
function _og_mailinglist_get_messageid_from_nid($nid) {
  return db_query("SELECT parent_message_id
    FROM {og_mailinglist_source}
    WHERE cid = :cid
    AND nid = :nid",
    array(':cid' => 0, ':nid' => $nid))
    ->fetchField();
}
