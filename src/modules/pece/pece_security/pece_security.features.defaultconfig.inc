<?php

/**
 * @file
 * pece_security.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function pece_security_defaultconfig_features() {
  return array(
    'pece_security' => array(
      'strongarm' => 'strongarm',
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_strongarm().
 */
function pece_security_defaultconfig_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'encrypt_default_config';
  $strongarm->value = 'default';
  $export['encrypt_default_config'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'encrypt_drupal_variable_key';
  $strongarm->value = 'yJiNNd3XaUAEjNS/pmQ96Q==';
  $export['encrypt_drupal_variable_key'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'honeypot_element_name';
  $strongarm->value = 'url';
  $export['honeypot_element_name'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'honeypot_log';
  $strongarm->value = 1;
  $export['honeypot_log'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'honeypot_protect_all_forms';
  $strongarm->value = 1;
  $export['honeypot_protect_all_forms'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'honeypot_time_limit';
  $strongarm->value = 3;
  $export['honeypot_time_limit'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'login_security_activity_threshold';
  $strongarm->value = '20';
  $export['login_security_activity_threshold'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'login_security_disable_core_login_error';
  $strongarm->value = 0;
  $export['login_security_disable_core_login_error'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'login_security_host_hard_banned';
  $strongarm->value = 'The IP address @ip is banned at @site, and will not be able to access any of its content from now on. Please contact the site administrator.';
  $export['login_security_host_hard_banned'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'login_security_host_soft_banned';
  $strongarm->value = 'This host is not allowed to log in to @site. Please contact your site administrator.';
  $export['login_security_host_soft_banned'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'login_security_host_wrong_count';
  $strongarm->value = '20';
  $export['login_security_host_wrong_count'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'login_security_host_wrong_count_hard';
  $strongarm->value = '20';
  $export['login_security_host_wrong_count_hard'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'login_security_last_access_timestamp';
  $strongarm->value = 1;
  $export['login_security_last_access_timestamp'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'login_security_last_login_timestamp';
  $strongarm->value = 1;
  $export['login_security_last_login_timestamp'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'login_security_login_activity_email_body';
  $strongarm->value = 'The configured threshold of @activity_threshold logins has been reached with a total of @tracking_current_count invalid login attempts. You should review your log information about login attempts at @site.';
  $export['login_security_login_activity_email_body'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'login_security_login_activity_email_subject';
  $strongarm->value = 'Security information: Unexpected login activity has been detected at @site.';
  $export['login_security_login_activity_email_subject'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'login_security_login_activity_email_user';
  $strongarm->value = 'admin';
  $export['login_security_login_activity_email_user'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'login_security_notice_attempts_available';
  $strongarm->value = 0;
  $export['login_security_notice_attempts_available'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'login_security_notice_attempts_message';
  $strongarm->value = 'You have used @user_current_count out of @user_block_attempts login attempts. After all @user_block_attempts have been used, you will be unable to login.';
  $export['login_security_notice_attempts_message'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'login_security_track_time';
  $strongarm->value = '24';
  $export['login_security_track_time'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'login_security_user_blocked';
  $strongarm->value = 'The user @username has been blocked due to failed login attempts.';
  $export['login_security_user_blocked'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'login_security_user_blocked_email_body';
  $strongarm->value = 'The user @username (@edit_uri) has been blocked at @site due to the amount of failed login attempts. Please check the logs for more information.';
  $export['login_security_user_blocked_email_body'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'login_security_user_blocked_email_subject';
  $strongarm->value = 'Security action: The user @username has been blocked.';
  $export['login_security_user_blocked_email_subject'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'login_security_user_blocked_email_user';
  $strongarm->value = 'admin';
  $export['login_security_user_blocked_email_user'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'login_security_user_wrong_count';
  $strongarm->value = '0';
  $export['login_security_user_wrong_count'] = $strongarm;

  return $export;
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function pece_security_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'admin tfa settings'.
  $permissions['admin tfa settings'] = array(
    'name' => 'admin tfa settings',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'tfa',
  );

  // Exported permission: 'administer encrypt'.
  $permissions['administer encrypt'] = array(
    'name' => 'administer encrypt',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'encrypt',
  );

  // Exported permission: 'administer keys'.
  $permissions['administer keys'] = array(
    'name' => 'administer keys',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'key',
  );

  // Exported permission: 'administer password policies'.
  $permissions['administer password policies'] = array(
    'name' => 'administer password policies',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'password_policy',
  );

  // Exported permission: 'bypass honeypot protection'.
  $permissions['bypass honeypot protection'] = array(
    'name' => 'bypass honeypot protection',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'honeypot',
  );

  // Exported permission: 'force password change'.
  $permissions['force password change'] = array(
    'name' => 'force password change',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'password_policy',
  );

  // Exported permission: 'unblock expired accounts'.
  $permissions['unblock expired accounts'] = array(
    'name' => 'unblock expired accounts',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'password_policy',
  );

  return $permissions;
}
