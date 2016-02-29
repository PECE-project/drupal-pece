<?php
/**
 * @file
 * pece_substantive_logic.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function pece_substantive_logic_defaultconfig_features() {
  return array(
    'pece_substantive_logic' => array(
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function pece_substantive_logic_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create pece_sub_logic content'.
  $permissions['create pece_sub_logic content'] = array(
    'name' => 'create pece_sub_logic content',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own pece_sub_logic content'.
  $permissions['delete own pece_sub_logic content'] = array(
    'name' => 'delete own pece_sub_logic content',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own pece_sub_logic content'.
  $permissions['edit own pece_sub_logic content'] = array(
    'name' => 'edit own pece_sub_logic content',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
    ),
    'module' => 'node',
  );

  return $permissions;
}
