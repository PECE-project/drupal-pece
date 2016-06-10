<?php
/**
 * @file
 * pece_photo_essay.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function pece_photo_essay_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_eck_bundle_info().
 */
function pece_photo_essay_eck_bundle_info() {
  $items = array(
    'pece_photo_essay_item_pece_photo_essay_item' => array(
      'machine_name' => 'pece_photo_essay_item_pece_photo_essay_item',
      'entity_type' => 'pece_photo_essay_item',
      'name' => 'pece_photo_essay_item',
      'label' => 'Photo essay item',
      'config' => array(),
    ),
  );
  return $items;
}

/**
 * Implements hook_eck_entity_type_info().
 */
function pece_photo_essay_eck_entity_type_info() {
  $items = array(
    'pece_photo_essay_item' => array(
      'name' => 'pece_photo_essay_item',
      'label' => 'Photo essay item',
      'properties' => array(
        'created' => array(
          'label' => 'Created',
          'type' => 'integer',
          'behavior' => 'created',
        ),
        'changed' => array(
          'label' => 'Changed',
          'type' => 'integer',
          'behavior' => 'changed',
        ),
      ),
    ),
  );
  return $items;
}

/**
 * Implements hook_node_info().
 */
function pece_photo_essay_node_info() {
  $items = array(
    'pece_photo_essay' => array(
      'name' => t('Photo Essay'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
