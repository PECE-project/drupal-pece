<?php

/**
 * @file
 * Contains functions for Profile Delete.
 */

/**
 * Confirm form for deleting own profile.
 */
function profile2_delete_confirm_form($form, &$form_state, $profile) {
  global $user;
  if (isset($profile) && is_object($profile)) {
    $form_state += array('profile2' => $profile);
    if ($user->uid === $profile->uid) {
      $confirm_question = t('Are you sure you want to delete your own %label profile ?', array('%label' => $profile->label));
    }
    elseif (user_access('administer profiles')) {
      $user_account = user_load($profile->uid);
      if (!empty($user_account)) {
        $confirm_question = t("Are you sure you want to delete profile %label of user %user?", array('%label' => $profile->label, '%user' => $user_account->name));
      }
    }
    return confirm_form($form, $confirm_question, 'user/' . $profile->uid);
  }
}

/**
 * Confirm form submit for deleting own profile.
 */
function profile2_delete_confirm_form_submit($form, &$form_state) {
  $profile = isset($form_state['profile2']) ? $form_state['profile2'] : '';
  if (isset($profile) && is_object($profile)) {
    $profile->delete();
    drupal_set_message(t('Deleted %label.', array('%label' => $profile->label)));
  }
  $form_state['redirect'] = 'user/' . $profile->uid;
}
