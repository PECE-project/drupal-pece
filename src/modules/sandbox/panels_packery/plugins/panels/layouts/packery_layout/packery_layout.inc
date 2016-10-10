<?php

$plugin = array(
  'title' => t('Packery'),
  'icon' => 'packery_layout.png',
  'css' => 'packer-layout.css',

  'theme' => 'packery_layout',

  'regions' => array(
    'contentmain' => t('Content'),
  ),
);

/**
 * Preprocess variables for the Packery layout.
 */
function template_preprocess_packery_layout(&$variables, $theme) {
  $display = $variables['display'];
  $renderer = $variables['renderer'];
  $layout = $variables['layout'];
  $path = $layout['path'];
  $config = $variables['settings'];
  $settings = array();

  // Theming.
  // --------

  $css_id = empty($variables['css_id']) ? drupal_html_id($display->uuid) : $variables['css_id'];
  $variables['attributes_array']['id'][] = $css_id;
  $variables['attributes_array']['class'][] = 'panel-display';
  $variables['attributes_array']['class'] = array_merge($variables['attributes_array']['class'], $variables['classes_array']);

  // Save exit. Usually, in situations such as first entering the layout there is no
  // benefit on having this functionallity working and errors happen for the display
  // not having an uuid nor a css_id set.
  if (empty($css_id)) {
    return;
  }


  // Packery.
  // --------

  $container_selector = "#$css_id .panel-panel-inner";
  $item_selector = '.panel-pane';

  libraries_load('packery');
  drupal_add_js($path . '/packery-layout.js');
  drupal_add_css($path . '/packery-layout.css');


  // Packery admin.
  // --------------

  $is_editing = !empty(class_parents($renderer)['panels_renderer_editor']);

  if ($is_editing) {
    $container_selector = "#$css_id .panels-ipe-sort-container";
    $item_selector = '.panels-ipe-portlet-wrapper';

    libraries_load('draggabilly');
    drupal_add_library('system', 'ui.resizable');
    drupal_add_js($path . '/packery-layout-admin.js');
    drupal_add_css($path . '/packery-layout-admin.css');

    $settings['IPEContainer'] = "#panels-ipe-display-{$renderer->clean_key}";
    $settings['IPECacheKeys'] = $renderer->clean_key;
  }


  // Finilize.
  // ---------

  // Initiate settings array.
  $settings['itemSelector'] = $item_selector;
  $settings['items'] = !empty($display->layout_settings['packery_items']) ? json_decode($display->layout_settings['packery_items']) : NULL;
  $settingsArray['packery'][$container_selector] = $settings;
  drupal_add_js($settingsArray, 'setting');
}
