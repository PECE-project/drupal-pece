<?php

/**
 * @file
 * pece_artifacts_spdsheet.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function pece_artifacts_spdsheet_defaultconfig_features() {
  return array(
    'pece_artifacts_spdsheet' => array(
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function pece_artifacts_spdsheet_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create pece_artifact_spdsheet content'.
  $permissions['create pece_artifact_spdsheet content'] = array(
    'name' => 'create pece_artifact_spdsheet content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any pece_artifact_spdsheet content'.
  $permissions['delete any pece_artifact_spdsheet content'] = array(
    'name' => 'delete any pece_artifact_spdsheet content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own pece_artifact_spdsheet content'.
  $permissions['delete own pece_artifact_spdsheet content'] = array(
    'name' => 'delete own pece_artifact_spdsheet content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any pece_artifact_spdsheet content'.
  $permissions['edit any pece_artifact_spdsheet content'] = array(
    'name' => 'edit any pece_artifact_spdsheet content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own pece_artifact_spdsheet content'.
  $permissions['edit own pece_artifact_spdsheet content'] = array(
    'name' => 'edit own pece_artifact_spdsheet content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  return $permissions;
}
