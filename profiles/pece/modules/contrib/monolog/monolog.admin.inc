<?php

/**
 * @file
 * Administrative settings for the Monolog module.
 */

use Monolog\Logger;

/**
 * Returns the logging level options.
 *
 * @return array
 */
function monolog_level_options() {
  return array(
    Logger::DEBUG => t('Debug'),
    Logger::INFO => t('Info'),
    Logger::NOTICE => t('Notice'),
    Logger::WARNING => t('Warning'),
    Logger::ERROR => t('Error'),
    Logger::CRITICAL => t('Critical'),
    Logger::ALERT => t('Alert'),
    Logger::EMERGENCY => t('Emergency'),
  );
}

/**
 * Returns an array of profile options.
 *
 * @return array
 */
function monolog_profile_options() {
  $options = &drupal_static(__FUNCTION__, array());
  if (!$options) {
    $profiles = monolog_profile_load_all();
    foreach ($profiles as $name => $profile) {
      $options[$name] = check_plain($profile->options['label']);
    }
  }
  return $options;
}

/**
 * Returns the handlers associated with a profile.
 *
 * @return array
 */
function monolog_get_profile_handlers($profile) {
  $profile_handlers = array();
  $handler_info = monolog_handler_info_load_all();
  foreach ($profile->options['handlers'] as $handler) {
    if (!isset($handler_info[$handler['handler']])) {
      $handler_info[$handler['handler']] = array('label' => $handler['handler']);
    }
    $profile_handlers[$handler['handler']] = $handler_info[$handler['handler']]['label'];
  }
  return $profile_handlers;
}

/**
 * Channel settings for the Monolog module.
 *
 * @ingroup forms
 */
function monolog_channel_form($form, &$form_state) {
  $channel_info = monolog_channel_info_load_all();
  $channel_profiles = variable_get('monolog_channel_profiles', array());

  $form['description'] = array(
    '#markup' => t('<p>A <strong>channel</strong> identifies which part of the application a record is related to.</p><p>Each channel is associated with a <a href="@href">profile</a> that defines which handlers are used to process the record, for example a <em>syslog handler</em> or <em>stream wrapper handler</em>.</p>', array('@href' => url('admin/config/development/monolog/profile'))),
  );

  $form['channel_table'] = array(
    '#theme' => 'monolog_channel_table',
    '#tree' => TRUE,
    'channel_info' => array(
      '#type' => 'value',
      '#value' => $channel_info,
    ),
    'channels' => array(),
  );

  foreach ($channel_info as $channel_name => $info) {
    if (!isset($channel_profiles[$channel_name])) {
      $channel_profiles[$channel_name] = $info['default profile'];
    }
    $form['channel_table']['channels'][$channel_name]['profile'] = array(
      '#type' => 'select',
      '#options' => monolog_profile_options(),
      '#default_value' => $channel_profiles[$channel_name],
    );
  }

  $form['actions'] = array(
    '#type' => 'actions',
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save channel settings'),
  );

  $form['#submit'] = array('monolog_channel_form_submit');

  return $form;
}

/**
 * Form submission handler for monolog_channel_form().
 */
function monolog_channel_form_submit($form, &$form_state) {
  $channel_profiles = array();
  foreach ($form_state['values']['channel_table']['channels'] as $name => $channel) {
    $channel_profiles[$name] = $channel['profile'];
  }
  variable_set('monolog_channel_profiles', $channel_profiles);
  drupal_set_message(t('The configuration options have been saved.'));
}

/**
 * Returns HTML for the channel table.
 *
 * @param array $variables
 *   An associative array containing:
 *   - element: The FAPI element being themed.
 *
 * @ingroup themeable
 */
function theme_monolog_channel_table(array $variables) {
  $output = '';

  $header = array(
    'channel' => t('Channel'),
    'profile' => t('Logging Profile'),
  );

  $rows = array();
  $channels = $variables['element']['channel_info']['#value'];
  foreach ($channels as $channel_name => $channel_info) {

    // @todo Theme function.
    $label = check_plain($channel_info['label']);
    $machine_name = '<small>' . t('(Machine name: @name)', array('@name' => $channel_name)) . '</small>';
    $descripton = '<div class="description">' . filter_xss_admin($channel_info['description'])  . '</div>';

    $rows[] = array(
      'channel' => $label . ' ' . $machine_name . $descripton,
      'profile' => drupal_render($variables['element']['channels'][$channel_name]['profile']),
    );
  }

  $output .= drupal_render_children($variables['element']);
  $output .= theme('table', array(
    'caption' => t('Logging Channels'),
    'header' => $header,
    'rows' => $rows,
    'empty' => t('There are no available logging channels.'),
    'attributes' => array('id' => 'monolog-channel-table'),
  ));

  return $output;
}

/**
 * Page callback; Displayes all profile pages.
 */
function monolog_profile_page() {
  $build = array();

  $build['description'] = array(
    '#markup' =>  t('<p>A <strong>profile</strong> is a collection of handlers that process the record.</p><p>Common examples of handlers are a <em>syslog handler</em> that routes records to the syslog and a <em>stream wrapper handler</em> that writes records to files and other streams.</p>'),
  );

  $header = array(
    'profile' => t('Profile'),
    'handlers' => t('Handlers'),
    'operations' => t('Operations'),
  );

  $rows = array();
  $profiles = monolog_profile_load_all();
  foreach ($profiles as $name => $profile) {
    $base_path = 'admin/config/development/monolog/profile/' . $name;

    // @todo Make a theme function.
    $label = check_plain($profile->options['label']);
    $machine_name = '<small>' . t('(Machine name: @name)', array('@name' => $profile->name)) . '</small>';

    $row = array(
      'profile' => $label . ' ' . $machine_name,
      'handlers' => join(', ', array_map('check_plain', monolog_get_profile_handlers($profile))),
    );

    if (empty($row['handlers'])) {
      $row['handlers'] = '<em>No handlers</em>';
    }

    $in_db = $profile->export_type & EXPORT_IN_DATABASE;
    $in_code = $profile->export_type & EXPORT_IN_CODE;

    $operations = array();
    $operations[] = array(
      'title' => t('Edit'),
      'href' => $base_path,
    );
    $operations[] = array(
      'title' => t('Export'),
      'href' => $base_path . '/export',
    );
    if ($profile->export_type & EXPORT_IN_DATABASE) {
      $operations[] = array(
        'title' => $profile->export_type & EXPORT_IN_CODE ? t('Revert') : t('Delete'),
        'href' => $base_path . '/delete',
      );
    }

    $row['operations'] = array(
      'data' => array(
        '#theme' => 'links__node_operations',
        '#links' => $operations,
        '#attributes' => array('class' => array('links', 'inline')),
      ),
    );

    $rows[] = $row;
  }

  $build['profiles'] = array(
    '#theme' => 'table',
    '#caption' => t('Logging Profiles'),
    '#empty' => t('There are no logging channels. Add one by clicking the "Add channel" link above.'),
    '#header' => $header,
    '#rows' => $rows,
  );

  return $build;
}

/**
 * Form for adding and editing logging profile configurations.
 *
 * @param stdClass $profile
 *   The logging profile configuration.
 *
 * @ingroup forms
 */
function monolog_profile_form($form, &$form_state, $profile = null) {
  $form['#is_new'] = (null === $profile);
  $base_path = 'admin/config/development/monolog/profile';

  if ($form['#is_new']) {
    $profile = monolog_profile_new();
  }

  $form['#monolog'] = array(
    'profile' => $profile,
  );

  $form['handlers'] = array(
    '#type' => 'value',
    '#value' => $profile->options['handlers'],
  );

  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $profile->options['label'],
    '#description' => t('The human-readable name of the logging profile.'),
    '#required' => TRUE,
    '#maxlength' => 255,
    '#size' => 30,
  );

  $form['name'] = array(
    '#type' => 'machine_name',
    '#default_value' => $profile->name,
    '#maxlength' => 32,
    '#machine_name' => array(
      'exists' => 'monolog_profile_load',
      'source' => array('label'),
    ),
    '#disabled' => !$form['#is_new'],
    '#description' => t('The machine readable name of the logging profile. This value can only contain letters, numbers, and underscores.'),
  );

  if (!$form['#is_new']) {

    $link = l(t('Add handler'), $base_path . '/' . $profile->name . '/handler/add');
    $form['action_link'] = array(
      '#markup' => '<ul class="action-links"><li>' . $link . '</li></ul>',
    );

    $form['channel_table'] = array(
      '#theme' => 'monolog_handler_table',
      '#tree' => TRUE,
      '#monolog' => array(
        'profile' => $profile,
        'handler_info' => monolog_handler_info_load_all(),
      ),
    );

    foreach ($profile->options['handlers'] as $name => $handler) {

      $form['channel_table']['level'][$name] = array(
        '#type' => 'select',
        '#title' => t('Logging level for @handler', array('@handler' => $handler['label'])),
        '#title_display' => 'invisible',
        '#default_value' => $handler['level'],
        '#options' => monolog_level_options(),
      );

      $form['channel_table']['bubble'][$name] = array(
        '#type' => 'select',
        '#title' => t('Bubble setting for @handler', array('@handler' => $handler['label'])),
        '#title_display' => 'invisible',
        '#default_value' => $handler['bubble'],
        '#options' => array(
          1 => t('Yes'),
          0 => t('No'),
        ),
      );

      $form['channel_table']['weight'][$name] = array(
        '#type' => 'select',
        '#title' => t('Weight for @handler', array('@handler' => $handler['label'])),
        '#title_display' => 'invisible',
        '#options' => drupal_map_assoc(range(-10, 10)),
        '#default_value' => $handler['weight'],
        '#attributes' => array('class' => array('monolog-handler-weight')),
      );
    }
  }

  $form['actions'] = array(
    '#type' => '#actions',
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save logging profile'),
  );

  $form['actions']['cancel'] = array(
    '#markup' => l(t('Go back to logging profiles page'), $base_path),
  );

  $form['#submit'][] = 'monolog_profile_form_submit';

  return $form;
}

/**
 * Form submission handler for monolog_profile_form().
 */
function monolog_profile_form_submit($form, &$form_state) {
  $profile = $form['#monolog']['profile'];
  form_state_values_clean($form_state);
  $name = $form_state['values']['name'];
  unset($form_state['values']['name']);

  // Add weight and label from the table.
  $keys = array('level', 'bubble', 'weight');
  foreach ($keys as $key) {
    if (isset($form_state['values']['channel_table'][$key])) {
      foreach ($form_state['values']['channel_table'][$key] as $handler_name => $weight) {
        $form_state['values']['handlers'][$handler_name][$key] = $weight;
      }
    }
  }

  // Removes the raw values passed through the tables.
  unset($form_state['values']['channel_table']);

  $profile->name = $name;
  $profile->options = $form_state['values'];

  try {
    if (!monolog_profile_save($profile)) {
      throw new Exception(t('Error saving logging profile.'));
    }

    $form_state['redirect'] = 'admin/config/development/monolog/profile/' . $name;
    drupal_set_message(t('The configuration options have been saved.'));

  }
  catch (Exception $e) {
    form_set_error(NULL, $e->getMessage());
    watchdog_exception('monolog', $e);
  }
}

/**
 * Returns HTML for the handler table.
 *
 * @param array $variables
 *   An associative array containing:
 *   - element: The FAPI element being themed.
 *
 * @ingroup themeable
 */
function theme_monolog_handler_table(array $variables) {
  $output = '';

  $header = array(
    t('Label'),
    t('Handler'),
    t('Log Level'),
    t('Bubble Messages'),
    t('Weight'),
    t('Operations'),
  );

  $handler_info = $variables['element']['#monolog']['handler_info'];
  $level_options = monolog_level_options();

  $profile = $variables['element']['#monolog']['profile'];

  $rows = array();
  foreach ($profile->options['handlers'] as $name => $handler) {
    $base_path = 'admin/config/development/monolog/profile/' . $profile->name . '/handler/' . $name;

    if (!isset($handler_info[$handler['handler']])) {
      $handler_info[$handler['handler']] = array('label' => $handler['handler']);
    }

    $row = array(
      'label' => check_plain($handler['label']),
      'handler' => check_plain($handler_info[$handler['handler']]['label']),
      'level' => drupal_render($variables['element']['level'][$name]),
      'bubble' => drupal_render($variables['element']['bubble'][$name]),
      'weight' => drupal_render($variables['element']['weight'][$name]),
    );

    $operations = array();
    $operations[] = array(
      'title' => t('Edit'),
      'href' => $base_path . '/edit',
    );
    $operations[] = array(
      'title' => t('Delete'),
      'href' => $base_path . '/delete',
    );

    $row['operations'] = array(
      'data' => array(
        '#theme' => 'links__node_operations',
        '#links' => $operations,
        '#attributes' => array('class' => array('links', 'inline')),
      ),
    );

    $rows[$name] = array(
      'data' => $row,
      'class' => array('draggable'),
    );
  }

  drupal_add_tabledrag('monolog-handler-table', 'order', 'sibling', 'monolog-handler-weight');
  $output .= drupal_render_children($variables['element']);
  $output .= theme('table', array(
    'caption' => t('Logging Handlers'),
    'header' => $header,
    'rows' => $rows,
    'empty' => t('This profile has no handlers. Add one by clicking the "Add handler" link above.'),
    'attributes' => array('id' => 'monolog-handler-table'),
  ));

  return $output;
}

/**
 * Deletes or reverts a profile configuration.
 *
 * @param stdClass $profile
 *   The profile being deleted.
 *
 * @see monolog_profile_delete_form_submit()
 *
 * @ingroup forms
 */
function monolog_profile_delete_form($form, &$form_state, $profile) {
  $form['#monolog'] = array(
    'profile' => $profile,
  );

  $revert = $profile->export_type & EXPORT_IN_CODE;

  $args = array('%label' => $profile->options['label']);
  if ($revert) {
    $prompt = t('Are you sure you want to revert the %label profile?', $args);
  }
  else {
    $prompt = t('Are you sure you want to remove the %label profile?', $args);
  }
  $cancel_path = 'admin/config/development/monolog/profile';
  $warning = t('This action cannot be undone.');
  $yes = $revert ? t('Revert') : t('Delete');

  return confirm_form($form, $prompt, $cancel_path, $warning, $yes, t('Cancel'));
}

/**
 * Form submission handler for monolog_profile_delete_form().
 */
function monolog_profile_delete_form_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    $profile = $form['#monolog']['profile'];
    $args = array('%label' => $profile->options['label']);
    if (monolog_profile_delete($profile)) {
      if ($profile->export_type & EXPORT_IN_CODE) {
        drupal_set_message(t('The %label profile has been reverted.', $args));
      }
      else {
        drupal_set_message(t('The %label profile has been removed.', $args));
      }
    } else {
      drupal_set_message(t('Error removing the %label profile.', $args), 'error');
    }
  }
  $form_state['redirect'] = 'admin/config/development/monolog/profile';
}

/**
 * Export form for profile configurations.
 *
 * @ingroup forms
 */
function monolog_profile_export_form($form, &$form_state, stdClass $profile) {
  // Pop "Add Hander" link off, add profile link.
  $breadcrumb = drupal_get_breadcrumb();
  array_pop($breadcrumb);
  $breadcrumb[] = l($profile->options['label'], 'admin/config/development/monolog/profile/' . $profile->name);
  drupal_set_breadcrumb($breadcrumb);

  $form['back'] = array(
    '#type' => 'link',
    '#title' => t('Go back to logging profiles page'),
    '#href' => 'admin/config/development/monolog/profile',
  );

  // Add the export form.
  $title = t('Logging profile configuration');
  $export = ctools_export_crud_export('monolog_profile', $profile);
  $form = ctools_export_form($form, $form_state, $export, $title);
  return $form;
}

/**
 * Import form for profile configurations.
 *
 * @see monolog_profile_import_form_validate()
 * @see monolog_profile_import_form_submit()
 *
 * @ingroup forms
 */
function monolog_profile_import_form($form, &$form_state) {
  ctools_include('export');

  $form['profile'] = array(
    '#type' => 'value',
    '#value' => '',
  );

  $form['import'] = array(
    '#title' => t('Logging profile configuration code'),
    '#type' => 'textarea',
    '#rows' => 10,
    '#required' => TRUE,
  );

  $form['overwrite'] = array(
    '#title' => t('Allow import to overwrite an existing logging profile configuration.'),
    '#type' => 'checkbox',
  );

  $form['actions'] = array(
    '#type' => 'actions',
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Import configuration'),
  );

  $form['actions']['cancel'] = array(
    '#type' => 'link',
    '#title' => t('Go back to logging profiles page'),
    '#href' => 'admin/config/development/monolog/profile',
  );

  $form['#validate'] = array('monolog_profile_import_form_validate');
  $form['#submit'] = array('monolog_profile_import_form_submit');

  return $form;
}

/**
 * Form validation handler for monolog_profile_import_form().
 */
function monolog_profile_import_form_validate($form, &$form_state) {
  $profile = ctools_export_crud_import('monolog_profile', $form_state['values']['import']);
  if (!is_string($profile)) {
    if (!$form_state['values']['overwrite'] && ctools_export_crud_load('monolog_profile', $profile->name)) {
      form_error($form['import'], t('Logging profile @name already exists', array('@name' => $profile->name)));
    }
    else {
      form_set_value($form['profile'], $profile, $form_state);
    }
  }
  else {
    form_error($form['import'], t('Unable to get an import from the code. Errors reported: @errors', array('@errors' => $profile)));
  }
}

/**
 * Form submission handler for monolog_profile_import_form().
 */
function monolog_profile_import_form_submit($form, &$form_state) {
  try {
    monolog_profile_delete($form_state['values']['profile']);
    if (!monolog_profile_save($form_state['values']['profile'])) {
      throw new \RuntimeException(t('Error importing profile.'));
    }
    $form_state['redirect'] = 'admin/config/development/monolog/profile';
    drupal_set_message(t('The configuration options have been imported.'));
  }
  catch (Exception $e) {
    form_set_error('import', $e->getMessage());
    watchdog_exception('monolog', $e);
  }
}

/**
 * Page callback; Lists the handlers than can be added.
 */
function monolog_handler_page($profile) {
  $build = array();

  $grouped_handlers = array();
  if (function_exists('composer_manager_register_autoloader')) {
    composer_manager_register_autoloader();
  }
  $handlers = monolog_handler_info_load_all();
  foreach ($handlers as $handler_name => $handler_info) {
    $grouped_handlers[$handler_info['group']][$handler_name] = $handler_info;
  }

  $base_path = 'admin/config/development/monolog/profile/' . $profile->name;

  $breadcrumb = drupal_get_breadcrumb();
  $breadcrumb[] = l($profile->options['label'], $base_path);
  drupal_set_breadcrumb($breadcrumb);

  // @todo Theme function.
  $output = '<dl>';
  foreach ($grouped_handlers as $group => $handlers) {
    $output .= '<h3>' . check_plain($group) . '</h3>';
    foreach ($handlers as $handler_name => $handler_info) {
      $path = $base_path . '/handler/add/' . $handler_name;
      $output .= '<dt>' . l($handler_info['label'], $path) . '</dt>';
      $output .= '<dd>' . filter_xss_admin($handler_info['description']) . '</dd>';
    }
  }
  $output .= '</dl>';

  $build['handlers'] = array(
    '#markup' => $output,
  );

  $build['cancel'] = array(
    '#markup' => l(t('Go back to profile edit page'), $base_path),
  );

  return $build;
}

/**
 * Handler settings callback.
 *
 * @param stdClass $profile
 *   The logging profile configuration.
 * @param array|null $handler
 *   The configuration options specific to the handler being edited.
 */
function monolog_handler_form($form, &$form_state, stdClass $profile, array $handler = null) {
  $form['#is_new'] = (null === $handler);

  $handler_name = ($form['#is_new']) ? arg(8) : $handler['handler'];
  if (!$handler_info = monolog_handler_info_load($handler_name)) {
    drupal_not_found();
  }

  // Pop "Add Hander" link off, add profile link.
  $breadcrumb = drupal_get_breadcrumb();
  $add_handler_link = array_pop($breadcrumb);
  $breadcrumb[] = l($profile->options['label'], 'admin/config/development/monolog/profile/' . $profile->name);

  if ($form['#is_new']) {
    $handler = array(
      'handler' => $handler_name,
      'label' => $handler_info['label'],
      'level' => Logger::INFO,
      'bubble' => 1,
      'weight' => 1,
    );

    // Re-add the "Add Handler link".
    $breadcrumb[] = $add_handler_link;
  }

  drupal_set_breadcrumb($breadcrumb);

  $form['#monolog'] = array(
    'profile' => $profile,
    'handler_name' => $handler_name,
  );

  $form['weight'] = array(
    '#type' => 'value',
    '#value' => $handler['weight'],
  );

  $form['label'] = array(
    '#title' => t('Name'),
    '#type' => 'textfield',
    '#default_value' => $handler['label'],
    '#description' => t('The human-readable name of the handler.'),
    '#required' => TRUE,
    '#maxlength' => 255,
    '#size' => 30,
  );

  $form['name'] = array(
    '#type' => 'machine_name',
    '#default_value' => $form['#is_new'] ? '' : arg(7),
    '#maxlength' => 32,
    '#machine_name' => array(
      'exists' => 'monolog_profile_load',
      'source' => array('label'),
    ),
    '#disabled' => !$form['#is_new'],
    '#description' => t('The machine readable name of the handler. This value can only contain letters, numbers, and underscores.'),
  );

  $form['level'] = array(
    '#title' => t('Logging level'),
    '#type' => 'select',
    '#default_value' => $handler['level'],
    '#options' => monolog_level_options(),
    '#description' => t('The minimum severity level of logged messages.'),
  );

  $form['bubble'] = array(
    '#title' => 'Allow messages to bubble up to the next handler in the stack.',
    '#type' => 'checkbox',
    '#default_value' => $handler['bubble'],
    '#description' => t('If unckecked, messages processed by this handler will be blocked from being processed by the subsequent handlers in the stack.'),
  );

  monolog_load_handler_include($handler_info);
  if ($handler_info['settings callback']) {
    if (isset($handler_info['default settings'])) {
      $handler += $handler_info['default settings'];
    }
    $handler_info['settings callback']($form, $form_state, $profile, $handler);
  }

  $form['actions'] = array(
    '#type' => 'actions',
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save handler'),
  );

  $form['actions']['cancel'] = array(
    '#markup' => l(t('Cancel'), 'admin/config/development/monolog/profile/' . $profile->name),
  );

  $form['#submit'] = array('monolog_handler_form_submit');

  return $form;
}

/**
 * Form submission handler for monolog_handler_form().
 */
function monolog_handler_form_submit($form, &$form_state) {
  $profile = $form['#monolog']['profile'];
  form_state_values_clean($form_state);
  $name = $form_state['values']['name'];
  unset($form_state['values']['name']);

  $profile->options['handlers'][$name] = $form_state['values'] += array(
    'handler' => $form['#monolog']['handler_name'],
  );

  try {
    if (!monolog_profile_save($profile)) {
      throw new \RuntimeException(t('Error saving handler.'));
    }

    $form_state['redirect'] = 'admin/config/development/monolog/profile/' . $profile->name;
    drupal_set_message(t('The configuration options have been saved.'));

  }
  catch (Exception $e) {
    form_set_error(NULL, $e->getMessage());
    watchdog_exception('monolog', $e);
  }
}

/**
 * Removes a handler from the logging profile.
 *
 * @param stdClass $profile
 *   The logging profile configuration.
 * @param array $handler
 *   The configuration options specific to the handler being edited.
 *
 * @see monolog_handler_delete_form_submit()
 *
 * @ingroup forms
 */
function monolog_handler_delete_form($form, &$form_state, stdClass $profile, array $handler = null) {
  $form['#monolog'] = array(
    'profile' => $profile,
    'handler' => $handler,
    'handler_name' => arg(7),
  );

  $args = array('%label' => $handler['label']);
  $prompt = t('Are you sure you want to remove the %label handler?', $args);
  $cancel_path = 'admin/config/development/monolog/profile/' . $profile->name;
  $warning = t('This action cannot be undone.');

  // Pop "Add Hander" link off, add profile link.
  $breadcrumb = drupal_get_breadcrumb();
  array_pop($breadcrumb);
  $breadcrumb[] = l($profile->options['label'], $cancel_path);
  drupal_set_breadcrumb($breadcrumb);

  return confirm_form($form, $prompt, $cancel_path, $warning, t('Delete'), t('Cancel'));
}

/**
 * Form submission handler for monolog_handler_delete_form().
 */
function monolog_handler_delete_form_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {

    $profile = $form['#monolog']['profile'];
    $handler = $form['#monolog']['handler'];
    $name = $form['#monolog']['handler_name'];

    unset($profile->options['handlers'][$name]);

    $args = array('%label' => $handler['label']);
    if (monolog_profile_save($profile)) {
      drupal_set_message(t('The %label handler has been removed.', $args));
    } else {
      drupal_set_message(t('Error removing the %label handler.', $args), 'error');
    }
  }
  $form_state['redirect'] = 'admin/config/development/monolog/profile/' . $profile->name;
}
