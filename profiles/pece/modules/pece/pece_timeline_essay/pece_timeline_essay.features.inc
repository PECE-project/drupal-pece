<?php

/**
 * @file
 * pece_timeline_essay.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function pece_timeline_essay_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  if ($module == "panelizer" && $api == "panelizer") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function pece_timeline_essay_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_eck_bundle_info().
 */
function pece_timeline_essay_eck_bundle_info() {
  $items = array(
    'pece_timeline_essay_item_pece_timeline_essay_item' => array(
      'machine_name' => 'pece_timeline_essay_item_pece_timeline_essay_item',
      'entity_type' => 'pece_timeline_essay_item',
      'name' => 'pece_timeline_essay_item',
      'label' => 'Timeline Essay Item',
      'config' => array(),
    ),
  );
  return $items;
}

/**
 * Implements hook_eck_entity_type_info().
 */
function pece_timeline_essay_eck_entity_type_info() {
  $items = array(
    'pece_timeline_essay_item' => array(
      'name' => 'pece_timeline_essay_item',
      'label' => 'Timeline Essay Item',
      'properties' => array(
        'title' => array(
          'label' => 'Title',
          'type' => 'text',
          'behavior' => 'title',
        ),
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
        'uuid' => array(
          'label' => 'UUID',
          'type' => 'text',
          'behavior' => 'uuid',
        ),
      ),
    ),
  );
  return $items;
}

/**
 * Implements hook_node_info().
 */
function pece_timeline_essay_node_info() {
  $items = array(
    'pece_timeline_essay' => array(
      'name' => t('Timeline Essay'),
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
