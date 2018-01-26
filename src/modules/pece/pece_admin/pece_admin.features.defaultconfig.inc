<?php
/**
 * @file
 * pece_admin.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function pece_admin_defaultconfig_features() {
  return array(
    'pece_admin' => array(
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function pece_admin_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer themes'.
  $permissions['administer themes'] = array(
    'name' => 'administer themes',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: 'access administration menu'.
  $permissions['access administration menu'] = array(
    'name' => 'access administration menu',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'admin_menu',
  );

  return $permissions;
}
