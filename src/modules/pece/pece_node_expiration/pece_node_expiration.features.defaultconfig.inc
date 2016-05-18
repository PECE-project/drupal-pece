<?php
/**
 * @file
 * pece_node_expiration.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function pece_node_expiration_defaultconfig_features() {
  return array(
    'pece_node_expiration' => array(
      'strongarm' => 'strongarm',
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_strongarm().
 */
function pece_node_expiration_defaultconfig_strongarm() {
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

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function pece_node_expiration_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer node expire'.
  $permissions['administer node expire'] = array(
    'name' => 'administer node expire',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node_expire',
  );

  // Exported permission: 'edit node expire'.
  $permissions['edit node expire'] = array(
    'name' => 'edit node expire',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
    ),
    'module' => 'node_expire',
  );

  return $permissions;
}
