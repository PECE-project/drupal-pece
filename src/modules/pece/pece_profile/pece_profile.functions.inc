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
  $user_profile = profile2_load_by_user($user);

  if (!isset($user_profile['pece_profile_main'])) {
   return;
  }

  $values = $form_state['values'];
  $contributor_role = user_role_load_by_name('Contributor');
  $profile_wrapper = entity_metadata_wrapper('profile2', $user_profile['pece_profile_main']);

  if (in_array($contributor_role->rid, array_keys( $user->roles)) &&
    isset($values['field_pece_authors']['und'][0]) &&
    $values['field_pece_authors']['und'][0]['name'] != $profile_wrapper->field_pece_full_name->value()) {

    $value = array(LANGUAGE_NONE => array(array('target_id' => $user->uid)));
    form_set_value($form['field_pece_contributors'], $value, $form_state);
  }
}