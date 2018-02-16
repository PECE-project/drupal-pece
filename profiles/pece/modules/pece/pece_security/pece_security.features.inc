<?php
/**
 * @file
 * pece_security.features.inc
 */

/**
 * Implements hook_encrypt_default_configs().
 */
function pece_security_encrypt_default_configs() {
  $configs = array();

  // Exported configuration: default.
  $configs['default'] = array(
    'name' => 'default',
    'label' => 'Default',
    'description' => 'The default configuration.',
    'method' => 'authenticated_aes',
    'method_settings' => '',
    'provider' => 'drupal_variable',
    'provider_settings' => array(
      'method' => 'base64_decode',
    ),
    'enabled' => 1,
    'created' => 1518650365,
    'changed' => 1518652169,
  );

  return $configs;
}

/**
 * Implements hook_key_default_configs().
 */
function pece_security_key_default_configs() {
  $configs = array();

  // Exported key: real_aes_key.
  $configs['real_aes_key'] = array(
    'id' => 'real_aes_key',
    'label' => 'Real AES Key',
    'description' => 'AES encryption key',
    'key_type' => 'authentication',
    'key_type_settings' => array(),
    'key_provider' => 'config',
    'key_provider_settings' => array(
      'key_value' => 'wt6pxke8i6W1cXhDyHw3Ryb7j2piBLBv',
    ),
    'key_input' => 'text_field',
    'key_input_settings' => array(),
  );

  return $configs;
}
