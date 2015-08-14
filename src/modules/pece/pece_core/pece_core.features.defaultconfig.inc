<?php
/**
 * @file
 * pece_core.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function pece_core_defaultconfig_features() {
  return array(
    'pece_core' => array(
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function pece_core_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access user profiles'.
  $permissions['access user profiles'] = array(
    'name' => 'access user profiles',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'user',
  );

  // Exported permission: 'create files'.
  $permissions['create files'] = array(
    'name' => 'create files',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'create pece_fieldsite content'.
  $permissions['create pece_fieldsite content'] = array(
    'name' => 'create pece_fieldsite content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own pece_fieldsite content'.
  $permissions['delete own pece_fieldsite content'] = array(
    'name' => 'delete own pece_fieldsite content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any pece_fieldsite content'.
  $permissions['edit any pece_fieldsite content'] = array(
    'name' => 'edit any pece_fieldsite content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own pece_fieldsite content'.
  $permissions['edit own pece_fieldsite content'] = array(
    'name' => 'edit own pece_fieldsite content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  return $permissions;
}
