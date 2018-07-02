<?php
/**
 * @file
 * pece_projects.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function pece_projects_defaultconfig_features() {
  return array(
    'pece_projects' => array(
      'strongarm' => 'strongarm',
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_strongarm().
 */
function pece_projects_defaultconfig_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'date_format_full_date';
  $strongarm->value = 'm/d/Y - H:i';
  $export['date_format_full_date'] = $strongarm;

  return $export;
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function pece_projects_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create pece_project content'.
  $permissions['create pece_project content'] = array(
    'name' => 'create pece_project content',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any pece_project content'.
  $permissions['delete any pece_project content'] = array(
    'name' => 'delete any pece_project content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own pece_project content'.
  $permissions['delete own pece_project content'] = array(
    'name' => 'delete own pece_project content',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any pece_project content'.
  $permissions['edit any pece_project content'] = array(
    'name' => 'edit any pece_project content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own pece_project content'.
  $permissions['edit own pece_project content'] = array(
    'name' => 'edit own pece_project content',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  return $permissions;
}
