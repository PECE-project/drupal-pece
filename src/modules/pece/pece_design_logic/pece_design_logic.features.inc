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
    'design_logic_design_logic_pages' => array(
      'machine_name' => 'design_logic_design_logic_pages',
      'entity_type' => 'design_logic',
      'name' => 'design_logic_pages',
      'label' => 'Design Logic Pages',
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
      'label' => 'Design Logic',
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
