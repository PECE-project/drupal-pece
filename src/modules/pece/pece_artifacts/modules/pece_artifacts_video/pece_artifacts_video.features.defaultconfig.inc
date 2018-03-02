<?php
/**
 * @file
 * pece_artifacts_video.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function pece_artifacts_video_defaultconfig_features() {
  return array(
    'pece_artifacts_video' => array(
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function pece_artifacts_video_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create pece_artifact_video content'.
  $permissions['create pece_artifact_video content'] = array(
    'name' => 'create pece_artifact_video content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own pece_artifact_video content'.
  $permissions['delete own pece_artifact_video content'] = array(
    'name' => 'delete own pece_artifact_video content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any pece_artifact_video content'.
  $permissions['edit any pece_artifact_video content'] = array(
    'name' => 'edit any pece_artifact_video content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit own pece_artifact_video content'.
  $permissions['edit own pece_artifact_video content'] = array(
    'name' => 'edit own pece_artifact_video content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  return $permissions;
}
