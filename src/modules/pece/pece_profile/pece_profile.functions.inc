<?php
/**
 * @file
 * Helper functions for the pece_profile module.
 */


/**
 * Validate function to check the authors field and fill the contributors
 * accourding the author name.
 */
function pece_profile_check_author(&$form, &$form_state) {

  global $user;

  if (!is_contributor($user) && !is_researcher($user)) {
    return;
  }
  // @TODO: Move it to pece_groups and ommit this validate from the form.
  // Skip contributors field autofill when on Edit group audience page.
  if (isset($form_state['pece_groups_edit_group_field']) &&
      $form_state['pece_groups_edit_group_field'] === TRUE) {
    return;
  }

  $field_contributors = field_get_items('node', $form['#entity'], 'field_pece_contributors');
  // Skip contributors field autofill when users is already set as so.
  if (_pece_profile_field_contributors_has_user($field_contributors, $user)) {
    return;
  }

  $values = $form_state['values'];
  $user_profile = profile2_load_by_user($user);
  // Skip contributors field autofill when current user is already the author (creator).
  if (isset($user_profile['pece_profile_main'])) {
    $profile_wrapper = entity_metadata_wrapper('profile2', $user_profile['pece_profile_main']);
    if (isset($values['field_pece_authors']['und'][0]) &&
      $values['field_pece_authors']['und'][0]['name'] == $profile_wrapper->field_pece_full_name->value()) {
      return;
    };
  }

  // @TODO: Needs to support multilanguage.
  $current_user = array(array('target_id' => $user->uid));
  $value = array(LANGUAGE_NONE => array_merge($field_contributors, $current_user));
  form_set_value($form['field_pece_contributors'], $value, $form_state);
}

function is_contributor($user) {
  $contributor_role = user_role_load_by_name('Contributor');
  return (in_array($contributor_role->rid, array_keys($user->roles)));
}

function is_researcher($user) {
  $contributor_role = user_role_load_by_name('Researcher');
  return (in_array($contributor_role->rid, array_keys($user->roles)));
}

/**
 * Check if a given user is already listed as contributor.
 */
function _pece_profile_field_contributors_has_user($field_values = array(), $user) {
  if (empty($field_values)) {
    return FALSE;
  }
  return (in_array(array('target_id' => $user->uid), $field_values));
}
