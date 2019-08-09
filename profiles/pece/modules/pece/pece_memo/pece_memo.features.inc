<?php

/**
 * @file
 * pece_memo.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function pece_memo_ctools_plugin_api($module = NULL, $api = NULL) {
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
function pece_memo_node_info() {
  $items = array(
    'pece_memo' => array(
      'name' => t('Memo'),
      'base' => 'node_content',
      'description' => t('PECE\'s memo content type.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
