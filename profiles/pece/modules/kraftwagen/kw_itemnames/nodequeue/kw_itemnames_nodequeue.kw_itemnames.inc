<?php

/**
 * Implements hook_kw_itemnames_type_info().
 */
function kw_itemnames_nodequeue_kw_itemnames_type_info() {
  $result = array();

  $result['nodequeue'] = array(
    'item load callback' => 'nodequeue_load',
    'item create callback' => 'kw_itemnames_nodequeue_item_create',
    'item update callback' => 'kw_itemnames_nodequeue_item_update',
    'item delete callback' => 'nodequeue_delete',
    'item extract id callback' => 'kw_itemnames_nodequeue_item_extract_id',
  );

  $result['subqueue'] = array(
    'item load callback' => 'nodequeue_load_subqueue',
    'item create callback' => 'kw_itemnames_subqueue_item_create',
    'item update callback' => 'kw_itemnames_subqueue_item_update',
    'item delete callback' => 'nodequeue_remove_subqueue',
    'item extract id callback' => 'kw_itemnames_subqueue_item_extract_id',
  );

  return $result;
}

function kw_itemnames_nodequeue_item_create($defaults, $required) {
  $queue = (object) ($required + $defaults);
  nodequeue_save($queue);
  return $queue;
}

function kw_itemnames_nodequeue_item_update($queue, $required) {
  foreach ($required as $key => $value) {
    $queue->{$key} = $value;
  }
  nodequeue_save($queue);
  return $queue;
}

function kw_itemnames_nodequeue_item_extract_id($queue) {
  return $queue->qid;
}

function kw_itemnames_subqueue_item_create($defaults, $required) {
  $subqueue = (object) ($required + $defaults);
  $subqueue = nodequeue_add_subqueue($subqueue->queue, $subqueue->title, $subqueue->reference);
  return $subqueue;
}

function kw_itemnames_subqueue_item_update($subqueue, $required) {
  if (isset($required['title'])) {
    nodequeue_subqueue_update_title($subqueue->sqid, $required['title']);
    $subqueue->title = $required['title'];
  }

  return $subqueue;
}

function kw_itemnames_subqueue_item_extract_id($subqueue) {
  return $subqueue->sqid;
}