<?php
/**
 * @file
 * Helper functions for the pece_profile module.
 */

/**
 * Check if a given user is already listed as contributor.
 */
function _pece_profile_field_contributors_has_user($field_values = array(), $user) {
  if (empty($field_values)) {
    return FALSE;
  }
  return (in_array(array('target_id' => $user->uid), $field_values));
}


/**
 * Check user full name.
 *
 * @user obj User
 */
function _user_has_fullname($user = FALSE) {
  if (!$user) {
    return FALSE;
  }
  // Skip if not a User obj.
  if (is_object($user) && isset($user->tid)) {
    return FALSE;
  }
  $user = (is_numeric($user) ? user_load($user) : $user);
  $userWpr = entity_metadata_wrapper('user', $user);
  if (isset($userWpr->profile_pece_profile_main) &&
    in_array('field_pece_full_name', array_keys($userWpr->profile_pece_profile_main->getPropertyInfo()))) {
    return !empty($userWpr->profile_pece_profile_main->field_pece_full_name->value());
  }
  return FALSE;
}

/**
 * Get full name or name from User or Creator term.
 * @param Object $entity
 *
 * @return mixed
 */
function pece_get_fullname_or_name($entity) {
  if (!is_object($entity)) {
    return FALSE;
  }
  // Name from Authors Vocabulary.
  if (isset($entity->tid)) {
    return $entity->name;
  }
  if (!isset($entity->uid)) {
    return $entity->name;
  }
  if (_user_has_fullname($entity)) {
    $userWpr = entity_metadata_wrapper('user', $entity);
    $full_name = $userWpr->profile_pece_profile_main->field_pece_full_name->value();
    if (!empty($full_name)){
      return $full_name;
    }
  }
  return $entity->name;
}
