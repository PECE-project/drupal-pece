<?php

/**
 * Implements hook_views_data_alter().
 */
function entityreference_view_widget_views_data_alter(&$data) {
  foreach (entity_get_info() as $info) {
    if (isset($info['base table']) && isset($data[$info['base table']]['table'])) {
      $data[$info['base table']]['entityreference_view_widget'] = array(
        'title' => $data[$info['base table']]['table']['group'],
        'group' => t('Entity Reference View Widget Checkbox'),
        'help' => t('Provide a checkbox to select the row for an entity reference.'),
        'real field' => $info['entity keys']['id'],
        'field' => array(
          'handler' => 'entityreference_view_widget_handler_field_checkbox',
          'click sortable' => FALSE,
        ),
      );
      // Support for EFQ Views.
      $efq = 'efq_' . $info['base table'];
      if (isset($data[$efq]['table'])) {
        $data[$efq]['entityreference_view_widget'] = $data[$info['base table']]['entityreference_view_widget'];
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
