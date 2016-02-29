<?php

/**
 * @file
 * User seed implementation.
 */

/**
 * Create a user seed.
 */
function seeds_user_seed_create($data = array()) {

  // Defaults.
  $data += array(
    'name' => 'default_user',
    'mail' => 'default_user@mail.com',
    'pass' => user_password(8),
    'status' => 1,
    'init' => 'email address',
  );

  // Make sure roles are handled correctly.
  // @todo: should be done trough a hookable system? Definitelly...
  if (!empty($data['roles'])) {
    $roles = array();
    foreach ($data['roles'] as $role_name) {
      if ($role = user_role_load_by_name($role_name)) {
        $roles[$role->rid] = $role->name;
      }
    }
    $data['roles'] = $roles;
  }

  // Return existing user, if available.
  if ($existing_user = _seeds_user_find($data)) {
    return $existing_user;
  }

  // Load user after save to make sure we have the most up to date user object.
  $new_user = user_save('', $data);
  return user_load($new_user->uid, TRUE);
}

/**
 * Remove a user seed.
 */
function seeds_user_seed_remove($data = array(), $value = array(), $config = array()) {
  if ($user = _seeds_user_find($value)) {
    _user_cancel(array(), $user, !empty($config['remove']['method']) ? $config['remove']['method'] : 'user_cancel_delete');
    return TRUE;
  }
}

/**
 * Helper method to find a user by it's possible unique properties.
 */
function _seeds_user_find($info) {
  // Ways to find the user
  $lookup_properties = array(
    'uid' => 'user_load',
    'mail' => 'user_load_by_mail',
    'name' => 'user_load_by_name',
  );

  // Return existing user, if available.
  foreach ($lookup_properties as $property => $loader) {
    if (!empty($info[$property]) && function_exists($loader) && $existing_user = $loader($info[$property])) {
      return $existing_user;
    }
  }

  return NULL;
}
