<?php

/**
 * @file
 * Function and hooks provided by the aes API.
 */

/**
 * @defgroup AES Encrypt module
 * @{
 * API Functions
 * Here's a brief and simple run-through of the functions which might be
 * interesting from a developers point of view. Most (see exceptions below)
 * of the functions are implementation independant, so behaviour should be
 * consistent regardless of which implementation (mcrypt or phpseclib) is used.
 *
 * Implementation independence exceptions:
 * 1. aes_make_iv is mute when using phpseclib since that implementation handle
 * its own IV internally.
 * 2. The $custom_cipher and $custom_iv arguments to aes_encrypt and aes_decrypt
 * are ignored when using phpseclib, since that implementation doesn't support
 * changing these values. Passing these arguments as anything else than null
 * will generate warnings in the watchdog when using phpseclib.
 *
 */

/**
 * Encrypts a string.
 * @code
 * // Default usage.
 * $encrypted_data = aes_encrypt("mydata");
 * // Extended usage.
 * $encrypt_params = array(
 *   'string' => 'mydata',
 *   'base64encode' => $base64encode,
 *   'custom_key' => $key,
 *   'custom_cipher' => $cipher,
 *   'custom_iv' => $iv,
 *   'custom_implementation' => $implementation,
 * );
 * $encrypted_data = call_user_func_array('aes_encrypt', $encrypt_params);
 * @endcode
 *
 * @param string $string
 *   The string to encrypt.
 * @param bool $base64encode
 *   Whether to return the string base64 encoded (recommended for database
 *   insertion).
 * @param string $custom_key
 *   Use this as the key rather than the stored one for the operation.
 * @param string $custom_cipher
 *   Use this cipher rather than the default one. (only with Mcrypt - ignored
 *   with phpseclib)
 * @param string $custom_iv
 *   Use this initialization vector instead of the default one.
 * @param string $custom_implementation
 *   Can be "phpseclib" or "mcrypt". Warning: Does not check if the requested
 *   implementation actually exists.
 *
 * @return bool|string
 *   The encrypted string on success, FALSE on error.
 */
//function aes_encrypt($string, $base64encode = TRUE, $custom_key = NULL, $custom_cipher = NULL, $custom_iv = NULL, $custom_implementation = NULL) {}

/**
 * Decrypts a string of encrypted data.
 * @code
 * // Default usage.
 * $decrypted_to_plain_text = aes_decrypt($encrypted_data);
 * // Extended usage.
 * $decrypt_params = array(
 *   'string' => $encrypted_data,
 *   'base64encoded' => $base64encoded,
 *   'custom_key' => aes_get_key(),
 *   'custom_cipher' => variable_get("aes_cipher", "rijndael-128"),
 *   'custom_iv' => variable_get("aes_encryption_iv", ""),
 *   'custom_implementation' => variable_get("aes_implementation", "mcrypt"),
 * );
 * $decrypted_to_plain_text = call_user_func_array('aes_decrypt', $decrypt_params);
 * @endcode
 *
 * @param string $string
 *   The string to decrypt.
 * @param bool $base64encoded
 *   Whether this encrypted string is base64 encoded or not.
 * @param string $custom_key
 *   Use this as the key rather than the stored one for the operation.
 * @param string $custom_cipher
 *   Use this cipher rather than the default one. (only with Mcrypt - ignored
 *   with phpseclib)
 * @param string $custom_iv
 *   Use this initialization vector instead of the default one.
 * @param string $custom_implementation
 *   Can be "phpseclib" or "mcrypt". Warning: Does not check if the requested
 *   implementation actually exists.
 *
 * @return bool|string
 *   The decrypted string on success, FALSE on error.
 */
//function aes_decrypt($string, $base64encoded = TRUE, $custom_key = NULL, $custom_cipher = NULL, $custom_iv = NULL, $custom_implementation = NULL) {}

/**
 * Stores the key given by writing it to the storage method currently used
 * (database or file). This could be pretty useful for create profiles or
 * distributions.
 *
 * @param string $key
 *   The key.
 *
 * @return bool
 *   TRUE on success, FALSE otherwise.
 */
//function aes_store_key($key) {}

/**
 * Checks if a users password exists.
 * @code
 * // Implements hook_user_view().
 * function mymodule_user_view($account, $view_mode, $langcode) {
 *   if (aes_password_exists($account->uid)) {
 *     // You custom code
 *   }
 * }
 * @endcode
 *
 * @param int $uid
 *   The user ID.
 * @see aes_user_view()
 *
 * @return bool
 *   TRUE if encrypted password is exist. FALSE otherwise.
 */
//function aes_password_exists($uid) {}

/**
 * Gets a users password, in plain text, or in it's encrypted form.
 * @code
 * // Implements hook_user_view().
 * function mymodule_user_view($account, $view_mode, $langcode) {
 *   if (aes_password_exists($account->uid)) {
 *     $password = aes_get_password($uid, TRUE);
 *     $account->content['info']['aes_password'] = array(
 *       '#type' => 'user_profile_item',
 *       '#title' => t('User password'),
 *       '#markup' => '<div id="aes_password">' . $password . '</div>',
 *     );
 *   }
 * }
 * @endcode
 *
 * @param int $uid
 *   The user ID.
 * @param bool $decrypt
 *   (optional) Whether to decrypt the password before returning it, or not.
 *   Defaults to FALSE.
 * @see aes_ajax_callback()
 *
 * @return bool|string
 *   The password in plain text on success, FALSE otherwise.
 */
//function aes_get_password($uid, $decrypt = FALSE) {}

/**
 * @addtogroup hooks
 * @{
 */

/**
 * hook_aes_config_change()
 * This hook provide ability for developers to reencrypt data in modules
 * when aes configuration changed.
 *
 * @param array $decrypt_params
 *   An associative array with decrypt arguments containing the following keys:
 *   - base64encode: bool Whether this encrypted string is base64 encoded
 *     or not.
 *   - custom_key: string Use this as the key rather than the stored one
 *     for the operation.
 *   - custom_cipher: string Use this cipher rather than the default one.
 *     (only with Mcrypt - ignored with phpseclib)
 *   - custom_iv: string Use this initialization vector instead
 *     of the default one.
 *   - custom_implementation: string Can be "phpseclib" or "mcrypt".
 *     Warning: Does not check if the requested implementation actually exists.
 * @param array $encrypt_params
 *   An associative array with encrypt arguments containing the following keys:
 *   - base64encode: bool Whether to return the string base64 encoded
 *     (recommended for database insertion).
 *   - custom_key: string Use this as the key rather than the stored one
 *     for the operation.
 *   - custom_cipher: string Use this cipher rather than the default one.
 *     (only with Mcrypt - ignored with phpseclib)
 *   - custom_iv: string Use this initialization vector instead of
 *     the default one.
 *   - custom_implementation: string Can be "phpseclib" or "mcrypt".
 *     Warning: Does not check if the requested implementation actually exists.
 *
 * @see aes_aes_config_change()
 */

function hook_aes_config_change($decrypt_params, $encrypt_params) {
  // Get your current crypted data.
  $current_crypted_data = variable_get('custom_data_key', FALSE);

  // Decrypt your current data to plain text.
  $decrypt_params['string'] = $current_crypted_data;
  $plain_data = call_user_func_array('aes_decrypt', $decrypt_params);

  // Encrypt data with new eas configuration settings.
  $encrypt_params['string'] = $plain_data;
  $new_crypted_data = call_user_func_array('aes_encrypt', $encrypt_params);

  // Save new crypted data to data store.
  variable_set("custom_data_key", $new_crypted_data);
}

/**
 * @} End of "addtogroup hooks".
 */
