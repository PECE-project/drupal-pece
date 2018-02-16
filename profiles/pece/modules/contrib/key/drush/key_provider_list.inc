<?php

/**
 * Get a list of available key providers.
 */
function _drush_key_provider_list() {
  $result = array();

  $storage_method = drush_get_option('storage-method');

  $plugins = key_get_plugins('key_provider', TRUE, TRUE);
  foreach ($plugins as $id => $plugin) {
    if (!isset($storage_method) || $plugin['storage method'] == $storage_method) {
      $row = array();
      $row['id'] = $id;
      $row['description'] = $plugin['description'];

      $result[$id] = $row;
    }
  }

  return $result;
}
