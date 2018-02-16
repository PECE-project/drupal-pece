<?php
/**
 * @file
 * Plugin definition for an authenticated AES-128 encryption method.
 */

use \Defuse\Crypto\Crypto;
use \Defuse\Crypto\Exception as Ex;

$plugin = real_aes_authenticated_aes_encrypt_encryption_methods();

/**
 * Implements hook_encrypt_encryption_methods().
 */
function real_aes_authenticated_aes_encrypt_encryption_methods() {
  return array(
    'title' => t('Authenticated AES (Real AES)'),
    'description' => t('<a href="@authenticated-url">Authenticated encryption</a> based on <a href="@aes-url">AES-128</a> in <a href="@cbc-url">CBC mode</a>. Verifies ciphertext integrity via an Encrypt-then-MAC scheme using <a href="@hmac-url">HMAC-SHA256</a>. See the Real AES README.txt for details.', array(
      '@authenticated-url' => 'https://en.wikipedia.org/wiki/Authenticated_encryption',
      '@aes-url' => 'https://en.wikipedia.org/wiki/Advanced_Encryption_Standard',
      '@cbc-url' => 'https://en.wikipedia.org/wiki/Block_cipher_mode_of_operation#Cipher_Block_Chaining_.28CBC.29',
      '@hmac-url' => 'https://en.wikipedia.org/wiki/Hash-based_message_authentication_code',
    )),
    'encrypt callback' => '_real_aes_encryption_methods_authenticated_aes',
    'dependency callback' => '_real_aes_authenticated_aes_check_requirements',
  );
}

/**
 * Callback for Encrypt implementation: Authenticated AES.
 *
 * This method uses the Real_AES loaded Defuse encryption library.
 * Base64 encoding is used by default, unless disabled by setting
 * 'base64' to FALSE in $options.
 */
function _real_aes_encryption_methods_authenticated_aes($op, $text, $key, $options = array()) {
  $disable_base64 = array_key_exists('base64', $options) && $options['base64'] == FALSE;
  // Check op.
  if ($op == 'decrypt') {

    // Check if we are disabling base64 encoding.
    if (!$disable_base64) {
      $text = base64_decode($text);
    }

    if (real_aes_load_library()) {
      try {
        return Crypto::decrypt($text, $key);
      }
      catch (Ex\CryptoTestFailed $ex) {
        return FALSE;
      }
      catch (Ex\CannotPerformOperation $ex) {
        return FALSE;
      }
    }

  }
  else {
    $processed_text = '';
    if (real_aes_load_library()) {
      // Encrypt.
      try {
        $processed_text = Crypto::encrypt($text, $key);
      }
      catch (Ex\CryptoTestFailed $ex) {
        return FALSE;
      } catch (Ex\CannotPerformOperation $ex) {
        return FALSE;
      }

      // Check if we are disabling base64 encoding.
      if (!$disable_base64) {
        $processed_text = base64_encode($processed_text);
      }
    }
    return $processed_text;
  }
}

/**
 * Callback to check if Real AES is enabled, and the library has been installed.
 */
function _real_aes_authenticated_aes_check_requirements() {
  $errors = array();

  if (!function_exists('real_aes_load_library')) {
    $errors[] = t('Real AES module is not installed.');
  }
  elseif (!real_aes_load_library()) {
    $errors[] = t('PHP-encryption library not installed.');
  }

  return $errors;
}
