<?php
/**
 * @file
 * pece_groups.features.og_features_role.inc
 */

/**
 * Implements hook_og_features_default_roles().
 */
function pece_groups_og_features_default_roles() {
  $roles = array();

  // Exported OG Role: 'node:pece_group:Contributor'.
  $roles['node:pece_group:Contributor'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'pece_group',
    'name' => 'Contributor',
  );

  // Exported OG Role: 'node:pece_group:Researcher'.
  $roles['node:pece_group:Researcher'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'pece_group',
    'name' => 'Researcher',
  );

  // Exported OG Role: 'node:pece_group:group administrator'.
  $roles['node:pece_group:group administrator'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'pece_group',
    'name' => 'group administrator',
  );

  return $roles;
}
