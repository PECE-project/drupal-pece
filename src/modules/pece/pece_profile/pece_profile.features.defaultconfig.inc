<?php
/**
 * @file
 * pece_profile.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function pece_profile_defaultconfig_features() {
  return array(
    'pece_profile' => array(
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function pece_profile_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access user profiles'.
  $permissions['access user profiles'] = array(
    'name' => 'access user profiles',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'user',
  );

  return $permissions;
}
