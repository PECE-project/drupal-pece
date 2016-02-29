<?php

/**
 * @file
 *
 * AES encryption module administration settings.
 */

 /**
 * Inits aes_config form.
 */
function aes_config() {
  $phpseclib_error_msg = "";

  $phpsec_load_result = aes_load_phpsec();
  $phpsec_loaded = FALSE;
  if ($phpsec_load_result > 0) {
    $phpsec_loaded = TRUE;
  }
  elseif ($phpsec_load_result == -1) {
    // Missing set_include_path.
    $phpseclib_error_msg = " <span style=\"color:#f00;\">" . t("Warning: phpseclib was found but can't be loaded since this sever doesn't allow setting the PHP include path.") . "</span>";
  }
  elseif ($phpsec_load_result == -2) {
    // Couldn't find phpseclib - don't output anything since this is perfectly
    // normal if using mcrypt.
  }
  elseif ($phpsec_load_result == -3) {
    // Found phpseclib, but couldn't read its files.
    $phpseclib_error_msg = " <span style=\"color:#f00;\">" . t("Warning: phpseclib was found but couldn't be read, check permissions.") . "</span>";
  }

  if (file_exists(variable_get("aes_key_path", "")) && is_writable(variable_get("aes_key_path", "")) == FALSE && variable_get("aes_key_storage_method", "Database") == "File") {
    drupal_set_message(t("The keyfile %keyfile_path is not writable. This module needs to be able to write to this file to update the encryption key.", array('%keyfile_path' => variable_get("aes_key_path", ""))), "warning");
  }

  $form = array();
  $form['aes_convert'] = array(
    '#type' => 'checkbox',
    '#title' => t('Create AES passwords'),
    '#default_value' => variable_get("aes_convert", FALSE),
    '#description' => t('Check this box if you would like for AES to start encrypting user passwords (and make them viewable to the roles with permission to do so). This is a process which normally will make more and more passwords AES-encrypted/readable over time since the AES module only can get an existing users password in plain text at certain moments, one such moment being when the user logs in. So you won\'t be able to view an existing users password until that user has logged in at least once after you checked this box. You may test this on yourself by logging out and in again, which should make your password appear on your user page.'),
  );

  $encryption_implementations = array();
  if ($phpsec_loaded) {
    $encryption_implementations["phpseclib"] = t("PHP Secure Communications Library (phpseclib)");
  }
  if (extension_loaded("mcrypt")) {
    $encryption_implementations["mcrypt"] = t("Mcrypt extension");
  }

  if (!empty($encryption_implementations["mcrypt"]) && !empty($encryption_implementations["phpseclib"])) {
    $implementations_description = t("The Mcrypt implementation is the (only) implementation this module used until support for phpseclib was added. The Mcrypt implementation is faster than phpseclib and also lets you define the cipher to be used, other than that, the two implementations are equivalent.");
  }
  elseif (!empty($encryption_implementations["mcrypt"]) && empty($encryption_implementations["phpseclib"])) {
    $implementations_description = t("The Mcrypt extension is the only installed implementation.") . $phpseclib_error_msg;
  }
  elseif (empty($encryption_implementations["mcrypt"]) && !empty($encryption_implementations["phpseclib"])) {
    $implementations_description = t("PHP Secure Communications Library is the only installed implementation.");
  }

  if (empty($encryption_implementations)) {
    $encryption_implementations = array(t('None!'));
    drupal_set_message(t("You do not have an AES implementation installed!"), "error");
  }

  $form['aes_implementation'] = array(
    '#type' => 'select',
    '#title' => t('AES implementation'),
    '#options' => $encryption_implementations,
    '#default_value' => variable_get("aes_implementation", "mcrypt"),
    '#description' => $implementations_description,
  );

  $form['view_method'] = array(
    '#type' => 'select',
    '#title' => t('Method for viewing passwords'),
    '#options' => array(
      'inplace' => t('In place'),
      'page' => t('Own page'),
      'both' => t('Both'),
      'neither' => t('Neither')
    ),
    '#default_value' => variable_get("aes_viewing_method", "page"),
    '#description' => t('Whether to show the password as an in-place AJAX field on the user info page or on a separate page with a tab on the user page, both, or neither.'),
  );

  $form['aes_cipher'] = array(
    '#type' => 'select',
    '#title' => t('Cipher'),
    '#options' => array(
      'rijndael-128' => 'Rijndael 128',
      'rijndael-192' => 'Rijndael 192',
      'rijndael-256' => 'Rijndael 256'
    ),
    '#default_value' => variable_get("aes_cipher", "rijndael-128"),
    '#states' => array(
      'invisible' => array(
        ':input[name="aes_implementation"]' => array('value' => 'phpseclib'),
      ),
    ),
  );

  $form['aes_cipher_notice'] = array(
    '#type' => 'item',
    '#title' => t('Cipher'),
    '#markup' => t("Is locked to Rijndael 128 when using the phpseclib implementation.") . "<br/>",
    '#states' => array(
      'visible' => array(
        ':input[name="aes_implementation"]' => array('value' => 'phpseclib'),
      ),
    ),
  );

  $iv = base64_decode(variable_get("aes_encryption_iv", ""));
  $iv = empty($iv)
    ? 'Not defined'
    : 'Base64: ' . variable_get("aes_encryption_iv") . "\r\nHex: 0x" . strtoupper(bin2hex($iv));

  $form['iv'] = array(
    '#type' => 'textarea',
    '#title' => t('Initialization vector'),
    '#description' => t("The value used to encrypt and decrypt message. Less secure than key. Should be exposed among with encoded data when encoding is passed to an external system. Currently fully supported by MCrypt mode, with PHPSecLib used only for custom calls."),
    '#disabled' => TRUE,
    '#default_value' => $iv,
    '#rows' => 2,
  );

  $form['aes_key_storage_method'] = array(
    '#type' => 'select',
    '#title' => t('Key storage method'),
    '#options' => array('Database' => 'Database', 'File' => 'File'),
    '#default_value' => variable_get("aes_key_storage_method", "Database"),
    '#description' => t('If possible, you should use the file storage method and assign a path below.'),
  );

  $form['aes_key_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Path to keyfile'),
    '#default_value' => variable_get("aes_key_path", ""),
    '#description' => t('The path, including the filename, of the file in which to store your key. The access restrictions on this file should be set as high as possible while still allowing webserver read/write access.'),
  );

  $form['aes_key'] = array(
    '#type' => 'password',
    '#title' => t('Key'),
    '#description' => t("The key for your encryption system. You normally don't need to worry about this since this module will generate a key for you if none is specified. However you have the option of using your own custom key here."),
  );

  $form['aes_key_c'] = array(
    '#type' => 'password',
    '#title' => t('Confirm key'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Validates aes_config form.
 */
function aes_config_validate($form, &$form_state) {

  if (empty($form_state['values']['aes_implementation'])) {
    form_set_error("aes_implementation", t("AES needs an encryption implementation to function. See the README.txt for instructions on how to install one."));
  }

  if (!empty($form_state['values']['aes_key'])) {
    if ($form_state['values']['aes_key'] !== $form_state['values']['aes_key_c']) {
      form_set_error("aes_key", t("The encryption keys didn't match."));
    }
  }

  // If the storage method is set to File, ensure the file can be opened.
  // for writing
  if ($form_state['values']['aes_key_storage_method'] == "File") {
    $fp = @fopen($form_state['values']['aes_key_path'], "a");

    if ($fp === FALSE) {
      form_set_error("aes_key_path", t("Can't write to the specified location."));
    }
    else {
      fclose($fp);
    }
  }
}

/**
 * Submits aes_config form.
 */
function aes_config_submit($form, &$form_state) {

  variable_set("aes_viewing_method", $form_state['values']['view_method']);

  if ($form_state['values']['aes_convert']) {
    if (!variable_get("aes_convert", FALSE)) {
      variable_set("aes_convert", TRUE);
      drupal_set_message(t("Creation of encrypted passwords enabled."));
    }
  }
  else {
    if (variable_get("aes_convert", FALSE)) {
      variable_set("aes_convert", FALSE);
      drupal_set_message(t("Creation of encrypted passwords disabled."));
    }
  }

  // Fulfill our promise if needed: PHPSecLib is locked to 128bits.
  if ($form_state['values']['aes_cipher'] == 'phpseclib') {
    $form_state['values']['aes_cipher'] = 'rijndael-128';
  }

  // Check if the storage method or key path has changed.
  if (($form_state['values']['aes_key_storage_method'] != variable_get("aes_key_storage_method", "Database")) || ($form_state['values']['aes_key_path'] != variable_get("aes_key_path",""))) {
    // If it has changed, we need to move the key.
    if ($form_state['values']['aes_key_storage_method'] != variable_get("aes_key_storage_method", "Database")) {
      drupal_set_message(t("Switching key storage method to %method.", array('%method' => $form_state['values']['aes_key_storage_method'])));
    } else {
      drupal_set_message(t("Changed key file path."));
    }
    // get the key
    $key = aes_get_key();
    // delete the key from the old storage
    aes_delete_key(variable_get("aes_key_storage_method"));
    // set key path
    variable_set("aes_key_path", $form_state['values']['aes_key_path']);
    // set the new storage
    variable_set("aes_key_storage_method", $form_state['values']['aes_key_storage_method']);
    // store the key in its new location
    aes_store_key($key);
  }

  // To use if re-encryption is required.
  $decrypt_params = array(
    'string' => '',
    'base64encoded' => TRUE,
    'custom_key' => aes_get_key(),
    'custom_cipher' => variable_get("aes_cipher", "rijndael-128"),
    'custom_iv' => variable_get("aes_encryption_iv", ""),
    'custom_implementation' => variable_get("aes_implementation", "mcrypt"),
  );
  $encrypt_params = array(
    'string' => '',
    'base64encode' => TRUE,
    'custom_key' => NULL,
    'custom_cipher' => NULL,
    'custom_iv' => NULL,
    'custom_implementation' => NULL,
  );
  $do_reencypt = FALSE;

  // If the cipher has changed...
  if ($form_state['values']['aes_cipher'] != variable_get("aes_cipher", "rijndael-128")) {
    variable_set("aes_cipher", $form_state['values']['aes_cipher']);
    $new_cipher = $form_state['values']['aes_cipher'];

    // update the cipher the system uses
    variable_set("aes_cipher", $form_state['values']['aes_cipher']);
    // Create a new iv to match the new cipher.
    aes_make_iv();

    $encrypt_params['custom_cipher'] = $new_cipher;
    $encrypt_params['custom_iv'] = variable_get("aes_encryption_iv");
    $do_reencypt = TRUE;
    drupal_set_message(t("Cipher changed."));
  }

  // If the key has changed...
  if (!empty($form_state['values']['aes_key'])) {
    if (!aes_store_key($form_state['values']['aes_key'])) {
      drupal_set_message(t("Failed to write new encryption key! Aborting."));
      return;
    }

    $encrypt_params['custom_key'] = $form_state['values']['aes_key'];
    $do_reencypt = TRUE;
    drupal_set_message(t("Key changed."));
  }

  // If the implementation has changed...
  if ($form_state['values']['aes_implementation'] != variable_get("aes_implementation", "mcrypt")) {
    variable_set("aes_implementation", $form_state['values']['aes_implementation']);
    $encrypt_params['custom_implementation'] = $form_state['values']['aes_implementation'];
    $do_reencypt = TRUE;

    if ($form_state['values']['aes_implementation'] == "phpseclib") {
      // If we have switched to phpseclib implementation, set the cipher to 128,
      // since it's the only one phpseclib supports.
      variable_set("aes_cipher", "rijndael-128");
      $encrypt_params['custom_cipher'] = "rijndael-128";
    }

    $iv = base64_decode(variable_get("aes_encryption_iv", ""));
    if (empty($iv)) {
      // Create a new IV, this IV won't actually be used by phpseclib, but it's
      // needed if the implementation is switched to mcrypt.
      aes_make_iv(TRUE);
      $encrypt_params['custom_iv'] = variable_get("aes_encryption_iv");
    }
    drupal_set_message(t("Implementation changed."));
  }

  // So far think of PHPSecLib as something not using IV by default.
  if ($decrypt_params['custom_implementation'] == 'phpseclib') {
    $decrypt_params['custom_iv'] = NULL;
  }
  if ($encrypt_params['custom_implementation'] == 'phpseclib') {
    $encrypt_params['custom_iv'] = NULL;
  }

  if ($do_reencypt) {
    // Calling custom hook_aes_config_change from each module which
    // implements this hook.
    foreach (module_implements('aes_config_change') as $module) {
      $function = $module . '_aes_config_change';
      $function($decrypt_params, $encrypt_params);
    }
  }
}

/**
 * Implements hook_aes_config_change().
 */
function aes_aes_config_change($decrypt_params, $encrypt_params) {
  // Re encrypt user paswords.
  $accounts = db_select('aes_passwords', 'p')
    ->fields('p', array('uid', 'pass'))
    ->condition('uid', 0, '!=')
    ->execute()
    ->fetchAll();
  foreach ($accounts as $account) {
    $decrypt_params['string'] = $account->pass;
    $plain_pass = call_user_func_array('aes_decrypt', $decrypt_params);
    $encrypt_params['string'] = $plain_pass;
    $new_pass = call_user_func_array('aes_encrypt', $encrypt_params);
    db_update('aes_passwords')
      ->fields(array('pass' => $new_pass))
      ->where("uid = :uid", array(
        ':uid' => $account->uid,
      ))
      ->execute();
  }
  if (count($accounts)) {
    drupal_set_message(t("Updated the passwords of @updates_num users because of a change in encryption settings.", array('@updates_num' => count($accounts))));
  }
}
