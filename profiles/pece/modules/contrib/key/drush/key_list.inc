<?php

/**
 * Get a list of available keys.
 */
function _drush_key_list() {
  $result = array();

  $keys = key_get_keys(TRUE);
  $key_types = key_get_plugins_as_options('key_type', TRUE, TRUE);
  $key_providers = key_get_plugins_as_options('key_provider', TRUE, TRUE);

  // Filter by key type, if specified.
  if (drush_get_option('key-type')) {
    $key_type_filter = _convert_csv_to_array(drush_get_option('key-type'));
    foreach ($keys as $id => $key) {
      if (!in_array($key['key_type'], $key_type_filter)) {
        unset($keys[$id]);
      }
    }
  }

  // Filter by key provider, if specified.
  if (drush_get_option('key-provider')) {
    $key_provider_filter = _convert_csv_to_array(drush_get_option('key-provider'));
    foreach ($keys as $id => $key) {
      if (!in_array($key['key_provider'], $key_provider_filter)) {
        unset($keys[$id]);
      }
    }
  }

  foreach ($keys as $id => $key) {
    $row = array();
    $row['id'] = $id;
    $row['label'] = $key['label'];
    $row['key_type'] = $key_types[$key['key_type']];
    $row['key_provider'] = $key_providers[$key['key_provider']];
    $result[$id] = $row;
  }

  return $result;
}
