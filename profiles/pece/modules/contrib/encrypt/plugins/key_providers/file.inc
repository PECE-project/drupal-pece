<?php

/**
 * @file
 * Plugin definition for the File key provider.
 */

define('ENCRYPT_FILE_NAME', 'encrypt_key.key');

$plugin = encrypt_file_encrypt_key_providers();

/**
 * Implements MODULE_FILENAME_encrypt_key_providers().
 */
function encrypt_file_encrypt_key_providers() {
  return array(
    'title' => t('File'),
    'description' => t('Use a file to store the encryption key.'),
    'key callback' => 'encrypt_get_file_key',
    'settings form' => 'encrypt_file_key_settings_form',
    'submit callback' => 'encrypt_file_key_settings_form_submit',
    'static key' => TRUE,
  );
}

/**
 * Callback method to return the encryption key from a file.
 */
function encrypt_get_file_key($settings) {
  $file_name = $settings['path'] . '/' . ENCRYPT_FILE_NAME;
  // If the file doesn't exist, just abort.
  if (!file_exists($file_name)) {
    drupal_set_message(t('The file %file does not exist! Encrypt cannot retrieve encryption key.', array('%file' => $file_name)), 'error');
    return;
  }

  $key = file_get_contents($file_name);

  switch ($settings['method']) {
    case 'file_contents':
      return $key;

    case 'base64_decode':
      return base64_decode($key);

    // This only exists for backward compatibility.
    case 'md5':
      return md5($key);
  }
}

/**
 * Settings form for our key provider.
 */
function encrypt_file_key_settings_form($defaults) {
  $form = array();

  $options = array(
    'file_contents' => t('File contents'),
    'base64_decode' => t('Base64 decode'),
  );
  // Add the MD5 option, if it is already being used, but flag it as
  // not recommended.
  if ($defaults['method'] == 'md5') {
    $options['md5'] = t('MD5 (not recommended)');
  }

  $form['path'] = array(
    '#type' => 'textfield',
    '#title' => t('Path to Key File'),
    '#description' => t('Filepath may be absolute (e.g. %abs) or relative to the Drupal directory (e.g. %rel).', array(
      '%abs' => '/var/www',
      '%rel' => '../../keys',
    )),
    '#default_value' => isset($defaults['path']) ? $defaults['path'] : '',
    '#element_validate' => array('encrypt_file_key_path_validate'),
    '#required' => TRUE,
    '#field_suffix' => '/' . ENCRYPT_FILE_NAME,
  );
  $form['method'] = array(
    '#type' => 'select',
    '#title' => t('Method'),
    '#description' => t('Choose an optional modification to the file contents.'),
    '#options' => $options,
    '#default_value' => isset($defaults['method']) ? $defaults['method'] : 'file_contents',
  );

  return $form;
}

/**
 * Validate key path.
 */
function encrypt_file_key_path_validate($element, &$form_state, $form) {
  $directory = $element['#value'];
  $file = $element['#value'] . '/' . ENCRYPT_FILE_NAME;

  if (!file_exists($directory)) {
    form_error($element, t('The directory %dir does not exist.', array('%dir' => $directory)));
  }
  elseif (!is_dir($directory)) {
    form_error($element, t('The key path provided exists, but is not a directory.'));
  }
  elseif (!file_exists($file) && !is_writable($directory)) {
    form_error($element, t('The directory %dir needs to be writable in order to create the key file.', array(
      '%dir' => $directory,
    )));
  }
  elseif (file_exists($file) && !is_readable($file)) {
    form_error($element, t('The key file %file exists, but is not readable by the web server.', array(
      '%file' => $file,
    )));
  }
}

/**
 * Submit callback for the settings form.
 */
function encrypt_file_key_settings_form_submit($form, $form_state) {
  $directory = $form_state['values']['encrypt_key_providers_file_settings']['path'];
  $file = $directory . '/' . ENCRYPT_FILE_NAME;

  // Check for contents of file; do not write over the key.
  if (file_exists($file) && file_get_contents($file)) {
    return;
  }

  // Create a default key.
  $open_file = fopen($file, 'wb');
  $key = drupal_random_bytes(16);
  // Base64 encode the key, if required.
  if ($form_state['values']['encrypt_key_providers_file_settings']['method'] == 'base64_decode') {
    $key = base64_encode($key);
  }
  fwrite($open_file, $key);
  fclose($open_file);

  // Ensure that the file is only readable and writable by owner.
  drupal_chmod($file, 0600);

  drupal_set_message(t('The key file has been written to %file', array(
    '%file' => $file,
  )));
}
