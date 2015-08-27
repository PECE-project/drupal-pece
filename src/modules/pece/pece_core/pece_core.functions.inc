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
