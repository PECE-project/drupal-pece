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
function password_policy_constraint_lowercase_description() {
  return array('name' => t('Lowercase'), 'description' => t('Password must contain the specified minimum number of lowercase letters.'));
}

/**
 * Error message of the constraint.
 */
function password_policy_constraint_lowercase_error($constraint) {
  return format_plural($constraint, 'Password must contain at least one lowercase character.', 'Password must contain at least @count lowercase characters.');
}

/**
 * Password validation.
 */
function password_policy_constraint_lowercase_validate($password, $constraint, $account) {
  $matches = array();
  $count = preg_match_all('/[a-z]/', $password, $matches);
  return $count >= $constraint;
}

/**
 * Javascript portion.
 */
function password_policy_constraint_lowercase_js($constraint, $account) {
  return <<<JS

    var count = (value.match(/[a-z]/g) || []).length;
    if (count < $constraint) {
      strength = 'low';
      msg.push(translate.constraint_lowercase);
    }
JS;
}
