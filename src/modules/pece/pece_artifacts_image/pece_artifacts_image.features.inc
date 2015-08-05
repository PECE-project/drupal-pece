<?php
/**
 * @file
 * pece_artifacts_image.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function pece_artifacts_image_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function pece_artifacts_image_node_info() {
  $items = array(
    'pece_artifact_image' => array(
      'name' => t('Artifact - Image'),
      'base' => 'node_content',
      'description' => t('The PECE\'s image artifact.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
