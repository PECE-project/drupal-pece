<?php

/**
 * @file
 * pece_frontpage_slideshow.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function pece_frontpage_slideshow_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function pece_frontpage_slideshow_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function pece_frontpage_slideshow_image_default_styles() {
  $styles = array();

  // Exported image style: pece_frontpage_image_short.
  $styles['pece_frontpage_image_short'] = array(
    'label' => 'PECE Frontpage Image short',
    'effects' => array(
      3 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 960,
          'height' => 230,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: pece_frontpage_image_style.
  $styles['pece_frontpage_image_style'] = array(
    'label' => 'PECE Frontpage Image Style',
    'effects' => array(
      3 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 960,
          'height' => 460,
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
function pece_frontpage_slideshow_node_info() {
  $items = array(
    'frontpage_image_slideshow' => array(
      'name' => t('Slideshow Image'),
      'base' => 'node_content',
      'description' => t('Contribute images for the front-page slideshow.'),
      'has_title' => '1',
      'title_label' => t('Slideshow'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
