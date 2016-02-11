<?php
/**
 * @file
 * pece_about.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function pece_about_ctools_plugin_api($module = NULL, $api = NULL) {
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
function pece_about_node_info() {
  $items = array(
    'pece_page' => array(
      'name' => t('Page'),
      'base' => 'node_content',
      'description' => t('Basic pages for custom contents.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
