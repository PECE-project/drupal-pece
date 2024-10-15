<?php
/**
 * @file
 * Contains \Drupal\pece_migrate\Plugin\migrate\source\Node.
 */
namespace  Drupal\pece_migrate\Plugin\migrate\source;
use Drupal\migrate\Row;
use Drupal\node\Plugin\migrate\source\d7\NodeComplete as D7Node;
use Drupal\Tests\Component\Annotation\Doctrine\Ticket\Doctrine\ORM\Entity;
use Exception;

/**
 * Gets all node revisions from the source, including translation revisions.
 *
 * @MigrateSource(
 *   id = "v1_node",
 *   source_module = "node"
 * )
 */
class Node extends D7Node {

  const PERMISSION_RESTRICTED = 'restricted';
  const PERMISSION_PRIVATE = 'private';
  const PERMISSION_OPEN = 'open';

  protected $permissionByUserView = [];

  public function query() {
    $query =  parent::query(); // TODO: Change the autogenerated stub

    return $query;
  }

  /**
   * {@inheritdoc}
   */
  public function fields() {
    $fields = parent::fields() + ['alias' => $this->t('Path alias')];
    $fields += ['permission_all_user_view' => $this->t('Permission for all users')];
    $fields += ['groups_with_view_access' => $this->t('Groups with view access')];
    return $fields;
  }

  /**
   * {@inheritdoc}
   * @throws Exception
   */
  public function prepareRow(Row $row) {
    // Include path alias.
    $nid = $row->getSourceProperty('nid');
    $query = $this->select('url_alias', 'ua')
      ->fields('ua', ['alias']);
    $query->condition('ua.source', 'node/' . $nid);
    $alias = $query->execute()->fetchField();
    if (!empty($alias)) {
      $row->setSourceProperty('alias', '/' . $alias);
    }

    // Check permissions
    $query = $this->select('field_data_field_permissions', 'fdfp')
      ->fields('fdfp', ['field_permissions_value'])
      ->condition('fdfp.entity_id', $nid);
    $permission = $query->execute()->fetchField();
    $groups = $this->getGroupsByContent($nid);
    $group_terms = [];
    foreach ($groups as $key => $item) {
      $group_terms[] = [
        'target_id' => $item
      ];
    }
    $row->setSourceProperty('groups_with_view_access', $group_terms);

    if ($permission == self::PERMISSION_OPEN) {
      // Check if content belongs to any group
      if (count($groups) > 0) {
        // Check group access (public = 0, private = 1)
        $groupAccess = $this->checkGroupsAccess($groups);
        // Get group content visibility
        $groupContentVisibility = $this->checkGroupsContentVisibility($groups);

        if ($groupAccess == 0 && $groupContentVisibility !== 2) {
          // All users can see the content
          $row->setSourceProperty('permission_all_user_view', true);
        }

        if ($groupAccess == 1 && $groupContentVisibility == 1) {
          $row->setSourceProperty('permission_all_user_view', true);
        }
      }
      else
        // All users see the content
        $row->setSourceProperty('permission_all_user_view', true);
    }

    return parent::prepareRow($row);
  }

  /**
   * Check groups access.
   * @throws Exception
   */
  public function checkGroupsAccess($groups): int
  {
    $access = 0;
    foreach ($groups as $key => $item) {
      $query = $this->select('field_data_group_access', 'fdga')
        ->fields('fdga', ['group_access_value'])
        ->condition('fdga.entity_id', $item);
      $access = $query->execute()->fetchField();
      //"What was once Public cannot be hidden by mistake" by Reva
      if ($access == 0)
        break;
    }
    return $access;
  }

  /**
   * Check groups visibility.
   * @throws Exception
   */
  public function checkGroupsContentVisibility($groups): int
  {
    $visibility = 0;
    foreach ($groups as $key => $item) {
      $query = $this->select('field_data_group_content_access', 'fdgca')
        ->fields('fdgca', ['group_content_access_value'])
        ->condition('fdgca.entity_id', $item);
      //default == 0, public == 1, private == 2
      $visibility = $query->execute()->fetchField();
      //"What was once Public cannot be hidden by mistake" by Reva
      if ($visibility == 1)
        break;
    }
    return $visibility;
  }

  /**
   * TODO: Check 'Group content visibility' field functionality in content (not in group) with Reva
   * Check the 'Group content visibility' field by content id
   * @throws Exception
   */
  public function checkGroupContentVisibility($nid): int
  {
    $query = $this->select('field_data_group_content_access', 'fdgca')
      ->fields('fdgca', ['group_content_access_value'])
      ->condition('fdgca.entity_id', $nid);
    //default == 0, public == 1, private == 2
    return $query->execute()->fetchField();
  }

  /**
   * Get the content groups
   * @throws Exception
   */
  public function getGroupsByContent($nid)
  {
    $query = $this->select('og_membership', 'ogm')
      ->fields('ogm', ['gid'])
      ->condition('ogm.etid', $nid);
    return $query->execute()->fetchCol();
  }
}
