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
  $view->description = 'Lists annotations';
  $view->tag = 'PECE';
  $view->base_table = 'node';
  $view->human_name = 'PECE Annotations';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Annotations';
  $handler->display->display_options['use_ajax'] = TRUE;
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
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
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
  $handler->display->display_options['fields']['title_1']['label'] = 'In response to';
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
  $handler->display->display_options['arguments']['field_pece_analytic_target_id']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['field_pece_analytic_target_id']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['field_pece_analytic_target_id']['validate_options']['types'] = array(
    'pece_analytic' => 'pece_analytic',
  );
  $handler->display->display_options['arguments']['field_pece_analytic_target_id']['validate_options']['access'] = TRUE;
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
  $handler = $view->new_display('panel_pane', 'Question annotations', 'pece_question_annotations');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: User: Rendered User */
  $handler->display->display_options['fields']['rendered_entity']['id'] = 'rendered_entity';
  $handler->display->display_options['fields']['rendered_entity']['table'] = 'views_entity_user';
  $handler->display->display_options['fields']['rendered_entity']['field'] = 'rendered_entity';
  $handler->display->display_options['fields']['rendered_entity']['relationship'] = 'uid';
  $handler->display->display_options['fields']['rendered_entity']['label'] = '';
  $handler->display->display_options['fields']['rendered_entity']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['rendered_entity']['link_to_entity'] = 1;
  $handler->display->display_options['fields']['rendered_entity']['display'] = 'view';
  $handler->display->display_options['fields']['rendered_entity']['view_mode'] = 'pece_thumbnail';
  $handler->display->display_options['fields']['rendered_entity']['bypass_access'] = 0;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'panopoly_day';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'panopoly_time';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['relationship'] = 'field_pece_artifact_target_id';
  $handler->display->display_options['fields']['title_1']['label'] = '';
  $handler->display->display_options['fields']['title_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title_1']['element_label_colon'] = FALSE;
  /* Field: Content: Artifact */
  $handler->display->display_options['fields']['field_pece_artifact']['id'] = 'field_pece_artifact';
  $handler->display->display_options['fields']['field_pece_artifact']['table'] = 'field_data_field_pece_artifact';
  $handler->display->display_options['fields']['field_pece_artifact']['field'] = 'field_pece_artifact';
  $handler->display->display_options['fields']['field_pece_artifact']['label'] = 'In response to:';
  $handler->display->display_options['fields']['field_pece_artifact']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_pece_artifact']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['field_pece_artifact']['element_wrapper_class'] = 'views-field-artifact-mini-teaser';
  $handler->display->display_options['fields']['field_pece_artifact']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_pece_artifact']['type'] = 'entityreference_entity_view';
  $handler->display->display_options['fields']['field_pece_artifact']['settings'] = array(
    'view_mode' => 'mini_teaser',
    'links' => 0,
    'use_content_language' => 1,
  );
  $handler->display->display_options['fields']['field_pece_artifact']['field_api_classes'] = TRUE;
  /* Field: Content: Description */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['element_type'] = '0';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['body']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['body']['field_api_classes'] = TRUE;
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = '';
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['edit_node']['text'] = 'Edit Annotation';

  /* Display: Artifact Annotations - Users  */
  $handler = $view->new_display('panel_pane', 'Artifact Annotations - Users ', 'pece_artifact_user_annotations');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Annotations';
  $handler->display->display_options['display_description'] = 'List users that have added annotations to a given artifact.';
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['defaults']['query'] = FALSE;
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['query']['options']['pure_distinct'] = TRUE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['exposed_block'] = TRUE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: User: Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['relationship'] = 'uid';
  $handler->display->display_options['fields']['uid']['exclude'] = TRUE;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['path'] = 'annotations/user/[uid]/artifact/!1';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_user'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Artifact (field_pece_artifact) */
  $handler->display->display_options['arguments']['field_pece_artifact_target_id_1']['id'] = 'field_pece_artifact_target_id_1';
  $handler->display->display_options['arguments']['field_pece_artifact_target_id_1']['table'] = 'field_data_field_pece_artifact';
  $handler->display->display_options['arguments']['field_pece_artifact_target_id_1']['field'] = 'field_pece_artifact_target_id';
  $handler->display->display_options['arguments']['field_pece_artifact_target_id_1']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_pece_artifact_target_id_1']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['field_pece_artifact_target_id_1']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_pece_artifact_target_id_1']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_pece_artifact_target_id_1']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_pece_artifact_target_id_1']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['field_pece_artifact_target_id_1']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['field_pece_artifact_target_id_1']['validate_options']['types'] = array(
    'pece_artifact_audio' => 'pece_artifact_audio',
    'pece_artifact_bundle' => 'pece_artifact_bundle',
    'pece_artifact_fieldnote' => 'pece_artifact_fieldnote',
    'pece_artifact_image' => 'pece_artifact_image',
    'pece_artifact_pdf' => 'pece_artifact_pdf',
    'pece_artifact_text' => 'pece_artifact_text',
    'pece_artifact_video' => 'pece_artifact_video',
    'pece_artifact_website' => 'pece_artifact_website',
  );
  $handler->display->display_options['arguments']['field_pece_artifact_target_id_1']['validate_options']['access'] = TRUE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
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

  /* Display: User - Artifact Annotations */
  $handler = $view->new_display('page', 'User - Artifact Annotations', 'pece_user_artifact_annotations');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = '[picture] %1 - [field_pece_artifact] Annotations';
  $handler->display->display_options['display_description'] = 'List annotations for a given user and a given artifact.';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_pece_analytic_target_id']['id'] = 'field_pece_analytic_target_id';
  $handler->display->display_options['relationships']['field_pece_analytic_target_id']['table'] = 'field_data_field_pece_analytic';
  $handler->display->display_options['relationships']['field_pece_analytic_target_id']['field'] = 'field_pece_analytic_target_id';
  $handler->display->display_options['relationships']['field_pece_analytic_target_id']['label'] = 'Question';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: User: Picture */
  $handler->display->display_options['fields']['picture']['id'] = 'picture';
  $handler->display->display_options['fields']['picture']['table'] = 'users';
  $handler->display->display_options['fields']['picture']['field'] = 'picture';
  $handler->display->display_options['fields']['picture']['relationship'] = 'uid';
  $handler->display->display_options['fields']['picture']['label'] = '';
  $handler->display->display_options['fields']['picture']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['picture']['image_style'] = 'pece_mini_teaser';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['relationship'] = 'field_pece_analytic_target_id';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  /* Field: Content: Artifact */
  $handler->display->display_options['fields']['field_pece_artifact']['id'] = 'field_pece_artifact';
  $handler->display->display_options['fields']['field_pece_artifact']['table'] = 'field_data_field_pece_artifact';
  $handler->display->display_options['fields']['field_pece_artifact']['field'] = 'field_pece_artifact';
  $handler->display->display_options['fields']['field_pece_artifact']['label'] = '';
  $handler->display->display_options['fields']['field_pece_artifact']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_pece_artifact']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_pece_artifact']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_pece_artifact']['settings'] = array(
    'link' => 0,
  );
  /* Field: Content: Artifact */
  $handler->display->display_options['fields']['field_pece_artifact_1']['id'] = 'field_pece_artifact_1';
  $handler->display->display_options['fields']['field_pece_artifact_1']['table'] = 'field_data_field_pece_artifact';
  $handler->display->display_options['fields']['field_pece_artifact_1']['field'] = 'field_pece_artifact';
  $handler->display->display_options['fields']['field_pece_artifact_1']['label'] = '';
  $handler->display->display_options['fields']['field_pece_artifact_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_pece_artifact_1']['type'] = 'entityreference_entity_view';
  $handler->display->display_options['fields']['field_pece_artifact_1']['settings'] = array(
    'view_mode' => 'mini_teaser',
    'links' => 0,
    'use_content_language' => 1,
  );
  /* Field: Content: Analytic (Question) */
  $handler->display->display_options['fields']['field_pece_analytic']['id'] = 'field_pece_analytic';
  $handler->display->display_options['fields']['field_pece_analytic']['table'] = 'field_data_field_pece_analytic';
  $handler->display->display_options['fields']['field_pece_analytic']['field'] = 'field_pece_analytic';
  $handler->display->display_options['fields']['field_pece_analytic']['label'] = '';
  $handler->display->display_options['fields']['field_pece_analytic']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_pece_analytic']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_pece_analytic']['alter']['path'] = 'annotions/question/[nid]/artifact/!2';
  $handler->display->display_options['fields']['field_pece_analytic']['element_type'] = 'h2';
  $handler->display->display_options['fields']['field_pece_analytic']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_pece_analytic']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_pece_analytic']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_pece_analytic']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_pece_analytic']['field_api_classes'] = TRUE;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'long';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'panopoly_time';
  /* Field: Content: Question Set */
  $handler->display->display_options['fields']['field_pece_struct_analytics']['id'] = 'field_pece_struct_analytics';
  $handler->display->display_options['fields']['field_pece_struct_analytics']['table'] = 'field_data_field_pece_struct_analytics';
  $handler->display->display_options['fields']['field_pece_struct_analytics']['field'] = 'field_pece_struct_analytics';
  $handler->display->display_options['fields']['field_pece_struct_analytics']['relationship'] = 'field_pece_analytic_target_id';
  $handler->display->display_options['fields']['field_pece_struct_analytics']['label'] = 'Structured Analytic';
  $handler->display->display_options['fields']['field_pece_struct_analytics']['element_type'] = 'span';
  $handler->display->display_options['fields']['field_pece_struct_analytics']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_pece_struct_analytics']['settings'] = array(
    'link' => 1,
  );
  $handler->display->display_options['fields']['field_pece_struct_analytics']['delta_offset'] = '0';
  /* Field: Content: Description */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['element_type'] = '0';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['body']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '600',
  );
  $handler->display->display_options['fields']['body']['field_api_classes'] = TRUE;
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
  $handler->display->display_options['fields']['field_pece_tags']['id'] = 'field_pece_tags';
  $handler->display->display_options['fields']['field_pece_tags']['table'] = 'field_data_field_pece_tags';
  $handler->display->display_options['fields']['field_pece_tags']['field'] = 'field_pece_tags';
  $handler->display->display_options['fields']['field_pece_tags']['label'] = '';
  $handler->display->display_options['fields']['field_pece_tags']['element_type'] = '0';
  $handler->display->display_options['fields']['field_pece_tags']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_pece_tags']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_pece_tags']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_pece_tags']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_pece_tags']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_pece_tags']['field_api_classes'] = TRUE;
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = '';
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['edit_node']['text'] = 'Edit Annotation';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: User: Uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'users';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['relationship'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Content: Artifact (field_pece_artifact) */
  $handler->display->display_options['arguments']['field_pece_artifact_target_id']['id'] = 'field_pece_artifact_target_id';
  $handler->display->display_options['arguments']['field_pece_artifact_target_id']['table'] = 'field_data_field_pece_artifact';
  $handler->display->display_options['arguments']['field_pece_artifact_target_id']['field'] = 'field_pece_artifact_target_id';
  $handler->display->display_options['arguments']['field_pece_artifact_target_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_pece_artifact_target_id']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['field_pece_artifact_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_pece_artifact_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_pece_artifact_target_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_pece_artifact_target_id']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['field_pece_artifact_target_id']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['field_pece_artifact_target_id']['validate_options']['types'] = array(
    'pece_artifact_audio' => 'pece_artifact_audio',
    'pece_artifact_bundle' => 'pece_artifact_bundle',
    'pece_artifact_fieldnote' => 'pece_artifact_fieldnote',
    'pece_artifact_image' => 'pece_artifact_image',
    'pece_artifact_pdf' => 'pece_artifact_pdf',
    'pece_artifact_text' => 'pece_artifact_text',
    'pece_artifact_video' => 'pece_artifact_video',
    'pece_artifact_website' => 'pece_artifact_website',
  );
  $handler->display->display_options['arguments']['field_pece_artifact_target_id']['validate_options']['access'] = TRUE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
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
  $handler->display->display_options['path'] = 'annotations/user/%/artifact/%';

  /* Display: Questions - Artifacts Annotetions */
  $handler = $view->new_display('page', 'Questions - Artifacts Annotetions', 'pece_question_artifact_annotions');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = '%1 [field_pece_struct_analytics] - %2';
  $handler->display->display_options['defaults']['footer'] = FALSE;
  /* Footer: Global: Text area */
  $handler->display->display_options['footer']['area']['id'] = 'area';
  $handler->display->display_options['footer']['area']['table'] = 'views';
  $handler->display->display_options['footer']['area']['field'] = 'area';
  $handler->display->display_options['footer']['area']['content'] = '<a href="/node/!1">See all responses to this analytic</a>';
  $handler->display->display_options['footer']['area']['format'] = 'panopoly_wysiwyg_text';
  $handler->display->display_options['footer']['area']['tokenize'] = TRUE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_pece_analytic_target_id']['id'] = 'field_pece_analytic_target_id';
  $handler->display->display_options['relationships']['field_pece_analytic_target_id']['table'] = 'field_data_field_pece_analytic';
  $handler->display->display_options['relationships']['field_pece_analytic_target_id']['field'] = 'field_pece_analytic_target_id';
  $handler->display->display_options['relationships']['field_pece_analytic_target_id']['label'] = 'Analytic';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: User: Rendered User */
  $handler->display->display_options['fields']['rendered_entity']['id'] = 'rendered_entity';
  $handler->display->display_options['fields']['rendered_entity']['table'] = 'views_entity_user';
  $handler->display->display_options['fields']['rendered_entity']['field'] = 'rendered_entity';
  $handler->display->display_options['fields']['rendered_entity']['relationship'] = 'uid';
  $handler->display->display_options['fields']['rendered_entity']['label'] = '';
  $handler->display->display_options['fields']['rendered_entity']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['rendered_entity']['link_to_entity'] = 1;
  $handler->display->display_options['fields']['rendered_entity']['display'] = 'view';
  $handler->display->display_options['fields']['rendered_entity']['view_mode'] = 'pece_thumbnail';
  $handler->display->display_options['fields']['rendered_entity']['bypass_access'] = 0;
  /* Field: Content: Question Set */
  $handler->display->display_options['fields']['field_pece_struct_analytics']['id'] = 'field_pece_struct_analytics';
  $handler->display->display_options['fields']['field_pece_struct_analytics']['table'] = 'field_data_field_pece_struct_analytics';
  $handler->display->display_options['fields']['field_pece_struct_analytics']['field'] = 'field_pece_struct_analytics';
  $handler->display->display_options['fields']['field_pece_struct_analytics']['relationship'] = 'field_pece_analytic_target_id';
  $handler->display->display_options['fields']['field_pece_struct_analytics']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_pece_struct_analytics']['settings'] = array(
    'link' => 1,
  );
  $handler->display->display_options['fields']['field_pece_struct_analytics']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_pece_struct_analytics']['field_api_classes'] = TRUE;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'panopoly_day';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'panopoly_time';
  /* Field: Content: Description */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['element_type'] = '0';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['body']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['body']['field_api_classes'] = TRUE;
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
  $handler->display->display_options['fields']['field_pece_tags_1']['label'] = '';
  $handler->display->display_options['fields']['field_pece_tags_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_pece_tags_1']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_pece_tags_1']['delta_offset'] = '0';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Analytic (Question) (field_pece_analytic) */
  $handler->display->display_options['arguments']['field_pece_analytic_target_id']['id'] = 'field_pece_analytic_target_id';
  $handler->display->display_options['arguments']['field_pece_analytic_target_id']['table'] = 'field_data_field_pece_analytic';
  $handler->display->display_options['arguments']['field_pece_analytic_target_id']['field'] = 'field_pece_analytic_target_id';
  $handler->display->display_options['arguments']['field_pece_analytic_target_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_pece_analytic_target_id']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['field_pece_analytic_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_pece_analytic_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_pece_analytic_target_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_pece_analytic_target_id']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['field_pece_analytic_target_id']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['field_pece_analytic_target_id']['validate_options']['types'] = array(
    'pece_analytic' => 'pece_analytic',
  );
  $handler->display->display_options['arguments']['field_pece_analytic_target_id']['validate_options']['access'] = TRUE;
  /* Contextual filter: Content: Artifact (field_pece_artifact) */
  $handler->display->display_options['arguments']['field_pece_artifact_target_id']['id'] = 'field_pece_artifact_target_id';
  $handler->display->display_options['arguments']['field_pece_artifact_target_id']['table'] = 'field_data_field_pece_artifact';
  $handler->display->display_options['arguments']['field_pece_artifact_target_id']['field'] = 'field_pece_artifact_target_id';
  $handler->display->display_options['arguments']['field_pece_artifact_target_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_pece_artifact_target_id']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['field_pece_artifact_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_pece_artifact_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_pece_artifact_target_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_pece_artifact_target_id']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['field_pece_artifact_target_id']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['field_pece_artifact_target_id']['validate_options']['types'] = array(
    'pece_artifact_audio' => 'pece_artifact_audio',
    'pece_artifact_bundle' => 'pece_artifact_bundle',
    'pece_artifact_fieldnote' => 'pece_artifact_fieldnote',
    'pece_artifact_image' => 'pece_artifact_image',
    'pece_artifact_pdf' => 'pece_artifact_pdf',
    'pece_artifact_text' => 'pece_artifact_text',
    'pece_artifact_video' => 'pece_artifact_video',
    'pece_artifact_website' => 'pece_artifact_website',
  );
  $handler->display->display_options['arguments']['field_pece_artifact_target_id']['validate_options']['access'] = TRUE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
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
  $handler->display->display_options['path'] = 'annotions/question/%/artifact/%';
  $translatables['pece_annotations'] = array(
    t('Master'),
    t('Annotations'),
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
    t('author'),
    t('In response to'),
    t('Tags'),
    t('All'),
    t('User'),
    t('Question annotations'),
    t('In response to:'),
    t('Edit Annotation'),
    t('View panes'),
    t('Artifact Annotations - Users '),
    t('List users that have added annotations to a given artifact.'),
    t('Uid'),
    t('User - Artifact Annotations'),
    t('[picture] %1 - [field_pece_artifact] Annotations'),
    t('List annotations for a given user and a given artifact.'),
    t('Question'),
    t('Nid'),
    t('Structured Analytic'),
    t('Questions - Artifacts Annotetions'),
    t('%1 [field_pece_struct_analytics] - %2'),
    t('<a href="/node/!1">See all responses to this analytic</a>'),
    t('Analytic'),
    t('Question Set'),
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
