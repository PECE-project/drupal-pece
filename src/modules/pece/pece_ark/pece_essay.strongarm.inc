<?php

/**
 * @file
 * pece_essay.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function pece_ark_strongarm() {
  $export = array();
  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_node:pece_ark_allowed_types';
  $strongarm->value = array(
    'citation-citation' => TRUE,
  );
  $export['panelizer_node:pece_ark_allowed_types'] = $strongarm;

  return $export;
}
