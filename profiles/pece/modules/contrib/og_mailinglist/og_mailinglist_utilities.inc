<?php
/**
 * @file
 * OG Mailinglist utilities.
 */

/**
 * Gets all subscribers of node.
 *
 * @param $node
 *  Node object.
 *
 * @param boolean $new_node
 *  If TRUE, then new node's subscriptions are saved to og_mailinglist_thread_subscription.
 *  If FALSE, it just loads subscriptions.
 */
function _og_mailinglist_get_subscribers($node, $group_node, $new_node = FALSE) {
  // If new node, save subscriptions for new node to og_mailinglist_thread_subscription.
  // If new comment, just load subscriptions.
  if ($new_node) {
    og_mailinglist_save_group_thread_subscriptions($group_node->nid, $node->nid);
  }

  $subscribers = og_mailinglist_get_thread_subscriptions($node->nid, TRUE);

  $debug_emails = variable_get('og_mailinglist_test_email_addresses', '');
  if (!empty($debug_emails)) {
    $emails = explode(",", $debug_emails);
    foreach ($emails as $email) {
      $subscribers[trim($email)] = '';
    }
  }

  return $subscribers;
}

/**
 * Build HTML using default input filter.
 */
function og_mailinglist_prepare_web_content($text) {
  return check_markup($text);
}

function _og_mailinglist_email_already_sent($nid, $cid = 0) {
  return (db_query("SELECT nid
               FROM {og_mailinglist_source}
               WHERE nid = :nid
               AND cid = :cid", array(':nid' => $nid, ':cid' => $cid))->fetchField());
}

function dd_log($data, $label = "") {
  $my_file = "/tmp/drupal_log";
  $fh = fopen($my_file, 'a') or die("can't open file");
  $string_data = print_r($data, TRUE);
  if (!empty($label)) {
    $string_data = $label . ": " . $string_data;
  }

  fwrite($fh, $string_data . "\n");
  fclose($fh);
}

function write_string_to_file($data, $name = "lsjdf") {
  $my_file = "/tmp/" . $name;
  $fh = fopen($my_file, 'w') or die("can't open file");
  $string_data = print_r($data, TRUE);
  fwrite($fh, $string_data . "\n");
  fclose($fh);
}

/**
 * Make a recursive copy of an array.
 *
 * @param array $array_source
 * @return array    copy of source array
 */
function array_copy($array_source) {
  // check if input is really an array
  if (!is_array($array_source)) {
    throw new Exception("Input is not an Array");
  }

  // initialize return array
  $array_return = array();

  // get array keys
  $array_keys = array_keys($array_source);
  // get array values
  $array_values = array_values($array_source);

  // loop through array and assign keys+values to new return array
  for ($x = 0; $x < count($array_keys); $x++) {
    // clone if object
    if (is_object($array_values[$x])) {
      $array_return[$array_keys[$x]] = clone $array_values[$x];
      // recursively add array
    }
    elseif (is_array($array_values[$x])) {
      $array_return[$array_keys[$x]] = array_copy($array_values[$x]);
      // assign just a plain scalar value
    }
    else {
      $array_return[$array_keys[$x]] = $array_values[$x];
    }
  }

  return $array_return;
}

/**
 * Load the parent group node of a node.
 *
 * @param $node
 *  The node or nid of the node to load group ids for.
 */
function og_mailinglist_get_groups($node) {
  // If node is already loaded, it contains group information.
  if (is_object($node)) {
    $groups = array();
    if (isset($node->og_group_ref[LANGUAGE_NONE])) {
      foreach ($node->og_group_ref[LANGUAGE_NONE] as $item) {
        $groups[] = $item['target_id'];
      }
    }
    // If node is group itself, we add it's id as well.
    if (isset($node->group_group)) {
      $groups[] = $node->nid;
    }
    return $groups;
  }
  // $node is probably a nid, let's use og's fancy function, it uses caching.
  $groups = og_get_entity_groups('node', $node);
  if (!empty($groups['node'])) {
    return $groups['node'];
  }
  return NULL;
}

/**
 * Capitalize all words
 * @param string Data to capitalize
 * @param string Word delimiters
 * @return string Capitalized words
 * Function taken from http://www.php.net/manual/en/function.ucwords.php#95325
 */
function capitalize_headers($words, $character_list = NULL) {
  // Use ucwords if no delimiters are given
  if (!isset($character_list)) {
    return ucwords($words);
  }

  // Go through all characters
  $capitalize_next = TRUE;

  for ($i = 0, $max = strlen($words); $i < $max; $i++) {
    if (strpos($character_list, $words[$i]) !== FALSE) {
      $capitalize_next = TRUE;
    }
    elseif ($capitalize_next) {
      $capitalize_next = FALSE;
      $words[$i] = strtoupper($words[$i]);
    }
  }

  return $words;
}

/**
 * Loads PHPMailer library if it's not loaded already.
 *
 * @return
 *  TRUE if the PHPMailer library is loaded, FALSE otherwise.
 */
function og_mailinglist_phpmailer_load_library() {
  if (!class_exists('PHPMailer')) {
    // First, try using libraries module.
    if (module_exists('libraries')) {
      // Let's see if PHPMailer is really available from libraries.
      $phpmailer_library = './' . libraries_get_path('phpmailer') . '/class.phpmailer.php';
      if (file_exists($phpmailer_library)) {
        include_once $phpmailer_library;
      }
    }
    // If PHPMailer is not already loaded, then try from module subdirectory.
    if (!class_exists('PHPMailer')) {
      $phpmailer_library = './' . drupal_get_path('module', 'og_mailinglist') . '/phpmailer/class.phpmailer.php';
      if (file_exists($phpmailer_library)) {
        include_once $phpmailer_library;
      }
    }
  }
  // Tell the caller if PHPMailer class exists.
  return class_exists('PHPMailer');
}

/**
 * Gets the directory in which PHPMailer is stored (for plugins)
 *
 * @return
 *  TRUE if the PHPMailer library is loaded, FALSE otherwise.
 */
function og_mailinglist_get_phpmailer_plugin_dir() {
  // First, try using libraries module.
  if (module_exists('libraries')) {
    // Let's see if PHPMailer is available from libraries.
    return './' . libraries_get_path('phpmailer') . '/';
  }
  return './' . drupal_get_path('module', 'og_mailinglist') . '/phpmailer/';
}

/**
 * Load the mimeDecode library.
 */
function og_mailinglist_mimeDecode_load_library() {
  // Check the standard include path for the file first
  if (!class_exists('Mail_mimeDecode')) {
    // With @ we surpress the Warning in case the file isn't found.
    @include_once('Mail/mimeDecode.php');
  }
  // Next we'll try grabbing the file from a few default pear install locations.
  if (!class_exists('Mail_mimeDecode')) {
    @include_once '/usr/share/php/Mail/mimeDecode.php';
  }
  if (!class_exists('Mail_mimeDecode')) {
    @include_once '/usr/share/pear/Mail/mimeDecode.php';
  }
  // If that didn't work, let's try using the libraries module.
  if (!class_exists('Mail_mimeDecode') and module_exists('libraries')) {
    // Let's see if PHPMailer is really available from libraries.
    $mail_mimedecode_library = './' . libraries_get_path('mimeDecode') . '/mimeDecode.php';
    @include_once $mail_mimedecode_library;
  }
  // If Mail_mimeDecode is still not loaded, then try from module subdirectory.
  if (!class_exists('Mail_mimeDecode')) {
    $mail_mimedecode_library = './' . drupal_get_path('module', 'og_mailinglist') . '/mimeDecode/mimeDecode.php';
    @include_once $mail_mimedecode_library;
  }
  // Tell the caller if Mail_mimeDecode class exists.
  return class_exists('Mail_mimeDecode');
}

/*
 * Get group name from group object.
 *
 * $group_node Group node object.
 */
function _og_mailinglist_get_group_name($group_node) {
  $fields = field_get_items('node', $group_node, OG_MAILINGLIST_EMAIL_FIELD);
  $group_name = $fields[0]['value'];
  // TODO: A hack to ensure this really is a name. Sometimes for viewing it
  // gets passed through og_mailinglist_field_formatter_prepare_view()
  if (strpos($group_name, '@') !== FALSE)  {
    $group_name = substr($group_name, 0, strpos($group_name, '@'));
  }
  return $group_name;
}
