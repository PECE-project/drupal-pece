<?php

/**
 * @file
 * pece_artifacts_tabular.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function pece_artifacts_tabular_ctools_plugin_api($module = NULL, $api = NULL) {
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
function pece_artifacts_tabular_node_info() {
  $items = array(
    'pece_artifact_tabular' => array(
      'name' => t('Artifact - Tabular data'),
      'base' => 'node_content',
      'description' => t('An artifact is the basic unit of data on PECE. Artifacts represent materials that an ethnographer determines to be data relevant to the site.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
