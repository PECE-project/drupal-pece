<?php
/**
 * @file
 * pece_biblio.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function pece_biblio_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access biblio content'.
  $permissions['access biblio content'] = array(
    'name' => 'access biblio content',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
      'editor' => 'editor',
    ),
    'module' => 'biblio',
  );

  return $permissions;
}
