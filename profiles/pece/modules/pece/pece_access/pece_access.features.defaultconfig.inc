<?php
/**
 * @file
 * pece_access.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function pece_access_defaultconfig_features() {
  return array(
    'pece_access' => array(
      'strongarm' => 'strongarm',
    ),
  );
}

/**
 * Implements hook_defaultconfig_strongarm().
 */
function pece_access_defaultconfig_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_group_manager_full_access';
  $strongarm->value = 0;
  $export['og_group_manager_full_access'] = $strongarm;

  return $export;
}
