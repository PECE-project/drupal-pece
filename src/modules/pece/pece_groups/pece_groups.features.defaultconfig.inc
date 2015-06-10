<?php
/**
 * @file
 * pece_groups.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function pece_groups_defaultconfig_features() {
  return array(
    'pece_groups' => array(
      'user_default_roles' => 'user_default_roles',
    ),
  );
}

/**
 * Implements hook_defaultconfig_user_default_roles().
 */
function pece_groups_defaultconfig_user_default_roles() {
  $roles = array();

  // Exported role: Contributors.
  $roles['Contributors'] = array(
    'name' => 'Contributors',
    'weight' => 5,
  );

  // Exported role: Researches.
  $roles['Researches'] = array(
    'name' => 'Researches',
    'weight' => 4,
  );

  return $roles;
}
