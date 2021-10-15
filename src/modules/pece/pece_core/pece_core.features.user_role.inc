<?php

/**
 * @file
 * pece_core.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function pece_core_user_default_roles() {
  $roles = array();

  // Exported role: Contributor.
  $roles['Contributor'] = array(
    'name' => 'Contributor',
    'weight' => 5,
  );

  // Exported role: Researcher.
  $roles['Researcher'] = array(
    'name' => 'Researcher',
    'weight' => 4,
  );

  // Exported role: platform-director.
  $roles['platform-director'] = array(
    'name' => 'platform-director',
    'weight' => 6,
  );

  // Exported role: data-importer.
  $roles['data-importer'] = array(
    'name' => 'Data Importer',
    'weight' => 7,
  );

  // Exported role: Manager.
  $roles['Manager'] = array(
    'name' => 'Manager',
    'weight' => 7,
  );

  return $roles;
}
