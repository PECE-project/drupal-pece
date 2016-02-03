<?php
/**
 * @file
 * pece_projects.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function pece_projects_defaultconfig_features() {
  return array(
    'pece_projects' => array(
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function pece_projects_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create pece_project content'.
  $permissions['create pece_project content'] = array(
    'name' => 'create pece_project content',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own pece_project content'.
  $permissions['delete own pece_project content'] = array(
    'name' => 'delete own pece_project content',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own pece_project content'.
  $permissions['edit own pece_project content'] = array(
    'name' => 'edit own pece_project content',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
    ),
    'module' => 'node',
  );

  return $permissions;
}
