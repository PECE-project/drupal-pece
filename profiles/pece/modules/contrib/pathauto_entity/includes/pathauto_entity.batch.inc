<?php

/**
 * @file
 * Pathauto Entity batch callback implementations.
 */

/**
 * Batch callback; count the current number of URL aliases for comparison later.
 *
 * Added here only because it needs to be in the same file as main
 * pathauto_entity_bulk_update_batch_process().
 *
 * @see pathauto_entity_bulk_update_form_submit()
 */
function pathauto_entity_bulk_update_batch_start(&$context) {
  module_load_include('inc', 'pathauto', 'pathauto.admin');
  pathauto_bulk_update_batch_start($context);
}

/**
 * Common batch processing callback for entity-based operations.
 *
 * Required to load the proper batch file.
 *
 * Overrides pathauto_bulk_update_batch_process().
 *
 * @see pathauto_entity_bulk_update_form_submit()
 * @see pathauto_bulk_update_batch_process()
 */
function pathauto_entity_bulk_update_batch_process($callback, $settings, &$context) {
  if (!empty($settings->batch_file)) {
    require_once DRUPAL_ROOT . '/' . $settings->batch_file;
  }
  // When dealing with entity aliases we also need to pass $settings array to
  // callback function, so it knows which entity types to generate aliases for.
  if ($callback == 'pathauto_entity_bulk_update_batch_callback') {
    return $callback($settings, $context);
  }
  else {
    return $callback($context);
  }
}

/**
 * Batch processing callback; Generate aliases for entities.
 *
 * Differs from standard bulk update callback functions by having $settings
 * as parameter, which we need to know which entity type should URL aliases
 * be generated for.
 *
 * @see pathauto_entity_pathauto()
 * @see pathauto_entity_bulk_update_batch_process()
 */
function pathauto_entity_bulk_update_batch_callback($settings, &$context) {
  if (!isset($context['sandbox']['count'])) {
    // First pass. Build an array with all the pairs of id and entity type to process.
    $context['sandbox']['count'] = 0;
    $context['sandbox']['items'] = array();

    $entity_type = $settings->module;

    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', $entity_type);
    $result = $query->execute();
    $ids = isset($result[$entity_type]) ? array_keys($result[$entity_type]) : array();

    foreach ($ids as $id) {
      $context['sandbox']['items'][] = array(
        'id' => $id,
        'type' => $entity_type
      );
    }
    $context['sandbox']['total'] = count($context['sandbox']['items']);

    // If there are no items to update, stop immediately.
    if (!$context['sandbox']['total']) {
      $context['finished'] = 1;
      return;
    }
  }

  // Extract 25 items to be processed in this pass.
  $items_to_process = array_slice($context['sandbox']['items'], $context['sandbox']['count'], 25);
  module_load_include('inc', 'pathauto');

  foreach ($items_to_process as $item) {
    $entity = entity_load($item['type'], array($item['id']));
    $entity = reset($entity);
    pathauto_entity_update_alias($item['type'], $entity, 'bulkupdate');
  }

  // Update progress stats.
  $context['sandbox']['count'] += count($items_to_process);
  if ($context['sandbox']['count'] != $context['sandbox']['total']) {
    $context['finished'] = $context['sandbox']['count'] / $context['sandbox']['total'];
  }
}

/**
 * Batch finished callback.
 *
 * Added here only because it needs to be in the same file as main
 * pathauto_entity_bulk_update_batch_process().
 *
 * @see pathauto_entity_bulk_update_form_submit()
 */
function pathauto_entity_bulk_update_batch_finished($success, $results, $operations) {
  module_load_include('inc', 'pathauto', 'pathauto.admin');
  pathauto_bulk_update_batch_finished($success, $results, $operations);
}
