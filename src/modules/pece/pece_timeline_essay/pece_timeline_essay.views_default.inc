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
  $view->name = 'pece_timeline_essay_items';
  $view->description = '';
  $view->tag = 'PECE';
  $view->base_table = 'node';
  $view->human_name = 'PECE - Timeline Essay Items';
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
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'field_thumbnail' => 'field_thumbnail',
    'field_pece_start_end_date' => 'field_pece_start_end_date',
    'field_pece_start_end_date_1' => 'field_pece_start_end_date_1',
    'entityreference_view_widget' => 'entityreference_view_widget',
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
    'field_thumbnail' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_pece_start_end_date' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_pece_start_end_date_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'entityreference_view_widget' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_pece_artifact_target_id']['id'] = 'field_pece_artifact_target_id';
  $handler->display->display_options['relationships']['field_pece_artifact_target_id']['table'] = 'field_data_field_pece_artifact';
  $handler->display->display_options['relationships']['field_pece_artifact_target_id']['field'] = 'field_pece_artifact_target_id';
  $handler->display->display_options['relationships']['field_pece_artifact_target_id']['required'] = TRUE;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_pece_timeline_essay_items_target_id']['id'] = 'field_pece_timeline_essay_items_target_id';
  $handler->display->display_options['relationships']['field_pece_timeline_essay_items_target_id']['table'] = 'field_data_field_pece_timeline_essay_items';
  $handler->display->display_options['relationships']['field_pece_timeline_essay_items_target_id']['field'] = 'field_pece_timeline_essay_items_target_id';
  /* Relationship: Broken/missing handler */
  $handler->display->display_options['relationships']['reverse_field_pece_artifact_pece_timeline_essay_item']['id'] = 'reverse_field_pece_artifact_pece_timeline_essay_item';
  $handler->display->display_options['relationships']['reverse_field_pece_artifact_pece_timeline_essay_item']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_field_pece_artifact_pece_timeline_essay_item']['field'] = 'reverse_field_pece_artifact_pece_timeline_essay_item';
  $handler->display->display_options['relationships']['reverse_field_pece_artifact_pece_timeline_essay_item']['label'] = 'Timeline Essay Item referencing Content from field_pece_artifact';
  /* Relationship: Entity Reference: Referencing entity */
  $handler->display->display_options['relationships']['reverse_field_pece_timeline_essay_items_node']['id'] = 'reverse_field_pece_timeline_essay_items_node';
  $handler->display->display_options['relationships']['reverse_field_pece_timeline_essay_items_node']['table'] = 'eck_pece_timeline_essay_item';
  $handler->display->display_options['relationships']['reverse_field_pece_timeline_essay_items_node']['field'] = 'reverse_field_pece_timeline_essay_items_node';
  $handler->display->display_options['relationships']['reverse_field_pece_timeline_essay_items_node']['relationship'] = 'field_pece_timeline_essay_items_target_id';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'field_pece_timeline_artifact_target_id';
  /* Field: Field: Text */
  $handler->display->display_options['fields']['field_description']['id'] = 'field_description';
  $handler->display->display_options['fields']['field_description']['table'] = 'field_data_field_description';
  $handler->display->display_options['fields']['field_description']['field'] = 'field_description';
  $handler->display->display_options['fields']['field_description']['relationship'] = 'reverse_field_pece_artifact_pece_timeline_essay_item';
  /* Field: Timeline Essay Item: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'eck_pece_timeline_essay_item';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['relationship'] = 'reverse_field_pece_timeline_artifact_pece_timeline_essay_item';
  $handler->display->display_options['fields']['title_1']['label'] = 'Timeline Item title';
  /* Field: Content: Description */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
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
    'pece_artifact_image' => 'pece_artifact_image',
    'pece_artifact_pdf' => 'pece_artifact_pdf',
    'pece_artifact_text' => 'pece_artifact_text',
    'pece_artifact_video' => 'pece_artifact_video',
    'pece_artifact_website' => 'pece_artifact_website',
  );
  $handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['label'] = 'Type';
  $handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';

  /* Display: Content pane */
  $handler = $view->new_display('panel_pane', 'Content pane', 'timeline_pane');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'timelinejs';
  $handler->display->display_options['style_options']['timeline_config']['height'] = '650px';
  $handler->display->display_options['style_options']['timeline_config']['hash_bookmark'] = 0;
  $handler->display->display_options['style_options']['timeline_config']['timenav_height'] = '300';
  $handler->display->display_options['style_options']['timeline_config']['timenav_mobile_height_percentage'] = '100';
  $handler->display->display_options['style_options']['timeline_config']['timenav_height_min'] = '100';
  $handler->display->display_options['style_options']['timeline_config']['start_at_end'] = 0;
  $handler->display->display_options['style_options']['additional_config']['start_at_current'] = 0;
  $handler->display->display_options['style_options']['timeline_fields']['media'] = 'field_pece_website_url';
  $handler->display->display_options['style_options']['timeline_fields']['start_date'] = 'field_pece_start_end_date';
  $handler->display->display_options['style_options']['timeline_fields']['end_date'] = 'field_pece_start_end_date_1';
  $handler->display->display_options['style_options']['timeline_fields']['text'] = 'field_description';
  $handler->display->display_options['style_options']['timeline_fields']['headline'] = 'title';
  $handler->display->display_options['style_options']['timeline_fields']['background_color'] = 'field_pece_timeline_color';
  $handler->display->display_options['style_options']['timeline_fields']['unique_id'] = 'uuid';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_pece_timeline_essay_items_target_id']['id'] = 'field_pece_timeline_essay_items_target_id';
  $handler->display->display_options['relationships']['field_pece_timeline_essay_items_target_id']['table'] = 'field_data_field_pece_timeline_essay_items';
  $handler->display->display_options['relationships']['field_pece_timeline_essay_items_target_id']['field'] = 'field_pece_timeline_essay_items_target_id';
  $handler->display->display_options['relationships']['field_pece_timeline_essay_items_target_id']['label'] = 'Timeline Essay Item From Timeline Essay Node';
  /* Relationship: Entity Reference: Referencing entity */
  $handler->display->display_options['relationships']['reverse_field_pece_timeline_essay_items_node']['id'] = 'reverse_field_pece_timeline_essay_items_node';
  $handler->display->display_options['relationships']['reverse_field_pece_timeline_essay_items_node']['table'] = 'eck_pece_timeline_essay_item';
  $handler->display->display_options['relationships']['reverse_field_pece_timeline_essay_items_node']['field'] = 'reverse_field_pece_timeline_essay_items_node';
  $handler->display->display_options['relationships']['reverse_field_pece_timeline_essay_items_node']['relationship'] = 'field_pece_timeline_essay_items_target_id';
  $handler->display->display_options['relationships']['reverse_field_pece_timeline_essay_items_node']['label'] = 'Timeline Essay Node Has Timeline Essay Item';
  /* Relationship: Timeline Essay Item referencing a Timeline Artifact */
  $handler->display->display_options['relationships']['reverse_field_pece_timeline_artifact_pece_timeline_essay_item']['id'] = 'reverse_field_pece_timeline_artifact_pece_timeline_essay_item';
  $handler->display->display_options['relationships']['reverse_field_pece_timeline_artifact_pece_timeline_essay_item']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_field_pece_timeline_artifact_pece_timeline_essay_item']['field'] = 'reverse_field_pece_timeline_artifact_pece_timeline_essay_item';
  $handler->display->display_options['relationships']['reverse_field_pece_timeline_artifact_pece_timeline_essay_item']['ui_name'] = 'Timeline Essay Item referencing a Timeline Artifact';
  $handler->display->display_options['relationships']['reverse_field_pece_timeline_artifact_pece_timeline_essay_item']['label'] = 'Timeline Essay Item To Timeline Artifact ';
  /* Relationship: Artifact being referenced by a Timeline Essay Item */
  $handler->display->display_options['relationships']['field_pece_timeline_artifact_target_id']['id'] = 'field_pece_timeline_artifact_target_id';
  $handler->display->display_options['relationships']['field_pece_timeline_artifact_target_id']['table'] = 'field_data_field_pece_timeline_artifact';
  $handler->display->display_options['relationships']['field_pece_timeline_artifact_target_id']['field'] = 'field_pece_timeline_artifact_target_id';
  $handler->display->display_options['relationships']['field_pece_timeline_artifact_target_id']['relationship'] = 'reverse_field_pece_timeline_artifact_pece_timeline_essay_item';
  $handler->display->display_options['relationships']['field_pece_timeline_artifact_target_id']['ui_name'] = 'Artifact being referenced by a Timeline Essay Item';
  $handler->display->display_options['relationships']['field_pece_timeline_artifact_target_id']['label'] = 'Artifact Node  From Timeline Essay Item';
  $handler->display->display_options['relationships']['field_pece_timeline_artifact_target_id']['required'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Artifact Title';
  /* Field: Field: Text */
  $handler->display->display_options['fields']['field_description']['id'] = 'field_description';
  $handler->display->display_options['fields']['field_description']['table'] = 'field_data_field_description';
  $handler->display->display_options['fields']['field_description']['field'] = 'field_description';
  $handler->display->display_options['fields']['field_description']['relationship'] = 'reverse_field_pece_timeline_artifact_pece_timeline_essay_item';
  $handler->display->display_options['fields']['field_description']['label'] = 'Timeline Item Text';
  $handler->display->display_options['fields']['field_description']['element_type'] = '0';
  $handler->display->display_options['fields']['field_description']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_description']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_description']['field_api_classes'] = TRUE;
  /* Field: Field: Start and End Date */
  $handler->display->display_options['fields']['field_pece_start_end_date']['id'] = 'field_pece_start_end_date';
  $handler->display->display_options['fields']['field_pece_start_end_date']['table'] = 'field_data_field_pece_start_end_date';
  $handler->display->display_options['fields']['field_pece_start_end_date']['field'] = 'field_pece_start_end_date';
  $handler->display->display_options['fields']['field_pece_start_end_date']['relationship'] = 'reverse_field_pece_timeline_artifact_pece_timeline_essay_item';
  $handler->display->display_options['fields']['field_pece_start_end_date']['label'] = 'Start Date';
  $handler->display->display_options['fields']['field_pece_start_end_date']['element_type'] = '0';
  $handler->display->display_options['fields']['field_pece_start_end_date']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_pece_start_end_date']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_pece_start_end_date']['settings'] = array(
    'format_type' => 'panopoly_day',
    'custom_date_format' => '',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
  );
  $handler->display->display_options['fields']['field_pece_start_end_date']['field_api_classes'] = TRUE;
  /* Field: Field: Start and End Date */
  $handler->display->display_options['fields']['field_pece_start_end_date_1']['id'] = 'field_pece_start_end_date_1';
  $handler->display->display_options['fields']['field_pece_start_end_date_1']['table'] = 'field_data_field_pece_start_end_date';
  $handler->display->display_options['fields']['field_pece_start_end_date_1']['field'] = 'field_pece_start_end_date';
  $handler->display->display_options['fields']['field_pece_start_end_date_1']['relationship'] = 'reverse_field_pece_timeline_artifact_pece_timeline_essay_item';
  $handler->display->display_options['fields']['field_pece_start_end_date_1']['label'] = 'End Date';
  $handler->display->display_options['fields']['field_pece_start_end_date_1']['settings'] = array(
    'format_type' => 'panopoly_day',
    'custom_date_format' => '',
    'fromto' => 'value2',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
  );
  /* Field: Timeline Essay Item: Background color */
  $handler->display->display_options['fields']['field_pece_timeline_color']['id'] = 'field_pece_timeline_color';
  $handler->display->display_options['fields']['field_pece_timeline_color']['table'] = 'field_data_field_pece_timeline_color';
  $handler->display->display_options['fields']['field_pece_timeline_color']['field'] = 'field_pece_timeline_color';
  $handler->display->display_options['fields']['field_pece_timeline_color']['relationship'] = 'reverse_field_pece_timeline_artifact_pece_timeline_essay_item';
  $handler->display->display_options['fields']['field_pece_timeline_color']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_pece_timeline_color']['field_api_classes'] = TRUE;
  /* Field: Timeline Essay Item: Timeline Essay Item UUID */
  $handler->display->display_options['fields']['uuid']['id'] = 'uuid';
  $handler->display->display_options['fields']['uuid']['table'] = 'eck_pece_timeline_essay_item';
  $handler->display->display_options['fields']['uuid']['field'] = 'uuid';
  $handler->display->display_options['fields']['uuid']['relationship'] = 'reverse_field_pece_timeline_artifact_pece_timeline_essay_item';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['relationship'] = 'reverse_field_pece_timeline_essay_items_node';
  $handler->display->display_options['fields']['nid']['label'] = 'Timeline Essay Original Node ID';
  /* Field: Timeline Essay Item: Media */
  $handler->display->display_options['fields']['field_pece_timeline_media']['id'] = 'field_pece_timeline_media';
  $handler->display->display_options['fields']['field_pece_timeline_media']['table'] = 'field_data_field_pece_timeline_media';
  $handler->display->display_options['fields']['field_pece_timeline_media']['field'] = 'field_pece_timeline_media';
  $handler->display->display_options['fields']['field_pece_timeline_media']['relationship'] = 'field_pece_timeline_essay_items_target_id';
  $handler->display->display_options['fields']['field_pece_timeline_media']['label'] = '';
  $handler->display->display_options['fields']['field_pece_timeline_media']['element_type'] = '0';
  $handler->display->display_options['fields']['field_pece_timeline_media']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_pece_timeline_media']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_pece_timeline_media']['element_default_classes'] = FALSE;
  /* Field: Content: Audio */
  $handler->display->display_options['fields']['field_pece_media_audio']['id'] = 'field_pece_media_audio';
  $handler->display->display_options['fields']['field_pece_media_audio']['table'] = 'field_data_field_pece_media_audio';
  $handler->display->display_options['fields']['field_pece_media_audio']['field'] = 'field_pece_media_audio';
  $handler->display->display_options['fields']['field_pece_media_audio']['relationship'] = 'field_pece_timeline_artifact_target_id';
  $handler->display->display_options['fields']['field_pece_media_audio']['label'] = '';
  $handler->display->display_options['fields']['field_pece_media_audio']['element_type'] = '0';
  $handler->display->display_options['fields']['field_pece_media_audio']['element_label_colon'] = FALSE;
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
  /* Field: Content: PDF Document */
  $handler->display->display_options['fields']['field_pece_media_pdf']['id'] = 'field_pece_media_pdf';
  $handler->display->display_options['fields']['field_pece_media_pdf']['table'] = 'field_data_field_pece_media_pdf';
  $handler->display->display_options['fields']['field_pece_media_pdf']['field'] = 'field_pece_media_pdf';
  $handler->display->display_options['fields']['field_pece_media_pdf']['relationship'] = 'field_pece_timeline_artifact_target_id';
  $handler->display->display_options['fields']['field_pece_media_pdf']['label'] = '';
  $handler->display->display_options['fields']['field_pece_media_pdf']['element_type'] = '0';
  $handler->display->display_options['fields']['field_pece_media_pdf']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_pece_media_pdf']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_pece_media_pdf']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_pece_media_pdf']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_pece_media_pdf']['type'] = 'pdf_reader_file';
  $handler->display->display_options['fields']['field_pece_media_pdf']['settings'] = array(
    'pdf_width' => '600',
    'pdf_height' => '780',
    'renderer' => 'pdf-js',
    'download' => 0,
    'colorbox' => FALSE,
    'colorbox_link_text' => '',
  );
  $handler->display->display_options['fields']['field_pece_media_pdf']['field_api_classes'] = TRUE;
  /* Field: Content: Video */
  $handler->display->display_options['fields']['field_pece_media_video']['id'] = 'field_pece_media_video';
  $handler->display->display_options['fields']['field_pece_media_video']['table'] = 'field_data_field_pece_media_video';
  $handler->display->display_options['fields']['field_pece_media_video']['field'] = 'field_pece_media_video';
  $handler->display->display_options['fields']['field_pece_media_video']['relationship'] = 'field_pece_timeline_artifact_target_id';
  $handler->display->display_options['fields']['field_pece_media_video']['label'] = '';
  $handler->display->display_options['fields']['field_pece_media_video']['element_type'] = '0';
  $handler->display->display_options['fields']['field_pece_media_video']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_pece_media_video']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_pece_media_video']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_pece_media_video']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_pece_media_video']['type'] = 'file_video';
  $handler->display->display_options['fields']['field_pece_media_video']['settings'] = array(
    'controls' => 0,
    'controls_list' => array(
      'fullscreen' => 0,
      'download' => 0,
      'remote_playback' => 0,
    ),
    'autoplay' => 0,
    'loop' => 0,
    'muted' => 0,
    'width' => '',
    'height' => '',
    'preload' => '',
    'multiple_file_behavior' => 'tags',
  );
  $handler->display->display_options['fields']['field_pece_media_video']['field_api_classes'] = TRUE;
  /* Field: Content: Website URL */
  $handler->display->display_options['fields']['field_pece_website_url']['id'] = 'field_pece_website_url';
  $handler->display->display_options['fields']['field_pece_website_url']['table'] = 'field_data_field_pece_website_url';
  $handler->display->display_options['fields']['field_pece_website_url']['field'] = 'field_pece_website_url';
  $handler->display->display_options['fields']['field_pece_website_url']['relationship'] = 'field_pece_timeline_artifact_target_id';
  $handler->display->display_options['fields']['field_pece_website_url']['label'] = '';
  $handler->display->display_options['fields']['field_pece_website_url']['element_type'] = '0';
  $handler->display->display_options['fields']['field_pece_website_url']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_pece_website_url']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_pece_website_url']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_pece_website_url']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_pece_website_url']['field_api_classes'] = TRUE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'reverse_field_pece_timeline_essay_items_node';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
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
  $handler->display->display_options['filters']['type']['relationship'] = 'field_pece_timeline_artifact_target_id';
  $handler->display->display_options['filters']['type']['value'] = array(
    'pece_artifact_audio' => 'pece_artifact_audio',
    'pece_artifact_image' => 'pece_artifact_image',
    'pece_artifact_pdf' => 'pece_artifact_pdf',
    'pece_artifact_text' => 'pece_artifact_text',
    'pece_artifact_video' => 'pece_artifact_video',
    'pece_artifact_website' => 'pece_artifact_website',
  );
  $handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['label'] = 'Type';
  $handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';

  /* Display: Contextual Filter Tests - Content pane */
  $handler = $view->new_display('panel_pane', 'Contextual Filter Tests - Content pane', 'panel_pane_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'field_description' => 'field_description',
    'field_pece_start_end_date' => 'field_pece_start_end_date',
    'field_pece_start_end_date_1' => 'field_pece_start_end_date_1',
    'field_pece_timeline_color' => 'field_pece_timeline_color',
    'uuid' => 'uuid',
    'nid' => 'nid',
    'field_pece_timeline_media' => 'field_pece_timeline_media',
    'field_pece_media_audio' => 'field_pece_media_audio',
    'field_pece_media_pdf' => 'field_pece_media_pdf',
    'field_pece_media_video' => 'field_pece_media_video',
    'field_pece_website_url' => 'field_pece_website_url',
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
    'field_description' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_pece_start_end_date' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_pece_start_end_date_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_pece_timeline_color' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'uuid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_pece_timeline_media' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_pece_media_audio' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_pece_media_pdf' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_pece_media_video' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_pece_website_url' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_pece_timeline_essay_items_target_id']['id'] = 'field_pece_timeline_essay_items_target_id';
  $handler->display->display_options['relationships']['field_pece_timeline_essay_items_target_id']['table'] = 'field_data_field_pece_timeline_essay_items';
  $handler->display->display_options['relationships']['field_pece_timeline_essay_items_target_id']['field'] = 'field_pece_timeline_essay_items_target_id';
  $handler->display->display_options['relationships']['field_pece_timeline_essay_items_target_id']['label'] = 'Timeline Essay Item From Timeline Essay Node';
  /* Relationship: Entity Reference: Referencing entity */
  $handler->display->display_options['relationships']['reverse_field_pece_timeline_essay_items_node']['id'] = 'reverse_field_pece_timeline_essay_items_node';
  $handler->display->display_options['relationships']['reverse_field_pece_timeline_essay_items_node']['table'] = 'eck_pece_timeline_essay_item';
  $handler->display->display_options['relationships']['reverse_field_pece_timeline_essay_items_node']['field'] = 'reverse_field_pece_timeline_essay_items_node';
  $handler->display->display_options['relationships']['reverse_field_pece_timeline_essay_items_node']['relationship'] = 'field_pece_timeline_essay_items_target_id';
  $handler->display->display_options['relationships']['reverse_field_pece_timeline_essay_items_node']['label'] = 'Timeline Essay Node Has Timeline Essay Item';
  /* Relationship: Timeline Essay Item referencing a Timeline Artifact */
  $handler->display->display_options['relationships']['reverse_field_pece_timeline_artifact_pece_timeline_essay_item']['id'] = 'reverse_field_pece_timeline_artifact_pece_timeline_essay_item';
  $handler->display->display_options['relationships']['reverse_field_pece_timeline_artifact_pece_timeline_essay_item']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_field_pece_timeline_artifact_pece_timeline_essay_item']['field'] = 'reverse_field_pece_timeline_artifact_pece_timeline_essay_item';
  $handler->display->display_options['relationships']['reverse_field_pece_timeline_artifact_pece_timeline_essay_item']['ui_name'] = 'Timeline Essay Item referencing a Timeline Artifact';
  $handler->display->display_options['relationships']['reverse_field_pece_timeline_artifact_pece_timeline_essay_item']['label'] = 'Timeline Essay Item To Timeline Artifact ';
  /* Relationship: Artifact being referenced by a Timeline Essay Item */
  $handler->display->display_options['relationships']['field_pece_timeline_artifact_target_id']['id'] = 'field_pece_timeline_artifact_target_id';
  $handler->display->display_options['relationships']['field_pece_timeline_artifact_target_id']['table'] = 'field_data_field_pece_timeline_artifact';
  $handler->display->display_options['relationships']['field_pece_timeline_artifact_target_id']['field'] = 'field_pece_timeline_artifact_target_id';
  $handler->display->display_options['relationships']['field_pece_timeline_artifact_target_id']['relationship'] = 'reverse_field_pece_timeline_artifact_pece_timeline_essay_item';
  $handler->display->display_options['relationships']['field_pece_timeline_artifact_target_id']['ui_name'] = 'Artifact being referenced by a Timeline Essay Item';
  $handler->display->display_options['relationships']['field_pece_timeline_artifact_target_id']['label'] = 'Artifact Node  From Timeline Essay Item';
  $handler->display->display_options['relationships']['field_pece_timeline_artifact_target_id']['required'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Artifact Title';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['relationship'] = 'field_pece_timeline_artifact_target_id';
  $handler->display->display_options['fields']['title_1']['label'] = 'Node Title Owns TLE Item';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'reverse_field_pece_timeline_essay_items_node';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
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
  $handler->display->display_options['filters']['type']['relationship'] = 'field_pece_timeline_artifact_target_id';
  $handler->display->display_options['filters']['type']['value'] = array(
    'pece_artifact_audio' => 'pece_artifact_audio',
    'pece_artifact_image' => 'pece_artifact_image',
    'pece_artifact_pdf' => 'pece_artifact_pdf',
    'pece_artifact_text' => 'pece_artifact_text',
    'pece_artifact_video' => 'pece_artifact_video',
    'pece_artifact_website' => 'pece_artifact_website',
  );
  $handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['label'] = 'Type';
  $handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
  $translatables['pece_timeline_essay_items'] = array(
    t('Master'),
    t('Timeline'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Content entity referenced from field_pece_artifact'),
    t('Timeline Essay Item entity referenced from field_pece_timeline_essay_items'),
    t('Timeline Essay Item referencing Content from field_pece_artifact'),
    t('Content referencing Timeline Essay Item from field_pece_timeline_essay_items'),
    t('Title'),
    t('Text'),
    t('Timeline Item title'),
    t('Description'),
    t('Type'),
    t('Content pane'),
    t('Timeline Essay Item From Timeline Essay Node'),
    t('Timeline Essay Node Has Timeline Essay Item'),
    t('Timeline Essay Item To Timeline Artifact '),
    t('Artifact Node  From Timeline Essay Item'),
    t('Artifact Title'),
    t('Timeline Item Text'),
    t('Start Date'),
    t('End Date'),
    t('Background color'),
    t('Timeline Essay Item UUID'),
    t('Timeline Essay Original Node ID'),
    t('All'),
    t('View panes'),
    t('Contextual Filter Tests - Content pane'),
    t('Node Title Owns TLE Item'),
  );
  $export['pece_timeline_essay_items'] = $view;

  return $export;
}
