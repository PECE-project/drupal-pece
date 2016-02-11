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
    'pece_about_page' => array(
      'name' => t('About Page'),
      'base' => 'node_content',
      'description' => t('Use this content type to add the about page.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
