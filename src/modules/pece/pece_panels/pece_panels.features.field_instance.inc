<?php
/**
 * @file
 * pece_panels.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function pece_panels_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'fieldable_panels_pane-node-field_node'.
  $field_instances['fieldable_panels_pane-node-field_node'] = array(
    'bundle' => 'node',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Select the content to show inside this block.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'fieldable_panels_pane',
    'entityconnect_show_add_icon' => 0,
    'entityconnect_show_edit_icon' => 0,
    'entityconnect_unload_add' => 1,
    'entityconnect_unload_edit' => 1,
    'fences_wrapper' => 'no_wrapper',
    'field_name' => 'field_node',
    'label' => 'Conteúdo',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'entityreference',
      'settings' => array(
        'match_operator' => 'CONTAINS',
        'path' => '',
        'size' => 60,
      ),
      'type' => 'entityreference_autocomplete',
      'weight' => -4,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Conteúdo');
  t('Select the content to show inside this block.');

  return $field_instances;
}
