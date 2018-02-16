<?php

/**
 * @file
 * Plugin definition for the generic Encryption key type.
 */

$plugin = array(
  'label' => t('Encryption'),
  'description' => t('A generic key type to use for an encryption key that does not belong to any other defined key type.'),
  'group' => 'encryption',
  'key value' => array(
    'plugin' => 'text_field',
  ),
  'default configuration' => 'key_type_encryption_default_configuration',
  'build configuration form' => 'key_type_encryption_build_configuration_form',
  'validate configuration form' => 'key_type_encryption_validate_configuration_form',
  'generate key value' => 'key_type_encryption_generate_key_value',
  'validate key value' => 'key_type_encryption_validate_key_value',
);

/**
 * The default plugin configuration.
 *
 * @return array
 *   The default plugin configuration.
 */
function key_type_encryption_default_configuration() {
  return array(
    'key_size' => '256',
  );
}

/**
 * Build the plugin configuration form.
 *
 * @return array
 *   The plugin configuration form.
 */
function key_type_encryption_build_configuration_form($form, &$form_state) {
  $config = $form_state['storage']['key_config'];
  $plugin_config = $config['key_type_settings'] + key_type_encryption_default_configuration();

  // Define the most common key size options.
  $key_size_options = array(
    '128' => 128,
    '256' => 256,
  );

  $key_size = $plugin_config['key_size'];
  $key_size_other_value = '';
  if (!in_array($key_size, $key_size_options)) {
    $key_size_other_value = $key_size;
    $key_size = 'other';
  }

  $form['key_size'] = array(
    '#type' => 'select',
    '#title' => t('Key size'),
    '#description' => t('The size of the key in bits, with 8 bits per byte.'),
    '#options' => $key_size_options + array('other' => t('Other')),
    '#default_value' => $key_size,
    '#required' => TRUE,
  );
  $form['key_size_other_value'] = array(
    '#type' => 'textfield',
    '#title' => t('Key size (other value)'),
    '#title_display' => 'invisible',
    '#description' => t('Enter a custom key size in bits.'),
    '#default_value' => $key_size_other_value,
    '#maxlength'=> 20,
    '#size'=> 20,
    '#states' => array(
      'visible' => array(
        'select[name="key_type_settings[key_size]"]' => array('value' => 'other'),
      ),
      'required' => array(
        'select[name="key_type_settings[key_size]"]' => array('value' => 'other'),
      ),
    ),
  );

  return $form;
}

/**
 * Validate the plugin configuration form.
 */
function key_type_encryption_validate_configuration_form($form, &$form_state) {
  // If 'Other' was selected for the key size, use the custom entered value.
  if ($form_state['values']['key_size'] == 'other') {
    $form_state['values']['key_size'] = $form_state['values']['key_size_other_value'];
  }
  unset($form_state['values']['key_size_other_value']);
}

/**
 * Generate a key value.
 *
 * @param array $config
 *   The key configuration.
 *
 * @return string
 *   A random key.
 */
function key_type_encryption_generate_key_value($config) {
  if (isset($config['key_type_settings']['key_size'])) {
    $bytes = $config['key_type_settings']['key_size'] / 8;
  }
  else {
    // If no key size has been defined, use 32 bytes as the default.
    $bytes = 32;
  }
  $random_key = drupal_random_bytes($bytes);

  return $random_key;
}

/**
 * Validate the key value.
 *
 * @param string $key_value
 *   The key value to validate.
 */
function key_type_encryption_validate_key_value($form, &$form_state, $key_value) {
  if (empty($form_state['values']['key_size'])) {
    return;
  }

  // Validate the key size.
  $bytes = $form_state['values']['key_size'] / 8;
  if (strlen($key_value) != $bytes) {
    form_set_error('key_size', t('The selected key size does not match the actual size of the key.'));
    return;
  }
}
