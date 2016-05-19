<?php
/**
 * @file
 * pece_biblio.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function pece_biblio_defaultconfig_features() {
  return array(
    'pece_biblio' => array(
      'strongarm' => 'strongarm',
    ),
  );
}

/**
 * Implements hook_defaultconfig_strongarm().
 */
function pece_biblio_defaultconfig_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'biblio_show_openurl_profile_form';
  $strongarm->value = 0;
  $export['biblio_show_openurl_profile_form'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'biblio_show_user_profile_form';
  $strongarm->value = 0;
  $export['biblio_show_user_profile_form'] = $strongarm;

  return $export;
}
