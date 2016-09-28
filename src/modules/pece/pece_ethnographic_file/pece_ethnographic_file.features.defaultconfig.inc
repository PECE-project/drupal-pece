<?php
/**
 * @file
 * pece_ethnographic_file.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function pece_ethnographic_file_defaultconfig_features() {
  return array(
    'pece_ethnographic_file' => array(
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function pece_ethnographic_file_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create pece_ethnographic_file content'.
  $permissions['create pece_ethnographic_file content'] = array(
    'name' => 'create pece_ethnographic_file content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any pece_ethnographic_file content'.
  $permissions['delete any pece_ethnographic_file content'] = array(
    'name' => 'delete any pece_ethnographic_file content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own pece_ethnographic_file content'.
  $permissions['delete own pece_ethnographic_file content'] = array(
    'name' => 'delete own pece_ethnographic_file content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any pece_ethnographic_file content'.
  $permissions['edit any pece_ethnographic_file content'] = array(
    'name' => 'edit any pece_ethnographic_file content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own pece_ethnographic_file content'.
  $permissions['edit own pece_ethnographic_file content'] = array(
    'name' => 'edit own pece_ethnographic_file content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  return $permissions;
}
