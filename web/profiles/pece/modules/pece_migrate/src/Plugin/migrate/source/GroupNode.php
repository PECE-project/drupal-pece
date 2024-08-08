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

  // const ROLE_RESEARCHER = 'researcher';
  // const ROLE_CONTRIBUTOR = 'contributor';
  const ROLE_ADMIN_MEMBER = 'administrator member';
  const ROLE_GROUP_ADMIN = 'group administrator';

  protected $groupUsers = [];

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

    // Collect role ids (of this group) for group administrator or member administrator roles
    $admin_role_ids_query = $this->select('og_role', 'r')
      ->fields('r', array('rid'))
      ->condition('r.gid', $gid)
      ->condition('r.name', [self::ROLE_ADMIN_MEMBER, self::ROLE_GROUP_ADMIN], 'IN');

    // Get users with at least one of these role ids
    $users = $this->select('og_users_roles', 'ur')
      ->fields('ur', array('uid'))
      ->distinct()
      ->condition('ur.rid', $admin_role_ids_query, 'IN')
      ->execute()
      ->fetchCol();

    foreach ($users as $key => $item) {
      $this->groupUsers[] = [
        'target_id' => $item
      ];
    }

    $row->setSourceProperty('d7_group_managers', $this->groupUsers);
    $this->groupUsers = [];
  }
}
