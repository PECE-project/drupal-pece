<?php
/**
 * @file
 * pece_design_logic.features.inc
 */

/**
 * Implements hook_eck_bundle_info().
 */
function pece_design_logic_eck_bundle_info() {
  $items = array(
    'design_logic_design_logic' => array(
      'machine_name' => 'design_logic_design_logic',
      'entity_type' => 'design_logic',
      'name' => 'design_logic',
      'label' => 'Design logic',
    ),
  );
  return $items;
}

/**
 * Implements hook_eck_entity_type_info().
 */
function pece_design_logic_eck_entity_type_info() {
  $items = array(
    'design_logic' => array(
      'name' => 'design_logic',
      'label' => 'Design logic',
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
