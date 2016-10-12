<?php
/**
 * @file
 * pece_panels.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function pece_panels_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_node'.
  $field_bases['field_node'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_node',
    'indexes' => array(
      'target_id' => array(
        0 => 'target_id',
      ),
    ),
    'locked' => 0,
    'module' => 'entityreference',
    'settings' => array(
      'handler' => 'views',
      'handler_settings' => array(
        'behaviors' => array(
          'er_viewmode_behavior' => array(
            'enabled_viewmodes' => array(
              'card' => 'card',
              'diff_standard' => 0,
              'featured' => 'featured',
              'free_panel' => 0,
              'full' => 0,
              'mini_teaser' => 'mini_teaser',
              'most_recent' => 0,
              'rss' => 0,
              'search_index' => 0,
              'search_result' => 0,
              'teaser' => 'teaser',
              'token' => 0,
            ),
            'status' => 1,
          ),
          'views-select-list' => array(
            'status' => 0,
          ),
        ),
        'view' => array(
          'args' => array(),
          'display_name' => 'entityreference_1',
          'view_name' => 'pece_essay_nodes',
        ),
      ),
      'profile2_private' => FALSE,
      'target_type' => 'node',
    ),
    'translatable' => 0,
    'type' => 'entityreference',
  );

  return $field_bases;
}
