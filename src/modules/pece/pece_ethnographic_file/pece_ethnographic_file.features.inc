<?php
/**
 * @file
 * pece_ethnographic_file.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function pece_ethnographic_file_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
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
 * Implements hook_node_info().
 */
function pece_ethnographic_file_node_info() {
  $items = array(
    'pece_ethnographic_file' => array(
      'name' => t('Ethnographic File'),
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
