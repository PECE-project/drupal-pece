<?php

/**
 * Implements hook_kw_itemnames_type_info().
 */
function kw_itemnames_url_alias_kw_itemnames_type_info() {
  $result = array();

  $result['url_alias'] = array(
    'item load callback' => 'path_load',
    'item create callback' => 'kw_itemnames_url_alias_item_create',
    'item update callback' => 'kw_itemnames_url_alias_item_update',
    'item delete callback' => 'path_delete',
    'item extract id callback' => 'kw_itemnames_url_alias_item_extract_id',
  );

  return $result;
}

function kw_itemnames_url_alias_item_create($defaults, $required) {
  $path = $required + $defaults;
  path_save($path);
  return $path;
}

function kw_itemnames_url_alias_item_update($path, $required) {
  foreach ($required as $key => $value) {
    $path[$key] = $value;
  }
  path_save($path);
  return $path;
}

function kw_itemnames_url_alias_item_extract_id($path) {
  return $path['pid'];
}

