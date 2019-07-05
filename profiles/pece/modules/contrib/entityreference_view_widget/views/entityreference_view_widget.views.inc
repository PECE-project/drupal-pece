<?php

/**
 * @file
 * File: entityreference_view_widget.views.inc.
 */

/**
 * Implements hook_views_data_alter().
 */
function entityreference_view_widget_views_data_alter(&$data) {
  $tables = array();

  // Build entity tables.
  $entity_info = entity_get_info();
  foreach ($entity_info as $info) {
    if (isset($info['base table'])) {
      $tables[$info['base table']] = $info['entity keys']['id'];
    }
  }

  // Build search_api index tables.
  if (module_exists('search_api_views')) {
    foreach (search_api_index_load_multiple(FALSE) as $index) {
      $tables['search_api_index_' . $index->machine_name] = 'search_api_id';
    }
  }

  foreach ($tables as $table => $name) {
    if (isset($data[$table]['table'])) {
      $data[$table]['entityreference_view_widget'] = array(
        'title' => $data[$table]['table']['group'],
        'group' => t('Entity Reference View Widget Checkbox'),
        'help' => t('Provide a checkbox to select the row for an entity reference.'),
        'real field' => $name,
        'field' => array(
          'handler' => 'entityreference_view_widget_handler_field_checkbox',
          'click sortable' => FALSE,
        ),
      );

      // Support for EFQ Views.
      $efq = 'efq_' . $table;
      if (isset($data[$efq]['table'])) {
        $data[$efq]['entityreference_view_widget'] = $data[$table]['entityreference_view_widget'];
      }
    }
  }
}

/**
 * Implements hook_views_plugins().
 */
function entityreference_view_widget_views_plugins() {
  $entity_tables = array();
  $tables = views_fetch_data();
  foreach ($tables as $table_name => $table) {
    if (!empty($table['table']['entity type'])) {
      $entity_tables[] = $table_name;
    }
  }

  $plugins = array(
    'display' => array(
      'entityreference_view_widget' => array(
        'title' => t('Entity Reference View Widget'),
        'help' => t('Selects referenceable entities for an entity reference view widget.'),
        'handler' => 'entityreference_view_widget_plugin_display',
        'use ajax' => TRUE,
        'use pager' => TRUE,
        'use more' => FALSE,
        'accept attachments' => FALSE,
        'theme' => 'views_view',
        // Make this plugin only available to tables that map to an entity type.
        'base' => $entity_tables,
        // Custom property, used with views_get_applicable_views() to retrieve
        // all views with a 'Entity Reference View' display.
        'entityreference view display' => TRUE,
      ),
    ),
  );
  return $plugins;
}
