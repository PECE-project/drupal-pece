<?php

// function pece_migrate_deploy_apply_content_policy() {
//   $node_bundles = [
//     'pece_artifact_audio',
//     'pece_artifact_bundle',
//     'pece_artifact_fieldnote',
//     'pece_artifact_image',
//     'pece_artifact_pdf',
//     'pece_artifact_text',
//     'pece_artifact_website',
//     'artifact_tabular_data',
//     'artifact_video',
//     'pece_essay',
//     'pece_memo',
//     'pece_photo_essay',
//     'pece_timeline_essay',
//     'pece_annotation',
//     'pece_project',
//     'pece_substantive_logic'
//   ];
//   forEach($node_bundles as $bundle) {
//     $nodes = \Drupal::entityTypeManager()
//               ->getListBuilder('node')
//               ->getStorage()
//               ->loadByProperties([
//                 'type' => $bundle,
//             ]);
//     forEach($nodes as $node) {
//       $node->access_policy = 'pece_content';
//       $node->save();
//     }
//   }
// }

// function pece_migrate_deploy_apply_group_policy() {
//   $groups = \Drupal::entityTypeManager()
//           ->getListBuilder('taxonomy_term')
//           ->getStorage()
//           ->loadByProperties([
//             'vid' => 'groups'
//         ]);
//   forEach($groups as $group) {
//     $group->access_policy = 'pece_group';
//     $group->save();
//   }
// }

  /**
   * Implements hook_deploy_NAME
   *
   * Removes extra groups that were added to artifacts due to an underfiltered query in migration.
   * This hook depends on having added the og_membership table from the PECE v1 site to the PECE v2 site.
   */
function pece_migrate_deploy_remove_extra_group_refs() {
  $db = \Drupal::database();

  // Get d7 to d10 group migration map
  $group_migration_map = $db->query('SELECT sourceid1, destid1 FROM migrate_map_v1_group')->fetchAllKeyed();

  // Get the d7 node id and group id of any organic group memberships not established via the og_group_ref field.
  // An array of arrays, each containing a node id and a group id.
  $d7_memberships_for_removal = $db->query("SELECT etid, gid FROM {og_membership} AS og WHERE field_name = 'og_user_node' AND NOT Exists (SELECT 1 FROM {og_membership} sub WHERE og.gid = sub.gid AND og.etid = sub.etid AND field_name = 'og_group_ref');")->fetchAll(PDO::FETCH_ASSOC);

  // Replace all d7 group ids with d10 group ids
  array_walk($d7_memberships_for_removal, function(&$membership, $index, $migration_map) {
    if (isset($migration_map[$membership['gid']])) {
      $membership['new_gid'] = $migration_map[$membership['gid']];
    }
  }, $group_migration_map);

  // $referenced_groups_by_node is an array, keyed by the nodes that reference groups, with values corresponding to the group references that should be removed from each node.
  $referenced_groups_by_node = array_reduce($d7_memberships_for_removal, function ($carry, $item) {
      if (!isset($carry[$item['etid']])) {
          $carry[$item['etid']] = [];
      }
      // Some groups may have been deleted prior to the migration, so make sure not to add null values to the array.
      // This is possible, apparently because og_membership entries in d7 were not deleted along with groups referenced in the table.
      if (isset($item['new_gid'])) {
        $carry[$item['etid']][] = $item['new_gid'];
      }
      return $carry;
  }, []);

  // Note that nodes_to_update may be a smaller array than $referenced_groups_by_node. We are mostly loading nodes by user id here (the root of the mixup), and there is not a node for each of these ids.
  $nodes_to_update = \Drupal::entityTypeManager()->getListBuilder('node')->getStorage()->loadMultiple(array_keys($referenced_groups_by_node));

  foreach($nodes_to_update as $node_id => $node) {
    $save_needed = FALSE;
    if (!isset($node->field_groups_with_view_access)) {
      continue;
    }
    $group_access_field_items = $node->field_groups_with_view_access;
    $duplicate_values = [];
    for ($i = count($group_access_field_items) -1; $i >= 0; $i--) {
      $field_item = $group_access_field_items[$i];
      if (in_array($field_item->target_id, $referenced_groups_by_node[$node_id]) || in_array($field_item->target_id, $duplicate_values)) {
        // remove the field item
        unset($node->field_groups_with_view_access[$i]);
        // remove the entry from $referenced_groups_by_node so that it does not try to delete any duplicate values.
        $referenced_groups_by_node[$node_id] = array_diff($referenced_groups_by_node[$node_id], array($field_item->target_id));
        $save_needed = TRUE;
      } else {
        // collect possible duplicates to assess for removal
        $duplicate_values[] = $field_item->target_id;
      }
    }
    if ($save_needed) {
      $node->save();
    }
  }

  // should we now drop the table og_memberships right in the hook or do it manually afterward?
}

function pece_migrate_deploy_add_d7_users_to_v1_researchers() {
  $db = \Drupal::database();

  // Get d7 to d10 user migration map
  $user_migration_map = $db->query('SELECT destid1 FROM migrate_map_v1_user')->fetchAllKeyed(0, 0);
  // Get the PECE v1 Researchers group
  $loaded_groups = \Drupal::entityTypeManager()->getStorage('taxonomy_term')->loadByProperties(["name" => "PECE v1 Researchers"]);
  $pece_v1_researchers_group = array_values($loaded_groups)[0];
  // Add every D7 user to the group
  $pece_v1_researchers_group->field_group_members = array_keys($user_migration_map);
  $pece_v1_researchers_group->save();
}
