<?php
/**
 * @file
 * Contains \Drupal\pece_migrate\Plugin\migrate\source\GroupNode.
 */
namespace  Drupal\pece_migrate\Plugin\migrate\source;
// use Drupal\migrate\Row;

use Drupal\migrate\Row;
use Drupal\node\Plugin\migrate\source\d7\NodeComplete as D7Node;
// use Drupal\Tests\Component\Annotation\Doctrine\Ticket\Doctrine\ORM\Entity;
// use Exception;

/**
 * Gets all node revisions from the source, including translation revisions.
 *
 * @MigrateSource(
 *   id = "v1_group_node",
 *   source_module = "node"
 * )
 */
class GroupNode extends D7Node {

  const ROLE_RESEARCHER = 'researcher';
  const ROLE_CONTRIBUTOR = 'contributor';

  protected $groupMembers = [];

  /**
   * {@inheritdoc}
   */
  public function fields() {
    $fields = parent::fields() + ['alias' => $this->t('Path alias')];
    $fields += ['d7_group_members' => $this->t('Group members')];
    // $fields += ['permission_by_group_view' => $this->t('Permission by group')];
    // $fields += ['permission_by_user_view' => $this->t('Permission by user')];
    // $fields += ['permission_by_role_view' => $this->t('Permission by role')];
    // $fields += ['permission_all_user_view' => $this->t('Permission for all users')];
    return $fields;
  }

  public function prepareRow(Row $row) {
    $gid = $row->getSourceProperty('nid');

    // Query to get user IDs based on group membership.
    $subquery = $this->select('og_membership', 'ogm')
      ->fields('ogm', array('etid'))
      ->condition('ogm.entity_type', 'user')
      ->condition('ogm.gid', $gid);

    // Get all users who are members of group
    $users = $this->select('users', 'u')
      ->fields('u', array('uid'))
      ->condition('u.uid', $subquery, 'IN')
      ->execute()
      ->fetchCol();

    foreach ($users as $key => $item) {
      $this->groupMembers[] = [
        'target_id' => $item
      ];
    }

    $row->setSourceProperty('d7_group_members', $this->groupMembers);
    $this->groupMembers = [];
  }
}
