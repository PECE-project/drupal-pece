<?php
/**
 * @file
 * pece_memo.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function pece_memo_defaultconfig_features() {
  return array(
    'pece_memo' => array(
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function pece_memo_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer panelizer node pece_memo breadcrumbs'.
  $permissions['administer panelizer node pece_memo breadcrumbs'] = array(
    'name' => 'administer panelizer node pece_memo breadcrumbs',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node pece_memo content'.
  $permissions['administer panelizer node pece_memo content'] = array(
    'name' => 'administer panelizer node pece_memo content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node pece_memo context'.
  $permissions['administer panelizer node pece_memo context'] = array(
    'name' => 'administer panelizer node pece_memo context',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node pece_memo defaults'.
  $permissions['administer panelizer node pece_memo defaults'] = array(
    'name' => 'administer panelizer node pece_memo defaults',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node pece_memo layout'.
  $permissions['administer panelizer node pece_memo layout'] = array(
    'name' => 'administer panelizer node pece_memo layout',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node pece_memo overview'.
  $permissions['administer panelizer node pece_memo overview'] = array(
    'name' => 'administer panelizer node pece_memo overview',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node pece_memo settings'.
  $permissions['administer panelizer node pece_memo settings'] = array(
    'name' => 'administer panelizer node pece_memo settings',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'panelizer',
  );

  // Exported permission: 'create pece_memo content'.
  $permissions['create pece_memo content'] = array(
    'name' => 'create pece_memo content',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any pece_memo content'.
  $permissions['delete any pece_memo content'] = array(
    'name' => 'delete any pece_memo content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own pece_memo content'.
  $permissions['delete own pece_memo content'] = array(
    'name' => 'delete own pece_memo content',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any pece_memo content'.
  $permissions['edit any pece_memo content'] = array(
    'name' => 'edit any pece_memo content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own pece_memo content'.
  $permissions['edit own pece_memo content'] = array(
    'name' => 'edit own pece_memo content',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  return $permissions;
}
