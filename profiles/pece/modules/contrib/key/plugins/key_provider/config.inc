<?php

/**
 * @file
 * Plugin definition for the Configuration key provider.
 */

$plugin = array(
  'label' => t('Configuration'),
  'description' => t('The Configuration key provider stores the key in configuration in the database.'),
  'storage method' => 'config',
  'key value' => array(
    'accepted' => TRUE,
    'required' => FALSE,
  ),
  'default configuration' => 'key_provider_config_default_configuration',
  'build configuration form' => 'key_provider_config_build_configuration_form',
  'get key value' => 'key_provider_config_get_key_value',
  'set key value' => 'key_provider_config_set_key_value',
  'delete key value' => 'key_provider_config_delete_key_value',
  'obscure key value' => 'key_provider_config_obscure_key_value',
);

/**
 * The default plugin configuration.
 *
 * @return array
 *   The default plugin configuration.
 */
function key_provider_config_default_configuration() {
  return array(
    'base64_encoded' => FALSE,
  );
}

/**
 * The settings form.
 *
 * @return array
 *   The settings form.
 */
function key_provider_config_build_configuration_form($form, &$form_state) {
  $config = $form_state['storage']['key_config'];
  $plugin_config = $form_state['storage']['key_config']['key_provider_settings'] + key_provider_config_default_configuration();

  // If this is for an encryption key.
  $key_type = key_get_plugin('key_type', $config['key_type']);
  if ($key_type['group'] == 'encryption') {
    // Add an option to indicate that the value is Base64-encoded.
    $form['base64_encoded'] = array(
      '#type' => 'checkbox',
      '#title' => t('Base64-encoded'),
      '#description' => t('Checking this will store the key with Base64 encoding.'),
      '#default_value' => $plugin_config['base64_encoded'],
    );
  }

  return $form;
}

/**
 * Return a key stored with the configuration.
 *
 * @param array $config
 *   The key configuration for which to retrieve the value.
 *
 * @return string
 *   The key value.
 */
function key_provider_config_get_key_value($config) {
  $key_value = isset($config['key_provider_settings']['key_value']) ? $config['key_provider_settings']['key_value'] : '';

  if (isset($config['key_provider_settings']['base64_encoded']) && $config['key_provider_settings']['base64_encoded'] == TRUE) {
    $key_value = base64_decode($key_value);
  }

  return $key_value;
}

/**
 * Sets the value of a key.
 *
 * @param array $config
 *   The key configuration for which to set the value.
 * @param array $form_state
 *   The form state.
 * @param string $key_value
 *   The key value.
 *
 * @return bool
 *   TRUE if successful, FALSE if unsuccessful.
 */
function key_provider_config_set_key_value($config, &$form_state, $key_value) {
  if (isset($config['key_provider_settings']['base64_encoded']) && $config['key_provider_settings']['base64_encoded'] == TRUE) {
    $key_value = base64_encode($key_value);
  }

  if ($form_state['values']['key_value'] = $key_value) {
    return TRUE;
  }
  else {
    return FALSE;
  }
}

/**
 * Deletes the value of a key.
 *
 * @param array $config
 *   The key configuration whose value will be deleted.
 *
 * @return bool
 *   TRUE if successful, FALSE if unsuccessful.
 */
function key_provider_config_delete_key_value($config) {
  // Nothing needs to be done, since the value will have been deleted
  // with the key configuration.
  return TRUE;
}

/**
 * Obscures the value of a key.
 *
 * @param string $key_value
 *   The key value to obscure.
 * @param array $options
 *   Options to use when obscuring the value.
 *
 * @return string
 *   The obscured key value.
 */
function key_provider_config_obscure_key_value($key_value, $options = array()) {
  // Key values are not obscured when this provider is used.
  return $key_value;
}
