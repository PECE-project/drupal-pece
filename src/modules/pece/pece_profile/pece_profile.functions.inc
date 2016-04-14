<?php
/**
 * @file
 * Helper functions for the pece_profile module.
 */

/**
 * Verifies if user is of role contributor.
 */
function is_contributor($user) {
  $contributor_role = user_role_load_by_name('Contributor');

  return (in_array($contributor_role->rid, array_keys($user->roles)));
}
