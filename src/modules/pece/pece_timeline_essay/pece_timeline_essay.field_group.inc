<?php

/**
 * @file
 * pece_timeline_essay.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function pece_timeline_essay_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = TRUE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_pece_timeline_media|pece_timeline_essay_item|pece_timeline_essay_item|form';
  $field_group->group_name = 'group_pece_timeline_media';
  $field_group->entity_type = 'pece_timeline_essay_item';
  $field_group->bundle = 'pece_timeline_essay_item';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Media',
    'weight' => '5',
    'children' => array(
      0 => 'field_image_credits',
      1 => 'field_pece_timeline_caption',
      2 => 'field_pece_timeline_media',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-pece-timeline-media field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_pece_timeline_media|pece_timeline_essay_item|pece_timeline_essay_item|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_settings|node|pece_timeline_essay|form';
  $field_group->group_name = 'group_settings';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'pece_timeline_essay';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Group settings',
    'weight' => '7',
    'children' => array(
      0 => 'group_content_access',
      1 => 'og_group_ref',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Group settings',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-settings field-group-fieldset',
        'description' => 'Be aware that this content might become <strong>Visible</strong> to anyone if you assign it to an <strong>Open Group</strong>.
',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $field_groups['group_settings|node|pece_timeline_essay|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Group settings');
  t('Media');

  return $field_groups;
}
