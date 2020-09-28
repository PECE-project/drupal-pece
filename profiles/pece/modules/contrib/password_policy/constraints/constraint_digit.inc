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
function password_policy_constraint_digit_description() {
  return array('name' => t('Digit'), 'description' => t('Password must contain the specified minimum number of digits.'));
}

/**
 * Error message of the constraint.
 */
function password_policy_constraint_digit_error($constraint) {
  return format_plural($constraint, 'Password must contain at least one digit.', 'Password must contain at least @count digits.');
}

/**
 * Password validation.
 */
function password_policy_constraint_digit_validate($password, $constraint, $account) {
  $matches = array();
  $count = preg_match_all('/[0-9]/', $password, $matches);
  return $count >= $constraint;
}

/**
 * Javascript portion.
 */
function password_policy_constraint_digit_js($constraint, $account) {
  return <<<JS

    var count = (value.match(/[0-9]/g) || []).length;
    if (count < $constraint) {
      strength = 'low';
      msg.push(translate.constraint_digit);
    }
JS;
}
