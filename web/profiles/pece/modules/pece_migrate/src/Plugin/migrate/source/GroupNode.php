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

  const GROUP_MEMBER_ROLES = ['Researcher', 'Contributor', 'member'];
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
    return $fields;
  }

  public function prepareRow(Row $row) {
    $gid = $row->getSourceProperty('nid');

    $this->groupManagers = $this->buildFieldDataByRoles($gid, self::GROUP_MANAGER_ROLES);
    $row->setSourceProperty('d7_group_managers', $this->groupManagers);
    $this->groupManagers = [];

    $this->groupMembers = $this->buildFieldDataByRoles($gid, self::GROUP_MEMBER_ROLES);
    $row->setSourceProperty('d7_group_members', $this->groupMembers);
    $this->groupMembers = [];
  }

  public function buildFieldDataByRoles($gid, Array $d7_group_roles) {
    // Collect role ids (of this group) for selected roles
    $role_ids_query = $this->select('og_role', 'r')
    ->fields('r', array('rid'))
    ->condition('r.gid', $gid)
    ->condition('r.name', $d7_group_roles, 'IN');

    // Get users with at least one of these role ids
    $users = $this->select('og_users_roles', 'ur')
      ->fields('ur', array('uid'))
      ->distinct()
      ->condition('ur.rid', $role_ids_query, 'IN')
      ->execute()
      ->fetchCol();

    $group_users = [];

    foreach ($users as $key => $item) {
      $group_users[] = [
        'target_id' => $item
      ];
    }

    return $group_users;
  }
}
