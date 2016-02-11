<?php
/**
 * @file
 * pece_substantive_logic.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function pece_substantive_logic_ctools_plugin_api($module = NULL, $api = NULL) {
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
function pece_substantive_logic_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function pece_substantive_logic_node_info() {
  $items = array(
    'pece_sub_logic' => array(
      'name' => t('Substantive Logic'),
      'base' => 'node_content',
      'description' => t('PECE\'s Substantive Logic content type.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
