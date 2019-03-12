<?php

/**
 * @file
 * pece_timeline_essay.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function pece_timeline_essay_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'eck add pece_timeline_essay_item pece_timeline_essay_item entities'.
  $permissions['eck add pece_timeline_essay_item pece_timeline_essay_item entities'] = array(
    'name' => 'eck add pece_timeline_essay_item pece_timeline_essay_item entities',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'eck',
  );

  // Exported permission: 'eck delete pece_timeline_essay_item pece_timeline_essay_item entities'.
  $permissions['eck delete pece_timeline_essay_item pece_timeline_essay_item entities'] = array(
    'name' => 'eck delete pece_timeline_essay_item pece_timeline_essay_item entities',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'eck',
  );

  // Exported permission: 'eck edit pece_timeline_essay_item pece_timeline_essay_item entities'.
  $permissions['eck edit pece_timeline_essay_item pece_timeline_essay_item entities'] = array(
    'name' => 'eck edit pece_timeline_essay_item pece_timeline_essay_item entities',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'eck',
  );

  // Exported permission: 'eck list pece_timeline_essay_item pece_timeline_essay_item entities'.
  $permissions['eck list pece_timeline_essay_item pece_timeline_essay_item entities'] = array(
    'name' => 'eck list pece_timeline_essay_item pece_timeline_essay_item entities',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'eck',
  );

  // Exported permission: 'eck view pece_timeline_essay_item pece_timeline_essay_item entities'.
  $permissions['eck view pece_timeline_essay_item pece_timeline_essay_item entities'] = array(
    'name' => 'eck view pece_timeline_essay_item pece_timeline_essay_item entities',
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

  return $permissions;
}
