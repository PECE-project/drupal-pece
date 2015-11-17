<?php
/**
 * @file
 * pece_artifacts_fieldnote.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function pece_artifacts_fieldnote_ctools_plugin_api($module = NULL, $api = NULL) {
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
 * Implements hook_views_api().
 */
function pece_artifacts_fieldnote_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function pece_artifacts_fieldnote_node_info() {
  $items = array(
    'pece_artifact_fieldnote' => array(
      'name' => t('Artifact - Fieldnote'),
      'base' => 'node_content',
      'description' => t('The PECE\'s Fieldnote artifact.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
