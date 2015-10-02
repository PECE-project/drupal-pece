<?php
/**
 * @file
 * pece_annotations.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function pece_annotations_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'pece_annotations';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'pece_annotations';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['expose_sort_order'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_pece_artifact_target_id']['id'] = 'field_pece_artifact_target_id';
  $handler->display->display_options['relationships']['field_pece_artifact_target_id']['table'] = 'field_data_field_pece_artifact';
  $handler->display->display_options['relationships']['field_pece_artifact_target_id']['field'] = 'field_pece_artifact_target_id';
  $handler->display->display_options['relationships']['field_pece_artifact_target_id']['label'] = 'Artifact';
  /* Field: Content: Author(s) */
  $handler->display->display_options['fields']['field_pece_authors']['id'] = 'field_pece_authors';
  $handler->display->display_options['fields']['field_pece_authors']['table'] = 'field_data_field_pece_authors';
  $handler->display->display_options['fields']['field_pece_authors']['field'] = 'field_pece_authors';
  $handler->display->display_options['fields']['field_pece_authors']['label'] = '';
  $handler->display->display_options['fields']['field_pece_authors']['element_type'] = '0';
  $handler->display->display_options['fields']['field_pece_authors']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_pece_authors']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_pece_authors']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_pece_authors']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_pece_authors']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_pece_authors']['field_api_classes'] = TRUE;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'long';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'panopoly_time';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['relationship'] = 'field_pece_artifact_target_id';
  $handler->display->display_options['fields']['title_1']['label'] = 'Artifact Title';
  $handler->display->display_options['fields']['title_1']['exclude'] = TRUE;
  /* Field: Content: License */
  $handler->display->display_options['fields']['field_pece_license']['id'] = 'field_pece_license';
  $handler->display->display_options['fields']['field_pece_license']['table'] = 'field_data_field_pece_license';
  $handler->display->display_options['fields']['field_pece_license']['field'] = 'field_pece_license';
  $handler->display->display_options['fields']['field_pece_license']['label'] = '';
  $handler->display->display_options['fields']['field_pece_license']['element_type'] = '0';
  $handler->display->display_options['fields']['field_pece_license']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_pece_license']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_pece_license']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_pece_license']['field_api_classes'] = TRUE;
  /* Field: Field: Tags */
  $handler->display->display_options['fields']['field_pece_tags_1']['id'] = 'field_pece_tags_1';
  $handler->display->display_options['fields']['field_pece_tags_1']['table'] = 'field_data_field_pece_tags';
  $handler->display->display_options['fields']['field_pece_tags_1']['field'] = 'field_pece_tags';
  $handler->display->display_options['fields']['field_pece_tags_1']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_pece_tags_1']['delta_offset'] = '0';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Analytic (Question) (field_pece_analytic) */
  $handler->display->display_options['arguments']['field_pece_analytic_target_id']['id'] = 'field_pece_analytic_target_id';
  $handler->display->display_options['arguments']['field_pece_analytic_target_id']['table'] = 'field_data_field_pece_analytic';
  $handler->display->display_options['arguments']['field_pece_analytic_target_id']['field'] = 'field_pece_analytic_target_id';
  $handler->display->display_options['arguments']['field_pece_analytic_target_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_pece_analytic_target_id']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['field_pece_analytic_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_pece_analytic_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_pece_analytic_target_id']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'pece_annotation' => 'pece_annotation',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Author uid */
  $handler->display->display_options['filters']['uid']['id'] = 'uid';
  $handler->display->display_options['filters']['uid']['table'] = 'node';
  $handler->display->display_options['filters']['uid']['field'] = 'uid';
  $handler->display->display_options['filters']['uid']['value'] = '';
  $handler->display->display_options['filters']['uid']['group'] = 1;
  $handler->display->display_options['filters']['uid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['uid']['expose']['operator_id'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['label'] = 'User';
  $handler->display->display_options['filters']['uid']['expose']['operator'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['identifier'] = 'uid';
  $handler->display->display_options['filters']['uid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    6 => 0,
    5 => 0,
  );
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['relationship'] = 'field_pece_artifact_target_id';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['group'] = 1;
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Artifact';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'artifact';
  $handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    6 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['title']['expose']['autocomplete_filter'] = 1;
  $handler->display->display_options['filters']['title']['expose']['autocomplete_items'] = '10';
  $handler->display->display_options['filters']['title']['expose']['autocomplete_min_chars'] = '0';
  $handler->display->display_options['filters']['title']['expose']['autocomplete_field'] = 'title_1';
  $handler->display->display_options['filters']['title']['expose']['autocomplete_raw_suggestion'] = 1;
  $handler->display->display_options['filters']['title']['expose']['autocomplete_raw_dropdown'] = 1;
  $handler->display->display_options['filters']['title']['expose']['autocomplete_dependent'] = 0;

  /* Display: Question annotations */
  $handler = $view->new_display('panel_pane', 'Question annotations', 'question_annotations');
  $handler->display->display_options['exposed_block'] = TRUE;
  $translatables['pece_annotations'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('Artifact'),
    t('Artifact Title'),
    t('Tags'),
    t('All'),
    t('User'),
    t('Question annotations'),
    t('View panes'),
  );
  $export['pece_annotations'] = $view;

  $view = new view();
  $view->name = 'pece_annotations_analytics_ref';
  $view->description = 'PECE\'s Analytics reference list.';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'PECE Analytics: Analytics list reference';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Entity Reference View Widget Checkbox: Content */
  $handler->display->display_options['fields']['entityreference_view_widget']['id'] = 'entityreference_view_widget';
  $handler->display->display_options['fields']['entityreference_view_widget']['table'] = 'node';
  $handler->display->display_options['fields']['entityreference_view_widget']['field'] = 'entityreference_view_widget';
  $handler->display->display_options['fields']['entityreference_view_widget']['label'] = '';
  $handler->display->display_options['fields']['entityreference_view_widget']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['entityreference_view_widget']['ervw']['force_single'] = 1;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Question';
  /* Field: Content: Question Set */
  $handler->display->display_options['fields']['field_pece_struct_analytics']['id'] = 'field_pece_struct_analytics';
  $handler->display->display_options['fields']['field_pece_struct_analytics']['table'] = 'field_data_field_pece_struct_analytics';
  $handler->display->display_options['fields']['field_pece_struct_analytics']['field'] = 'field_pece_struct_analytics';
  $handler->display->display_options['fields']['field_pece_struct_analytics']['label'] = '';
  $handler->display->display_options['fields']['field_pece_struct_analytics']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_pece_struct_analytics']['element_type'] = '0';
  $handler->display->display_options['fields']['field_pece_struct_analytics']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_pece_struct_analytics']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_pece_struct_analytics']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_pece_struct_analytics']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_pece_struct_analytics']['group_columns'] = array(
    'entity_id' => 'entity_id',
  );
  $handler->display->display_options['fields']['field_pece_struct_analytics']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_pece_struct_analytics']['field_api_classes'] = TRUE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'pece_analytic' => 'pece_analytic',
  );

  /* Display: Entity Reference View Widget */
  $handler = $view->new_display('entityreference_view_widget', 'Entity Reference View Widget', 'entityreference_view_widget_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['defaults']['use_ajax'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_pece_struct_analytics',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['columns'] = array(
    'entityreference_view_widget' => 'entityreference_view_widget',
    'title' => 'title',
    'field_pece_struct_analytics' => 'field_pece_struct_analytics',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'entityreference_view_widget' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_pece_struct_analytics' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $translatables['pece_annotations_analytics_ref'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('Question'),
    t('Entity Reference View Widget'),
  );
  $export['pece_annotations_analytics_ref'] = $view;

  return $export;
}
