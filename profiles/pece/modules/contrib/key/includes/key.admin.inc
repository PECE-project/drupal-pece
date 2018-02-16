<?php

/**
 * @file
 * Administrative functionality for managing key configurations.
 */

/**
 * Menu callback; displays the list of key configurations.
 *
 * @return array
 *   The table of key configurations.
 */
function key_configs_list() {
  $configs = key_get_keys();

  $header = array(
    t('Key'),
    t('Type'),
    t('Provider'),
    array('data' => t('Operations'), 'colspan' => '2'),
  );
  $rows = array();

  foreach ($configs as $id => $config) {
    $label = $config['label'];
    $id = $config['id'];
    $description = $config['description'];
    $key_type = key_get_plugin('key_type', $config['key_type']);
    $key_provider = key_get_plugin('key_provider', $config['key_provider']);

    $config_url_string = str_replace('_', '-', $id);

    $variables = array(
      'label' => $label,
      'id' => $id,
      'description' => $description,
    );

    // Set the name column.
    $row = array(theme('key_configs_list_description', $variables));

    // Set the key type column.
    $row[] = array('data' => $key_type['label']);

    // Set the key provider column.
    $row[] = array('data' => $key_provider['label']);

    // Set the edit column.
    $row[] = array('data' => l(t('edit'), KEY_MENU_PATH . '/manage/' . $config_url_string));

    // Set the delete column.
    $row[] = array('data' => l(t('delete'), KEY_MENU_PATH . '/manage/' . $config_url_string . '/delete'));

    $rows[] = $row;
  }

  $build['key_configs_list_table'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#empty' => t('No keys are available. <a href="@link">Add a key</a>.', array('@link' => url(KEY_MENU_PATH . '/add'))),
  );

  return $build;
}

/**
 * Form constructor for the key configuration form.
 *
 * @param array $config
 *   (optional) An array representing the configuration, when editing an
 *   existing configuration.
 *
 * @return array
 *   The key configuration form.
 */
function key_config_form($form, &$form_state, $config = array()) {
  // Add the defaults to the configuration, if they are needed.
  $config += _key_config_defaults();

  // If the form is rebuilding.
  if ($form_state['rebuild']) {
    $fields = array(
      'key_type',
      'key_type_settings',
      'key_provider',
      'key_provider_settings',
    );
    // Get current values from the form state.
    foreach ($fields as $field) {
      if (isset($form_state['values'][$field])) {
        $config[$field] = $form_state['values'][$field];
      }
    }

    // If a key type change triggered the rebuild.
    if ($form_state['triggering_element']['#name'] == 'key_type') {
      // Update the type and input plugins.
      _key_update_key_type($form_state, $config);
      _key_update_key_input($form_state, $config);
    }

    // If a key provider change triggered the rebuild.
    if ($form_state['triggering_element']['#name'] == 'key_provider') {
      // Update the provider and input plugins.
      _key_update_key_provider($form_state, $config);
      _key_update_key_input($form_state, $config);
    }
  }
  // If the form is not rebuilding.
  else {
    // Clear the plugin cache.
    _key_clear_plugin_cache();

    // Store the original key configuration.
    $form_state['storage']['original_key'] = empty($config['id']) ? NULL : $config;

    // Store the key value data in form state for use by plugins.
    $form_state['storage']['key_value'] = _key_set_key_value_data($config);

    // Update the input plugin.
    _key_update_key_input($form_state, $config);
  }

  // Store the current key configuration.
  $form_state['storage']['key_config'] = $config;

  // Load the plugins.
  $key_type = key_get_plugin('key_type', $config['key_type']);
  $key_provider = key_get_plugin('key_provider', $config['key_provider']);

  $form['label'] = array(
    '#title' => t('Key name'),
    '#type' => 'textfield',
    '#default_value' => $config['label'],
    '#required' => TRUE,
    '#size' => 30,
  );
  $form['id'] = array(
    '#type' => 'machine_name',
    '#default_value' => $config['id'],
    '#maxlength' => 32,
    '#disabled' => !empty($config['id']),
    '#machine_name' => array(
      'exists' => 'key_config_load',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for the key. It must only contain lowercase letters, numbers, and underscores.'),
  );
  $form['description'] = array(
    '#title' => t('Description'),
    '#type' => 'textfield',
    '#default_value' => $config['description'],
    '#description' => t('A short description of the key.'),
  );

  // This is the element that contains all of the dynamic parts of the form.
  $form['settings'] = array(
    '#type' => 'container',
    '#prefix' => '<div id="key-settings">',
    '#suffix' => '</div>',
  );

  // Key type section.
  $form['settings']['type_section'] = array(
    '#type' => 'fieldset',
    '#title' => t('Type settings'),
    '#collapsible' => TRUE,
  );
  $form['settings']['type_section']['key_type'] = array(
    '#type' => 'select',
    '#title' => t('Key type'),
    '#options' => key_get_plugins_as_options('key_type', FALSE),
    '#required' => TRUE,
    '#default_value' => $config['key_type'],
    '#ajax' => array(
      'callback' => '_key_config_form_ajax_update_settings',
      'event' => 'change',
      'wrapper' => 'key-settings',
    ),
  );
  $form['settings']['type_section']['key_type_description'] = array(
    '#markup' => $key_type['description'],
  );
  $form['settings']['type_section']['key_type_settings'] = array(
    '#type' => 'container',
    '#title' => t('Key type settings'),
    '#title_display' => FALSE,
    '#tree' => TRUE,
  );
  if ($key_type_settings_form = ctools_plugin_get_function(key_get_plugin('key_type', $config['key_type']), 'build configuration form')) {
    $plugin_form_state = _key_create_plugin_form_state('key_type', $form_state);
    $form['settings']['type_section']['key_type_settings'] += $key_type_settings_form(array(), $plugin_form_state);
    $form_state['values']['key_type_settings'] = $plugin_form_state['values'];
  }

  // Key provider section.
  $form['settings']['provider_section'] = array(
    '#type' => 'fieldset',
    '#title' => t('Provider settings'),
    '#collapsible' => TRUE,
  );
  $form['settings']['provider_section']['key_provider'] = array(
    '#type' => 'select',
    '#title' => t('Key provider'),
    '#options' => key_get_plugins_as_options('key_provider', FALSE),
    '#required' => TRUE,
    '#default_value' => $config['key_provider'],
    '#ajax' => array(
      'callback' => '_key_config_form_ajax_update_settings',
      'event' => 'change',
      'wrapper' => 'key-settings',
    ),
  );
  $form['settings']['provider_section']['key_provider_description'] = array(
    '#markup' => $key_provider['description'],
  );
  $form['settings']['provider_section']['key_provider_settings'] = array(
    '#type' => 'container',
    '#title' => t('Key provider settings'),
    '#title_display' => FALSE,
    '#tree' => TRUE,
  );
  if ($key_provider_settings_form = ctools_plugin_get_function(key_get_plugin('key_provider', $config['key_provider']), 'build configuration form')) {
    $plugin_form_state = _key_create_plugin_form_state('key_provider', $form_state);
    $form['settings']['provider_section']['key_provider_settings'] += $key_provider_settings_form(array(), $plugin_form_state);
    $form_state['values']['key_provider_settings'] = $plugin_form_state['values'];
  }

  // Key input section.
  $form['settings']['input_section'] = array(
    '#type' => 'fieldset',
    '#title' => t('Value'),
    '#collapsible' => TRUE,
  );
  $form['settings']['input_section']['key_input'] = array(
    '#type' => 'value',
    '#value' => $config['key_input'],
  );
  $form['settings']['input_section']['key_input_settings'] = array(
    '#type' => 'container',
    '#title' => t('Key input settings'),
    '#title_display' => FALSE,
    '#tree' => TRUE,
  );
  if ($key_input_settings_form = ctools_plugin_get_function(key_get_plugin('key_input', $config['key_input']), 'build configuration form')) {
    $plugin_form_state = _key_create_plugin_form_state('key_input', $form_state);
    $form['settings']['input_section']['key_input_settings'] += $key_input_settings_form(array(), $plugin_form_state);
    $form_state['values']['key_input_settings'] = $plugin_form_state['values'];
  }

  $form['actions'] = array(
    '#type' => 'actions',
  );
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save key'),
    '#submit' => array('key_config_form_submit'),
    '#weight' => 40,
  );
  if (!empty($config['id'])) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete key'),
      '#submit' => array('key_config_form_delete_submit'),
      '#limit_validation_errors' => array(),
      '#weight' => 45,
    );
  }

  return $form;
}

/**
 * Callback for AJAX form re-rendering.
 */
function _key_config_form_ajax_update_settings($form, $form_state) {
  return $form['settings'];
}

/**
 * Form validate handler for key_config_form().
 */
function key_config_form_validate($form, &$form_state) {
  if (!$form_state['submitted']) {
    return;
  }

  $plugin_types = _key_get_plugin_types();
  $key_type = key_get_plugin('key_type', $form_state['values']['key_type']);
  $key_provider = key_get_plugin('key_provider', $form_state['values']['key_provider']);
  $key_input = key_get_plugin('key_input', $form_state['values']['key_input']);

  // Update the key configuration in form state storage.
  foreach (array_keys($form_state['storage']['key_config']) as $id) {
    if (isset($form_state['values'][$id])) {
      $form_state['storage']['key_config'][$id] = $form_state['values'][$id];
    }
  }

  // Make sure each plugin settings field is an array.
  foreach (_key_get_plugin_types() as $type) {
    if (empty($form_state['values'][$type . '_settings'])) {
      $form_state['values'][$type . '_settings'] = array();
    }
  }

  $processed_values = array(
    'submitted' => NULL,
    'processed_submitted' => NULL,
  );
  foreach ($plugin_types as $type) {
    $plugin = $$type;
    $plugin_form_state = _key_create_plugin_form_state($type, $form_state);

    // Special behavior for the Key Input plugin.
    if ($type == 'key_input') {
      // If the provider accepts a key value.
      if ($key_provider['key value']['accepted']) {
        $process_value_function = ctools_plugin_get_function($key_input, 'process submitted key value');
        $processed_values = $process_value_function($plugin_form_state);
      }
    }

    if ($validate_function = ctools_plugin_get_function($plugin, 'validate configuration form')) {
      $validate_function($form, $plugin_form_state);
    }
    $form_state['values'][$type . '_settings'] = $plugin_form_state['values'];
    _key_move_form_state_storage($plugin_form_state, $form_state);
  }

  // Store the submitted and processed key values in form state.
  $form_state['storage']['key_value']['submitted'] = $processed_values['submitted'];
  $form_state['storage']['key_value']['processed_submitted'] = $processed_values['processed_submitted'];

  // Allow the Key Type plugin to validate the key value. Use the processed
  // key value if there is one. Otherwise, retrieve the key value using the
  // key provider.
  if ($validate_function = ctools_plugin_get_function($key_type, 'validate key value')) {
    if (!empty($processed_values['processed_submitted'])) {
      $key_value = $processed_values['processed_submitted'];
    }
    else {
      // Create a temporary key configuration to retrieve the key value.
      $temp_key = $form_state['values'];
      $key_value = key_get_key_value($temp_key);
    }
    $plugin_form_state = _key_create_plugin_form_state('key_type', $form_state);
    $validate_function($form, $plugin_form_state, $key_value);
    $form_state['values']['key_type_settings'] = $plugin_form_state['values'];
    _key_move_form_state_storage($plugin_form_state, $form_state);
  }
}

/**
 * Form submission handler for key_config_form().
 */
function key_config_form_submit($form, &$form_state) {
  $key_value_data = $form_state['storage']['key_value'];

  // Update the key configuration in form state storage.
  foreach (array_keys($form_state['storage']['key_config']) as $id) {
    if (isset($form_state['values'][$id])) {
      $form_state['storage']['key_config'][$id] = $form_state['values'][$id];
    }
  }

  $key_provider = key_get_plugin('key_provider', $form_state['values']['key_provider']);
  $original_key = $form_state['storage']['original_key'];
  $config = $form_state['storage']['key_config'];

  foreach (_key_get_plugin_types() as $type) {
    $plugin = key_get_plugin($type, $config[$type]);
    $plugin_form_state = _key_create_plugin_form_state($type, $form_state);

    if ($submit_function = ctools_plugin_get_function($plugin, 'submit configuration form')) {
      $submit_function($form, $plugin_form_state);
      $form_state['values'][$type . '_settings'] = $plugin_form_state['values'];
      _key_move_form_state_storage($plugin_form_state, $form_state);
    }
  }

  // If the key provider allows a key value to be set.
  if ($key_provider['key value']['accepted'] && $set_key_value_function = ctools_plugin_get_function($key_provider, 'set key value')) {
    // If either the key provider has changed or the submitted value
    // is not the same as the obscured value.
    if (($original_key && $original_key['key_provider'] != $form_state['values']['key_provider'])
      || ($key_value_data['submitted'] != $key_value_data['obscured'])) {
      // Set the key value.
      $plugin_form_state = _key_create_plugin_form_state('key_provider', $form_state);
      $set_key_value_function($config, $plugin_form_state, $key_value_data['processed_submitted']);
      $form_state['values']['key_provider_settings'] = $plugin_form_state['values'];
      _key_move_form_state_storage($plugin_form_state, $form_state);
    }
  }

  $fields = array(
    'id' => (string) $form_state['values']['id'],
    'label' => (string) $form_state['values']['label'],
    'description' => (string) $form_state['values']['description'],
    'key_type' => (string) $form_state['values']['key_type'],
    'key_type_settings' => (isset($form_state['values']['key_type_settings'])) ? serialize($form_state['values']['key_type_settings']) : array(),
    'key_provider' => (string) $form_state['values']['key_provider'],
    'key_provider_settings' => (isset($form_state['values']['key_provider_settings'])) ? serialize($form_state['values']['key_provider_settings']) : array(),
    'key_input' => (string) $form_state['values']['key_input'],
    'key_input_settings' => (isset($form_state['values']['key_input_settings'])) ? serialize($form_state['values']['key_input_settings']) : array(),
  );

  $save_result = key_save_key($fields, $form_state['storage']['original_key']);

  // If the save was successful, redirect to the list page.
  if ($save_result) {
    $form_state['redirect'] = KEY_MENU_PATH . '/list';
  }
}

/**
 * Form submission handler for key_config_form().
 *
 * Handles the 'Delete' button on the key configuration form.
 */
function key_config_form_delete_submit($form, &$form_state) {
  $form_state['redirect'] = KEY_MENU_PATH . '/manage/' . str_replace('_', '-', $form['id']['#default_value']) . '/delete';
}

/**
 * Menu callback to delete a key configuration.
 *
 * @param array $config
 *   The configuration to delete.
 *
 * @return array
 *   The delete confirmation form.
 */
function key_config_delete_confirm($form, &$form_state, $config) {
  $form['id'] = array('#type' => 'value', '#value' => $config['id']);
  $form['label'] = array('#type' => 'value', '#value' => $config['label']);

  $message = t('Are you sure you want to delete the key %label?', array('%label' => $config['label']));
  $caption = '<p>' . t('This action cannot be undone.') . '</p>';

  // Allow the plugins to modify the form.
  foreach (_key_get_plugin_types() as $type) {
    $plugin = key_get_plugin($type, $config[$type]);
    if ($delete_form_function = ctools_plugin_get_function($plugin, 'build delete form')) {
      $delete_form_function($form, $form_state, $config, $message, $caption);
    }
  }

  return confirm_form($form, filter_xss_admin($message), KEY_MENU_PATH, filter_xss_admin($caption), t('Delete'));
}

/**
 * Form validate handler for key_config_delete_confirm().
 */
function key_config_delete_confirm_validate($form, &$form_state) {
  $id = (isset($form_state['values']['id'])) ? $form_state['values']['id'] : NULL;

  // Load the configuration.
  $config = key_get_key($id);

  // Allow the plugins to perform additional validation.
  foreach (_key_get_plugin_types() as $type) {
    $plugin = key_get_plugin($type, $config[$type]);
    if ($validate_form_function = ctools_plugin_get_function($plugin, 'validate delete form')) {
      $validate_form_function($form, $form_state, $config);
    }
  }
}

/**
 * Submit handler for key_config_delete_confirm().
 */
function key_config_delete_confirm_submit($form, &$form_state) {
  $id = (isset($form_state['values']['id'])) ? $form_state['values']['id'] : NULL;

  // Load the configuration, so the values can be used after deletion.
  $config = key_get_key($id);

  key_delete_key($id);
  $form_state['redirect'] = KEY_MENU_PATH;

  // Allow the plugins to perform additional actions.
  foreach (_key_get_plugin_types() as $type) {
    $plugin = key_get_plugin($type, $config[$type]);
    if ($submit_form_function = ctools_plugin_get_function($plugin, 'submit delete form')) {
      $submit_form_function($form, $form_state, $config);
    }
  }
}

/**
 * Returns HTML for a key configuration description.
 *
 * @param array $variables
 *   An associative array containing:
 *   - label: The human-readable label of the configuration.
 *   - id: The machine name of the configuration.
 *   - description: A brief description of the configuration.
 *
 * @return string
 *   The HTML for the description.
 */
function theme_key_configs_list_description($variables) {
  $label = $variables['label'];
  $id = $variables['id'];
  $description = $variables['description'];

  $output = check_plain($label);
  $output .= ' <small>' . t('(Machine name: @id)', array('@id' => $id)) . '</small>';
  $output .= '<div class="description">' . filter_xss_admin($description) . '</div>';

  return $output;
}

/**
 * Set the key value data.
 *
 * @param array $config
 *   The key configuration.
 *
 * @return array
 *   The key value data.
 */
function _key_set_key_value_data($config = array()) {
  $key_value_data = array(
    'original' => NULL,
    'processed_original' => NULL,
    'obscured' => NULL,
    'current' => '',
  );

  // If this is a new key being added, return the defaults.
  if (empty($config['id'])) {
    return $key_value_data;
  }

  $key_type = key_get_plugin('key_type', $config['key_type']);
  $key_provider = key_get_plugin('key_provider', $config['key_provider']);
  $key_input = key_get_plugin('key_input', $config['key_input']);

  $obscure_options = array();

  // Add settings from plugins.
  $obscure_options['key_type_id'] = $key_type['name'];
  $obscure_options['key_type_group'] = $key_type['group'];
  $obscure_options['key_provider_id'] = $key_provider['name'];

  $key_value = array();

  // Get the existing key value.
  $key_value['original'] = key_get_key_value($config['id']);

  // Process the original key value.
  if ($process_function = ctools_plugin_get_function($key_input, 'process existing key value')) {
    $key_value['processed_original'] = $process_function($config['key_input_settings'], $key_value['original']);
  }
  else {
    $key_value['processed_original'] = $key_value['original'];
  }

  // Obscure the processed key value.
  if ($obscured_function = ctools_plugin_get_function($key_provider, 'obscure key value')) {
    $obscured_key_value = $obscured_function($key_value['processed_original'], $obscure_options);
  }
  else {
    $obscured_key_value = $key_value['processed_original'];
  }
  if ($obscured_key_value != $key_value['processed_original']) {
    $key_value['obscured'] = $obscured_key_value;
  }
  else {
    $key_value['obscured'] = '';
  }

  // Set the current value.
  $key_value['current'] = (!empty($key_value['obscured'])) ? $key_value['obscured'] : $key_value['processed_original'];

  return $key_value;
}

/**
 * Update the key type plugin.
 *
 * @param array $config
 *   The key configuration.
 */
function _key_update_key_type(&$form_state, &$config) {
  $key_type = key_get_plugin('key_type', $form_state['values']['key_type']);
  $original_key = isset($form_state['storage']['original_key']) ? $form_state['storage']['original_key'] : NULL;

  // If the original key's plugin ID matches the existing one.
  if ($original_key['key_type'] == $key_type['name']) {
    // Use the configuration from the original key's plugin.
    $plugin_config = $original_key['key_type_settings'];
  }
  elseif ($default_configuration_function = ctools_plugin_get_function($key_type, 'default configuration')) {
    // Use the plugin's default configuration.
    $plugin_config = call_user_func($default_configuration_function);
  }
  else {
    $plugin_config = array();
  }

  $config['key_type'] = $form_state['values']['key_type'];
  $config['key_type_settings'] = $plugin_config;
  $form_state['values']['key_type_settings'] = $plugin_config;
  $form_state['values']['key_type_settings'] = $plugin_config;
}

/**
 * Update the key provider plugin.
 *
 * @param array $config
 *   The key configuration.
 */
function _key_update_key_provider(&$form_state, &$config) {
  $key_provider = key_get_plugin('key_provider', $form_state['values']['key_provider']);
  $original_key = isset($form_state['storage']['original_key']) ? $form_state['storage']['original_key'] : NULL;

  // If the original key's plugin ID matches the existing one.
  if ($original_key['key_provider'] == $key_provider['name']) {
    // Use the configuration from the original key's plugin.
    $plugin_config = $original_key['key_provider_settings'];
  }
  elseif ($default_configuration_function = ctools_plugin_get_function($key_provider, 'default configuration')) {
    // Use the plugin's default configuration.
    $plugin_config = call_user_func($default_configuration_function);
  }
  else {
    $plugin_config = array();
  }

  $config['key_provider'] = $form_state['values']['key_provider'];
  $config['key_provider_settings'] = $plugin_config;
  $form_state['values']['key_provider_settings'] = $plugin_config;
  $form_state['values']['key_provider_settings'] = $plugin_config;
}

/**
 * Update the key input plugin.
 *
 * @param array $config
 *   The key configuration.
 */
function _key_update_key_input(&$form_state, &$config) {
  $key_provider = key_get_plugin('key_provider', $config['key_provider']);
  $key_type = key_get_plugin('key_type', $config['key_type']);

  // Get the current key value data.
  $key_value_data = $form_state['storage']['key_value'];

  // Determine which Key Input should be used.
  $key_input_id = 'none';
  if ($key_provider['key value']['accepted']) {
    $key_input_id = $key_type['key value']['plugin'];
  }

  // Set the Key Input plugin.
  $config['key_input'] = $key_input_id;
  $key_input = key_get_plugin('key_input', $config['key_input']);

  // Set the plugin's configuration to the default. It may be
  // overridden below.
  if ($default_configuration_function = ctools_plugin_get_function($key_input, 'default configuration')) {
    // Use the plugin's default configuration.
    $plugin_config = call_user_func($default_configuration_function);
  }
  else {
    $plugin_config = array();
  }

  // Clear the current key value. It may be overridden below.
  $key_value_data['current'] = '';

  $use_original_key_value = FALSE;

  // If an original key exists, one of the following conditions must
  // be met in order to use the key value from it:
  // - The key value was not obscured when the form first loaded.
  // - The original key provider is the same as the current one
  //   AND the original key type is the same as the current one.
  if ($form_state['storage']['original_key']) {
    $original_key = $form_state['storage']['original_key'];

    // If the key value is not obscured.
    if (empty($key_value_data['obscured'])) {
      $use_original_key_value = TRUE;
    }
    // If the original key provider is the same as the current one.
    if ($original_key['key_provider'] == $config['key_provider']) {
      // If the original key type is the same as the current one.
      if ($original_key['key_type'] == $config['key_type']) {
        $use_original_key_value = TRUE;
      }
    }
  }

  // If the original key value can be used.
  if ($use_original_key_value) {
    // Use the configuration from the original key's plugin.
    $plugin_config = $original_key['key_input_settings'];

    // Set the current key value.
    $key_value_data['current'] = (!empty($key_value_data['obscured'])) ? $key_value_data['obscured'] : $key_value_data['processed_original'];
  }

  $config['key_input_settings'] = $plugin_config;
  $form_state['values']['key_input_settings'] = array();
  $form_state['values']['key_input_settings'] = array();
  $form_state['storage']['key_value'] = $key_value_data;
}

/**
 * Creates a form state for a plugin.
 *
 * @param string $type
 *   The plugin type ID.
 * @param array $form_state
 *   The form state to copy values from.
 *
 * @return array
 *   A copy of the form state with values from the plugin.
 */
function _key_create_plugin_form_state($type, $form_state) {
  // Copy the form state.
  $plugin_form_state = $form_state;

  // Clear the values, except for this plugin type's settings.
  $plugin_form_state['values'] = (isset($form_state['values'][$type . '_settings'])) ? $form_state['values'][$type . '_settings'] : array();

  return $plugin_form_state;
}

/**
 * Moves storage variables from one form state to another.
 *
 * @param array $from
 *   The form state to move from.
 * @param array $to
 *   The form state to move to.
 */
function _key_move_form_state_storage($from, &$to) {
  foreach ($from['storage'] as $index => $value) {
    $to['storage'][$index] = $value;
  }
}
