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

  // Exported permission: 'access administration menu'.
  $permissions['access administration menu'] = array(
    'name' => 'access administration menu',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'admin_menu',
  );

  // Exported permission: 'access administration pages'.
  $permissions['access administration pages'] = array(
    'name' => 'access administration pages',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'system',
  );

  // Exported permission: 'administer feeds'.
  $permissions['administer feeds'] = array(
    'name' => 'administer feeds',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'feeds',
  );

  // Exported permission: 'administer themes'.
  $permissions['administer themes'] = array(
    'name' => 'administer themes',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: 'administer users'.
  $permissions['administer users'] = array(
    'name' => 'administer users',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'user',
  );

  // Exported permission: 'assign all roles'.
  $permissions['assign all roles'] = array(
    'name' => 'assign all roles',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'role_delegation',
  );

  // Exported permission: 'bypass node access'.
  $permissions['bypass node access'] = array(
    'name' => 'bypass node access',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create site notices'.
  $permissions['create site notices'] = array(
    'name' => 'create site notices',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'site_notice',
  );

  // Exported permission: 'delete any site notices'.
  $permissions['delete any site notices'] = array(
    'name' => 'delete any site notices',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'site_notice',
  );

  // Exported permission: 'edit any site notices'.
  $permissions['edit any site notices'] = array(
    'name' => 'edit any site notices',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'site_notice',
  );

  // Exported permission: 'have total control'.
  $permissions['have total control'] = array(
    'name' => 'have total control',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'total_control',
  );

  // Exported permission: 'revert revisions'.
  $permissions['revert revisions'] = array(
    'name' => 'revert revisions',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'view revisions'.
  $permissions['view revisions'] = array(
    'name' => 'view revisions',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  return $permissions;
}
