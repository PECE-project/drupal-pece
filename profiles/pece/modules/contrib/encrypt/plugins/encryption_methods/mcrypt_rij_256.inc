<?php

/**
 * @file
 * Plugin definition for the Mcrypt extension and Rijndael 256 cipher.
 * THIS METHOD IS DEPRECATED AND SHOULD NOT BE USED FOR ENCRYPTION.
 */

// Load the Mcrypt AES (CBC Mode) plugin file, so
// _encrypt_mcrypt_extension_is_present() is available.
module_load_include('inc', 'encrypt', 'plugins/encryption_methods/mcrypt_aes');

$plugin = encrypt_mcrypt_rij_256_encrypt_encryption_methods();

/**
 * Implements MODULE_FILENAME_encrypt_encryption_methods().
 */
function encrypt_mcrypt_rij_256_encrypt_encryption_methods() {
  return array(
    'title' => t('Mcrypt Rijndael 256'),
    'description' => t('Uses PHP\'s Mcrypt extension and Rijndael 256.'),
    'encrypt callback' => '_encrypt_encryption_methods_mcrypt_rij_256',
    'dependency callback' => '_encrypt_mcrypt_extension_is_present',
    'deprecated' => TRUE,
  );
}

/**
 * Callback for Encrypt implementation: Mcrypt Rijndael 256.
 *
 * This method uses PHP's Mcrypt extension and Rijndael 256. Base64 encoding is
 * used by default, unless disabled by setting 'base64' to FALSE in $options.
 */
function _encrypt_encryption_methods_mcrypt_rij_256($op, $text, $key, $options = array()) {
  $processed_text = '';

  // Key cannot be too long for this encryption.
  $key = drupal_substr($key, 0, 32);

  // Define iv cipher.
  $iv_size = mcrypt_get_iv_size(MCRYPT_RIJNDAEL_256, MCRYPT_MODE_ECB);
  $iv = mcrypt_create_iv($iv_size, MCRYPT_RAND);
  $disable_base64 = array_key_exists('base64', $options) && $options['base64'] == FALSE;

  // Check op.
  if ($op == 'decrypt') {
    // Check if we are disabling base64 encoding
    if (!$disable_base64) {
      $text = base64_decode($text);
    }

    // Decrypt text.
    return trim(mcrypt_decrypt(MCRYPT_RIJNDAEL_256, $key, $text, MCRYPT_MODE_ECB, $iv));
  }
  else {
    // Encrypt.
    $processed_text = mcrypt_encrypt(MCRYPT_RIJNDAEL_256, $key, $text, MCRYPT_MODE_ECB, $iv);

    // Check if we are disabling base64 encoding
    if (!$disable_base64) {
      $processed_text = base64_encode($processed_text);
    }

    return $processed_text;
  }
}
