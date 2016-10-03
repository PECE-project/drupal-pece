<?php
/**
 * @file
 * pece_essay.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function pece_essay_defaultconfig_features() {
  return array(
    'pece_essay' => array(
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function pece_essay_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create pece_essay content'.
  $permissions['create pece_essay content'] = array(
    'name' => 'create pece_essay content',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any pece_essay content'.
  $permissions['delete any pece_essay content'] = array(
    'name' => 'delete any pece_essay content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own pece_essay content'.
  $permissions['delete own pece_essay content'] = array(
    'name' => 'delete own pece_essay content',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any pece_essay content'.
  $permissions['edit any pece_essay content'] = array(
    'name' => 'edit any pece_essay content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own pece_essay content'.
  $permissions['edit own pece_essay content'] = array(
    'name' => 'edit own pece_essay content',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  return $permissions;
}
