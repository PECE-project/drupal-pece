<?php

/**
 * @file
 * Node seed implementation.
 */

/**
 * Create a node seed.
 */
function seeds_node_seed_create($data = array()) {
  $info = field_info_instances('node');

  // Defaults.
  $node = $data + array(
    'title' => 'Default seed node title',
    'type' => array_keys($info)[0],
    'language' => LANGUAGE_NONE,
    'status' => 1,
    'promote' => 0,
    'comment' => 1,
  );

  // Return existing node, if available.
  if ($existing_node = _seeds_node_find($node)) {
    $node = $existing_node;
  }
  // Create node, if not found.
  else {
    $node = (object) $node;
    _seeds_entity_prepare_fieds($node);
    node_save($node);
  }

  // If no nid is present, the node was neither found nor saved correctly.
  if (empty($node->nid)) {
    return NULL;
  }

  _seeds_entity_simplify_fieds($node);

  return $node;
}

/**
 * Remove a node seed.
 */
function seeds_node_seed_remove($data = array(), $value = array()) {
  $node = _seeds_node_find($value);
  if (!empty($node)) {
    node_delete($node->nid);
    return TRUE;
  }
  return FALSE;
}

/**
 * Helper method to find a node by it's possible unique properties.
 */
function _seeds_node_find($info) {
  if (!empty($info['nid']) && $existing_node = node_load($info['nid'])) {
    return $existing_node;
  }
  return NULL;
}

/**
 * Helper method to map to language structured fields
 * from the simplified JSON format.
 */
function _seeds_entity_prepare_fieds($entity, $entity_type = 'node') {
  $info = field_info_instances($entity_type);
  foreach ($info[$entity->type] as $field_name => $field_instance_info) {
    if (!empty($entity->{$field_name})) {
      $entity->{$field_name} = array(
        $entity->language => is_array($entity->{$field_name}) ? $entity->{$field_name} : array(
          $entity->{$field_name}
        ),
      );

      // @todo: make the following logic in a hook?
      $field_info = field_info_field($field_name);

      switch ($field_info['type']) {
        case 'taxonomy_term_reference':
          foreach ($entity->{$field_name}[$entity->language] as $key => $value) {
            $entity->{$field_name}[$entity->language][$key] = array(
              'tid' => $value,
            );
          }
          break;

        case 'text_long':
          foreach ($entity->{$field_name}[$entity->language] as $key => $value) {
            $entity->{$field_name}[$entity->language][$key] = array(
              'value' => $value,
            );
          }
          break;
      }
    }
  }
}

/**
 * Helper method to map from language structured fields
 * to the simplified JSON
 */
function _seeds_entity_simplify_fieds($entity, $entity_type = 'node') {
  $info = field_info_instances($entity_type);
  foreach ($info[$entity->type] as $field_name => $field_instance_info) {
    if (!empty($entity->{$field_name})) {
      $entity->{$field_name} = $entity->{$field_name}[$entity->language];
    }

    // @todo: make the following logic in a hook?
    $field_info = field_info_field($field_name);

    switch ($field_info['type']) {
      case 'taxonomy_term_reference':
        foreach ($entity->{$field_name} as $key => $value) {
          $entity->{$field_name}[$key] = $value['tid'];
        }
        break;

      case 'text_long':
        foreach ($entity->{$field_name} as $key => $value) {
          $entity->{$field_name}[$key] = $value['value'];
        }
        break;
    }

    // Parse single valued fields.
    if (count($entity->{$field_name}) == 1) {
      $entity->{$field_name} = $entity->{$field_name}[0];
    }
  }
}
