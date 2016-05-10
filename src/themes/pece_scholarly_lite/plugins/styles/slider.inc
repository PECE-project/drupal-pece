<?php

/**
 * @file
 * Definition of the Slider panel style.
 */

$plugin = array(
  'title' => t('Slider'),
  'description' => t('Slider options.'),
  'render pane' => 'slider_pane_style',
);

/**
 * Theme function for the plugin style.
 */
function theme_slider_pane_style(&$variables) {
  $pane = $variables['pane'];
  $html_id = drupal_html_id('panels-pane-' . $pane->pid);
  $variables['attributes_array']['id'] = $html_id;

  $slider_selector = '#' . $html_id . ' .view-content';

  $theme_path = drupal_get_path('theme', 'pece_scholarly_lite');
  drupal_add_js($theme_path . '/assets/lib/slick-carousel/slick/slick.js');
  drupal_add_js($theme_path . '/assets/js/slider.js');
  drupal_add_js(array('peceSlider' => array($slider_selector => array())), 'setting');

  return theme('panels_pane', $variables);
}
