<?php
/**
 * @file
 * Contains \Drupal\pece_migrate\Plugin\migrate\source\GroupNode.
 */
namespace  Drupal\pece_migrate\Plugin\migrate\source;

use Drupal\migrate\Row;
use Drupal\node\Plugin\migrate\source\d7\Node as D7Node;

/**
 * Gets all node revisions from the source, including translation revisions.
 *
 * @MigrateSource(
 *   id = "v1_group_node",
 *   source_module = "node"
 * )
 */
class GroupNode extends D7Node {

  // const GROUP_MEMBER_ROLES = ['Researcher', 'Contributor', 'member'];
  const GROUP_MANAGER_ROLES = ['administrator member', 'group administrator'];

  protected $groupMembers = [];
  protected $groupManagers = [];

  /**
   * {@inheritdoc}
   */
  public function fields() {
    $fields = parent::fields() + ['alias' => $this->t('Path alias')];
    $fields += ['d7_group_members' => $this->t('Group members')];
    $fields += ['d7_group_managers' => $this->t('Group managers')];
    $fields += ['d7_group_access' => $this->t('Group access')];
    return $fields;
  }

  public function prepareRow(Row $row) {
    $gid = $row->getSourceProperty('nid');

    // Get the group access setting
    $group_access = $this->select('field_data_group_access', 'fdga')
      ->fields('fdga', ['group_access_value'])
      ->condition('fdga.entity_id', $gid)
      ->execute()
      ->fetchField();

    $managers = $this->buildFieldDataByRoles($gid, self::GROUP_MANAGER_ROLES);

    // Query to get user IDs based on group membership.
    // For the case of members, we cannot build the data based on roles, since the member role is  implicit, and not actually present in the og_users_roles table at all
    $members_query = $this->select('og_membership', 'ogm')
      ->fields('ogm', array('etid'))
      ->condition('ogm.entity_type', 'user')
      ->condition('ogm.gid', $gid);

    if (!empty($managers)) {
      $members_query = $members_query->condition('ogm.etid', $managers, 'NOT IN');
    }

    $members = $members_query
    ->execute()
    ->fetchCol();

    foreach ($members as $key => $item) {
      $this->groupMembers[] = [
        'target_id' => $item
      ];
    }

    foreach ($managers as $key => $item) {
      $this->groupManagers[] = [
        'target_id' => $item
      ];
    }

    $row->setSourceProperty('d7_group_access', $group_access);
    $row->setSourceProperty('d7_group_members', $this->groupMembers);
    $row->setSourceProperty('d7_group_managers', $this->groupManagers);
    $this->groupMembers = [];
    $this->groupManagers = [];
  }

  public function buildFieldDataByRoles($gid, Array $d7_group_roles) {
    // Collect role ids (of this group) for selected roles
    $role_ids_query = $this->select('og_role', 'r')
    ->fields('r', array('rid'))
    ->condition('r.gid', $gid)
    ->condition('r.name', $d7_group_roles, 'IN');

    // Get users with at least one of these role ids
    return $this->select('og_users_roles', 'ur')
      ->fields('ur', array('uid'))
      ->distinct()
      ->condition('ur.rid', $role_ids_query, 'IN')
      ->execute()
      ->fetchCol();
  }
}
