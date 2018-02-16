<?php

/**
 * @file
 * Plugin definition for the "none" encryption method.
 */

$plugin = encrypt_none_encrypt_encryption_methods();

/**
 * Implements MODULE_FILENAME_encrypt_encryption_methods().
 */
function encrypt_none_encrypt_encryption_methods() {
  return array(
    'title' => t('None'),
    'description' => t('This uses no encryption.  It is not suggested to use this.'),
    'encrypt callback' => 'encrypt_encryption_methods_none',
  );
}

/**
 * Callback for Encrypt implementation: none.
 */
function encrypt_encryption_methods_none($op, $text, $key, $options = array()) {
  return $text;
}
