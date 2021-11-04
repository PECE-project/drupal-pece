<?php

/**
 * Administrative helper functions for PECE Core module.
 */

function pece_core_get_available_perm_names() {
  $permissions = user_permission_get_modules();
  return array_keys($permissions);
}

/**
 * Assign all available permissions for a given user role.
 */
function pece_core_assign_available_perm_by_role($role = '') {
  module_load_include('inc', 'pece_core', 'pece_core.functions');
  $all_perms = pece_core_get_available_perm_names();
  $final_perms = array();
  foreach (array_values($all_perms) as $perm) {
    $final_perms[$perm] = TRUE;
  }
  $perm_setup[$role] = $final_perms;
  // Assign permissions to $role user role.
  return $perm_setup;
}

/**
 * Helper to assign all available permissions for administrator user role.
 */
function pece_core_rebuild_administrator_perms() {
  $permissions = pece_core_assign_available_perm_by_role('administrator');
  pece_set_permissions($permissions);
}
