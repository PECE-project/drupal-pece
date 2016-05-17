<?php
/**
 * @file
 * pece_node_expiration.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function pece_node_expiration_user_default_permissions() {
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
    ),
    'module' => 'node_expire',
  );

  return $permissions;
}
