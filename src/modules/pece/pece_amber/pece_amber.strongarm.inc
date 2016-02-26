<?php
/**
 * @file
 * pece_amber.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function pece_amber_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'amber_alternate_backends';
  $strongarm->value = array();
  $export['amber_alternate_backends'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'amber_available_action';
  $strongarm->value = '0';
  $export['amber_available_action'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'amber_available_action_hover';
  $strongarm->value = '2';
  $export['amber_available_action_hover'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'amber_aws_access_key';
  $strongarm->value = '';
  $export['amber_aws_access_key'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'amber_aws_bucket';
  $strongarm->value = '';
  $export['amber_aws_bucket'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'amber_aws_region';
  $strongarm->value = 'us-east-1';
  $export['amber_aws_region'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'amber_aws_secret_key';
  $strongarm->value = '';
  $export['amber_aws_secret_key'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'amber_backend';
  $strongarm->value = '0';
  $export['amber_backend'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'amber_content_scanned';
  $strongarm->value = 1;
  $export['amber_content_scanned'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'amber_country_available_action';
  $strongarm->value = '0';
  $export['amber_country_available_action'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'amber_country_available_action_hover';
  $strongarm->value = '2';
  $export['amber_country_available_action_hover'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'amber_country_id';
  $strongarm->value = '';
  $export['amber_country_id'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'amber_country_unavailable_action';
  $strongarm->value = '1';
  $export['amber_country_unavailable_action'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'amber_country_unavailable_action_hover';
  $strongarm->value = '2';
  $export['amber_country_unavailable_action_hover'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'amber_enabled';
  $strongarm->value = 1;
  $export['amber_enabled'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'amber_excluded_formats';
  $strongarm->value = '';
  $export['amber_excluded_formats'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'amber_excluded_sites';
  $strongarm->value = 'localhost';
  $export['amber_excluded_sites'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'amber_last_check_run';
  $strongarm->value = 1456493811;
  $export['amber_last_check_run'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'amber_max_disk';
  $strongarm->value = '1000';
  $export['amber_max_disk'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'amber_max_file';
  $strongarm->value = '1000';
  $export['amber_max_file'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'amber_perma_apikey';
  $strongarm->value = '';
  $export['amber_perma_apikey'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'amber_perma_server_api_url';
  $strongarm->value = 'http://api.perma.cc';
  $export['amber_perma_server_api_url'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'amber_perma_server_url';
  $strongarm->value = 'http://perma.cc';
  $export['amber_perma_server_url'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'amber_storage_location';
  $strongarm->value = 'sites/default/files/amber';
  $export['amber_storage_location'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'amber_timegate';
  $strongarm->value = 'http://timetravel.mementoweb.org/timegate';
  $export['amber_timegate'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'amber_unavailable_action';
  $strongarm->value = '1';
  $export['amber_unavailable_action'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'amber_unavailable_action_hover';
  $strongarm->value = '2';
  $export['amber_unavailable_action_hover'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'amber_update_strategy';
  $strongarm->value = '0';
  $export['amber_update_strategy'] = $strongarm;

  return $export;
}
