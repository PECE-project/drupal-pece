<?php

/**
 * @file
 * Administration page callbacks for the node_expire module.
 */

/**
 * Administrative settings.
 *
 * @return array
 *   An array containing form items to place on the module settings page.
 */
function node_expire_admin_settings() {
  $form['handle_content_expiry'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Handle content expiry'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['handle_content_expiry']['node_expire_handle_content_expiry'] = array(
    '#type'          => 'radios',
    '#title'         => t('Handle content expiry'),
    '#default_value' => variable_get('node_expire_handle_content_expiry', 2),
    '#options'       => array(
      0 => t('In legacy mode'),
      1 => t('Trigger "Content Expired" event every cron run when the node is expired'),
      2 => t('Trigger "Content Expired" event only once when the node is expired'),
    ),
    '#description'   => t('In non-legacy mode node expiry is set for each node type separately and disabled by default.') . ' ' .
    t('Enable it at Structure -> Content types -> {Your content type} -> Edit -> Publishing options.') . '<br />' .
    t('"Trigger "Content Expired" event only once " option allows to ignore nodes, which already have been processed.') . '<br />' .
    t('Legacy mode means: not possible to allow expiry separately for each particular node type, trigger "Content Expired" event every cron run, legacy data saving'),
  );

  // Visibility.
  $states = array(
    'visible' => array(
      ':input[name="node_expire_handle_content_expiry"]' => array(
        array('value' => '1'),
        array('value' => '2'),
      ),
    ),
  );

  // Variable node_expire_date_entry_elements is not used in legacy mode,
  // so in legacy mode it is safe to keep any of it's value.
  // It is necessary just to take care about proper validation
  // (see node_expire_admin_settings_validate below).
  $form['date_entry_elements'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Date values entry elements'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#states' => $states,
  );
  $form['date_entry_elements']['node_expire_date_entry_elements'] = array(
    '#type'          => 'radios',
    '#title'         => t('Enter date values using'),
    '#default_value' => _node_expire_get_date_entry_elements(),
    '#options'       => array(
      0 => t('Text fields'),
      1 => t('Date popups'),
    ),
    '#description'   => t('"Date popups" option requires Date module to be installed') . ' ' .
    t('with Date Popup enabled. This option is not available in legacy mode.'),
    '#states' => $states,
  );

  $form['past_date_allowed'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Expire date in the past'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['past_date_allowed']['node_expire_past_date_allowed'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Allow expire date in the past'),
    '#default_value' => variable_get('node_expire_past_date_allowed', 0),
    '#description'   => t('Checking this box will allow to save nodes with expire date in the past. This is helpful during site development and testing.'),
  );

  // End of node_expire_admin_settings().
  return system_settings_form($form);
}

/**
 * Validation for the administrative settings form.
 *
 * @param object $form
 *   An associative array containing the structure of the form.
 * @param object $form_state
 *   A keyed array containing the current state of the form.
 */
function node_expire_admin_settings_validate($form, &$form_state) {
  if ($form_state['values']['node_expire_date_entry_elements'] == 1 &&
    $form_state['values']['node_expire_handle_content_expiry'] != 0 &&
    !module_exists('date_popup')) {
    form_set_error('date_entry_elements',
      t('To use "Date popups" option Date module should be installed with Date Popup enabled.')
      // . ' ' . t('This option is not available in legacy mode.')
    );
  }
  // End of node_expire_admin_settings_validate().
}
