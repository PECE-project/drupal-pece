<?php
/**
 * @file
 * pece_annotations.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function pece_annotations_defaultconfig_features() {
  return array(
    'pece_annotations' => array(
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function pece_annotations_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create pece_annotation content'.
  $permissions['create pece_annotation content'] = array(
    'name' => 'create pece_annotation content',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any pece_annotation content'.
  $permissions['delete any pece_annotation content'] = array(
    'name' => 'delete any pece_annotation content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own pece_annotation content'.
  $permissions['delete own pece_annotation content'] = array(
    'name' => 'delete own pece_annotation content',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any pece_annotation content'.
  $permissions['edit any pece_annotation content'] = array(
    'name' => 'edit any pece_annotation content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own pece_annotation content'.
  $permissions['edit own pece_annotation content'] = array(
    'name' => 'edit own pece_annotation content',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  return $permissions;
}
