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
function password_policy_constraint_letter_description() {
  return array('name' => t('Letter'), 'description' => t('Password must contain the specified minimum number of letters.'));
}

/**
 * Error message of the constraint.
 */
function password_policy_constraint_letter_error($constraint) {
  return format_plural($constraint, 'Password must contain at least one letter.', 'Password must contain at least @count letters.');
}

/**
 * Password validation.
 */
function password_policy_constraint_letter_validate($password, $constraint, $account) {
  $matches = array();
  $count = preg_match_all('/[a-z]/i', $password, $matches);
  return $count >= $constraint;
}

/**
 * Javascript portion.
 */
function password_policy_constraint_letter_js($constraint, $account) {
  return <<<JS

    var count = (value.match(/[a-z]/gi) || []).length;
    if (count < $constraint) {
      strength = 'low';
      msg.push(translate.constraint_letter);
    }
JS;
}
