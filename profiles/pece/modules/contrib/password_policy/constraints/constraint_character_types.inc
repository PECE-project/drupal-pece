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
function password_policy_constraint_character_types_description() {
  return array('name' => t('Character types'), 'description' => t('Password must contain the specified minimum number of character types (lowercase, uppercase, digit or punctuation).'));
}

/**
 * Error message of the constraint.
 */
function password_policy_constraint_character_types_error($constraint) {
  return format_plural($constraint, 'Password must contain characters of at least one of the following types: lowercase, uppercase, digit or punctuation.', 'Password must contain characters of at least @count different types (lowercase, uppercase, digit or punctuation).');
}

/**
 * Password validation.
 */
function password_policy_constraint_character_types_validate($password, $constraint, $account) {
  $upper = preg_match('/[A-Z]/', $password);
  $lower = preg_match('/[a-z]/', $password);
  $digit = preg_match('/[0-9]/', $password);
  $punctuation_characters = '`~!@#$%^&*()_+=-|}{"?:><,./;\'\\[]';
  $punctuation_pattern = '/[' . preg_quote($punctuation_characters, '/') . ']/';
  $punctuation = preg_match($punctuation_pattern, $password);
  $count = $upper + $lower + $digit + $punctuation;
  return $count >= $constraint;
}

/**
 * Javascript portion.
 */
function password_policy_constraint_character_types_js($constraint, $account) {
  return <<<JS

    var upper = /[A-Z]/.test(value) | 0;
    var lower = /[a-z]/.test(value) | 0;
    var digit = /[0-9]/.test(value) | 0;
    var punctuation = /[`~!@#$%^&*()_+=\-|}{"?:><,./;'\\\[\]]/.test(value) | 0;

    var count = upper + lower + digit + punctuation;
    if (count < $constraint) {
      strength = 'low';
      msg.push(translate.constraint_character_types);
    }
JS;
}
