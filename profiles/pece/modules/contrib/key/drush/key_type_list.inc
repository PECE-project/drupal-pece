<?php

/**
 * Get a list of available key types.
 */
function _drush_key_type_list() {
  $result = array();

  $group = drush_get_option('group');

  $plugins = key_get_plugins('key_type', TRUE, TRUE);
  foreach ($plugins as $id => $plugin) {
    if (!isset($group) || $plugin['group'] == $group) {
      $row = array();
      $row['id'] = $id;
      $row['description'] = $plugin['description'];

      $result[$id] = $row;
    }
  }

  return $result;
}
