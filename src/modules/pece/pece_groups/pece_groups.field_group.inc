<?php
/**
 * @file
 * pece_groups.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function pece_groups_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_fields|node|pece_group|form';
  $field_group->group_name = 'group_fields';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'pece_group';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Group settings',
    'weight' => '5',
    'children' => array(
      0 => 'group_group',
      1 => 'og_group_ref',
      2 => 'group_content_access',
      3 => 'group_access',
      4 => 'group_register',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-fields field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_fields|node|pece_group|form'] = $field_group;

  return $export;
}
