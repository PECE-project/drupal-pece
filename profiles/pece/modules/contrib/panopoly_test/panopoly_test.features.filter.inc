<?php
/**
 * @file
 * panopoly_test.features.filter.inc
 */

/**
 * Implements hook_filter_default_formats().
 */
function panopoly_test_filter_default_formats() {
  $formats = array();

  // Exported format: Panopoly Custom.
  $formats['_panopoly_custom'] = array(
    'format' => '_panopoly_custom',
    'name' => 'Panopoly Custom',
    'cache' => 1,
    'status' => 1,
    'weight' => 0,
    'filters' => array(),
  );

  // Exported format: Panopoly Custom Kitchen Sink.
  $formats['_panopoly_custom_kitchen'] = array(
    'format' => '_panopoly_custom_kitchen',
    'name' => 'Panopoly Custom Kitchen Sink',
    'cache' => 1,
    'status' => 1,
    'weight' => 0,
    'filters' => array(),
  );

  return $formats;
}
