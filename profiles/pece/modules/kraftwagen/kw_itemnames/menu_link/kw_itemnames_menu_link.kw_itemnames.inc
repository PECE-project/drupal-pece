<?php

/**
 * Implements hook_kw_itemnames_type_info().
 */
function kw_itemnames_menu_link_kw_itemnames_type_info() {
  $result = array();

  $result['menu_link'] = array(
    'item load callback' => 'menu_link_load',
    'item create callback' => 'kw_itemnames_menu_link_item_create',
    'item update callback' => 'kw_itemnames_menu_link_item_update',
    'item delete callback' => 'menu_link_delete',
    'item extract id callback' => 'kw_itemnames_menu_link_item_extract_id',
  );

  return $result;
}

function kw_itemnames_menu_link_item_create($defaults, $required) {
  $link = $required + $defaults;
  menu_link_save($link);
  return $link;
}

function kw_itemnames_menu_link_item_update($link, $required) {
  foreach ($required as $key => $value) {
    $link[$key] = $value;
  }
  menu_link_save($link);
  return $link;
}

function kw_itemnames_menu_link_item_extract_id($link) {
  return $link['mlid'];
}

