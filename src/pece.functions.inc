<?php

/**
 * Parse a YAML stream.
 *
 * @param $input
 *   The YAML stream.
 *
 * @return mixed
 *   Array of parsed YAML elements (or FALSE on failure).
 */
function pece_parse_yaml($input = '') {
  if (function_exists('yaml_parse')) {
    return yaml_parse($input);
  }

  // Load fallback library.
  if ($path_to_spyc_library = libraries_get_path('spyc-master')) {
    include_once $path_to_spyc_library . '/Spyc.php';
  }

  if (!function_exists('spyc_load')) {
    drupal_set_message(t('Parse YAML: Unable to find a YAML parser.'), 'error', FALSE);
    return FALSE;
  }

  try {
    $parsed = spyc_load($input);
  } catch(Exception $exception) {
    drupal_set_message(t('Failed parsing YAML stream. ') . $exception->getMessage(), 'error');
    return FALSE;
  }
  return $parsed;
}

/**
 * Setup core permissions.
 *
 * @param
 *   A associative array map of permissions to grant/remove.
 *   Example:
 *     array(
 *       'all' => array(
 *         'use Search Autocomplete' => TRUE, // Sample for granting to all user roles.
 *       ),
 *       'role name' => array(
 *         'granting permission' => TRUE,  // Sample for granting a permission.
 *         'removing permission' => FALSE, // Sample for removing a permission.
 *       ),
 *     );
 */
function pece_set_permissions($permission_map = array()) {
  $all_permissions = user_permission_get_modules();
  $user_roles = user_roles();

  foreach ($user_roles as $rid => $role_name) {
    $assigning_permissions = empty($permission_map[$role_name]) ? array() : $permission_map[$role_name];
    $assigning_permissions += empty($permission_map['all']) ? array() : $permission_map['all'];

    // Clean-up non-existing permissions.
    foreach ($assigning_permissions as $permission_name => $change) {
      if (empty($all_permissions[$permission_name])) {
        unset($assigning_permissions[$permission_name]);
      }
    }

    user_role_change_permissions($rid, $assigning_permissions);
  }
}
