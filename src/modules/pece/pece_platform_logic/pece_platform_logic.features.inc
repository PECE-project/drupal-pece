<?php
/**
 * @file
 * pece_platform_logic.features.inc
 */

/**
 * Implements hook_views_api().
 */
function pece_platform_logic_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_eck_bundle_info().
 */
function pece_platform_logic_eck_bundle_info() {
  $items = array(
    'platform_logic_platform_logic' => array(
      'machine_name' => 'platform_logic_platform_logic',
      'entity_type' => 'platform_logic',
      'name' => 'platform_logic',
      'label' => 'Platform logic',
      'config' => array(),
    ),
  );
  return $items;
}

/**
 * Implements hook_eck_entity_type_info().
 */
function pece_platform_logic_eck_entity_type_info() {
  $items = array(
    'platform_logic' => array(
      'name' => 'platform_logic',
      'label' => 'Platform logic',
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
