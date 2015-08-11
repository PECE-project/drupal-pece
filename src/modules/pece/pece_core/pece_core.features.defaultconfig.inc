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
      'user_default_roles' => 'user_default_roles',
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

  return $permissions;
}

/**
 * Implements hook_defaultconfig_user_default_roles().
 */
function pece_core_defaultconfig_user_default_roles() {
  $roles = array();

  // Exported role: Contributor.
  $roles['Contributor'] = array(
    'name' => 'Contributor',
    'weight' => 5,
  );

  // Exported role: Researcher.
  $roles['Researcher'] = array(
    'name' => 'Researcher',
    'weight' => 4,
  );

  return $roles;
}
