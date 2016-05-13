<?php
/**
 * @file
 * pece_artifacts_fieldnote.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function pece_artifacts_fieldnote_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'pece_group_field_diary';
  $view->description = '';
  $view->tag = 'PECE';
  $view->base_table = 'node';
  $view->human_name = 'PECE - Group Field Diary';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Group Field Diary';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Groups audience */
  $handler->display->display_options['fields']['og_group_ref']['id'] = 'og_group_ref';
  $handler->display->display_options['fields']['og_group_ref']['table'] = 'og_membership';
  $handler->display->display_options['fields']['og_group_ref']['field'] = 'og_group_ref';
  $handler->display->display_options['fields']['og_group_ref']['exclude'] = TRUE;
  $handler->display->display_options['fields']['og_group_ref']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['og_group_ref']['delta_offset'] = '0';
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['exclude'] = TRUE;
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'F d, Y';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'panopoly_time';
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['text'] = '<div class="field-diary-body">[body] <div class="read-more"><a href="/node/[nid]">(...)</a></div></div>';
  $handler->display->display_options['fields']['body']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['body']['element_type'] = '0';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['body']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['body']['type'] = 'text_trimmed';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '650',
  );
  $handler->display->display_options['fields']['body']['field_api_classes'] = TRUE;
  /* Field: Field: Tags */
  $handler->display->display_options['fields']['field_pece_tags']['id'] = 'field_pece_tags';
  $handler->display->display_options['fields']['field_pece_tags']['table'] = 'field_data_field_pece_tags';
  $handler->display->display_options['fields']['field_pece_tags']['field'] = 'field_pece_tags';
  $handler->display->display_options['fields']['field_pece_tags']['label'] = '';
  $handler->display->display_options['fields']['field_pece_tags']['element_type'] = '0';
  $handler->display->display_options['fields']['field_pece_tags']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_pece_tags']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_pece_tags']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_pece_tags']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_pece_tags']['field_api_classes'] = TRUE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Groups audience (og_group_ref) */
  $handler->display->display_options['arguments']['og_group_ref_target_id']['id'] = 'og_group_ref_target_id';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['field'] = 'og_group_ref_target_id';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['og_group_ref_target_id']['validate']['type'] = 'og';
  $handler->display->display_options['filter_groups']['operator'] = 'OR';
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'AND',
    2 => 'AND',
    3 => 'AND',
  );
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
    'pece_artifact_fieldnote' => 'pece_artifact_fieldnote',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Permissions (field_permissions) */
  $handler->display->display_options['filters']['field_permissions_value']['id'] = 'field_permissions_value';
  $handler->display->display_options['filters']['field_permissions_value']['table'] = 'field_data_field_permissions';
  $handler->display->display_options['filters']['field_permissions_value']['field'] = 'field_permissions_value';
  $handler->display->display_options['filters']['field_permissions_value']['value'] = array(
    'open' => 'open',
  );
  $handler->display->display_options['filters']['field_permissions_value']['group'] = 1;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status_1']['id'] = 'status_1';
  $handler->display->display_options['filters']['status_1']['table'] = 'node';
  $handler->display->display_options['filters']['status_1']['field'] = 'status';
  $handler->display->display_options['filters']['status_1']['value'] = '1';
  $handler->display->display_options['filters']['status_1']['group'] = 2;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type_2']['id'] = 'type_2';
  $handler->display->display_options['filters']['type_2']['table'] = 'node';
  $handler->display->display_options['filters']['type_2']['field'] = 'type';
  $handler->display->display_options['filters']['type_2']['value'] = array(
    'pece_artifact_fieldnote' => 'pece_artifact_fieldnote',
  );
  $handler->display->display_options['filters']['type_2']['group'] = 2;
  /* Filter criterion: Content: Permissions (field_permissions) */
  $handler->display->display_options['filters']['field_permissions_value_1']['id'] = 'field_permissions_value_1';
  $handler->display->display_options['filters']['field_permissions_value_1']['table'] = 'field_data_field_permissions';
  $handler->display->display_options['filters']['field_permissions_value_1']['field'] = 'field_permissions_value';
  $handler->display->display_options['filters']['field_permissions_value_1']['value'] = array(
    'restricted' => 'restricted',
  );
  $handler->display->display_options['filters']['field_permissions_value_1']['group'] = 2;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status_2']['id'] = 'status_2';
  $handler->display->display_options['filters']['status_2']['table'] = 'node';
  $handler->display->display_options['filters']['status_2']['field'] = 'status';
  $handler->display->display_options['filters']['status_2']['value'] = '1';
  $handler->display->display_options['filters']['status_2']['group'] = 3;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type_1']['id'] = 'type_1';
  $handler->display->display_options['filters']['type_1']['table'] = 'node';
  $handler->display->display_options['filters']['type_1']['field'] = 'type';
  $handler->display->display_options['filters']['type_1']['value'] = array(
    'pece_artifact_fieldnote' => 'pece_artifact_fieldnote',
  );
  $handler->display->display_options['filters']['type_1']['group'] = 3;
  /* Filter criterion: User: The user ID */
  $handler->display->display_options['filters']['uid_raw']['id'] = 'uid_raw';
  $handler->display->display_options['filters']['uid_raw']['table'] = 'users';
  $handler->display->display_options['filters']['uid_raw']['field'] = 'uid_raw';
  $handler->display->display_options['filters']['uid_raw']['relationship'] = 'uid';
  $handler->display->display_options['filters']['uid_raw']['group'] = 3;

  /* Display: Content pane */
  $handler = $view->new_display('panel_pane', 'Content pane', 'panel_pane_1');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Path */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['label'] = '';
  $handler->display->display_options['fields']['path']['exclude'] = TRUE;
  $handler->display->display_options['fields']['path']['element_label_colon'] = FALSE;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['created']['alter']['path'] = '[path]';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'long';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'F d, Y';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'panopoly_time';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Groups audience */
  $handler->display->display_options['fields']['og_group_ref']['id'] = 'og_group_ref';
  $handler->display->display_options['fields']['og_group_ref']['table'] = 'og_membership';
  $handler->display->display_options['fields']['og_group_ref']['field'] = 'og_group_ref';
  $handler->display->display_options['fields']['og_group_ref']['exclude'] = TRUE;
  $handler->display->display_options['fields']['og_group_ref']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['og_group_ref']['delta_offset'] = '0';
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['text'] = '<div class="field-diary-body">[body] <div class="read-more"><a href="/node/[nid]">(...)</a></div></div>';
  $handler->display->display_options['fields']['body']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['body']['element_type'] = '0';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['body']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['body']['type'] = 'text_trimmed';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '650',
  );
  $handler->display->display_options['fields']['body']['field_api_classes'] = TRUE;
  /* Field: Field: Tags */
  $handler->display->display_options['fields']['field_pece_tags']['id'] = 'field_pece_tags';
  $handler->display->display_options['fields']['field_pece_tags']['table'] = 'field_data_field_pece_tags';
  $handler->display->display_options['fields']['field_pece_tags']['field'] = 'field_pece_tags';
  $handler->display->display_options['fields']['field_pece_tags']['label'] = '';
  $handler->display->display_options['fields']['field_pece_tags']['element_type'] = '0';
  $handler->display->display_options['fields']['field_pece_tags']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_pece_tags']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_pece_tags']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_pece_tags']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_pece_tags']['field_api_classes'] = TRUE;
  $translatables['pece_group_field_diary'] = array(
    t('Master'),
    t('Group Field Diary'),
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
    t('author'),
    t('Groups audience'),
    t('<div class="field-diary-body">[body] <div class="read-more"><a href="/node/[nid]">(...)</a></div></div>'),
    t('All'),
    t('Content pane'),
    t('View panes'),
  );
  $export['pece_group_field_diary'] = $view;

  $view = new view();
  $view->name = 'pece_user_field_diary';
  $view->description = '';
  $view->tag = 'PECE';
  $view->base_table = 'node';
  $view->human_name = 'PECE - User Field Diary';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'PECE - User Field Diary';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'Read more...';
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    2 => '2',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['required'] = TRUE;
  /* Field: Content: Path */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['label'] = '';
  $handler->display->display_options['fields']['path']['exclude'] = TRUE;
  $handler->display->display_options['fields']['path']['element_label_colon'] = FALSE;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['created']['alter']['path'] = '[path]';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'long';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'F d, Y';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'panopoly_time';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['exclude'] = TRUE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['body']['alter']['text'] = '<div class="field-diary-body">[body] <div class="read-more"><a href="/node/[nid]">(...)</a></div></div>';
  $handler->display->display_options['fields']['body']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['body']['element_type'] = '0';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['body']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['body']['type'] = 'text_trimmed';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '650',
  );
  $handler->display->display_options['fields']['body']['field_api_classes'] = TRUE;
  /* Field: Field: Tags */
  $handler->display->display_options['fields']['field_pece_tags']['id'] = 'field_pece_tags';
  $handler->display->display_options['fields']['field_pece_tags']['table'] = 'field_data_field_pece_tags';
  $handler->display->display_options['fields']['field_pece_tags']['field'] = 'field_pece_tags';
  $handler->display->display_options['fields']['field_pece_tags']['label'] = '';
  $handler->display->display_options['fields']['field_pece_tags']['element_type'] = '0';
  $handler->display->display_options['fields']['field_pece_tags']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_pece_tags']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_pece_tags']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_pece_tags']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_pece_tags']['separator'] = ',';
  $handler->display->display_options['fields']['field_pece_tags']['field_api_classes'] = TRUE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Author uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'node';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['uid']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['uid']['title'] = '[name]\'s Field Diary';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['filter_groups']['operator'] = 'OR';
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'AND',
    2 => 'AND',
    3 => 'AND',
  );
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
    'pece_artifact_fieldnote' => 'pece_artifact_fieldnote',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Permissions (field_permissions) */
  $handler->display->display_options['filters']['field_permissions_value']['id'] = 'field_permissions_value';
  $handler->display->display_options['filters']['field_permissions_value']['table'] = 'field_data_field_permissions';
  $handler->display->display_options['filters']['field_permissions_value']['field'] = 'field_permissions_value';
  $handler->display->display_options['filters']['field_permissions_value']['value'] = array(
    'open' => 'open',
  );
  $handler->display->display_options['filters']['field_permissions_value']['group'] = 1;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status_1']['id'] = 'status_1';
  $handler->display->display_options['filters']['status_1']['table'] = 'node';
  $handler->display->display_options['filters']['status_1']['field'] = 'status';
  $handler->display->display_options['filters']['status_1']['value'] = '1';
  $handler->display->display_options['filters']['status_1']['group'] = 2;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type_2']['id'] = 'type_2';
  $handler->display->display_options['filters']['type_2']['table'] = 'node';
  $handler->display->display_options['filters']['type_2']['field'] = 'type';
  $handler->display->display_options['filters']['type_2']['value'] = array(
    'pece_artifact_fieldnote' => 'pece_artifact_fieldnote',
  );
  $handler->display->display_options['filters']['type_2']['group'] = 2;
  /* Filter criterion: Content: Permissions (field_permissions) */
  $handler->display->display_options['filters']['field_permissions_value_1']['id'] = 'field_permissions_value_1';
  $handler->display->display_options['filters']['field_permissions_value_1']['table'] = 'field_data_field_permissions';
  $handler->display->display_options['filters']['field_permissions_value_1']['field'] = 'field_permissions_value';
  $handler->display->display_options['filters']['field_permissions_value_1']['value'] = array(
    'restricted' => 'restricted',
  );
  $handler->display->display_options['filters']['field_permissions_value_1']['group'] = 2;
  /* Filter criterion: User: Roles */
  $handler->display->display_options['filters']['rid']['id'] = 'rid';
  $handler->display->display_options['filters']['rid']['table'] = 'users_roles';
  $handler->display->display_options['filters']['rid']['field'] = 'rid';
  $handler->display->display_options['filters']['rid']['relationship'] = 'uid';
  $handler->display->display_options['filters']['rid']['value'] = array(
    6 => '6',
  );
  $handler->display->display_options['filters']['rid']['group'] = 2;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status_2']['id'] = 'status_2';
  $handler->display->display_options['filters']['status_2']['table'] = 'node';
  $handler->display->display_options['filters']['status_2']['field'] = 'status';
  $handler->display->display_options['filters']['status_2']['value'] = '1';
  $handler->display->display_options['filters']['status_2']['group'] = 3;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type_1']['id'] = 'type_1';
  $handler->display->display_options['filters']['type_1']['table'] = 'node';
  $handler->display->display_options['filters']['type_1']['field'] = 'type';
  $handler->display->display_options['filters']['type_1']['value'] = array(
    'pece_artifact_fieldnote' => 'pece_artifact_fieldnote',
  );
  $handler->display->display_options['filters']['type_1']['group'] = 3;
  /* Filter criterion: User: The user ID */
  $handler->display->display_options['filters']['uid_raw']['id'] = 'uid_raw';
  $handler->display->display_options['filters']['uid_raw']['table'] = 'users';
  $handler->display->display_options['filters']['uid_raw']['field'] = 'uid_raw';
  $handler->display->display_options['filters']['uid_raw']['relationship'] = 'uid';
  $handler->display->display_options['filters']['uid_raw']['group'] = 3;

  /* Display: Content pane */
  $handler = $view->new_display('panel_pane', 'Content pane', 'pece_user_field_diary');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Field Diary';
  $translatables['pece_user_field_diary'] = array(
    t('Master'),
    t('PECE - User Field Diary'),
    t('Read more...'),
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
    t('author'),
    t('Nid'),
    t('Name'),
    t('<div class="field-diary-body">[body] <div class="read-more"><a href="/node/[nid]">(...)</a></div></div>'),
    t('All'),
    t('[name]\'s Field Diary'),
    t('Content pane'),
    t('Field Diary'),
    t('more'),
    t('View panes'),
  );
  $export['pece_user_field_diary'] = $view;

  return $export;
}
