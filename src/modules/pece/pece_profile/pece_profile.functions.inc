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
  $values = $form_state['values'];
  $user_profile = profile2_load_by_user($user);

  // Skip autofill the contributor field if current user is already the author.
  if (isset($user_profile['pece_profile_main'])) {
    $profile_wrapper = entity_metadata_wrapper('profile2', $user_profile['pece_profile_main']);
    if (isset($values['field_pece_authors']['und'][0]) &&
      $values['field_pece_authors']['und'][0]['name'] == $profile_wrapper->field_pece_full_name->value()) {
      return;
    };
  }

  // Skip autofill the contributor field if current user isn't contributor.
  if (!is_contributor($user) ||
      $values['field_pece_contributors']['und'][0]['target_id'] == $user->uid) {
    return;
  }

  $value = array(LANGUAGE_NONE => array(array('target_id' => $user->uid)));
  form_set_value($form['field_pece_contributors'], $value, $form_state);
}

function is_contributor($user) {
  $contributor_role = user_role_load_by_name('Contributor');

  return (in_array($contributor_role->rid, array_keys($user->roles)));
}
