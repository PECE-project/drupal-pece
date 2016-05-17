<?php
/**
 * @file
 * pece_node_expiration.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function pece_node_expiration_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_expire_date_entry_elements';
  $strongarm->value = '0';
  $export['node_expire_date_entry_elements'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_expire_date_format';
  $strongarm->value = 'm-d-Y';
  $export['node_expire_date_format'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_expire_handle_content_expiry';
  $strongarm->value = '2';
  $export['node_expire_handle_content_expiry'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_expire_past_date_allowed';
  $strongarm->value = 0;
  $export['node_expire_past_date_allowed'] = $strongarm;

  return $export;
}
