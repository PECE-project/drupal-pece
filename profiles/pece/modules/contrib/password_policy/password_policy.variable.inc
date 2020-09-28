<?php

/**
 * @file
 * Variable module hook implementations.
 */

include_once 'password_policy.admin.inc';

/**
 * Implements hook_variable_info().
 */
function password_policy_variable_info($options) {
  $variables['password_policy_warning_[mail_part]'] = array(
    'title' => t('Password Policy warning e-mail'),
    'type' => 'mail_text',
    'default' => array(
      'subject' => PASSWORD_POLICY_DEFAULT_WARNING_SUBJECT,
      'body' => PASSWORD_POLICY_DEFAULT_WARNING_BODY,
    ),
    'description' => t('Customize the warning e-mail message, which is sent to remind of password expiration.') . _password_policy_warning_email_tokens_help(),
    'group' => 'user_mails',
  );
  return $variables;
}
