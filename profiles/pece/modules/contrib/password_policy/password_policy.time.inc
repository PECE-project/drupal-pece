<?php

/**
 * @file
 * Password Policy time retrieval functions.
 *
 * These functions should be used whenever a time is needed within the module.
 * They provide a way to control the time as seen by the module during testing.
 *
 * Instead of:           Use:
 * -----------           ----
 * time()                _password_policy_get_current_time()
 * REQUEST_TIME          _password_policy_get_request_time()
 * $account->access      _password_policy_get_user_access_time($account)
 * $account->created     _password_policy_get_user_created_time($account)
 * $account->login       _password_policy_get_user_login_time($account)
 *
 * Times are read according to one of two clocks:
 *   1. The system clock.
 *   2. The test clock, which is offset from the system clock by a controllable
 *      amount of time.
 *
 * The system clock is active by default. The test clock is active when a test
 * is being executed.
 *
 * The test clock can be controlled using
 * _password_policy_advance_test_clock().
 */

/**
 * Gets access time for given user.
 */
function _password_policy_get_user_access_time($account) {
  return _password_policy_get_user_time($account, 'access');
}

/**
 * Gets created time for given user.
 */
function _password_policy_get_user_created_time($account) {
  return _password_policy_get_user_time($account, 'created');
}

/**
 * Gets login time for given user.
 */
function _password_policy_get_user_login_time($account) {
  return _password_policy_get_user_time($account, 'login');
}

/**
 * Gets time for user by user object property name.
 */
function _password_policy_get_user_time($account, $time_name) {
  $time = $account->$time_name;
  return _password_policy_get_time_per_active_clock($time);
}

/**
 * Gets current time.
 */
function _password_policy_get_current_time() {
  return _password_policy_get_time_per_active_clock(time());
}

/**
 * Gets request time.
 */
function _password_policy_get_request_time() {
  return _password_policy_get_time_per_active_clock(REQUEST_TIME);
}

/**
 * Gets time according to the active clock.
 *
 * The system clock is active by default. The test clock is active when a test
 * is being executed.
 *
 * @param int $time
 *   A time in seconds since the Unix epoch.
 *
 * @return int
 *   The same time according to the active clock.
 */
function _password_policy_get_time_per_active_clock($time) {
  if (_password_policy_is_running_test()) {
    return _password_policy_get_time_per_test_clock($time);
  }
  return $time;
}

/**
 * Returns whether test is running.
 */
function _password_policy_is_running_test() {
  $test_info = &$GLOBALS['drupal_test_info'];
  return !empty($test_info['test_run_id']);
}

/**
 * Gets time according to test clock.
 *
 * The test clock is offset from the system clock by a number of seconds set in
 * a database variable.
 */
function _password_policy_get_time_per_test_clock($time) {
  $offset = _password_policy_get_test_clock_offset();
  return $time + $offset;
}

/**
 * Advances test clock.
 *
 * Increases the difference between the test clock and the system clock by a
 * given offset of seconds.
 *
 * @param int $offset
 *   Offset in seconds. Can be positive or negative.
 */
function _password_policy_advance_test_clock($offset) {
  $current_offset = _password_policy_get_test_clock_offset();
  $new_offset = $current_offset + $offset;
  variable_set('password_policy_test_clock_offset', $new_offset);
}

/**
 * Gets offset of test clock versus system clock.
 */
function _password_policy_get_test_clock_offset() {
  return variable_get('password_policy_test_clock_offset', 0);
}
