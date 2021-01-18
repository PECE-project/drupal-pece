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
  $profile =  profile2_load_by_user($user, 'pece_profile_main');
  if (isset($profile->field_pece_full_name)) {
    return !empty($profile->field_pece_full_name[LANGUAGE_NONE][0]['value']);
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
    $profile = profile2_load_by_user($entity, 'pece_profile_main');
    $full_name = $profile->field_pece_full_name[LANGUAGE_NONE][0]['value'];
    if (!empty($full_name)){
      return $full_name;
    }
  }
  return $entity->name;
}
