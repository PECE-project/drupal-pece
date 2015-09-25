<?php
/**
 * @file
 * pece_artifacts_image.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function pece_artifacts_image_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_pece_media_image'
  $field_bases['field_pece_media_image'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_pece_media_image',
    'indexes' => array(
      'fid' => array(
        0 => 'fid',
      ),
    ),
    'locked' => 0,
    'module' => 'image',
    'settings' => array(
      'default_image' => 0,
      'profile2_private' => FALSE,
      'uri_scheme' => 'private',
    ),
    'translatable' => 0,
    'type' => 'image',
  );

  return $field_bases;
}
