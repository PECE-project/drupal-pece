<?php
/**
 * @file
 * pece_analytics.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function pece_analytics_defaultconfig_features() {
  return array(
    'pece_analytics' => array(
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function pece_analytics_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create pece_analytic content'.
  $permissions['create pece_analytic content'] = array(
    'name' => 'create pece_analytic content',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own pece_analytic content'.
  $permissions['delete own pece_analytic content'] = array(
    'name' => 'delete own pece_analytic content',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own pece_analytic content'.
  $permissions['edit own pece_analytic content'] = array(
    'name' => 'edit own pece_analytic content',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit terms in pece_structured_analytics'.
  $permissions['edit terms in pece_structured_analytics'] = array(
    'name' => 'edit terms in pece_structured_analytics',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'taxonomy',
  );

  return $permissions;
}
