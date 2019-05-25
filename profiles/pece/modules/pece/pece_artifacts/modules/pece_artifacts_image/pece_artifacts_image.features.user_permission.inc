<?php

/**
 * @file
 * pece_artifacts_image.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function pece_artifacts_image_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'delete any image files'.
  $permissions['delete any image files'] = array(
    'name' => 'delete any image files',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'delete own image files'.
  $permissions['delete own image files'] = array(
    'name' => 'delete own image files',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'download any image files'.
  $permissions['download any image files'] = array(
    'name' => 'download any image files',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'download own image files'.
  $permissions['download own image files'] = array(
    'name' => 'download own image files',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'edit any image files'.
  $permissions['edit any image files'] = array(
    'name' => 'edit any image files',
    'roles' => array(
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'file_entity',
  );

  // Exported permission: 'edit own image files'.
  $permissions['edit own image files'] = array(
    'name' => 'edit own image files',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'file_entity',
  );

  return $permissions;
}
