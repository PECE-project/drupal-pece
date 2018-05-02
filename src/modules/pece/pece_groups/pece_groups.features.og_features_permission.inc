<?php
/**
 * @file
 * pece_groups.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function pece_groups_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:pece_group:administer group'
  $permissions['node:pece_group:administer group'] = array(
    'roles' => array(
      'group administrator' => 'group administrator',
    ),
  );

  // Exported og permission: 'node:pece_group:manage members'
  $permissions['node:pece_group:manage members'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group administrator' => 'group administrator',
    ),
  );

  // Exported og permission: 'node:pece_group:manage permissions'
  $permissions['node:pece_group:manage permissions'] = array(
    'roles' => array(
      'group administrator' => 'group administrator',
    ),
  );

  // Exported og permission: 'node:pece_group:manage roles'
  $permissions['node:pece_group:manage roles'] = array(
    'roles' => array(
      'group administrator' => 'group administrator',
    ),
  );

  return $permissions;
}
