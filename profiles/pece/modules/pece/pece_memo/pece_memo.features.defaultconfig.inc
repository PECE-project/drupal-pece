<?php

/**
 * @file
 * pece_memo.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function pece_memo_defaultconfig_features() {
  return array(
    'pece_memo' => array(
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function pece_memo_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create pece_memo content'.
  $permissions['create pece_memo content'] = array(
    'name' => 'create pece_memo content',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any pece_memo content'.
  $permissions['delete any pece_memo content'] = array(
    'name' => 'delete any pece_memo content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own pece_memo content'.
  $permissions['delete own pece_memo content'] = array(
    'name' => 'delete own pece_memo content',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any pece_memo content'.
  $permissions['edit any pece_memo content'] = array(
    'name' => 'edit any pece_memo content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own pece_memo content'.
  $permissions['edit own pece_memo content'] = array(
    'name' => 'edit own pece_memo content',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  return $permissions;
}
