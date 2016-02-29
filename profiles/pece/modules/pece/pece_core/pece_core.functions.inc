<?php

/**
 * Helper functions for PECE Core module.
 */

/**
 * Custom function to add modal
 */
function pece_core_modal_presets($modal_name, $width, $height) {
  // Include the CTools tools that we need.
  ctools_include('ajax');
  ctools_include('modal');

  $theme_default = variable_get('theme_default');

  $settings = array(
    $modal_name => array(
      'modalSize' => array(
        'type' => 'fixed',
        'width' => $width,
        'height' => $height,
      ),
      'modalOptions' => array(
        'backdropClose' => TRUE,
      ),
      'loadingText' => t('Loading...'),
      'closeText' => t('close'),
      'closeImage' => '',
      'throbber' => theme('image', array(
        'path' => drupal_get_path('theme', $theme_default) . '/img/throbber.gif',
        'title' => t('Loading.'),
        'alt' => t('Loading'),
      )),
    ),
  );
  drupal_add_js($settings, 'setting');

  // Add CTools' javascript to the page.
  ctools_modal_add_js();
}

/**
 * Helper method to perform jQuery.extend like default settings.
 */
function pece_array_extend() {
  $arrays = func_get_args();
  $base = array_shift($arrays);
  foreach ($arrays as $array) {
    reset($base);
    while (list($key, $value) = @each($array)) {
      if (is_array($value) && @is_array($base[$key])) {
        $base[$key] = pece_array_extend($base[$key], $value);
      } else {
        $base[$key] = $value;
      }
    }
  }
  return $base;
}
