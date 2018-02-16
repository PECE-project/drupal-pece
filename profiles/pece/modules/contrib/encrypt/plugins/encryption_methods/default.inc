<?php

/**
 * @file
 * Plugin definition for the Default encryption method.
 * THIS METHOD IS DEPRECATED AND SHOULD NOT BE USED FOR ENCRYPTION.
 */

$plugin = encrypt_default_encrypt_encryption_methods();

/**
 * Implements MODULE_FILENAME_encrypt_encryption_methods().
 */
function encrypt_default_encrypt_encryption_methods() {
  return array(
    'title' => t('Basic'),
    'description' => t('This is the basic default encryption type that does not require any special extensions.'),
    'encrypt callback' => 'encrypt_encryption_methods_basic',
    'deprecated' => TRUE,
  );
}

/**
 * Callback for Encrypt implementation: default.
 *
 * This method uses a simple encryption method of character replacement.
 */
function encrypt_encryption_methods_basic($op, $text, $key, $options = array()) {
  $processed_text = '';

  // Caching length operations to speed up for loops.
  $text_length = strlen($text);
  $key_length = strlen($key);

  // Loop through each character.
  for ($i = 0; $i < $text_length; $i++) {
    $char = substr($text, $i, 1);
    $keychar = substr($key, ($i % $key_length) - 1, 1);
    // Encrypt or decrypt the character.
    if ($op == 'decrypt') {
      $char = chr(ord($char) - ord($keychar));
    }
    else {
      $char = chr(ord($char) + ord($keychar));
    }
    $processed_text .= $char;
  }

  return $processed_text;
}
