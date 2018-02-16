<?php

/**
 * @file
 * Plugin definition for the Textarea Field key input.
 */

$plugin = array(
  'label' => t('Textarea field'),
  'description' => t('A simple textarea field.'),
  'default configuration' => 'key_input_textarea_field_default_configuration',
  'build configuration form' => 'key_input_textarea_field_build_configuration_form',
  'process submitted key value' => '_key_default_process_submitted_key_value',
  'process existing key value' => '_key_default_process_existing_key_value',
);

/**
 * Define the default plugin configuration.
 *
 * @return array
 *   The default plugin configuration.
 */
function key_input_textarea_field_default_configuration() {
  return array(
    'key_value' => '',
    'base64_encoded' => FALSE,
  );
}

/**
 * Build the plugin configuration form.
 *
 * @return array
 *   The plugin configuration form.
 */
function key_input_textarea_field_build_configuration_form($form, &$form_state) {
  $key_value_data = $form_state['storage']['key_value'];
  $config = $form_state['storage']['key_config'];
  $plugin_config = $config['key_input_settings'] + key_input_textarea_field_default_configuration();
  $key_type = key_get_plugin('key_type', $config['key_type']);
  $key_provider = key_get_plugin('key_provider', $config['key_provider']);

  $form['key_value'] = array(
    '#type' => 'textarea',
    '#title' => t('Key value'),
    '#required' => $key_provider['key value']['required'],
    '#default_value' => $key_value_data['current'],
    // Tell the browser not to autocomplete this field.
    '#attributes' => array('autocomplete' => 'off'),
  );

  // If this key input is for an encryption key.
  if ($key_type['group'] == 'encryption') {
    // Add an option to indicate that the value is Base64-encoded.
    $form['base64_encoded'] = array(
      '#type' => 'checkbox',
      '#title' => t('Base64-encoded'),
      '#description' => t('Check this if the key value being submitted has been Base64-encoded.'),
      '#default_value' => $plugin_config['base64_encoded'],
    );
  }

  return $form;
}
