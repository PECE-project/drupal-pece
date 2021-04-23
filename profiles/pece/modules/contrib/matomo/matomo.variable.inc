<?php

/**
 * @file
 * Definition of variables for Variable API module.
 */

/**
 * Implements hook_variable_info().
 */
function matomo_variable_info($options) {
  $variables['matomo_site_id'] = array(
    'type' => 'string',
    'title' => t('Matomo site ID', array(), $options),
    'default' => '',
    'description' => t('The user account number is unique to the websites domain. Click the <strong>Settings</strong> link in your Matomo account, then the <strong>Websites</strong> tab and enter the appropriate site <strong>ID</strong> into this field.'),
    'required' => TRUE,
    'group' => 'matomo',
    'localize' => TRUE,
    'multidomain' => TRUE,
    'validate callback' => 'matomo_validate_matomo_site_id',
  );

  return $variables;
}

/**
 * Implements hook_variable_group_info().
 */
function matomo_variable_group_info() {
  $groups['matomo'] = array(
    'title' => t('Matomo'),
    'description' => t('Configure tracking behavior to get insights into your website traffic and marketing effectiveness.'),
    'access' => 'administer matomo',
    'path' => array('admin/config/system/matomo'),
  );

  return $groups;
}

/**
 * Validate Matomo site ID variable.
 *
 * @param array $variable
 *
 * @return string
 */
function matomo_validate_matomo_site_id($variable) {
  if (!preg_match('/^\d{1,}$/', $variable['value'])) {
    return t('A valid Matomo site ID is an integer only.');
  }
}
