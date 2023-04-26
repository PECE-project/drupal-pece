<?php
/**
 * @file
 * pece_project_logic.features.inc
 */

/**
 * Implements hook_views_api().
 */
function pece_project_logic_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_eck_bundle_info().
 */
function pece_project_logic_eck_bundle_info() {
  $items = array(
    'project_logic_project_logic' => array(
      'machine_name' => 'project_logic_project_logic',
      'entity_type' => 'project_logic',
      'name' => 'project_logic',
      'label' => 'Project logic',
      'config' => array(),
    ),
  );
  return $items;
}

/**
 * Implements hook_eck_entity_type_info().
 */
function pece_project_logic_eck_entity_type_info() {
  $items = array(
    'project_logic' => array(
      'name' => 'project_logic',
      'label' => 'Project logic',
      'properties' => array(
        'title' => array(
          'label' => 'Title',
          'type' => 'text',
          'behavior' => 'title',
        ),
      ),
    ),
  );
  return $items;
}
