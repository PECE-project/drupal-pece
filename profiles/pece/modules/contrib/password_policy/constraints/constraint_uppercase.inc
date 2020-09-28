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
function password_policy_constraint_uppercase_description() {
  return array('name' => t('Uppercase'), 'description' => t('Password must contain the specified minimum number of uppercase letters.'));
}

/**
 * Error message of the constraint.
 */
function password_policy_constraint_uppercase_error($constraint) {
  return format_plural($constraint, 'Password must contain at least one uppercase character.', 'Password must contain at least @count uppercase characters.');
}

/**
 * Password validation.
 */
function password_policy_constraint_uppercase_validate($password, $constraint, $account) {
  $matches = array();
  $count = preg_match_all('/[A-Z]/', $password, $matches);
  return $count >= $constraint;
}

/**
 * Javascript portion.
 */
function password_policy_constraint_uppercase_js($constraint, $account) {
  return <<<JS

    var count = (value.match(/[A-Z]/g) || []).length;
    if (count < $constraint) {
      strength = 'low';
      msg.push(translate.constraint_uppercase);
    }
JS;
}
