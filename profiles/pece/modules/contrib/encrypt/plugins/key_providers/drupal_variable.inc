<?php

/**
 * @file
 * Plugin definition for the Drupal Private Key key provider.
 */

$plugin = encrypt_drupal_variable_encrypt_key_providers();

/**
 * Implements MODULE_FILENAME_encrypt_key_providers().
 */
function encrypt_drupal_variable_encrypt_key_providers() {
  return array(
    'title' => t('Drupal encrypt_drupal_variable_key variable'),
    'description' => t('Use a variable called encrypt_drupal_variable_key, preferably set in your settings.php $conf array.'),
    'key callback' => 'encrypt_get_encrypt_drupal_variable_key',
    'settings form' => 'encrypt_drupal_variable_key_settings_form',
    'dependency callback' => '_encrypt_drupal_variable_is_present',
    'static key' => TRUE,
  );
}

/**
 * Callback function to return a variable.
 */
function encrypt_get_encrypt_drupal_variable_key($settings) {
  $key = variable_get('encrypt_drupal_variable_key', NULL);
  if (empty($key)) {
    watchdog('encrypt', 'You need to set the encrypt_drupal_variable_key variable, preferably in $conf in your settings.php.', array(), WATCHDOG_EMERGENCY);
    drupal_set_message("Encryption settings are insufficient. See your site log for more information.", 'error');
  }

  if (isset($settings['method'])) {
    switch ($settings['method']) {
      case 'base64_decode':
        $key = base64_decode($key);
        break;
    }
  }

  return $key;
}

/**
 * Settings form for the Drupal variable key provider.
 */
function encrypt_drupal_variable_key_settings_form($defaults) {
  $form = array();

  $form['method'] = array(
    '#type' => 'select',
    '#title' => t('Method'),
    '#options' => array(
      'variable_contents' => t('Variable contents'),
      'base64_decode' => t('Base64 decode'),
    ),
    '#default_value' => isset($defaults['method']) ? $defaults['method'] : 'variable_contents',
  );

  return $form;
}

/**
 * Callback function to validate the variable is present.
 */
function _encrypt_drupal_variable_is_present() {
  $errors = array();

  $key = variable_get('encrypt_drupal_variable_key', NULL);
  if (empty($key)) {
    $errors[] = t('The encrypt_drupal_variable_key is currently null. You should set it, preferably in $conf in your settings.php.');
  }

  return $errors;
}
