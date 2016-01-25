<?php
/**
 * @file
 * pece_security.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function pece_security_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer aes'.
  $permissions['administer aes'] = array(
    'name' => 'administer aes',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'aes',
  );

  // Exported permission: 'view passwords'.
  $permissions['view passwords'] = array(
    'name' => 'view passwords',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'aes',
  );

  return $permissions;
}
