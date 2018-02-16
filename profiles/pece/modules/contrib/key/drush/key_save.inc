<?php

use Drush\Log\LogLevel;
require_once drupal_get_path('module', 'key') . '/includes/key.admin.inc';

/**
 * Save a key.
 *
 * @param string $id
 *   The ID of the key to save.
 * @param string|null $key_value
 *   A key value to save.
 *
 * @return bool
 *   FALSE if not successful.
 */
function _drush_key_save($id, $key_value = NULL) {
  $values = array();
  $values['id'] = $id;

  // Look for a key with the specified ID. If one exists, and the overwrite
  // option was not specified, set an error and abort.
  $existing_key = key_get_key($id, TRUE);
  $overwrite = drush_get_option('overwrite');
  if ($existing_key && !$overwrite) {
    return drush_set_error('DRUSH_KEY_EXISTS', dt('Key !id exists; specify --overwrite to overwrite.', array('!id' => $values['id'])));
  }

  // Add a warning about overwriting a key.
  if ($existing_key) {
    drush_log(dt('Be extremely careful when overwriting a key! It may result in losing access to a service or making encrypted data unreadable.'), LogLevel::WARNING);
  }

  // Confirm that the key should be saved.
  drush_print(dt('The following key will be saved: !id', array('!id' => $values['id'])));
  if (!drush_confirm(dt('Do you really want to continue?'))) {
    return drush_user_abort();
  }

  // Define the available fields for key configurations,
  // along with their default values.
  $key_config_fields = array(
    'label' => $id,
    'description' => '',
    'key-type' => 'authentication',
    'key-type-settings' => array(),
    'key-provider' => 'config',
    'key-provider-settings' => array(),
    'key-input' => 'none',
    'key-input-settings' => array(),
  );

  // Set any values defined as options.
  foreach (array_keys(key_drush_save_options()) as $option) {
    $value = drush_get_option($option, NULL);
    if (isset($value) && in_array($option, array_keys($key_config_fields))) {
      if (in_array($option, array(
        'key-type-settings',
        'key-provider-settings',
        'key-input-settings',
      ))) {
        $values[str_replace('-', '_', $option)] = drupal_json_decode($value);
      }
      else {
        $values[str_replace('-', '_', $option)] = $value;
      }
    }
  }

  // Use the default for any value that was not defined.
  foreach ($key_config_fields as $key_config_field => $key_config_default) {
    $key_config_field = str_replace('-', '_', $key_config_field);
    if (!isset($values[$key_config_field])) {
      $values[str_replace('-', '_', $key_config_field)] = $key_config_default;
    }
  }

  if (!$existing_key) {
    $existing_key = array();
  }

  // If a key value was specified.
  if (isset($key_value)) {
    $key_provider = key_get_plugin('key_provider', $values['key_provider']);

    // If the key provider supports setting a key value.
    if ($key_provider['key value']['accepted'] && $set_key_value_function = ctools_plugin_get_function($key_provider, 'set key value')) {
      // Create a dummy form state.
      $form_state = array('values' => $values);

      // Set the key value.
      $plugin_form_state = _key_create_plugin_form_state('key_provider', $form_state);
      $set_key_value_function($values, $plugin_form_state, $key_value);
      $form_state['values']['key_provider_settings'] = $plugin_form_state['values'];

      $values = $form_state['values'];
    }
  }

  // Save the key.
  key_save_key($values, $existing_key, FALSE);

  // Load the key to confirm that it was saved.
  $key_check = key_get_key($values['id'], TRUE);

  if (!$key_check) {
    return drush_set_error('DRUSH_KEY_NOT_SAVED', dt('Key !id was not saved.', array('!id' => $values['id'])));
  }

  drush_log(dt('Key !id was saved successfully.', array('!id' => $values['id'])), LogLevel::OK);
}
