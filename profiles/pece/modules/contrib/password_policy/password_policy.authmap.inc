<?php

/**
 * @file
 * Functions to support excluding authentication modules from policies.
 */

/**
 * Whether policy excludes an authentication module used to authenticate user.
 *
 * @param array $policy
 *   Policy array.
 * @param object $account
 *   User object.
 *
 * @return bool
 *   TRUE if the policy excludes authentication module used to authenticate
 *   user; otherwise, FALSE.
 */
function _password_policy_policy_excludes_authentication_module_of_user(array $policy, $account) {
  $excluded_authentication_modules = $policy['excluded_authentication_modules'];
  if (empty($excluded_authentication_modules)) {
    return FALSE;
  }
  $user_authentication_modules = _password_policy_get_authentication_modules_for_user($account);
  $user_excluded_authentication_modules = array_intersect($excluded_authentication_modules, $user_authentication_modules);
  return !empty($user_excluded_authentication_modules);
}

/**
 * Loads excluded authentication modules into policy.
 *
 * @param array $policy
 *   Policy array.
 */
function _password_policy_load_policy_excluded_authentication_modules(array &$policy) {
  $excluded_authentication_modules = db_select('password_policy_excluded_authentication_modules', 'p', array('target' => 'slave'))
    ->fields('p', array('module'))
    ->condition('pid', $policy['pid'])
    ->execute()
    ->fetchCol();
  $policy['excluded_authentication_modules'] = $excluded_authentication_modules;
}

/**
 * Gets authentication modules used to authenticate user.
 *
 * @param object $account
 *   User object.
 *
 * @return array
 *   Authentication modules.
 */
function _password_policy_get_authentication_modules_for_user($account) {
  return db_query("SELECT module FROM {authmap} WHERE uid = :uid", array(':uid' => $account->uid))->fetchCol();
}

/**
 * Gets all authentication modules in use on site.
 *
 * @return array
 *   Authentication modules.
 */
function _password_policy_get_authentication_modules() {
  return db_select('authmap', 'a')
    ->fields('a', array('module'))
    ->groupBy('module')
    ->execute()
    ->fetchCol();
}
