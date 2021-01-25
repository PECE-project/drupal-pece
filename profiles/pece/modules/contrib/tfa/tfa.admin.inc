<?php

/**
 * @file
 * TFA Administration and settings functions.
 */

/**
 * Admin settings form.
 */
function tfa_admin_settings($form, $form_state) {
  // Gather plugins.
  $plugins = $send_plugins = $validate_plugins = $login_plugins = array();
  foreach (module_invoke_all('tfa_api') as $key => $data) {
    if (is_subclass_of($data['class'], 'TfaBasePlugin')) {
      $plugins[$key] = $data;
    }
    if (in_array('TfaValidationPluginInterface', class_implements($data['class']))) {
      $validate_plugins[$key] = $data['name'];
    }
    if (in_array('TfaSendPluginInterface', class_implements($data['class']))) {
      $send_plugins[$key] = $data['name'];
    }
    elseif (in_array('TfaLoginPluginInterface', class_implements($data['class']))) {
      $login_plugins[$key] = $data['name'];
    }
  }

  // Check if openssl or mcrypt extensions are available.
  if (!extension_loaded('openssl') && !extension_loaded('mcrypt')) {
    // @todo allow alter in case of other encryption libs.
    drupal_set_message(t('The TFA module requires one of the PHP OpenSSL or Mcrypt extensions to be installed on the web server. See <a href="!link">the TFA help documentation</a> for setup.', array('!link' => url('admin/help/tfa'))), 'error');
    return array();
  }

  // Return if there are no plugins.
  if (empty($plugins) || empty($validate_plugins)) {
    drupal_set_message(t('No plugins available for validation. See <a href="!link">the TFA help documentation</a> for setup.', array('!link' => url('admin/help/tfa'))), 'error');
    return array();
  }

  $enabled = variable_get('tfa_enabled', 0);

  $form['plugins'] = array(
    '#type' => 'fieldset',
    '#title' => t('Available plugins'),
  );
  $items = array();
  foreach ($plugins as $key => $plugin) {
    $message = '<strong>@name</strong> (%type)';
    // Include message whether plugin is set.
    if ($enabled && variable_get('tfa_validate_plugin', '') === $key) {
      $message .= ' - active validator';
    }
    elseif ($enabled && in_array($key, variable_get('tfa_login_plugins', array()))) {
      $message .= ' - active login';
    }
    elseif ($enabled && in_array($key, variable_get('tfa_fallback_plugins', array()))) {
      $message .= ' - active fallback';
    }
    elseif ($enabled) {
      $message .= ' - unused';
    }
    // phpcs:disable Drupal.Semantics.FunctionT.NotLiteralString
    $items[] = t($message, array(
      '%type' => _tfa_class_types($plugin['class']),
      '@name' => $plugin['name'],
    ));
  }
  $form['plugins']['list'] = array(
    '#value' => 'markup',
    '#markup' => theme('item_list', array('items' => $items)),
  );

  // Option to enable entire process or not.
  $form['tfa_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable TFA'),
    '#default_value' => $enabled,
    '#description' => t('Enable TFA for account authentication.'),
  );
  // Reusable #states for tfa_enabled.
  $enabled_state = array(
    'visible' => array(
      ':input[name="tfa_enabled"]' => array('checked' => TRUE),
    ),
  );

  // Default active plugin.
  if (count($validate_plugins) >= 1) {
    $form['tfa_validate'] = array(
      '#type' => 'select',
      '#title' => t('Default validation plugin'),
      '#options' => $validate_plugins,
      '#default_value' => variable_get('tfa_validate_plugin', ''),
      '#description' => t('Plugin that will be used as the default TFA process.'),
      '#states' => $enabled_state,
    );
  }
  else {
    $form['no_validate'] = array(
      '#value' => 'markup',
      '#markup' => t('No available validation plugins available. TFA process will not occur.'),
    );
  }

  // Order of fallback plugins.
  if (count($validate_plugins) > 1) {
    $enabled_fallback = variable_get('tfa_fallback_plugins', array());
    $form['tfa_fallback'] = array(
      '#type' => 'fieldset',
      '#title' => t('Validation fallback plugins'),
      '#description' => t('Fallback plugins and order. Note, if a fallback plugin is not setup for an account it will not be active in the TFA form.'),
      '#states' => $enabled_state,
      '#tree' => TRUE,
    );
    // First enabled.
    foreach ($enabled_fallback as $order => $key) {
      $validate_state = array(
        'invisible' => array(
          ':input[name="tfa_validate"]' => array('value' => $key),
        ),
      );
      $form['tfa_fallback'][$key] = array(
        'enable' => array(
          '#title' => $validate_plugins[$key],
          '#type' => 'checkbox',
          '#default_value' => TRUE,
          // Don't show options that are set as the main validation plugin.
          '#states' => $validate_state,
        ),
        'weight' => array(
          '#type' => 'weight',
          '#title' => t('Order'),
          '#default_value' => $order,
          '#delta' => 10,
          '#title_display' => 'invisible',
          '#states' => $validate_state,
        ),
      );
    }
    // Then other plugins.
    foreach ($validate_plugins as $key => $plugin_name) {
      if (isset($form['tfa_fallback'][$key])) {
        continue;
      }
      $validate_state = array(
        'invisible' => array(
          ':input[name="tfa_validate"]' => array('value' => $key),
        ),
      );
      $form['tfa_fallback'][$key] = array(
        'enable' => array(
          '#title' => $plugin_name,
          '#type' => 'checkbox',
          '#default_value' => in_array($key, $enabled_fallback) ? TRUE : FALSE,
          // Don't show options that are set as the main validation plugin.
          '#states' => $validate_state,
        ),
        'weight' => array(
          '#type' => 'weight',
          '#title' => t('Order'),
          '#default_value' => in_array($key, $enabled_fallback) ? array_search($key, $enabled_fallback) : 0,
          '#delta' => 10,
          '#title_display' => 'invisible',
          '#states' => $validate_state,
        ),
      );
    }
  }

  // Enable login plugins.
  if (count($login_plugins) >= 1) {
    $form['tfa_login'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Login plugins'),
      '#options' => $login_plugins,
      '#default_value' => variable_get('tfa_login_plugins', array()),
      '#description' => t('Plugins that can allow a user to skip the TFA process. If any plugin returns true the user will not be required to follow TFA. <strong>Use with caution.</strong>'),
      '#states' => $enabled_state,
    );
  }

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}

/**
 * Admin form submission handler.
 */
function tfa_admin_settings_submit($form, &$form_state) {
  drupal_set_message(t('Configuration saved'));
  $values = $form_state['values'];
  // Set enabled.
  if (!empty($values['tfa_enabled'])) {
    variable_set('tfa_enabled', $values['tfa_enabled']);
  }
  else {
    variable_del('tfa_enabled');
    return;
  }

  // Set main validation plugins.
  variable_set('tfa_validate_plugin', $values['tfa_validate']);

  // Set fallback plugins.
  $fallback = array();
  if (!empty($values['tfa_fallback'])) {
    foreach ($values['tfa_fallback'] as $key => $data) {
      if ($values['tfa_validate'] !== $key && $data['enable']) {
        $fallback[$data['weight']] = $key;
      }
    }
  }
  // Always include the default validation plugin in case the context plugins
  // are altered. TFA will skip it if it's the same as validation at runtime.
  $fallback[-999] = $values['tfa_validate'];
  ksort($fallback);
  variable_set('tfa_fallback_plugins', $fallback);

  // Set login plugins.
  $login = array();
  if (!empty($values['tfa_login'])) {
    foreach ($values['tfa_login'] as $key => $enabled) {
      if ($enabled) {
        $login[] = $key;
      }
    }
  }
  variable_set('tfa_login_plugins', $login);
}

/**
 * Get human-readable types.
 */
function _tfa_class_types($class) {
  $types = array();
  if (in_array('TfaValidationPluginInterface', class_implements($class))) {
    $types[] = 'validation';
  }
  if (in_array('TfaSendPluginInterface', class_implements($class))) {
    $types[] = 'send';
  }
  if (in_array('TfaLoginPluginInterface', class_implements($class))) {
    $types[] = 'login';
  }
  if (empty($types)) {
    $types[] = 'standard';
  }
  return implode(', ', $types);
}
