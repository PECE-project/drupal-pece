<?php
/**
 * @file
 * pece_amber.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function pece_amber_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer amber'.
  $permissions['administer amber'] = array(
    'name' => 'administer amber',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'amber',
  );

  return $permissions;
}
