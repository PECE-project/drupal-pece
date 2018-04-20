<?php
/**
 * @file
 * pece_profile.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function pece_profile_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'realname_pattern';
  $strongarm->value = '[user:profile-pece-profile-main:field_pece_full_name]';
  $export['realname_pattern'] = $strongarm;

  return $export;
}
