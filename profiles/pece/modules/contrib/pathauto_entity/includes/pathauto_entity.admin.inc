<?php

/**
 * @file
 * Pathauto Entity admin callback implementations.
 */

/**
 * Form constructor for entity type to be used with Pathauto selection form.
 *
 * @see pathauto_entity_menu()
 *
 * @ingroup forms
 */
function pathauto_entity_available_entity_types_form($form, &$form_state) {
  $form = array();

  $description = '<p><strong>' . t('Choose which entity types form the list below that you would like to use with pathauto.') . '</strong></p>';
  $description .= '<p>' . t('Make sure you have defined <a href="@patterns_url">patterns</a> for all entity types you want to create URL aliases for.', array(
    '@patterns_url' => url('admin/config/search/path/patterns'),
  )) . '</p>';
  $form['description'] = array(
    '#type' => 'markup',
    '#markup' => $description,
  );

  $available_entities = array();
  foreach (pathauto_entity_supported_entity_types() as $entity_type => $entity_info) {
    $available_entities[$entity_type] = $entity_info['label'];
  }

  $active = pathauto_entity_available_entity_types();
  $bundles = variable_get('pathauto_entity_bundles');

  $form['entities'] = array(
    '#type' => 'fieldset',
    '#title' => t('Available entity types'),
    '#weight' => 0,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['entities']['pathauto_entity_available_entity_types'] = array(
    '#type' => 'checkboxes',
    '#ttiel' => t('Select Entities'),
    '#options' => $available_entities,
    '#default_value' => !empty($active) ? $active : array(),
  );

  $form['advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced Settings'),
    '#weight' => 5,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['advanced']['pathauto_entity_bundles'] = array(
    '#type' => 'checkbox',
    '#title' => t('Expose bundles to Delete Aliases'),
    '#description' => t('If your custom entites defaultUri is setup to use the Bundle Type as the default root path and not the Entity Type. Example: bundle/1 <br/> Then select this option, but either way it does not hurt to have this selected.<br/> Note: You will know that you should select this option if you have generated aliases for your custom entities but still see a 0 listed on the Delete Aliases tab.'),
    '#default_value' => !empty($bundles) ? $bundles : FALSE,
  );

  $form['advanced']['pathauto_entity_collapse_fieldsets'] = array(
    '#type' => 'checkbox',
    '#title' => t('Collapse pattern fieldsets'),
    '#description' => t('This options is meant to help with uncluttering the <em>Patterns</em> page by collapsing all fieldsets.'),
    '#default_value' => variable_get('pathauto_entity_collapse_fieldsets', TRUE),
  );

  return system_settings_form($form);
}

/**
 * Form contructor for path alias bulk update form.
 *
 * Overrides Pathauto's pathauto_bulk_update_form() to avoid grouping form
 * options for custom entity types by their 'batch_update_callback' value
 * (see issue https://drupal.org/node/2124379).
 *
 * @see pathauto_menu()
 * @see pathauto_entity_bulk_update_form_submit()
 * @see pathauto_bulk_update_form()
 *
 * @ingroup forms
 */
function pathauto_entity_bulk_update_form() {
  $form['#update_callbacks'] = array();

  $form['update'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Select the types of un-aliased paths for which to generate URL aliases'),
    '#options' => array(),
    '#default_value' => array(),
  );

  $pathauto_settings = module_invoke_all('pathauto', 'settings');
  foreach ($pathauto_settings as $delta => $settings) {
    if (!empty($settings->batch_update_callback)) {
      // We cannot use just $delta value as an array key here,
      // as for $delta == 0 the functionality would break.
      $key = $settings->batch_update_callback . '_' . $delta;
      $form['#update_callbacks'][$key] = $settings;
      $form['update']['#options'][$key] = $settings->groupheader;
    }
  }

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Update'),
  );

  return $form;
}

/**
 * Form submit handler for path alias bulk update form.
 *
 * Overrides Pathauto's pathauto_batch_update_form_submit() handler
 * to allow us to pass $settings data to batch operations.
 *
 * @see pathauto_entity_bulk_update_form()
 * @see pathauto_bulk_update_form_submit()
 *
 * @see pathauto_entity_bulk_update_batch_start()
 * @see pathauto_entity_bulk_update_batch_process()
 * @see pathauto_entity_bulk_update_batch_finished()
 */
function pathauto_entity_bulk_update_form_submit($form, &$form_state) {
  $batch = array(
    'title' => t('Bulk updating URL aliases'),
    'operations' => array(
      array('pathauto_entity_bulk_update_batch_start', array()),
    ),
    'finished' => 'pathauto_entity_bulk_update_batch_finished',
    'file' => drupal_get_path('module', 'pathauto_entity') . '/includes/pathauto_entity.batch.inc',
  );

  foreach ($form_state['values']['update'] as $key => $value) {
    if (!empty($value)) {
      $callback = $form['#update_callbacks'][$key]->batch_update_callback;
      $settings = $form['#update_callbacks'][$key];
      if (!empty($settings->batch_file)) {
        $batch['operations'][] = array('pathauto_entity_bulk_update_batch_process', array($callback, $settings));
      }
      else {
        $batch['operations'][] = array($callback, array());
      }
    }
  }

  batch_set($batch);
}
