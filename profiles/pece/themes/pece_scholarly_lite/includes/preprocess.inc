<?php
/**
 * @file
 * PECE theme preprocess implementations.
 */

include_once('preprocess.entity.inc');
include_once('preprocess.views.inc');
include_once('preprocess.fields.inc');

/**
 * Implements template_preprocess_panels_pane().
 */
function pece_scholarly_lite_preprocess_panels_pane(&$variables) {
  if (!empty($variables['classes_array'])) {
    $variables['attributes_array'] = isset($variables['attributes_array']) ? $variables['attributes_array'] : array();
    $variables['attributes_array']['class'] = isset($variables['attributes_array']['class']) ? $variables['attributes_array']['class'] : array();
    $variables['attributes_array']['class'] += $variables['classes_array'];
  }
}
