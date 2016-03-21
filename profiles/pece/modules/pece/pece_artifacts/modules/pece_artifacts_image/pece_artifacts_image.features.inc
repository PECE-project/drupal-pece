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
  if ($module == "panelizer" && $api == "panelizer") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function pece_artifacts_image_image_default_styles() {
  $styles = array();

  // Exported image style: pece_artifact_image_large.
  $styles['pece_artifact_image_large'] = array(
    'label' => 'PECE Artifact Image Large',
    'effects' => array(
      1 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 550,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function pece_artifacts_image_node_info() {
  $items = array(
    'pece_artifact_image' => array(
      'name' => t('Artifact - Image'),
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
