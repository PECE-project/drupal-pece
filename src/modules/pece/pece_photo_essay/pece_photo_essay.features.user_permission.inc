<?php

/**
 * @file
 * pece_photo_essay.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function pece_photo_essay_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create pece_photo_essay content'.
  $permissions['create pece_photo_essay content'] = array(
    'name' => 'create pece_photo_essay content',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any pece_photo_essay content'.
  $permissions['delete any pece_photo_essay content'] = array(
    'name' => 'delete any pece_photo_essay content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own pece_photo_essay content'.
  $permissions['delete own pece_photo_essay content'] = array(
    'name' => 'delete own pece_photo_essay content',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own pece_photo_essay content'.
  $permissions['edit own pece_photo_essay content'] = array(
    'name' => 'edit own pece_photo_essay content',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'set pece_photo_essay published on date'.
  $permissions['set pece_photo_essay published on date'] = array(
    'name' => 'set pece_photo_essay published on date',
    'roles' => array(),
    'module' => 'publication_date',
  );

  return $permissions;
}
