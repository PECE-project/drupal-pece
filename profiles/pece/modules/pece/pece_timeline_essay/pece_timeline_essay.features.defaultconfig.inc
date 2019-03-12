<?php
/**
 * @file
 * pece_timeline_essay.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function pece_timeline_essay_defaultconfig_features() {
  return array(
    'pece_timeline_essay' => array(
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function pece_timeline_essay_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create pece_timeline_essay content'.
  $permissions['create pece_timeline_essay content'] = array(
    'name' => 'create pece_timeline_essay content',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own pece_timeline_essay content'.
  $permissions['delete own pece_timeline_essay content'] = array(
    'name' => 'delete own pece_timeline_essay content',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own pece_timeline_essay content'.
  $permissions['edit own pece_timeline_essay content'] = array(
    'name' => 'edit own pece_timeline_essay content',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
    ),
    'module' => 'node',
  );

  return $permissions;
}
