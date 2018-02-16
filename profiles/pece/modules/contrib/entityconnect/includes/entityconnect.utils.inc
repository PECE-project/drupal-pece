<?php

/**
 * Helper function to retieve all allowed entityreference fields.
 */
function _entityconnect_get_ref_fields() {
  $ref_fields = array();

  foreach (field_info_fields() as $id => $field) {
    // Add support for Entity reference module.
    if ($field['type'] == 'entityreference' && $field['module'] == 'entityreference') {
      $entity_reference_info = entityreference_get_selection_handler($field);
      $entity_type = $entity_reference_info->field['settings']['target_type'];
      $target_bundle = isset($entity_reference_info->field['settings']['handler_settings']['target_bundles']) ? $entity_reference_info->field['settings']['handler_settings']['target_bundles'] : NULL;

      switch ($entity_type) {
        case 'user':
          if (user_access('administer users') && (user_access('entityconnect add button') || user_access('entityconnect edit button'))) {
            $ref_fields[$id] = $field;
          }
          break;

        case 'node':
          if (isset($target_bundle) && count($target_bundle) == 1) {
            if ((user_access('create ' . array_pop($target_bundle) . ' content') || user_access('administer nodes'))
              && (user_access('entityconnect add button') || user_access('entityconnect edit button'))) {
              $ref_fields[$id] = $field;
            }
          }
          elseif (user_access('entityconnect add button') || user_access('entityconnect edit button')) {
            $ref_fields[$id] = $field;
          }
          break;

        case 'taxonomy_term':
          if (user_access('entityconnect add button') || user_access('entityconnect edit button')) {
            $ref_fields[$id] = $field;
          }
          break;

        case 'taxonomy_vocabulary':
          if (user_access('entityconnect add button') || user_access('entityconnect edit button')) {
            $ref_fields[$id] = $field;
          }
          break;

        default:
          break;
      }
    }

    // Add support for Reference module.
    if (($field['type'] == 'node_reference' && $field['module'] == 'node_reference')
      || ($field['type'] == 'user_reference' && $field['module'] == 'user_reference')) {
      if (user_access('entityconnect add button') || user_access('entityconnect edit button')) {
        $ref_fields[$id] = $field;
      }
    }
  }

  drupal_alter('entityconnect_ref_fields', $ref_fields);

  return $ref_fields;
}

function _entityconnect_get_references_field_type_list() {

  $modules_list = array(
    'entityreference',
    'node_reference',
    'user_reference'
  );
  drupal_alter('entityconnect_field_type_list', $modules_list);

  return $modules_list;
}
