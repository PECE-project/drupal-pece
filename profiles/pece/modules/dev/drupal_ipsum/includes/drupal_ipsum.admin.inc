<?php
/**
 * @file Drupal Ipsum admin pages.
 */

/**
 * Form callback.
 *
 * @see drupal_ipsum_menu().
 */
function drupal_ipsum_admin_config() {
  $form = array();

  // Get base form.
  $drupal_ipsum_form = drupal_ipsum_get_form();

  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Drupal Ipsum settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => t('Text generation settings'),
    '#weight' => 0,
  );

  foreach ($drupal_ipsum_form as $key => $item) {
    $form['settings'][$key] = $item;
  }

  // Get content types.
  $node_types = node_type_get_types();

  $form['content_types'] = array(
    '#type' => 'fieldset',
    '#title' => t('Content Types'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => t('Enable Drupal Ipsum for the following content types:'),
    '#weight' => 1,
  );

  foreach ($node_types as $type => $typeobj) {
    $form['content_types']["drupal_ipsum_{$type}_enable"] = array(
      '#title' => $typeobj->name,
      '#type' => 'checkbox',
      '#default_value' => variable_get("drupal_ipsum_{$type}_enable", FALSE),
    );
  }

  return system_settings_form($form);
}

/**
 * Validate callback.
 *
 * @see drupal_ipsum_admin_config().
 */
function _drupal_ipsum_admin_config_validate($form, &$form_state) {
  if (!is_numeric($form_state['values']['drupal_ipsum_length'])) {
    form_set_error('drupal_ipsum_length', t('Drupal Ipsum text length must be numeric'));
  }
}