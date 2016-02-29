<?php

/**
 * Implements hook_kw_itemnames_type_info().
 */
function kw_itemnames_paragraphs_kw_itemnames_type_info() {
  $result = array();

  $result['paragraphs_item'] = array(
    'item load callback' => 'kw_itemnames_paragraphs_item_load',
    'item load arguments' => array('%item_id'),

    'item create callback' => 'kw_itemnames_paragraphs_item_create',
    'item create arguments' => array('%defaults', '%required'),

    'item update callback' => 'kw_itemnames_paragraphs_item_update',
    'item update arguments' => array('%item', '%required'),

    'item delete callback' => 'kw_itemnames_paragraphs_item_delete',
    'item delete arguments' => array('%item_id'),

    'item extract id callback' => 'kw_itemnames_paragraphs_item_extract_id',
    'item extract id arguments' => array('%item'),
  );

  return $result;
}

function kw_itemnames_paragraphs_item_load($entity_id) {
  $entities = entity_load('paragraphs_item', array($entity_id));
  return !empty($entities) ? reset($entities) : FALSE;
}

function kw_itemnames_paragraphs_item_create($defaults, $required) {
  $entity_array = $required + $defaults;
  $ignore = _kw_itemnames_paragraphs_ignore_key_list();

  $hostEntity = $entity_array['hostEntity'];
  $hostEntityType = $entity_array['hostEntityType'];
  $field_name = $entity_array['fieldName'];

  $info = entity_get_info('paragraphs_item');
  $start_array = array();
  foreach ($info['bundle keys'] as $type => $key) {
    if (isset($entity_array[$key])) {
      $start_array[$key] = $entity_array[$key];
    }
  }

  $start_array['field_name'] = $field_name;

  $entity = entity_create('paragraphs_item', $start_array);
  foreach ($entity_array as $key => $value) {
    if (in_array($key, $ignore)) {
      continue;
    }
    $entity->{$key} = $value;
  }

  $entity->setHostEntity($hostEntityType, $hostEntity);

  $entity->save(TRUE);

  return $entity;
}

function kw_itemnames_paragraphs_item_update($entity, $required) {
  $ignore = _kw_itemnames_paragraphs_ignore_key_list();
  foreach ($required as $key => $value) {
    if (in_array($key, $ignore)) {
      continue;
    }
    $entity->{$key} = $value;
  }

  $entity->forceHostEntity($required['hostEntity']);
  $entity->save();

  return $entity;
}

function kw_itemnames_paragraphs_item_delete($entity_id) {
  entity_delete('paragraphs_item', $entity_id);
}

function kw_itemnames_paragraphs_item_extract_id($entity) {
  list($entity_id, ,) = entity_extract_ids('paragraphs_item', $entity);
  return $entity_id;
}
