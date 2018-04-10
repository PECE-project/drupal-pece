<?php
/**
 * @file
 * pece_photo_essay.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function pece_photo_essay_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_node:pece_photo_essay:page_manager_selection';
  $strongarm->value = 'node:pece_photo_essay:default';
  $export['panelizer_node:pece_photo_essay:page_manager_selection'] = $strongarm;

  return $export;
}
