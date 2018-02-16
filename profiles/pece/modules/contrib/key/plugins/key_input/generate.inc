<?php

/**
 * @file
 * Plugin definition for the Generate key input.
 */

$plugin = array(
  'label' => t('Generate'),
  'description' => t('Uses the key_type generate function.'),
  'default configuration' => 'key_input_generate_default_configuration',
  'build configuration form' => 'key_input_generate_build_configuration_form',
  'process submitted key value' => 'key_input_generate_process_submitted_key_value',
  'process existing key value' => '_key_default_process_existing_key_value',
);

/**
 * Define the default plugin configuration.
 *
 * @return array
 *   The default plugin configuration.
 */
function key_input_generate_default_configuration() {
  return array(
    'generated' => FALSE,
    'display_once' => TRUE,
  );
}

/**
 * Build the plugin configuration form.
 *
 * @return array
 *   The plugin configuration form.
 */
function key_input_generate_build_configuration_form($form, &$form_state) {
  $key_value_data = $form_state['storage']['key_value'];

  $config = $form_state['storage']['key_config'];
  $plugin_config = $config['key_input_settings'] + key_input_generate_default_configuration();

  // If the key value has already been generated.
  if ($plugin_config['generated']) {
    $form['key_value_message'] = array(
      '#markup' => t('The key value has already been generated and will not be changed.'),
    );
    $form['display_once'] = array(
      '#type' => 'value',
      '#value' => $plugin_config['display_once'],
    );
  }
  else {
    $form['key_value_message'] = array(
      '#markup' => t('The key value will be automatically generated using the selected key type settings.'),
    );

    // Allow the user to choose to display the key value once.
    $form['display_once'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display value'),
      '#description' => t('Check this to display the generated value once.'),
      '#default_value' => $plugin_config['display_once'],
    );
  }

  $form['generated'] = array(
    '#type' => 'value',
    '#value' => $plugin_config['generated'],
  );

  return $form;
}

/**
 * Generate a key value using the selected key type settings.
 *
 * @return array
 *   - 'submitted': The original submitted value.
 *   - 'processed_submitted': The processed value.
 */
function key_input_generate_process_submitted_key_value(&$form_state) {
  $key_input_settings = $form_state['values'];
  $key_value_data = $form_state['storage']['key_value'];
  $config = $form_state['storage']['key_config'];

  // If the key value has already been generated, use the existing value.
  // Otherwise, generate a key.
  if ($key_input_settings['generated']) {
    $processed_values = array(
      'submitted' => $key_value_data['current'],
      'processed_submitted' => $key_value_data['current'],
    );
  }
  else {
    $key_type = key_get_plugin('key_type', $config['key_type']);
    $generate_function = ctools_plugin_get_function($key_type, 'generate key value');
    $key_value = $generate_function($config);
    $form_state['values']['generated'] = TRUE;

    $processed_values = array(
      'submitted' => $key_value,
      'processed_submitted' => $key_value,
    );

    // If the user requested to display the generated password.
    if ($key_input_settings['display_once']) {
      drupal_set_message(t('A key value of the requested type has been generated and is displayed below as a Base64-encoded string. You will need to decode it to get the actual key value, which may or may not be human-readable. The key value will not be displayed again, so take note of it now, if necessary.<br>%key_value', array('%key_value' => base64_encode($key_value))), $type = 'status');
    }
  }

  return $processed_values;
}
