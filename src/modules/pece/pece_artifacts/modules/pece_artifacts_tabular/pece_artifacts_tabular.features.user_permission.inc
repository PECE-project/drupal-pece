<?php

/**
 * @file
 * pece_artifacts_tabular.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function pece_artifacts_tabular_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access direct download file'.
  $permissions['access direct download file'] = array(
    'name' => 'access direct download file',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'download_file',
  );

  return $permissions;
}
