<?php
/**
 * @file
 * pece_timeline_essay.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function pece_timeline_essay_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'timeline';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Timeline';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Timeline';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'timelinejs';
  $handler->display->display_options['style_options']['timeline_config']['hash_bookmark'] = 0;
  $handler->display->display_options['style_options']['timeline_config']['start_at_end'] = 0;
  $handler->display->display_options['style_options']['timeline_config']['language'] = 'en';
  $handler->display->display_options['style_options']['additional_config']['start_at_current'] = 0;
  $handler->display->display_options['style_options']['timeline_fields']['media'] = 'field_pece_media_image_1';
  $handler->display->display_options['style_options']['timeline_fields']['start_date'] = 'created';
  $handler->display->display_options['style_options']['timeline_fields']['end_date'] = 'status';
  $handler->display->display_options['style_options']['timeline_fields']['display_date'] = 'status';
  $handler->display->display_options['style_options']['timeline_fields']['text'] = 'field_description';
  $handler->display->display_options['style_options']['timeline_fields']['headline'] = 'title_1';
  $handler->display->display_options['style_options']['timeline_fields']['background'] = 'field_pece_media_image_1';
  $handler->display->display_options['style_options']['timeline_fields']['background_color'] = 'field_pece_timeline_color';
  $handler->display->display_options['style_options']['timeline_fields']['unique_id'] = 'uuid';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_pece_timeline_essay_items_target_id']['id'] = 'field_pece_timeline_essay_items_target_id';
  $handler->display->display_options['relationships']['field_pece_timeline_essay_items_target_id']['table'] = 'field_data_field_pece_timeline_essay_items';
  $handler->display->display_options['relationships']['field_pece_timeline_essay_items_target_id']['field'] = 'field_pece_timeline_essay_items_target_id';
  $handler->display->display_options['relationships']['field_pece_timeline_essay_items_target_id']['label'] = 'Timeline Essay Item from TL Node ';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_pece_timeline_artifact_target_id']['id'] = 'field_pece_timeline_artifact_target_id';
  $handler->display->display_options['relationships']['field_pece_timeline_artifact_target_id']['table'] = 'field_data_field_pece_timeline_artifact';
  $handler->display->display_options['relationships']['field_pece_timeline_artifact_target_id']['field'] = 'field_pece_timeline_artifact_target_id';
  $handler->display->display_options['relationships']['field_pece_timeline_artifact_target_id']['relationship'] = 'field_pece_timeline_essay_items_target_id';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Description */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['exclude'] = TRUE;
  $handler->display->display_options['fields']['body']['element_type'] = '0';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['body']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['body']['type'] = 'smart_trim_format';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_link' => '0',
    'trim_length' => '300',
    'trim_type' => 'chars',
    'trim_suffix' => '...',
    'more_link' => '0',
    'more_text' => 'Read more',
    'summary_handler' => 'full',
    'trim_options' => array(
      'text' => 0,
    ),
    'trim_preserve_tags' => '',
  );
  $handler->display->display_options['fields']['body']['field_api_classes'] = TRUE;
  /* Field: Content: Thumbnail image */
  $handler->display->display_options['fields']['field_pece_media_image']['id'] = 'field_pece_media_image';
  $handler->display->display_options['fields']['field_pece_media_image']['table'] = 'field_data_field_pece_media_image';
  $handler->display->display_options['fields']['field_pece_media_image']['field'] = 'field_pece_media_image';
  $handler->display->display_options['fields']['field_pece_media_image']['label'] = 'Image';
  $handler->display->display_options['fields']['field_pece_media_image']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_pece_media_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_pece_media_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_pece_media_image']['settings'] = array(
    'image_style' => 'medium',
    'image_link' => 'content',
  );
  /* Field: Content: Published */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['exclude'] = TRUE;
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['exclude'] = TRUE;
  $handler->display->display_options['fields']['created']['date_format'] = 'panopoly_day';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'panopoly_time';
  /* Field: Content: Node UUID */
  $handler->display->display_options['fields']['uuid']['id'] = 'uuid';
  $handler->display->display_options['fields']['uuid']['table'] = 'node';
  $handler->display->display_options['fields']['uuid']['field'] = 'uuid';
  $handler->display->display_options['fields']['uuid']['label'] = '';
  $handler->display->display_options['fields']['uuid']['element_label_colon'] = FALSE;
  /* Field: Timeline Essay Item: Id */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'eck_pece_timeline_essay_item';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  /* Field: Timeline Essay Item: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'eck_pece_timeline_essay_item';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['relationship'] = 'field_pece_timeline_essay_items_target_id';
  $handler->display->display_options['fields']['title_1']['label'] = 'TL Title';
  /* Field: Field: Essay Text */
  $handler->display->display_options['fields']['field_description']['id'] = 'field_description';
  $handler->display->display_options['fields']['field_description']['table'] = 'field_data_field_description';
  $handler->display->display_options['fields']['field_description']['field'] = 'field_description';
  $handler->display->display_options['fields']['field_description']['relationship'] = 'field_pece_timeline_essay_items_target_id';
  /* Field: Field: Start and End Date */
  $handler->display->display_options['fields']['field_pece_start_end_date']['id'] = 'field_pece_start_end_date';
  $handler->display->display_options['fields']['field_pece_start_end_date']['table'] = 'field_data_field_pece_start_end_date';
  $handler->display->display_options['fields']['field_pece_start_end_date']['field'] = 'field_pece_start_end_date';
  /* Field: Timeline Essay Item: Background color */
  $handler->display->display_options['fields']['field_pece_timeline_color']['id'] = 'field_pece_timeline_color';
  $handler->display->display_options['fields']['field_pece_timeline_color']['table'] = 'field_data_field_pece_timeline_color';
  $handler->display->display_options['fields']['field_pece_timeline_color']['field'] = 'field_pece_timeline_color';
  $handler->display->display_options['fields']['field_pece_timeline_color']['relationship'] = 'field_pece_timeline_essay_items_target_id';
  $handler->display->display_options['fields']['field_pece_timeline_color']['label'] = '';
  $handler->display->display_options['fields']['field_pece_timeline_color']['element_type'] = '0';
  $handler->display->display_options['fields']['field_pece_timeline_color']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_pece_timeline_color']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_pece_timeline_color']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_pece_timeline_color']['settings'] = array(
    'width' => '50',
    'height' => '50',
  );
  $handler->display->display_options['fields']['field_pece_timeline_color']['field_api_classes'] = TRUE;
  /* Field: Content: Rendered Node */
  $handler->display->display_options['fields']['rendered_entity']['id'] = 'rendered_entity';
  $handler->display->display_options['fields']['rendered_entity']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['rendered_entity']['field'] = 'rendered_entity';
  $handler->display->display_options['fields']['rendered_entity']['relationship'] = 'field_pece_timeline_artifact_target_id';
  $handler->display->display_options['fields']['rendered_entity']['link_to_entity'] = 1;
  $handler->display->display_options['fields']['rendered_entity']['view_mode'] = 'full';
  $handler->display->display_options['fields']['rendered_entity']['bypass_access'] = 0;
  /* Field: Content: Audio */
  $handler->display->display_options['fields']['field_pece_media_audio']['id'] = 'field_pece_media_audio';
  $handler->display->display_options['fields']['field_pece_media_audio']['table'] = 'field_data_field_pece_media_audio';
  $handler->display->display_options['fields']['field_pece_media_audio']['field'] = 'field_pece_media_audio';
  $handler->display->display_options['fields']['field_pece_media_audio']['relationship'] = 'field_pece_timeline_artifact_target_id';
  $handler->display->display_options['fields']['field_pece_media_audio']['element_type'] = '0';
  $handler->display->display_options['fields']['field_pece_media_audio']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_pece_media_audio']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_pece_media_audio']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_pece_media_audio']['type'] = 'file_audio';
  $handler->display->display_options['fields']['field_pece_media_audio']['settings'] = array(
    'controls' => 1,
    'controls_list' => array(
      'download' => 'download',
      'remote_playback' => 'remote_playback',
    ),
    'autoplay' => 0,
    'loop' => 0,
    'preload' => '',
    'multiple_file_behavior' => 'tags',
  );
  $handler->display->display_options['fields']['field_pece_media_audio']['field_api_classes'] = TRUE;
  /* Field: Content: Thumbnail image */
  $handler->display->display_options['fields']['field_pece_media_image_1']['id'] = 'field_pece_media_image_1';
  $handler->display->display_options['fields']['field_pece_media_image_1']['table'] = 'field_data_field_pece_media_image';
  $handler->display->display_options['fields']['field_pece_media_image_1']['field'] = 'field_pece_media_image';
  $handler->display->display_options['fields']['field_pece_media_image_1']['relationship'] = 'field_pece_timeline_artifact_target_id';
  $handler->display->display_options['fields']['field_pece_media_image_1']['label'] = 'Image';
  $handler->display->display_options['fields']['field_pece_media_image_1']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_pece_media_image_1']['settings'] = array(
    'image_style' => '',
    'image_link' => '',
  );
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['nid']['default_argument_options']['argument'] = '1315';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
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
    'pece_artifact_audio' => 'pece_artifact_audio',
    'pece_artifact_bundle' => 'pece_artifact_bundle',
    'pece_artifact_fieldnote' => 'pece_artifact_fieldnote',
    'pece_artifact_image' => 'pece_artifact_image',
    'pece_artifact_pdf' => 'pece_artifact_pdf',
    'pece_artifact_text' => 'pece_artifact_text',
    'pece_artifact_video' => 'pece_artifact_video',
    'pece_artifact_website' => 'pece_artifact_website',
    'pece_timeline_essay' => 'pece_timeline_essay',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'timeline';

  /* Display: Content pane */
  $handler = $view->new_display('panel_pane', 'Content pane', 'panel_pane_1');
  $translatables['timeline'] = array(
    t('Master'),
    t('Timeline'),
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
    t('Timeline Essay Item from TL Node '),
    t('Content entity referenced from field_pece_timeline_artifact'),
    t('Title'),
    t('Description'),
    t('Image'),
    t('Published'),
    t('Post date'),
    t('Id'),
    t('.'),
    t(','),
    t('TL Title'),
    t('Essay Text'),
    t('Start and End Date'),
    t('Rendered Node'),
    t('Audio'),
    t('All'),
    t('Page'),
    t('Content pane'),
    t('View panes'),
  );
  $export['timeline'] = $view;

  return $export;
}
