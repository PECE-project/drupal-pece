<?php

/**
 * @file
 * Plugin definition for the Key Module key provider.
 */

$plugin = key_encrypt_encrypt_key_providers();

/**
 * Implements MODULE_FILENAME_encrypt_key_providers().
 */
function key_encrypt_encrypt_key_providers() {
  return array(
    'title' => t('Key module'),
    'description' => t('Use the Key module to store and provide the key.'),
    'key callback' => 'key_encrypt_key_get_key',
    'settings form' => 'key_encrypt_key_settings_form',
    'static key' => TRUE,
  );
}

/**
 * Callback function to return the key.
 */
function key_encrypt_key_get_key($settings) {
  if (empty($settings['key_config'])) {
    return FALSE;
  }
  $key = key_get_key_value($settings['key_config']);

  return $key;
}

/**
 * Settings form for the Key Module key provider.
 */
function key_encrypt_key_settings_form($defaults) {
  $form = array();

  $form['key_config'] = array(
    '#type' => 'select',
    '#title' => t('Key'),
    '#description' => t('Keys listed here are defined in the <a href="@path">Key module</a>.', array('@path' => url('admin/config/system/keys'))),
    '#empty_option' => t('- Select a key -'),
    '#options' => key_get_key_names_as_options(),
    '#default_value' => isset($defaults['key_config']) ? $defaults['key_config'] : '',
    '#required' => TRUE,
  );

  return $form;
}
