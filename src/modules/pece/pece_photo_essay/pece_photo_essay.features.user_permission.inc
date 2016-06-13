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
      'editor' => 'editor',
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
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'eck add pece_photo_essay_item pece_photo_essay_item entities'.
  $permissions['eck add pece_photo_essay_item pece_photo_essay_item entities'] = array(
    'name' => 'eck add pece_photo_essay_item pece_photo_essay_item entities',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'eck',
  );

  // Exported permission: 'eck delete pece_photo_essay_item pece_photo_essay_item entities'.
  $permissions['eck delete pece_photo_essay_item pece_photo_essay_item entities'] = array(
    'name' => 'eck delete pece_photo_essay_item pece_photo_essay_item entities',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'eck',
  );

  // Exported permission: 'eck edit pece_photo_essay_item pece_photo_essay_item entities'.
  $permissions['eck edit pece_photo_essay_item pece_photo_essay_item entities'] = array(
    'name' => 'eck edit pece_photo_essay_item pece_photo_essay_item entities',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'eck',
  );

  // Exported permission: 'eck view pece_photo_essay_item pece_photo_essay_item entities'.
  $permissions['eck view pece_photo_essay_item pece_photo_essay_item entities'] = array(
    'name' => 'eck view pece_photo_essay_item pece_photo_essay_item entities',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
      'editor' => 'editor',
    ),
    'module' => 'eck',
  );

  // Exported permission: 'edit any pece_photo_essay content'.
  $permissions['edit any pece_photo_essay content'] = array(
    'name' => 'edit any pece_photo_essay content',
    'roles' => array(
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
      'editor' => 'editor',
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
