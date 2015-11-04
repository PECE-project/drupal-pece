<?php
/**
 * @file
 * pece_core.file_default_displays.inc
 */

/**
 * Implements hook_file_default_displays().
 */
function pece_core_file_default_displays() {
  $export = array();

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__mini_teaser__file_field_image';
  $file_display->weight = 0;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'image_style' => 'pece_mini_teaser',
    'image_link' => '',
  );
  $export['image__mini_teaser__file_field_image'] = $file_display;

  return $export;
}
