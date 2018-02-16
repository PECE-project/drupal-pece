<?php

/**
 * @file
 * Plugin definition for the phpseclib encryption method.
 */

$plugin = encrypt_phpseclib_encrypt_encryption_methods();

/**
 * Implements MODULE_FILENAME_encrypt_encryption_methods().
 */
function encrypt_phpseclib_encrypt_encryption_methods() {
  return array(
    'title' => t('PHP Secure Communications Library (phpseclib)'),
    'description' => t('Uses the <a href="http://phpseclib.sourceforge.net/">phpseclib</a> library. This method is only preferable if you cannot install mcrypt.'),
    'encrypt callback' => '_encrypt_encryption_methods_phpseclib',
    'dependency callback' => '_encrypt_phpseclib_dependencies',
  );
}

/**
 * Callback for Encrypt implementation: phpseclib.
 *
 * This method uses the PHP Secure Communications Library and AES-256.
 * Base64 encoding is used by default, unless disabled by setting
 * 'base64' to FALSE in $options.
 */
function _encrypt_encryption_methods_phpseclib($op, $text, $key, $options = array()) {
  $processed_text = '';

  $disable_base64 = array_key_exists('base64', $options) && $options['base64'] == FALSE;

  // If we're decrypting and base64 encoding is not disabled.
  if ($op == 'decrypt' && !$disable_base64) {
    $text = base64_decode($text);
  }

  if ($path = libraries_get_path('phpseclib')) {
    // Include the AES file and instantiate.
    require_once $path . '/Crypt/AES.php';
    $aes = new Crypt_AES();

    $aes->setKey($key);

    $processed_text = $aes->{$op}($text);
  }

  // If we're encrypting and base64 encoding is not disabled.
  if ($op == 'encrypt' && !$disable_base64) {
    $processed_text = base64_encode($processed_text);
  }

  return trim($processed_text);
}

/**
 * Callback to see if the phpseclib library is present.
 */
function _encrypt_phpseclib_dependencies() {
  $errors = array();

  if (!module_exists('libraries')) {
    $errors[] = t('You must download and enable the <a href="http://drupal.org/project/libraries">Libraries API</a> module.');
  }
  if (!file_exists('sites/all/libraries/phpseclib') && !file_exists(conf_path() . '/phpseclib')) {
    $errors[] = t('You must download the <a href="http://phpseclib.sourceforge.net/">phpseclib</a> library and place it in either sites/all/libraries or sites/yourdomain/libraries.');
  }

  return $errors;
}
