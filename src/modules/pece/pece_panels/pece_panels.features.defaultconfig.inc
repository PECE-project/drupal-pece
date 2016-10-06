<?php
/**
 * @file
 * pece_panels.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function pece_panels_defaultconfig_features() {
  return array(
    'pece_panels' => array(
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function pece_panels_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'bypass access in place editing'.
  $permissions['bypass access in place editing'] = array(
    'name' => 'bypass access in place editing',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'panels',
  );

  // Exported permission: 'use panels in place editing'.
  $permissions['use panels in place editing'] = array(
    'name' => 'use panels in place editing',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'panels',
  );

  return $permissions;
}
