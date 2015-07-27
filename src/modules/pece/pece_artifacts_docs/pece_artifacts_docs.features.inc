<?php
/**
 * @file
 * pece_artifacts_docs.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function pece_artifacts_docs_ctools_plugin_api($module = NULL, $api = NULL) {
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
function pece_artifacts_docs_node_info() {
  $items = array(
    'pece_artifact_fieldnote' => array(
      'name' => t('Fieldnote'),
      'base' => 'node_content',
      'description' => t('The PECE\'s Artifact Fieldnote content type.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
