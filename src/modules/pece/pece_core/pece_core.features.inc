<?php
/**
 * @file
 * pece_core.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function pece_core_ctools_plugin_api($module = NULL, $api = NULL) {
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
function pece_core_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function pece_core_node_info() {
  $items = array(
    'pece_fieldsite' => array(
      'name' => t('Fieldsite'),
      'base' => 'node_content',
      'description' => 'PECE\'s Fieldsite content',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
