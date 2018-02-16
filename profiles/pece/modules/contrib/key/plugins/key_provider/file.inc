<?php

/**
 * @file
 * Plugin definition for the File key provider.
 */

$plugin = array(
  'label' => t('File'),
  'description' => t('The File key provider allows a key to be stored in a file, preferably outside of the web root.'),
  'storage method' => 'file',
  'key value' => array(
    'accepted' => FALSE,
    'required' => FALSE,
  ),
  'default configuration' => 'key_provider_file_default_configuration',
  'build configuration form' => 'key_provider_file_build_configuration_form',
  'validate configuration form' => 'key_provider_file_validate_configuration_form',
  'get key value' => 'key_provider_file_get_key_value',
);

/**
 * The default plugin configuration.
 *
 * @return array
 *   The default plugin configuration.
 */
function key_provider_file_default_configuration() {
  return array(
    'file_location' => '',
    'base64_encoded' => FALSE,
  );
}

/**
 * Build the plugin configuration form.
 *
 * @return array
 *   The plugin configuration form.
 */
function key_provider_file_build_configuration_form($form, &$form_state) {
  $config = $form_state['storage']['key_config'];
  $plugin_config = $form_state['storage']['key_config']['key_provider_settings'] + key_provider_file_default_configuration();

  $form['file_location'] = array(
    '#type' => 'textfield',
    '#title' => t('File location'),
    '#description' => t('The location of the file in which the key will be stored. The path may be absolute (e.g., %abs), relative to the Drupal directory (e.g., %rel), or defined using a stream wrapper (e.g., %str).',
      array(
        '%abs' => '/etc/keys/foobar.key',
        '%rel' => '../keys/foobar.key',
        '%str' => 'private://keys/foobar.key',
      )
    ),
    '#default_value' => $plugin_config['file_location'],
    '#required' => TRUE,
  );

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
 * Validate callback for the configuration form.
 */
function key_provider_file_validate_configuration_form($form, &$form_state) {
  $key_provider_settings = $form_state['values'];
  $file = $key_provider_settings['file_location'];

  // Does the file exist?
  if (!is_file($file)) {
    form_set_error('file_location', t('There is no file at the specified location.'));
    return;
  }

  // Is the file readable?
  if ((!is_readable($file))) {
    form_set_error('file_location', t('The file at the specified location is not readable.'));
    return;
  }
}

/**
 * Callback function to return a key from a file.
 */
function key_provider_file_get_key_value($config) {
  if (empty($config['key_provider_settings']['file_location'])) {
    return NULL;
  }
  $file = $config['key_provider_settings']['file_location'];

  // Make sure the file exists and is readable.
  if (!is_file($file) || !is_readable($file)) {
    return NULL;
  }

  $key_value = file_get_contents($file);

  // Base64-decode if necessary.
  if (isset($config['key_provider_settings']['base64_encoded']) && $config['key_provider_settings']['base64_encoded']) {
    $key_value = base64_decode($key_value);
  }

  return $key_value;
}
