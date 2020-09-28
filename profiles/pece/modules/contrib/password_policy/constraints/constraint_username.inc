<?php

/**
 * @file
 * Password policy constraint callbacks.
 */

/****************************************************************************/
/* Constraint API                                                           */
/****************************************************************************/

/**
 * Description of the constraint.
 */
function password_policy_constraint_username_description() {
  return array('name' => t('Username'), 'description' => t('Password must not contain the username (case insensitive). Put any positive number to enforce this policy.'));
}

/**
 * Error message of the constraint.
 */
function password_policy_constraint_username_error($constraint) {
  return t('Password must not contain the username.');
}

/**
 * Password validation.
 */
function password_policy_constraint_username_validate($password, $constraint, $account) {
  // The username may be empty if not entered on the user registration form.
  if (!$account->name) {
    return TRUE;
  }

  $username_lowercase = drupal_strtolower($account->name);
  $password_lowercase = drupal_strtolower($password);
  return strpos($password_lowercase, $username_lowercase) === FALSE;
}

/**
 * Javascript portion.
 */
function password_policy_constraint_username_js($constraint, $account) {
  // Add username as JavaScript setting.
  $username = isset($account->name) ? $account->name : '';
  $data = array(
    'passwordPolicy' => array(
      'username' => $username,
    ),
  );
  drupal_add_js($data, 'setting');

  return <<<JS

    var username = '';
    var usernameInput = jQuery('input.username');
    if (usernameInput.length) {
      username = usernameInput.val();
    }
    else {
      username = Drupal.settings.passwordPolicy.username;
    }
    if (username) {
      var username_lowercase = username.toLowerCase();
      var password_lowercase = value.toLowerCase();
      if (password_lowercase.indexOf(username_lowercase) != -1) {
        strength = 'low';
        msg.push(translate.constraint_username);
      }
    }
JS;
}
