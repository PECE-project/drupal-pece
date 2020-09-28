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
function password_policy_constraint_alphanumeric_description() {
  return array('name' => t('Alphanumeric'), 'description' => t('Password must contain the specified minimum number of alphanumeric (letters or numbers) characters.'));
}

/**
 * Error message of the constraint.
 */
function password_policy_constraint_alphanumeric_error($constraint) {
  return format_plural($constraint, 'Password must contain at least one alphanumeric (letter or number) character.', 'Password must contain at least @count alphanumeric (letter or number) characters.');
}

/**
 * Password validation.
 */
function password_policy_constraint_alphanumeric_validate($password, $constraint, $account) {
  $matches = array();
  $count = preg_match_all('/[a-z0-9]/i', $password, $matches);
  return $count >= $constraint;
}

/**
 * Javascript portion.
 */
function password_policy_constraint_alphanumeric_js($constraint, $account) {
  return <<<JS

    var count = (value.match(/[a-z0-9]/gi) || []).length;
    if (count < $constraint) {
      strength = 'low';
      msg.push(translate.constraint_alphanumeric);
    }
JS;
}
