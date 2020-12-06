<?php

/**
 * @file
 * pece_core.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function pece_core_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "file_entity" && $api == "file_default_displays") {
    return array("version" => "1");
  }
  if ($module == "file_entity" && $api == "file_type") {
    return array("version" => "1");
  }
  if ($module == "page_manager" && $api == "pages_default") {
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
function pece_core_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function pece_core_image_default_styles() {
  $styles = array();

  // Exported image style: pece_mini_teaser.
  $styles['pece_mini_teaser'] = array(
    'label' => 'PECE Mini Teaser',
    'effects' => array(
      6 => array(
        'name' => 'manualcrop_crop',
        'data' => array(
          'width' => 70,
          'height' => 70,
          'keepproportions' => 1,
          'reuse_crop_style' => 'panopoly_image_full',
          'style_name' => 'pece_mini_teaser',
        ),
        'weight' => -10,
      ),
      5 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 70,
          'height' => 70,
        ),
        'weight' => -9,
      ),
    ),
  );

  // Exported image style: pece_most_recent.
  $styles['pece_most_recent'] = array(
    'label' => 'PECE Most Recent',
    'effects' => array(
      4 => array(
        'name' => 'manualcrop_crop',
        'data' => array(
          'width' => 120,
          'height' => 120,
          'keepproportions' => 1,
          'reuse_crop_style' => 'panopoly_image_full',
          'style_name' => 'pece_most_recent',
        ),
        'weight' => -10,
      ),
      3 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 120,
          'height' => 120,
        ),
        'weight' => -9,
      ),
    ),
  );

  // Exported image style: pece_thumbnail.
  $styles['pece_thumbnail'] = array(
    'label' => 'PECE Thumbnail',
    'effects' => array(
      2 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 70,
          'height' => 70,
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
function pece_core_node_info() {
  $items = array(
    'pece_fieldsite' => array(
      'name' => t('Fieldsite'),
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
