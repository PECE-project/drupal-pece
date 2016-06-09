<?php
/**
 * @file
 * pece_photo_essay.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function pece_photo_essay_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_photo_essay_items'.
  $field_bases['field_photo_essay_items'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_photo_essay_items',
    'indexes' => array(
      'target_id' => array(
        0 => 'target_id',
      ),
    ),
    'locked' => 0,
    'module' => 'entityreference',
    'settings' => array(
      'handler' => 'base',
      'handler_settings' => array(
        'behaviors' => array(
          'views-select-list' => array(
            'status' => 0,
          ),
        ),
        'sort' => array(
          'type' => 'none',
        ),
        'target_bundles' => array(
          'photo_essay_item' => 'photo_essay_item',
        ),
      ),
      'profile2_private' => FALSE,
      'target_type' => 'photo_essay_item',
    ),
    'translatable' => 0,
    'type' => 'entityreference',
  );

  return $field_bases;
}
