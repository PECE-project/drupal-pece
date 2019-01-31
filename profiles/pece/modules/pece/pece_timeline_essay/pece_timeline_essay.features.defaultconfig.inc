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

  // Exported permission: 'eck add pece_timeline_essay_item pece_timeline_essay_item entities'.
  $permissions['eck add pece_timeline_essay_item pece_timeline_essay_item entities'] = array(
    'name' => 'eck add pece_timeline_essay_item pece_timeline_essay_item entities',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
    ),
    'module' => 'eck',
  );

  // Exported permission: 'eck delete pece_timeline_essay_item pece_timeline_essay_item entities'.
  $permissions['eck delete pece_timeline_essay_item pece_timeline_essay_item entities'] = array(
    'name' => 'eck delete pece_timeline_essay_item pece_timeline_essay_item entities',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
    ),
    'module' => 'eck',
  );

  // Exported permission: 'eck edit pece_timeline_essay_item pece_timeline_essay_item entities'.
  $permissions['eck edit pece_timeline_essay_item pece_timeline_essay_item entities'] = array(
    'name' => 'eck edit pece_timeline_essay_item pece_timeline_essay_item entities',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
    ),
    'module' => 'eck',
  );

  // Exported permission: 'eck list pece_timeline_essay_item pece_timeline_essay_item entities'.
  $permissions['eck list pece_timeline_essay_item pece_timeline_essay_item entities'] = array(
    'name' => 'eck list pece_timeline_essay_item pece_timeline_essay_item entities',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
    ),
    'module' => 'eck',
  );

  // Exported permission: 'eck view pece_timeline_essay_item pece_timeline_essay_item entities'.
  $permissions['eck view pece_timeline_essay_item pece_timeline_essay_item entities'] = array(
    'name' => 'eck view pece_timeline_essay_item pece_timeline_essay_item entities',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
    ),
    'module' => 'eck',
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
