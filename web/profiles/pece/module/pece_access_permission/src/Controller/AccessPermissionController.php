<?php


namespace Drupal\pece_access_permission\Controller;

use Drupal\Core\Controller\ControllerBase;

class AccessPermissionController extends ControllerBase {

  /**
   * To control if content can be viewed or edited by the user.
   *
   * @param $user
   * @param $entity
   * @param $permission
   *
   * @return bool
   */
  public function handleCanViewEdit($user, $entity, $permission){
    if ($entity->getOwner() == $user)
      return TRUE;
    $permissionIds = $this->getPermission($entity, $permission);
    if (count($permissionIds) > 0){
      $userIds = $this->getMembersByUser($user, $permissionIds);
      if (count($userIds) > 0)
        return TRUE;
      else{
        $groupsId = $this->getGroupsByUser($user);
        if (count($groupsId) > 0 && count($this->getGroupsPermissionByUser($groupsId, $permissionIds)) > 0)
          return TRUE;
      }
    }
    else
      return TRUE;
    return FALSE;
  }

  /**
   * Get all permissions of this entity.
   *
   * @param $entity
   * @param $type
   *
   * @return array|int
   */
  public function getPermission($entity, $type){
    $query = \Drupal::entityQuery('paragraph')
      ->condition('type', 'paragraph_access_permission')
      ->condition('parent_id', $entity->id());
    switch ($type){
      case 'view':
        $or = $query->orConditionGroup();
        $or->condition('field_acc_perm_permissions', 'administer')
           ->condition('field_acc_perm_permissions', 'edit')
           ->condition('field_acc_perm_permissions', 'view');
        $query->condition($or);
        break;
      case 'edit':
        $or = $query->orConditionGroup();
        $query->condition('field_acc_perm_permissions', 'administer')
              ->condition('field_acc_perm_permissions', 'edit');
        $query->condition($or);
        break;
      case 'administer':
        $query->condition('field_acc_perm_permissions', 'administer');
        break;
    }
    return $query->execute();
  }

  /**
   * Get all paragraph_members that have this user.
   * Optional parameter $permissionIds to fetch paragraph_members in permissions.
   *
   * @param null $permissionIds
   * @param $user
   *
   * @return array|int
   */
  public function getMembersByUser($user, $permissionIds = NULL){
    $query = \Drupal::entityQuery('paragraph')
      ->condition('type', 'paragraph_members')
      ->condition('field_members_user', $user->id());
    if (!is_null($permissionIds)) {
      $or = $query->orConditionGroup();
      foreach ($permissionIds as $parentId)
        $or->condition('parent_id', $parentId);
      $query->condition($or);
    }
    return $query->execute();
  }

  /**
   * Get all groups that have this user as a member or owner.
   *
   * @param $user
   *
   * @return array|int
   */
  public function getGroupsByUser($user){
    $query = \Drupal::entityQuery('groups')
      ->condition('type', 'pece_group');
    $or = $query->orConditionGroup()
      ->condition('field_pece_group_owners', $user->id());
    if($parentId = $this->getMembersByUser($user))
      foreach ($parentId as $id)
        $or->condition('field_pece_group_members', $id);
    $query->condition($or);
    return $query->execute();
  }

  /**
   * Get all groups that belong to a permission and this user is a member or owner.
   *
   * @param $groupsId
   * @param $permissionIds
   *
   * @return array|int
   */
  public function getGroupsPermissionByUser($groupsId, $permissionIds){
    $query = \Drupal::entityQuery('paragraph')
      ->condition('type', 'paragraph_groups');
    $orGroups = $query->orConditionGroup();
    foreach ($groupsId as $groupId) {
      $orGroups->condition('field_groups_group', $groupId);
    }
    $orGroupParent = $query->orConditionGroup();
    foreach ($permissionIds as $parentId) {
      $orGroupParent->condition('parent_id', $parentId);
    }
    $query->condition($orGroupParent)
      ->condition($orGroups);
    return $query->execute();
  }
}
