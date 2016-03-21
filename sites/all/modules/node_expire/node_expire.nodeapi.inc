<?php

/**
 * @file
 * Node API integration.
 */

/**
 * Implements hook_node_load().
 */
function _node_expire_node_load($nodes, $types) {
  // Only deal with node types that have the Node expire feature enabled.
  $ntypes = variable_get('node_expire_ntypes', array());
  $node_expire_enabled = array();

  // Check if node_expire are enabled for each node.
  // If node_expires are not enabled, do nothing.
  foreach ($nodes as $node) {
    // Store whether node_expires are enabled for this node.
    if ((isset($ntypes[$node->type])) and ($ntypes = $ntypes[$node->type])) {
      $node_expire_enabled[] = $node->nid;
    }
  }

  // For nodes with node_expire enabled, fetch information from the database.
  if (!empty($node_expire_enabled)) {
    $handle_content_expiry = variable_get('node_expire_handle_content_expiry', 2);
    $result = db_query(
      'SELECT n.nid, n.type, expire, expired, lastnotify
       FROM {node} n
         INNER JOIN {node_expire} ne
           ON n.nid = ne.nid
       WHERE n.nid
         IN (:node_expire_enabled)',
      array(':node_expire_enabled' => $node_expire_enabled));
    foreach ($result as $record) {
      if ($handle_content_expiry == 0) {
        $nodes[$record->nid]->expire = $record->expire;
      }
      else {
        $ntype = isset($ntypes[$record->type]) ? $ntypes[$record->type] : NULL;
        $nodes[$record->nid]->expire = _node_expire_date_db_to_str($record->expire, $ntype);
      }
      $nodes[$record->nid]->expired = $record->expired;
      $nodes[$record->nid]->lastnotify = $record->lastnotify;
    }
  }
}

/**
 * Implements hook_node_prepare().
 */
function _node_expire_node_prepare(&$ntype, $node) {
  // To prevent default value 1969-12-31 check also $ntypes['default'].
  if (!isset($node->expire) && $ntype['default']) {
    $node->expire = format_date(strtotime($ntype['default']), 'custom', NODE_EXPIRE_FORMAT);
  }
  // This gives a way to users without edit exipration permission
  // to update nodes with default expiration.
  if (isset($node->expire) && !user_access('edit node expire')) {
    $node->expire = format_date(strtotime($ntype['default']), 'custom', NODE_EXPIRE_FORMAT);
  }
}

/**
 * Implements hook_node_validate().
 */
function _node_expire_node_validate(&$ntype, $node) {
  $handle_content_expiry = variable_get('node_expire_handle_content_expiry', 2);
  if ($handle_content_expiry != 0) {
    if (!isset($ntype['enabled']) || !$ntype['enabled']) {
      return;
    }
  }

  // The only restriction we have is that the node can't expire in the past.
  if ($node->expire == '') {
    if (!empty($ntype['required']) && $ntype['default']) {
      form_set_error('expire_date', t('You must choose an expiration date.'));
    }
  }
  elseif (!$expire = strtotime($node->expire) or $expire <= 0) {
    form_set_error('expire_date', t('You have to specify a valid expiration date.'));
  }
  elseif (variable_get('node_expire_past_date_allowed', 0) == 0 && $expire <= REQUEST_TIME) {
    form_set_error('expire_date', t("You can't expire a node in the past!"));
  }
  elseif (!empty($ntype['max']) and $expire > strtotime($ntype['max'], $node->created)) {
    form_set_error('expire_date', t('It must expire before %date.',
    array(
      '%date' => format_date(strtotime($ntype['max'], $node->created), 'custom', NODE_EXPIRE_FORMAT),
    )));
  }
}

/**
 * Implements hook_node_update() and hook_node_insert().
 */
function _node_expire_node_update_insert(&$ntype, $node) {
  $handle_content_expiry = variable_get('node_expire_handle_content_expiry', 2);
  if ($handle_content_expiry == 0) {
    // Old (legacy) style of processing.
    // Has the expiration been removed, or does it exist?
    if (isset($node->expire)) {
      db_delete('node_expire')
        ->condition('nid', $node->nid)
        ->execute();
      // Should we create a new record?
      if ($node->expire) {
        if (strtotime($node->expire)) {
          $node->expire = strtotime($node->expire);
        }
        $node->expired = FALSE;
        drupal_write_record('node_expire', $node);
      }
    }
  }
  else {
    if (!isset($ntype['enabled']) || !$ntype['enabled']) {
      return;
    }

    // Create a proper $node_expire stdClass.
    $node_expire = new stdClass();
    $node_expire->nid = $node->nid;

    // For compatibility with Node Clone module.
    // Set default $node->expire value if it is not set.
    if (!isset($node->expire)) {
      _node_expire_node_prepare($ntype, $node);
    }

    // Expire.
    $date_expire = _node_expire_date_str_to_db($node->expire, $ntype);
    $node_expire->expire = $date_expire;

    // Lastnotify.
    if (isset($node->lastnotify)) {
      $node_expire->lastnotify = $node->lastnotify;
    }
    else {
      // Default value.
      $node_expire->lastnotify = 0;
    }

    // Expired.
    if (isset($node->expired)) {
      $node_expire->new_record = 0;
      $node_expire->expired = $node->expired;
      if ($node_expire->expire >= NODE_EXPIRE_NO_EXPIRE) {
        // No expiry for this node.
        $node_expire->expired = 0;
      }
    }
    elseif (isset($node->original->expired)) {
      // For VBO (Views Bulk Operations) compatibility.
      // With VBO it is necessary to get all Node expire information
      // from $node->original instead of $node.
      $node_expire->new_record = 0;
      $node_expire->expired = $node->original->expired;
      // Also get other Node expire values.
      // Expire.
      $date_expire
        = _node_expire_date_str_to_db($node->original->expire, $ntype);
      $node_expire->expire = $date_expire;
      // Lastnotify.
      if (isset($node->original->lastnotify)) {
        $node_expire->lastnotify = $node->original->lastnotify;
      }
      else {
        // Default value.
        $node_expire->lastnotify = 0;
      }

      if ($node_expire->expire >= NODE_EXPIRE_NO_EXPIRE) {
        // No expiry for this node.
        $node_expire->expired = 0;
      }
    }
    else {
      // No record in the database yet.
      $node_expire->new_record = 1;
      // Default value.
      $node_expire->expired = 0;
    }

    // Write the record.
    _node_expire_write_record($node_expire, $node->nid);
  }
}

/**
 * Writes node_expire record.
 */
function _node_expire_write_record($node_expire, $nid) {
  // Check, is it insert or update.
  $cnt = db_query(
    'SELECT count(nid)
     FROM {node_expire} ne
     WHERE ne.nid = :nid',
    array(':nid' => $nid))->fetchField();

  // Write the record.
  if ($cnt == 0) {
    // Insert.
    drupal_write_record('node_expire', $node_expire);
  }
  else {
    // Update.
    drupal_write_record('node_expire', $node_expire, 'nid');
  }
}

/**
 * Implements hook_node_delete().
 */
function _node_expire_node_delete(&$ntype, $node) {
  db_delete('node_expire')
    ->condition('nid', $node->nid)
    ->execute();
}


/**
 * Implements hook_form_alter().
 *
 * Adds expiration options to the node entry forms
 */
function _node_expire_form_alter_nodeform(&$ntype, &$form, &$form_state, $form_id) {
  // Check if the Node expire feature is enabled for the node type.
  $node = isset($form['#node']) ? $form['#node'] : NULL;

  $handle_content_expiry = variable_get('node_expire_handle_content_expiry', 2);
  if ($handle_content_expiry != 0) {
    if (empty($ntype['enabled'])) {
      return;
    }
    // Replace not set to default string.
    if (!isset($node->expire)) {
      // $ntype = isset($ntypes[$node->type]) ? $ntypes[$node->type] : NULL;
      $node->expire = _node_expire_date_db_to_str('', $ntype);
    }
  }
  else {
    // Replace not set to empty string.
    if (!isset($node->expire)) {
      $node->expire = '';
    }
    // Convert the timestamp into a human readable date - legacy branch.
    if (is_numeric($node->expire)) {
      $node->expire = format_date($node->expire, 'custom', NODE_EXPIRE_FORMAT);
    }
  }

  // This supports node to never expire.
  if (empty($ntype['default']) && empty($node->expire)) {
    $ntype['required'] = FALSE;
  }
  if (user_access('edit node expire')) {
    if (_node_expire_get_date_entry_elements()) {
      // Date popups.
      $expire_field = array(
        '#title' => t('Expiration date'),
        '#description' => t('Time date to consider the node expired. Format: %time (YYYY-MM-DD).',
          array(
            '%time' => format_date(REQUEST_TIME, 'custom', NODE_EXPIRE_FORMAT),
          )
        ),
        '#type' => 'date_popup',
        '#date_format' => NODE_EXPIRE_FORMAT,
        '#required' => $ntype['required'],
        '#default_value' => $node->expire,
      );
    }
    else {
      // Text fields.
      $expire_field = array(
        '#title' => t('Expiration date'),
        '#description' => t('Time date to consider the node expired. Format: %time (YYYY-MM-DD).',
          array(
            '%time' => format_date(REQUEST_TIME, 'custom', NODE_EXPIRE_FORMAT),
          )
        ),
        '#type' => 'textfield',
        '#maxlength' => 25,
        '#required' => $ntype['required'],
        '#default_value' => $node->expire,
      );
    }
  }
  else {
    $expire_field = array(
      '#type' => 'value',
      '#value' => $node->expire,
    );
  }

  // If we use hidden value, do not create fieldset.
  if ($expire_field['#type'] == 'value') {
    $form['options1'] = array();
    $form['options1']['expire'] = &$expire_field;
  }
  // If the form doesn't have the publishing options we'll create our own.
  elseif (!$form['options']['#access']) {
    $form['options1'] = array(
      '#type' => 'fieldset',
      '#title' => t('Publishing options'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
      '#weight' => 95,
    );
    $form['options1']['expire'] = &$expire_field;
  }
  else {
    $form['options']['expire'] = &$expire_field;
  }

  if (isset($node->expired)) {
    $form['node_expire'] = array(
      '#type' => 'value',
      '#value' => TRUE,
    );
  }
}

/**
 * Convert date string to timestamp int.
 *
 * @param string $date_in
 *   String date representation for UI:
 *   not set, non-date string, date string.
 * @param object $ntype
 *   Node expire configuration for particular node type.
 *
 * @return int
 *   Timestamp (int) date representation for DB:
 *   timestamp int, NODE_EXPIRE_NO_EXPIRE as a special value.
 */
function _node_expire_date_str_to_db($date_in, $ntype) {
  if (!isset($date_in)) {
    $date_out = NODE_EXPIRE_NO_EXPIRE;
    return $date_out;
  }

  $date_inner = trim($date_in);
  if (!strtotime($date_inner)) {
    // Make a valid date string.
    if (isset($ntype) &&
      !empty($ntype->default) &&
      (strtotime($ntype->default))) {
      $date_inner = $ntype->default;
    }
    else {
      $date_out = NODE_EXPIRE_NO_EXPIRE;
      return $date_out;
    }
  }

  $date_out = strtotime($date_inner);

  return $date_out;
}

/**
 * Convert timestamp int to date string.
 *
 * @param int $date_in
 *   Timestamp (int) date representation for DB:
 *   not set, timestamp int.
 * @param object $ntype
 *   Node expire configuration for particular node type.
 *
 * @return string
 *   String date representation for UI:
 *   date string or ''.
 */
function _node_expire_date_db_to_str($date_in, $ntype) {
  $date_inner = $date_in;
  if ((empty($date_inner)) ||
    (!(_node_expire_is_valid_time_stamp($date_inner)))) {
    if (isset($ntype) &&
      !empty($ntype->default) &&
      (strtotime($ntype->default))) {
      $date_out = $ntype->default;
    }
    else {
      $date_out = '';
    }
  }
  elseif ($date_inner >= NODE_EXPIRE_NO_EXPIRE) {
    $date_out = '';
  }
  else {
    $date_out = date(NODE_EXPIRE_FORMAT, $date_inner);
  }
  return $date_out;
}

/**
 * Checks timestamp to be valid.
 */
function _node_expire_is_valid_time_stamp($timestamp) {
  return ((string) (int) $timestamp === $timestamp)
    && ($timestamp <= PHP_INT_MAX)
    && ($timestamp >= ~PHP_INT_MAX);
}
