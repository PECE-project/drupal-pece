<?php

/**
 * Implements hook_drush_help().
 */
function key_drush_help($section) {
  switch ($section) {
    case 'meta:key:title':
      return dt('Commands for managing keys');

    case 'drush:key-save':
      return dt("Save a key. If a key value is defined and the key provider supports setting values, it will be saved. If any options are omitted, default values will be used.");
  }
}

/**
 * Implements hook_drush_command().
 */
function key_drush_command() {
  $items['key-save'] = array(
    'description' => dt('Save a key.'),
    'examples' => array(
      'drush key-save secret_password \'pA$$w0rd\' --label="Secret password" --key-type=authentication --key-provider=config --key-input=text_field' => 'Define a key for a password to use for authentication using the Configuration key provider.',
      'drush key-save encryption_key --label="Encryption key" --key-type=encryption --key-type-settings=\'{"key_size":256}\' --key-provider=file --key-provider-settings=\'{"file_location":"private://keys/encryption.key", "base64_encoded":true}\' --key-input=none' => 'Define a key to use for encryption using the File key provider.',
    ),
    'arguments' => array(
      'id' => dt('The ID (machine name) of the key to save.'),
      'key_value' => dt('A key value to save. May or may not be allowed or required, depending on the key provider'),
    ),
    'required-arguments' => 1,
    'options' => key_drush_save_options(),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
  );

  $items['key-delete'] = array(
    'description' => dt('Delete a key.'),
    'arguments' => array(
      'id' => dt('The ID (machine name) of the key to delete.'),
    ),
    'required-arguments' => TRUE,
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
  );

  $items['key-list'] = array(
    'description' => dt('Display a list of available keys.'),
    'options' => array(
      'key-type' => array(
        'description' => dt('An optional, comma-delimited list of key types. To see a list of available key types, use `drush key-type-list`.'),
        'example-value' => 'authentication,encryption',
      ),
      'key-provider' => array(
        'description' => dt('An optional, comma-delimited list of key providers. To see a list of available key providers, use `drush key-provider-list`.'),
        'example-value' => 'config,file',
      ),
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'outputformat' => array(
      'default' => 'table',
      'pipe-format' => 'list',
      'field-labels' => array(
        'id' => 'ID',
        'label' => 'Label',
        'key_type' => 'Type',
        'key_provider' => 'Provider',
      ),
      'output-data-type' => 'format-table',
    ),
  );

  $items['key-type-list'] = array(
    'description' => dt('Display a list of available key types.'),
    'options' => array(
      'group' => array(
        'description' => dt('An optional key type group on which to filter.'),
        'example-value' => 'authentication,encryption',
      ),
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'outputformat' => array(
      'default' => 'table',
      'pipe-format' => 'list',
      'field-labels' => array(
        'id' => 'ID',
        'description' => 'Description',
      ),
      'output-data-type' => 'format-table',
    ),
  );

  $items['key-provider-list'] = array(
    'description' => dt('Display a list of available key providers.'),
    'options' => array(
      'storage-method' => array(
        'description' => dt('An optional key provider storage method on which to filter.'),
        'example-value' => 'config,file',
      ),
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'outputformat' => array(
      'default' => 'table',
      'pipe-format' => 'list',
      'field-labels' => array(
        'id' => 'ID',
        'description' => 'Description',
      ),
      'output-data-type' => 'format-table',
    ),
  );

  $items['key-value-get'] = array(
    'description' => dt('Get a key value.'),
    'arguments' => array(
      'id' => dt('The ID (machine name) of the key whose value should be retrieved.'),
    ),
    'required-arguments' => TRUE,
    'options' => array(
      'base64' => dt('Base64-encode the key value. This is useful in the case of binary encryption keys that would otherwise not be displayed in a readable way.'),
      'pipe' => dt('Print just the key value, and nothing else.'),
    ),
    'aliases' => array('key-value'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'outputformat' => array(
      'default' => 'key-value',
      'pipe-format' => 'string',
      'label' => 'Key value',
      'output-data-type' => 'format-single',
    ),
  );

  return $items;
}

/**
 * Define the list of available drush options.
 *
 * @return array
 *   The list of drush options.
 */
function key_drush_save_options() {
  return array(
    'label' => array(
      'description' => dt('The human-readable label of the key.'),
    ),
    'description' => array(
      'description' => dt('A short description of the key.'),
    ),
    'key-type' => array(
      'description' => dt('The key type. To see a list of available key types, use `drush key-type-list`.'),
      'example-value' => 'authentication,encryption',
    ),
    'key-type-settings' => array(
      'description' => dt('Settings specific to the defined key type, in JSON format.'),
    ),
    'key-provider' => array(
      'description' => dt('The key provider. To see a list of available key providers, use `drush key-provider-list`.'),
      'example-value' => 'config,file',
    ),
    'key-provider-settings' => array(
      'description' => dt('Settings specific to the defined key provider, in JSON format.'),
    ),
    'key-input' => array(
      'description' => dt('The key input method.'),
      'example-value' => 'none,text_field',
    ),
    'key-input-settings' => array(
      'description' => dt('Settings specific to the defined key input, in JSON format.'),
    ),
    'overwrite' => 'Do not fail if the key already exists; overwrite it instead. Default is --no-overwrite.',
  );
}

/**
 * Command callback to save a key.
 */
function drush_key_save($id, $key_value = NULL) {
  require_once __DIR__ . '/key_save.inc';
  return _drush_key_save($id, $key_value);
}

/**
 * Command callback to delete a key.
 */
function drush_key_delete($id) {
  require_once __DIR__ . '/key_delete.inc';
  return _drush_key_delete($id);
}

/**
 * Command callback to get a list of available keys.
 */
function drush_key_list() {
  require_once __DIR__ . '/key_list.inc';
  return _drush_key_list();
}

/**
 * Command callback to get a list of available key types.
 */
function drush_key_type_list() {
  require_once __DIR__ . '/key_type_list.inc';
  return _drush_key_type_list();
}

/**
 * Command callback to get a list of available key providers.
 */
function drush_key_provider_list() {
  require_once __DIR__ . '/key_provider_list.inc';
  return _drush_key_provider_list();
}

/**
 * Command callback to get a key value.
 */
function drush_key_value_get($id) {
  require_once __DIR__ . '/key_value_get.inc';
  return _drush_key_value_get($id);
}
