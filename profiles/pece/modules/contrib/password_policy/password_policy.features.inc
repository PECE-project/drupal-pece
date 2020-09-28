<?php

/**
 * @file
 * Integrates Features for Password Policy.
 */

/**
 * Implements hook_features_export_options().
 */
function password_policy_features_export_options() {
  return db_query('SELECT name FROM {password_policy}', array(), array('target' => 'slave'))
    ->fetchAllKeyed(0, 0);
}

/**
 * Implements hook_features_export().
 */
function password_policy_features_export($data, &$export, $module_name) {
  $export['dependencies']['features'] = 'features';
  $export['dependencies']['password_policy'] = 'password_policy';

  foreach ($data as $policy_name) {
    $policy = password_policy_load_policy_by_name($policy_name);

    // Export roles to which policy applies.
    foreach ($policy['roles'] as $rid) {
      $role = user_role_load($rid);
      $export['features']['user_role'][$role->name] = $role->name;
    }

    $export['features']['password_policy'][$policy_name] = $policy_name;
  }

  return $export;
}

/**
 * Implements hook_features_export_render().
 */
function password_policy_features_export_render($module_name, $data, $export = NULL) {
  $code = array();
  foreach ($data as $policy_name) {
    $policy = password_policy_load_policy_by_name($policy_name);
    if ($policy) {
      $roles = array();
      foreach ($policy['roles'] as $rid) {
        $role = user_role_load($rid);
        $roles[] = $role->name;
      }
      $policy['roles'] = $roles;
      unset($policy['pid']);
      $code[$policy['name']] = $policy;
    }
  }

  $code = '  return ' . features_var_export($code, '  ') . ';';

  return array('password_policy_features_default_policies' => $code);
}

/**
 * Implements hook_features_revert().
 */
function password_policy_features_revert($module_name) {
  password_policy_features_rebuild($module_name);
}

/**
 * Implements hook_features_rebuild().
 */
function password_policy_features_rebuild($module_name) {
  $saved_policies = module_invoke($module_name, 'password_policy_features_default_policies');
  foreach ($saved_policies as $policy) {
    $roles = array();
    foreach ($policy['roles'] as $name) {
      $role = user_role_load_by_name($name);
      $roles[$role->rid] = $role->rid;
    }
    $policy['roles'] = $roles;

    $exists = password_policy_load_policy_by_name($policy['name']);
    if ($exists) {
      $policy['pid'] = $exists['pid'];
    }

    password_policy_save_policy($policy);
  }
}
