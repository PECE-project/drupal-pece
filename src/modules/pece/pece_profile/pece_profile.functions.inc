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
 * Get full name or name from the user.
 * @param null $user
 *
 * @return mixed
 */
function pece_get_fullname_or_name($user = FALSE) {
  $fullName = FALSE;
  if (!$user) {
    global $user;
  }
  $userWpr = entity_metadata_wrapper('user', $user);
  $fullName = $userWpr->profile_pece_profile_main->field_pece_full_name->value();
  return $fullName ? $fullName : $user->name;
}
