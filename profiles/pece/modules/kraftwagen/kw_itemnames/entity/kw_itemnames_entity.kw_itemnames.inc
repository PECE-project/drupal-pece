<?php

/**
 * Implements hook_kw_itemnames_type_info().
 */
function kw_itemnames_entity_kw_itemnames_type_info() {
  $result = array();

  foreach(entity_get_info() as $entity_type => $entity_info) {
    if (isset($entity_info['kw_itemnames_entity_disabled']) && empty($entity_info['kw_itemnames_entity_disabled'])) {
      continue;
    }

    $result[$entity_type] = array(
      'item load callback' => 'kw_itemnames_entity_item_load',
      'item load arguments' => array($entity_type, '%item_id'),

      'item create callback' => 'kw_itemnames_entity_item_create',
      'item create arguments' => array($entity_type, '%defaults', '%required'),

      'item update callback' => 'kw_itemnames_entity_item_update',
      'item update arguments' => array($entity_type, '%item', '%required'),

      'item delete callback' => 'kw_itemnames_entity_item_delete',
      'item delete arguments' => array($entity_type, '%item_id'),

      'item extract id callback' => 'kw_itemnames_entity_item_extract_id',
      'item extract id arguments' => array($entity_type, '%item'),
    );
  }

  return $result;
}

function kw_itemnames_entity_item_load($entity_type, $entity_id) {
  $entities = entity_load($entity_type, array($entity_id));
  return !empty($entities) ? reset($entities) : FALSE;
}

function kw_itemnames_entity_item_create($entity_type, $defaults, $required) {
  $entity_array = $required + $defaults;
  $info = entity_get_info($entity_type);

  $start_array = array();
  foreach ($info['entity keys'] as $type => $key) {
    if (isset($entity_array[$key])) {
      $start_array[$key] = $entity_array[$key];
    }
  }

  $entity = entity_create($entity_type, $start_array);
  foreach ($entity_array as $key => $value) {
    $entity->{$key} = $value;
  }
  entity_save($entity_type, $entity);

  return $entity;
}

function kw_itemnames_entity_item_update($entity_type, $entity, $required) {
  foreach ($required as $key => $value) {
    $entity->{$key} = $value;
  }
  entity_save($entity_type, $entity);
  return $entity;
}

function kw_itemnames_entity_item_delete($entity_type, $entity_id) {
  entity_delete($entity_type, $entity_id);
}

function kw_itemnames_entity_item_extract_id($entity_type, $entity) {
  list($entity_id,,) = entity_extract_ids($entity_type, $entity);
  return $entity_id;
}

