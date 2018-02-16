<?php

/**
 * @file
 * This file holds the functions for the Encrypt admin settings.
 *
 * @ingroup encrypt
 */

/**
 * Menu callback; displays the list of configurations.
 */
function encrypt_configs_list() {
  $configs = encrypt_get_configs();
  $methods = encrypt_get_encryption_methods();
  $providers = encrypt_get_key_providers();
  $default_config = variable_get('encrypt_default_config', NULL);

  $header = array(
    t('Name'),
    t('Encryption Method'),
    t('Key Provider'),
    t('Created'),
    t('Status'),
    array('data' => t('Operations'), 'colspan' => '3'),
  );
  $rows = array();

  foreach ($configs as $key => $config) {
    $label = $config['label'];
    $name = $config['name'];
    $description = $config['description'];
    $method = $config['method'];
    $provider = $config['provider'];
    $created = format_date($config['created'], 'short');

    $config_url_str = str_replace('_', '-', $name);

    $variables = array(
      'label' => $label,
      'name' => $name,
      'description' => $description,
    );

    // Set the name column.
    $row = array(theme('encrypt_configs_list_description', $variables));

    // Set the encryption method column.
    $row[] = array('data' => $methods[$method]['title']);

    // Set the key provider column.
    $row[] = array('data' => $providers[$provider]['title']);

    // Set the created column.
    $row[] = array('data' => $created);

    // Set the status column.
    $status = array();
    $status[] = ($config['enabled']) ? t('Enabled') : t('Disabled');
    if ($default_config == $config['name']) {
      $status[] = t('Default');
    }
    $row[] = array('data' => implode(', ', $status));

    // Set the edit column.
    $row[] = array('data' => l(t('edit'), ENCRYPT_MENU_PATH . '/edit/' . $config_url_str));

    // Set the delete column.
    $row[] = array('data' => l(t('delete'), ENCRYPT_MENU_PATH . '/delete/' . $config_url_str));

    // Set the make default column if this is not already the default.
    if ($default_config != $name) {
      $row[] = array('data' => l(t('make default'), ENCRYPT_MENU_PATH . '/default/' . $config_url_str));
    }
    else {
      $row[] = array('data' => '');
    }

    $rows[] = $row;
  }

  $build['encrypt_configs_list_table'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#empty' => t('No encryption configurations are available. <a href="@link">Add a configuration</a>.', array('@link' => url(ENCRYPT_MENU_PATH . '/add'))),
  );

  return $build;
}

/**
 * Form constructor for the configuration edit form.
 *
 * @param array $config
 *   (optional) An array representing the configuration, when editing an
 *   existing configuration.
 *
 * @see encrypt_config_form_validate()
 * @see encrypt_config_form_submit()
 * @ingroup forms
 */
function encrypt_config_form($form, &$form_state, $config = NULL) {
  $default_config = variable_get('encrypt_default_config', NULL);

  // Clear the plugin cache on the first page load (but not on AJAX refreshes).
  if (!isset($form_state['values'])) {
    _encrypt_clear_plugin_cache();
  }

  // Retrieve all methods and providers.
  $methods = encrypt_get_encryption_methods();
  $providers = encrypt_get_key_providers();

  // Make sure all plugin files are included (for form validation, etc.)
  // @todo: There has to be a better/faster/cleaner way to do this.
  foreach ($providers as $provider) {
    $form_state['build_info']['files']["encrypt:plugins:{$provider['name']}"] = $provider['path'] . '/' . $provider['file'];
  }

  // Create a list of method titles to be used for radio buttons.
  // Only display a deprecated method if it's the currently selected
  // method for this configuration. List it at the bottom.
  $method_options = array();
  foreach ($methods as $id => $method) {
    if (!$method['deprecated']) {
      $method_options[$id] = $method['title'];
    }
  }
  foreach ($methods as $id => $method) {
    if ($method['deprecated'] && $id == $config['method']) {
      $method_options[$id] = $method['title'] . ' <span class="encrypt-warning">' . t('(Deprecated)') . '</span>';
    }
  }

  // Create a list of provider titles to be used for radio buttons.
  // Only display a deprecated provider if it's the currently selected
  // provider for this configuration. List it at the bottom.
  $provider_options = array();
  foreach ($providers as $id => $provider) {
    if (!$provider['deprecated']) {
      $provider_options[$id] = $provider['title'];
    }
  }
  foreach ($providers as $id => $provider) {
    if ($provider['deprecated'] && $id == $config['provider']) {
      $provider_options[$id] = $provider['title'] . ' <span class="encrypt-warning">' . t('(Deprecated)') . '</span>';
    }
  }

  $form = array();

  $form['#attached'] = array(
    'css' => array(
      drupal_get_path('module', 'encrypt') . '/encrypt.css',
    ),
  );

  $form['label'] = array(
    '#title' => t('Name'),
    '#type' => 'textfield',
    '#default_value' => $config['label'],
    '#description' => t('The human-readable name of the configuration.'),
    '#required' => TRUE,
    '#size' => 30,
  );
  $form['name'] = array(
    '#type' => 'machine_name',
    '#default_value' => $config['name'],
    '#maxlength' => 32,
    '#disabled' => isset($config['name']),
    '#machine_name' => array(
      'exists' => 'encrypt_config_load',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for the configuration. It must only contain lowercase letters, numbers, and underscores.'),
  );
  $form['description'] = array(
    '#title' => t('Description'),
    '#type' => 'textarea',
    '#default_value' => $config['description'],
    '#description' => t('A short description of the configuration.'),
  );

  $form['settings'] = array(
    '#type' => 'vertical_tabs',
    '#attached' => array(
      'js' => array(drupal_get_path('module', 'encrypt') . '/js/encrypt_admin.js'),
    ),
  );

  $form['general_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('General settings'),
    '#collapsible' => TRUE,
    '#group' => 'settings',
  );
  $form['general_settings']['enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enabled'),
    '#default_value' => $config['enabled'],
    '#description' => t('If checked, this configuration will be available for encryption. The default configuration must be enabled.'),
  );

  // If this is the default configuration, disable the enabled checkbox.
  if ($config['name'] == $default_config) {
    $form['general_settings']['enabled']['#disabled'] = TRUE;
  }

  $form['method_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Encryption method settings'),
    '#collapsible' => TRUE,
    '#group' => 'settings',
  );
  $form['method_settings']['encrypt_encryption_method'] = array(
    '#type' => 'radios',
    '#title' => t('Encryption Method'),
    '#description' => t('Define the default encryption method for the site. Since encryption methods are stored with the data, this can be changed even after you have stored encrypted data.'),
    '#required' => TRUE,
    '#options' => $method_options,
    '#default_value' => $config['method'],
    '#ajax' => array(
      'method' => 'replace',
      'callback' => 'encrypt_encryption_methods_additional_settings_ajax',
      'wrapper' => 'encrypt-encryption-methods-additional-settings',
    ),
  );
  // Disable any method with dependency errors.
  _encrypt_admin_form_add_options($methods, $form['method_settings']['encrypt_encryption_method']);

  $form['method_settings']['method_settings_wrapper'] = array(
    '#type' => 'container',
    '#prefix' => '<div id="encrypt-encryption-methods-additional-settings">',
    '#suffix' => '</div>',
  );

  if (isset($form_state['values']['encrypt_encryption_method'])) {
    $method = $form_state['values']['encrypt_encryption_method'];
  }
  elseif (isset($config['method'])) {
    $method = $config['method'];
  }
  else {
    $method = NULL;
  }

  if ($method) {
    if ($method_settings_form = ctools_plugin_get_function($methods[$method], 'settings form')) {
      $form['method_settings']['method_settings_wrapper']['method_settings'] = array(
        '#type' => 'fieldset',
        '#title' => t('Additional Encryption Method Settings'),
      );

      $form['method_settings']['method_settings_wrapper']['method_settings']['encrypt_encryption_methods_' . $method . '_settings'] = array('#tree' => TRUE) + call_user_func($method_settings_form, $config['method_settings']);
    }
  }

  $form['provider_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Key provider settings'),
    '#collapsible' => TRUE,
    '#group' => 'settings',
  );
  $form['provider_settings']['encrypt_key_provider'] = array(
    '#type' => 'radios',
    '#title' => t('Key Provider'),
    '#description' => t('Select the method by which encrypt will retrieve an encryption key. NOTE: Once this is set, it is not a good idea to change it. All of your encrypted data may be lost if the encryption key changes.'),
    '#required' => TRUE,
    '#options' => $provider_options,
    '#default_value' => $config['provider'],
    '#ajax' => array(
      'method' => 'replace',
      'callback' => 'encrypt_key_providers_additional_settings_ajax',
      'wrapper' => 'encrypt-key-providers-additional-settings',
    ),
  );
  // Disable any method with dependency errors.
  _encrypt_admin_form_add_options($providers, $form['provider_settings']['encrypt_key_provider']);

  $form['provider_settings']['key_settings_wrapper'] = array(
    '#type' => 'container',
    '#prefix' => '<div id="encrypt-key-providers-additional-settings">',
    '#suffix' => '</div>',
  );

  if (isset($form_state['values']['encrypt_key_provider'])) {
    $provider = $form_state['values']['encrypt_key_provider'];
  }
  elseif (isset($config['provider'])) {
    $provider = $config['provider'];
  }
  else {
    $provider = NULL;
  }

  if ($provider) {
    if ($provider_settings_form = ctools_plugin_get_function($providers[$provider], 'settings form')) {
      $form['provider_settings']['key_settings_wrapper']['key_settings'] = array(
        '#type' => 'fieldset',
        '#title' => t('Additional Key Provider Settings'),
      );

      $form['provider_settings']['key_settings_wrapper']['key_settings']['encrypt_key_providers_' . $provider . '_settings'] = array('#tree' => TRUE) + call_user_func($provider_settings_form, $config['provider_settings']);
    }
  }

  $form['created'] = array(
    '#type' => 'value',
    '#value' => $config['created'],
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
    '#submit' => array('encrypt_config_form_submit'),
    '#weight' => 40,
  );
  if (isset($config['name'])) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete configuration'),
      '#submit' => array('encrypt_config_form_delete_submit'),
      '#limit_validation_errors' => array(),
      '#weight' => 45,
    );
  }

  return $form;
}

/**
 * Form validation handler for encrypt_config_form().
 */
function encrypt_config_form_validate($form, &$form_state) {
  // Don't allow the default configuration to be disabled.
  $default_config = variable_get('encrypt_default_config', NULL);

  if ($default_config == $form_state['values']['name'] && !$form_state['values']['enabled']) {
    form_set_error('general_settings][enabled', t('The default configuration must be enabled.'));
  }
}

/**
 * Form submission handler for encrypt_config_form().
 */
function encrypt_config_form_submit($form, &$form_state) {
  $method = encrypt_get_encryption_method($form_state['values']['encrypt_encryption_method']);
  $key_provider = encrypt_get_key_provider($form_state['values']['encrypt_key_provider']);

  foreach (array($method, $key_provider) as $plugin) {
    if ($submit_callback = ctools_plugin_get_function($plugin, 'submit callback')) {
      // Create a copy so that the plugin callback cannot change the
      // form state.
      $form_state_copy = $form_state;
      call_user_func($submit_callback, $form, $form_state_copy);
    }
  }

  $fields = array(
    'name' => (string) $form_state['values']['name'],
    'label' => (string) $form_state['values']['label'],
    'description' => (string) $form_state['values']['description'],
    'method' => (string) $form_state['values']['encrypt_encryption_method'],
    'provider' => (string) $form_state['values']['encrypt_key_provider'],
    'enabled' => (int) $form_state['values']['enabled'],
    'created' => $form_state['values']['created'],
  );

  if (empty($form_state['values']['encrypt_encryption_methods_' . $fields['method'] . '_settings'])) {
    $fields['method_settings'] = '';
  }
  else {
    $fields['method_settings'] = $form_state['values']['encrypt_encryption_methods_' . $fields['method'] . '_settings'];
  }

  if (empty($form_state['values']['encrypt_key_providers_' . $fields['provider'] . '_settings'])) {
    $fields['provider_settings'] = '';
  }
  else {
    $fields['provider_settings'] = $form_state['values']['encrypt_key_providers_' . $fields['provider'] . '_settings'];
  }

  encrypt_save_config($fields);

  $form_state['redirect'] = ENCRYPT_MENU_PATH . '/list';
}

/**
 * Form submission handler for encrypt_config_form().
 *
 * Handles the 'Delete' button on the encryption configuration form.
 */
function encrypt_config_form_delete_submit($form, &$form_state) {
  $form_state['redirect'] = ENCRYPT_MENU_PATH . '/delete/' . str_replace('_', '-', $form['name']['#default_value']);
}

/**
 * Menu callback to delete an encryption configuration.
 *
 * @ingroup forms
 */
function encrypt_config_delete_confirm($form, &$form_state, $config) {
  $default_config = variable_get('encrypt_default_config', NULL);

  if ($default_config == $config['name']) {
    drupal_set_message(t('The default configuration cannot be deleted.'), 'error');
    drupal_goto(ENCRYPT_MENU_PATH);
  }

  $form['name'] = array('#type' => 'value', '#value' => $config['name']);
  $form['label'] = array('#type' => 'value', '#value' => $config['label']);

  $message = t('Are you sure you want to delete the configuration %label?', array('%label' => $config['label']));
  $caption = '<p>' . t('This action cannot be undone.') . '</p>';

  return confirm_form($form, filter_xss_admin($message), ENCRYPT_MENU_PATH, filter_xss_admin($caption), t('Delete'));
}

/**
 * Submit handler for encrypt_config_delete_confirm.
 *
 * @see encrypt_config_delete_confirm()
 */
function encrypt_config_delete_confirm_submit($form, &$form_state) {
  db_delete('encrypt_config')
    ->condition('name', $form_state['values']['name'])
    ->execute();

  $t_args = array('%label' => $form_state['values']['label']);
  drupal_set_message(t('The configuration %label has been deleted.', $t_args));
  watchdog('encrypt', 'Deleted encryption configuration %label.', $t_args, WATCHDOG_NOTICE);

  $form_state['redirect'] = ENCRYPT_MENU_PATH;
}

/**
 * Menu callback to make a configuration the default.
 */
function encrypt_config_make_default($config) {
  variable_set('encrypt_default_config', $config['name']);

  $default_config = variable_get('encrypt_default_config', NULL);
  $t_args = array('%label' => $config['label']);
  if ($default_config == $config['name']) {
    // If the configuration is not enabled and it's the new default, enable it.
    if (!$config['enabled']) {
      db_update('encrypt_config')
        ->fields(array('enabled' => 1))
        ->condition('name', $config['name'])
        ->execute();
      drupal_set_message(t('The configuration %label has been enabled.', $t_args));
      watchdog('node', 'Enabled encryption configuration %label.', $t_args, WATCHDOG_NOTICE);
    }

    drupal_set_message(t('The configuration %label has been made the default.', $t_args));
    watchdog('encrypt', 'Made encryption configuration %label the default.', $t_args, WATCHDOG_NOTICE);
  }
  else {
    drupal_set_message(t('The configuration %label could not be made the default.', $t_args), 'error');
    watchdog('encrypt', 'Error when trying to make encryption configuration %label the default.', $t_args, WATCHDOG_ERROR);
  }

  drupal_goto(ENCRYPT_MENU_PATH);
}

/**
 * Callback for AJAX form re-rendering for method additional settings.
 */
function encrypt_encryption_methods_additional_settings_ajax($form, $form_state) {
  return $form['method_settings']['method_settings_wrapper'];
}

/**
 * Callback for AJAX form re-rendering for provider additional settings.
 */
function encrypt_key_providers_additional_settings_ajax($form, $form_state) {
  return $form['provider_settings']['key_settings_wrapper'];
}

/**
 * Add other elements to forms.
 */
function _encrypt_admin_form_add_options($items, &$element) {
  foreach ($items as $id => $item) {
    $element[$id] = array(
      '#description' => $item['description'],
      '#disabled' => !empty($item['dependency errors']),
    );

    // Add a list of dependency errors (if there are any).
    if (!empty($item['dependency errors'])) {
      $element[$id]['#description'] .= theme('item_list', array(
        'items' => $item['dependency errors'],
        'attributes' => array('class' => 'encrypt-dependency-errors'),
      ));
    }
  }
}

/**
 * Old settings callback.
 *
 * This form is no longer used, so if a user reaches it, display a notice
 * that an update is necessary.
 */
function encrypt_admin_settings($form, &$form_state) {
  _encrypt_display_update_message();
}

/**
 * Returns HTML for a configuration description.
 *
 * @param array $variables
 *   An associative array containing:
 *   - label: The human-readable label of the configuration.
 *   - name: The machine name of the configuration.
 *   - description: A brief description of the configuration.
 *
 * @ingroup themeable
 */
function theme_encrypt_configs_list_description($variables) {
  $label = $variables['label'];
  $name = $variables['name'];
  $description = $variables['description'];

  $output = check_plain($label);
  $output .= ' <small>' . t('(Machine name: @name)', array('@name' => $name)) . '</small>';
  $output .= '<div class="description">' . filter_xss_admin($description) . '</div>';

  return $output;
}
