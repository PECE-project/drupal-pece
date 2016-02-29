<?php

/**
 * Implements hook_kw_itemnames_type_info().
 */
function kw_itemnames_user_role_kw_itemnames_type_info() {
  $result = array();

  $result['user_role'] = array(
    'item load callback' => 'user_role_load',
    'item create callback' => 'kw_itemnames_user_role_item_create',
    'item update callback' => 'kw_itemnames_user_role_item_update',
    'item delete callback' => 'user_role_delete',
    'item extract id callback' => 'kw_itemnames_user_role_item_extract_id',
  );

  return $result;
}

function kw_itemnames_user_role_item_create($defaults, $required) {
  $role = (object) ($required + $defaults);
  user_role_save($role);
  return $role;
}

function kw_itemnames_user_role_item_update($role, $required) {
  foreach ($required as $key => $value) {
    $role->{$key} = $value;
  }
  user_role_save($role);
  return $role;
}

function kw_itemnames_user_role_item_extract_id($role) {
  return $role->rid;
}

