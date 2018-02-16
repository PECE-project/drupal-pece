<?php

/**
 * @file
 * This file holds the ffunctions necessary to encrypt and decrypt
 *
 * @ingroup encrypt
 */

/**
 * Private internal function to Encrypt and Decrypt text.
 *
 * @param string $op
 *   Whether to encrypt or decrypt.
 *   - "encrypt": Encrypt text
 *   - "decrypt": Decrypt text
 *
 * @param string $text
 *   Text to encrypt
 *
 * @param array $options
 *   Array of options for encryption
 *
 * @param mixed $method
 *   String name of method to use.  Uses setting
 *   default if NULL
 *
 * @param mixed $key_provider
 *   The key provider used to fetch the encryption key. Uses default if NULL.
 *
 * @param string $config
 *   A configuration to use. Uses the default configuration if NULL.
 *
 * @return string
 *   Depends on the value of $op
 *   - "encrypt": A serialized array representing the encrypted text, method,
 *     and key provider.
 *   - "decrypt": The decrypted text.
 */
function _encrypt_decrypt($op = 'encrypt', $text = '', $options = array(), $method = NULL, $key_provider = NULL, $config = NULL) {
  $encryption_array = array();
  $processed = '';

  // Check text.
  if ($text === '') {
    return $processed;
  }

  // Check op.
  if ($op !== 'encrypt') {
    $op = 'decrypt';
  }

  if ($op == 'decrypt') {
    // The text may not actually be serialized, so suppress the warning.
    $encryption_array = @unserialize($text);

    $method = isset($encryption_array['method']) ? $encryption_array['method'] : $method;
    $key_provider = isset($encryption_array['key_provider']) ? $encryption_array['key_provider'] : $key_provider;
    $text = isset($encryption_array['text']) ? $encryption_array['text'] : $text;
    $options = isset($encryption_array['options']) ? $encryption_array['options'] + $options : $options;
    $method_settings = isset($encryption_array['method_settings']) ? $encryption_array['method_settings'] : '';
    $provider_settings = isset($encryption_array['provider_settings']) ? $encryption_array['provider_settings'] : '';
  }

  // If the configuration was specified, load it. Otherwise, load the
  // default configuration.
  if ($config) {
    $config = encrypt_get_config($config);
  }
  else {
    $config = encrypt_get_default_config($config);
  }

  // If the method was not specified, use the method
  // from the configuration.
  if (empty($method)) {
    $method = $config['method'];
  }

  // If the method settings were not specified, use the method settings
  // from the configuration.
  if (empty($method_settings)) {
    $method_settings = $config['method_settings'];
  }

  // If the provider was not specified, use the provider
  // from the configuration.
  if (empty($key_provider)) {
    $key_provider = $config['provider'];
  }

  // If the provider settings were not specified, use the provider settings
  // from the configuration.
  if (empty($provider_settings)) {
    $provider_settings = $config['provider_settings'];
  }

  // Get the encryption key from the default key provider.
  $key = encrypt_get_key_from_key_provider($key_provider, $provider_settings, $config);
  if(!$key){
    drupal_set_message(t('The key from %key_provider could not be retrieved.', array('%key_provider' => $key_provider)), 'error');
    throw new Exception('Key not found');
  }

  // Call callback function for encryption and decryption.
  $encryption_method = encrypt_get_encryption_method($method);
  $function = ctools_plugin_get_function($encryption_method, 'encrypt callback');
  $processed = call_user_func($function, $op, $text, $key, $options, $config);

  // Check for returned value.
  if (!empty($processed) && $op == 'encrypt') {
    $encryption_array = array(
      'text' => $processed,
      'method' => $method,
      'key_provider' => $key_provider,
      'options' => $options,
      'method_settings' => $method_settings,
      'provider_settings' => $provider_settings,
    );
    // Serialize array.
    $processed = serialize($encryption_array);
  }

  return $processed;
}
