<?php

/**
 * @file
 * Plugin definition for Mcrypt AES in CBC mode.
 */

$plugin = encrypt_mcrypt_aes_cbc_encrypt_encryption_methods();

/**
 * Implements MODULE_FILENAME_encrypt_encryption_methods().
 */
function encrypt_mcrypt_aes_cbc_encrypt_encryption_methods() {
  return array(
    'title' => t('Mcrypt AES (CBC Mode)'),
    'description' => t('Uses PHP\'s Mcrypt extension and AES in CBC mode. The key MUST be 16, 24, or 32 bytes.'),
    'encrypt callback' => '_encrypt_encryption_methods_mcrypt_aes_cbc',
    'dependency callback' => '_encrypt_mcrypt_extension_is_present',
  );
}

/**
 * Callback for Encrypt implementation: Mcrypt AES in CBC mode.
 *
 * This method uses PHP's Mcrypt extension and AES in CBC mode. Base64
 * encoding is used by default, unless disabled by setting 'base64' to
 * FALSE in $options.
 */
function _encrypt_encryption_methods_mcrypt_aes_cbc($op, $text, $key, $options = array(), $method_settings = array()) {
  $disable_base64 = array_key_exists('base64', $options) && $options['base64'] == FALSE;

  // Open the Mcrypt handle.
  $mcrypt = mcrypt_module_open(MCRYPT_RIJNDAEL_128, '', MCRYPT_MODE_CBC, '');
  $iv_size = mcrypt_enc_get_iv_size($mcrypt);
  $block_size = mcrypt_enc_get_block_size($mcrypt);
  $hash_function = 'sha256';
  $allowed_key_sizes = array(16, 24, 32);
  $key_size = strlen($key);
  $salt_size = 32;
  $hmac_size = 32;

  // If the key is not the right size, report an error.
  if (empty($key) || !in_array($key_size, $allowed_key_sizes)) {
    $t_args = array(
      '@action' => ($op == 'decrypt') ? t('Decryption') : t('Encryption'),
    );
    drupal_set_message(t('@action failed because the key is not the right size.', $t_args), 'error');
    watchdog('encrypt', '@action failed because the key is not the right size.', $t_args, WATCHDOG_CRITICAL);
    throw new Exception(t('@action failed because the key is not the right size.', $t_args));
  }

  // Check op.
  if ($op == 'decrypt') {
    // Base64 decode unless disabled.
    if (!$disable_base64) {
      $text = base64_decode($text);
    }

    // Extract the HMAC.
    $hmac = substr($text, 0, $hmac_size);
    $text = substr($text, $hmac_size);

    // Extract the salt, using half for encryption and
    // half for authentication.
    $salt = substr($text, 0, $salt_size);
    $esalt = substr($salt, 0, strlen($salt) / 2);
    $asalt = substr($salt, strlen($salt) / 2);

    // Generate the authentication subkey.
    $akey = _encrypt_encryption_methods_mcrypt_aes_cbc_hkdf($hash_function, $key, $key_size, $asalt);

    // Calculate the HMAC.
    $calculated_hmac = _encrypt_encryption_methods_mcrypt_aes_cbc_hkdf($hash_function, $text, $hmac_size, $akey);

    // If the HMAC cannot be validated, throw an exception.
    if ($calculated_hmac != $hmac) {
      drupal_set_message(t('Decryption failed because the HMAC could not be validated.'), 'error');
      watchdog('encrypt', 'Decryption failed because the HMAC could not be validated.', array(), WATCHDOG_CRITICAL);
      throw new Exception(t('Decryption failed because the HMAC could not be validated.'));
    }

    $text = substr($text, $salt_size);

    // Get the IV and remove it from the encrypted data.
    $iv = substr($text, 0, $iv_size);
    $text = substr($text, $iv_size);

    // Generate the encryption subkey.
    $ekey = _encrypt_encryption_methods_mcrypt_aes_cbc_hkdf($hash_function, $key, $key_size, $esalt);

    // Initialize for decryption.
    mcrypt_generic_init($mcrypt, $ekey, $iv);

    // Decrypt the data.
    $processed_text = mdecrypt_generic($mcrypt, $text);

    // Terminate decryption.
    mcrypt_generic_deinit($mcrypt);

    // Remove any padding.
    $pad = ord($processed_text[strlen($processed_text) - 1]);
    $processed_text = substr($processed_text, 0, -$pad);

    // Close the Mcrypt handle.
    mcrypt_module_close($mcrypt);
  }
  else {
    // Create a random IV.
    $iv = mcrypt_create_iv($iv_size, MCRYPT_DEV_URANDOM);

    // Generate a random 32-byte salt, using half for encryption and
    // half for authentication.
    $salt = drupal_random_bytes($salt_size);
    $esalt = substr($salt, 0, strlen($salt) / 2);
    $asalt = substr($salt, strlen($salt) / 2);

    // Generate a subkey for encryption.
    $ekey = _encrypt_encryption_methods_mcrypt_aes_cbc_hkdf($hash_function, $key, $key_size, $esalt);

    // Initialize for encryption.
    mcrypt_generic_init($mcrypt, $ekey, $iv);

    // Determine the necessary padding amount.
    $pad = $block_size - (strlen($text) % $block_size);

    // Encrypt the text.
    $processed_text = mcrypt_generic($mcrypt, $text . str_repeat(chr($pad), $pad));

    // Prepend the encrypted data with the salt and IV.
    $processed_text = $salt . $iv . $processed_text;

    // Generate a subkey to use as a salt for the HMAC.
    $akey = _encrypt_encryption_methods_mcrypt_aes_cbc_hkdf($hash_function, $key, $key_size, $asalt);

    // Calculate the HMAC and prepend it to the processed data.
    $hmac = _encrypt_encryption_methods_mcrypt_aes_cbc_hkdf($hash_function, $processed_text, $hmac_size, $akey);
    $processed_text = $hmac . $processed_text;

    // Base64 encode unless disabled.
    if (!$disable_base64) {
      $processed_text = base64_encode($processed_text);
    }

    // Close the Mcrypt handle.
    mcrypt_module_close($mcrypt);
  }

  return $processed_text;
}

/**
 * Generate a hash.
 *
 * @param string $hash_function Hash function
 * @param string $ikm Initial keying material
 * @param int $length Length of the key in bytes
 * @param string $salt Salt
 * @return string $key The generated key
 */
function _encrypt_encryption_methods_mcrypt_aes_cbc_hkdf($hash_function, $ikm, $length, $salt) {
  $key = hash_hmac($hash_function, $ikm, $salt, TRUE);
  $key = substr($key, 0, $length);

  return $key;
}

/**
 * Callback to see if the Mcrypt library is present.
 */
function _encrypt_mcrypt_extension_is_present() {
  $errors = array();

  if (!function_exists('mcrypt_encrypt')) {
    $errors[] = t('Mcrypt library not installed.');
  }

  return $errors;
}
