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
function password_policy_constraint_punctuation_description() {
  return array('name' => t('Punctuation'), 'description' => t('Password must contain the specified minimum number of punctuation (not whitespace or an alphanumeric) characters.'));
}

/**
 * Error message of the constraint.
 */
function password_policy_constraint_punctuation_error($constraint) {
  return format_plural($constraint, 'Password must contain at least one punctuation (not whitespace or an alphanumeric) character.', 'Password must contain at least @count punctuation (not whitespace or an alphanumeric) characters.');
}

/**
 * Password validation.
 */
function password_policy_constraint_punctuation_validate($password, $constraint, $account) {
  $matches = array();
  $punctuation_characters = '`~!@#$%^&*()_+=-|}{"?:><,./;\'\\[]';
  $punctuation_pattern = '/[' . preg_quote($punctuation_characters, '/') . ']/';
  $count = preg_match_all($punctuation_pattern, $password, $matches);
  return $count >= $constraint;
}

/**
 * Javascript portion.
 */
function password_policy_constraint_punctuation_js($constraint, $account) {
  return <<<JS

    var count = (value.match(/[`~!@#$%^&*()_+=\-|}{"?:><,./;'\\\[\]]/g) || []).length;
    if (count < $constraint) {
      strength = 'low';
      msg.push(translate.constraint_punctuation);
    }
JS;
}
