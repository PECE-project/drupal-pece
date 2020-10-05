<?php

/**
 * @file
 * pece_artifacts_video.panelizer.inc
 */

/**
 * Implements hook_panelizer_defaults().
 */
function pece_artifacts_video_panelizer_defaults() {
  $export = array();

  $panelizer = new stdClass();
  $panelizer->disabled = FALSE; /* Edit this to true to make a default panelizer disabled initially */
  $panelizer->api_version = 1;
  $panelizer->title = 'Default';
  $panelizer->panelizer_type = 'node';
  $panelizer->panelizer_key = 'pece_artifact_video';
  $panelizer->access = array();
  $panelizer->view_mode = 'page_manager';
  $panelizer->name = 'node:pece_artifact_video:default';
  $panelizer->css_id = '';
  $panelizer->css_class = '';
  $panelizer->css = '';
  $panelizer->no_blocks = FALSE;
  $panelizer->title_element = 'H2';
  $panelizer->link_to_entity = TRUE;
  $panelizer->extra = array();
  $panelizer->pipeline = 'ipe';
  $panelizer->contexts = array();
  $panelizer->relationships = array();
  $display = new panels_display();
  $display->layout = 'radix_phelan';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'column1' => NULL,
      'column2' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '%node:title';
  $display->uuid = '3dc17552-42a2-4ce8-977b-4d4baf5192e8';
  $display->storage_type = 'panelizer_default';
  $display->storage_id = 'node:pece_artifact_video:default';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-ff740cd9-c93c-469d-9b81-4ce8a37fae4c';
  $pane->panel = 'column1';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_media_video';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'above',
    'formatter' => 'file_video',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(
      'text' => 'Download [file:name]',
      'controls' => 1,
      'autoplay' => 0,
      'loop' => 0,
      'multiple_file_behavior' => 'tags',
      'muted' => 0,
      'width' => '',
      'height' => '',
    ),
    'context' => 'panelizer',
    'override_title' => 0,
    'override_title_text' => '',
    'override_title_heading' => 'h2',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = 'ff740cd9-c93c-469d-9b81-4ce8a37fae4c';
  $display->content['new-ff740cd9-c93c-469d-9b81-4ce8a37fae4c'] = $pane;
  $display->panels['column1'][0] = 'new-ff740cd9-c93c-469d-9b81-4ce8a37fae4c';
  $pane = new stdClass();
  $pane->pid = 'new-2d4df107-f6c9-4f5d-be81-e7f718738b9f';
  $pane->panel = 'column1';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_file_format';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'above',
    'formatter' => 'text_default',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(),
    'context' => 'panelizer',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = '2d4df107-f6c9-4f5d-be81-e7f718738b9f';
  $display->content['new-2d4df107-f6c9-4f5d-be81-e7f718738b9f'] = $pane;
  $display->panels['column1'][1] = 'new-2d4df107-f6c9-4f5d-be81-e7f718738b9f';
  $pane = new stdClass();
  $pane->pid = 'new-7cd67a66-b73b-4489-bc95-e2fe1190c930';
  $pane->panel = 'column1';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_media_duration';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'above',
    'formatter' => 'text_default',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(),
    'context' => 'panelizer',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 2;
  $pane->locks = array();
  $pane->uuid = '7cd67a66-b73b-4489-bc95-e2fe1190c930';
  $display->content['new-7cd67a66-b73b-4489-bc95-e2fe1190c930'] = $pane;
  $display->panels['column1'][2] = 'new-7cd67a66-b73b-4489-bc95-e2fe1190c930';
  $pane = new stdClass();
  $pane->pid = 'new-95e246a9-84bc-4564-a71e-6219e7133b0c';
  $pane->panel = 'column1';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_license';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'above',
    'formatter' => 'creative_commons_small_image',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(),
    'context' => 'panelizer',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 3;
  $pane->locks = array();
  $pane->uuid = '95e246a9-84bc-4564-a71e-6219e7133b0c';
  $display->content['new-95e246a9-84bc-4564-a71e-6219e7133b0c'] = $pane;
  $display->panels['column1'][3] = 'new-95e246a9-84bc-4564-a71e-6219e7133b0c';
  $pane = new stdClass();
  $pane->pid = 'new-e63dbd8c-ed97-4b6b-a8eb-f15ef8e373fd';
  $pane->panel = 'column1';
  $pane->type = 'node_links';
  $pane->subtype = 'node_links';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'override_title' => FALSE,
    'override_title_text' => '',
    'build_mode' => 'page_manager',
    'identifier' => '',
    'link' => TRUE,
    'context' => 'panelizer',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array(
    'css_class' => 'link-wrapper',
  );
  $pane->extras = array();
  $pane->position = 4;
  $pane->locks = array();
  $pane->uuid = 'e63dbd8c-ed97-4b6b-a8eb-f15ef8e373fd';
  $display->content['new-e63dbd8c-ed97-4b6b-a8eb-f15ef8e373fd'] = $pane;
  $display->panels['column1'][4] = 'new-e63dbd8c-ed97-4b6b-a8eb-f15ef8e373fd';
  $pane = new stdClass();
  $pane->pid = 'new-02f03cd8-a49a-4ad5-a190-281e36430fcb';
  $pane->panel = 'column1';
  $pane->type = 'annotation';
  $pane->subtype = 'annotation';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'map' => array(
      'path' => 'panels/ajax',
      'load_functions' => '',
      'to_arg_functions' => '',
      'access_callback' => 'user_access',
      'access_arguments' => 'a:1:{i:0;s:14:"access content";}',
      'page_callback' => 'panels_ajax_router',
      'page_arguments' => array(
        0 => 'editor',
        1 => 'add-pane',
        2 => 'panelizer:default:node:pece_artifact_video.page_manager:default',
        3 => 'column1',
        4 => 'annotation',
        5 => 'annotation',
        6 => 'form',
      ),
      'delivery_callback' => 'ajax_deliver',
      'fit' => '3',
      'number_parts' => '2',
      'context' => '0',
      'tab_parent' => '',
      'tab_root' => 'panels/ajax',
      'title' => '',
      'title_callback' => 't',
      'title_arguments' => '',
      'theme_callback' => 'ajax_base_page_theme',
      'theme_arguments' => array(
        0 => 'editor',
        1 => 'add-pane',
        2 => 'panelizer:default:node:pece_artifact_video.page_manager:default',
        3 => 'column1',
        4 => 'annotation',
        5 => 'annotation',
        6 => 'form',
      ),
      'type' => '0',
      'description' => '',
      'position' => '',
      'weight' => '0',
      'include_file' => '',
      'href' => 'panels/ajax',
      'tab_root_href' => 'panels/ajax',
      'tab_parent_href' => '',
      'options' => array(),
      'access' => TRUE,
      'localized_options' => array(),
      'original_map' => array(
        0 => 'panels',
        1 => 'ajax',
        2 => 'editor',
        3 => 'add-pane',
        4 => 'panelizer:default:node:pece_artifact_video.page_manager:default',
        5 => 'column1',
        6 => 'annotation',
        7 => 'annotation',
        8 => 'form',
      ),
      'map' => array(
        0 => 'panels',
        1 => 'ajax',
        2 => 'editor',
        3 => 'add-pane',
        4 => 'panelizer:default:node:pece_artifact_video.page_manager:default',
        5 => 'column1',
        6 => 'annotation',
        7 => 'annotation',
        8 => 'form',
      ),
    ),
    'override_title' => 0,
    'override_title_text' => '',
    'override_title_heading' => 'h2',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 5;
  $pane->locks = array();
  $pane->uuid = '02f03cd8-a49a-4ad5-a190-281e36430fcb';
  $display->content['new-02f03cd8-a49a-4ad5-a190-281e36430fcb'] = $pane;
  $display->panels['column1'][5] = 'new-02f03cd8-a49a-4ad5-a190-281e36430fcb';
  $pane = new stdClass();
  $pane->pid = 'new-07807078-8d41-49b3-b9b6-9a5c9b477ca3';
  $pane->panel = 'column1';
  $pane->type = 'views_panes';
  $pane->subtype = 'pece_annotations-pece_artifact_user_annotations';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'view_settings' => 'fields',
    'header_type' => 'none',
    'view_mode' => 'teaser',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 6;
  $pane->locks = array();
  $pane->uuid = '07807078-8d41-49b3-b9b6-9a5c9b477ca3';
  $display->content['new-07807078-8d41-49b3-b9b6-9a5c9b477ca3'] = $pane;
  $display->panels['column1'][6] = 'new-07807078-8d41-49b3-b9b6-9a5c9b477ca3';
  $pane = new stdClass();
  $pane->pid = 'new-926a4e2b-195b-4491-a039-cc5a423c45c5';
  $pane->panel = 'column2';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_authors';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'above',
    'formatter' => 'taxonomy_term_reference_link',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(),
    'context' => 'panelizer',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '926a4e2b-195b-4491-a039-cc5a423c45c5';
  $display->content['new-926a4e2b-195b-4491-a039-cc5a423c45c5'] = $pane;
  $display->panels['column2'][0] = 'new-926a4e2b-195b-4491-a039-cc5a423c45c5';
  $pane = new stdClass();
  $pane->pid = 'new-c2ccfdde-7119-4440-a494-d683232d235f';
  $pane->panel = 'column2';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_created';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
    'formatter' => 'date_default',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(
      'format_type' => 'medium',
      'multiple_number' => '',
      'multiple_from' => '',
      'multiple_to' => '',
      'fromto' => 'both',
      'show_remaining_days' => 0,
    ),
    'context' => array(),
    'override_title' => 0,
    'override_title_text' => '',
    'override_title_heading' => 'h2',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = 'c2ccfdde-7119-4440-a494-d683232d235f';
  $display->content['new-c2ccfdde-7119-4440-a494-d683232d235f'] = $pane;
  $display->panels['column2'][1] = 'new-c2ccfdde-7119-4440-a494-d683232d235f';
  $pane = new stdClass();
  $pane->pid = 'new-59ec5faa-9f5e-4da3-ac97-5c7d29397eb3';
  $pane->panel = 'column2';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_contributors';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'above',
    'formatter' => 'og_list_default',
    'delta_limit' => '0',
    'delta_offset' => '0',
    'delta_reversed' => 0,
    'formatter_settings' => array(
      'link' => 1,
    ),
    'context' => 'panelizer',
    'override_title' => 0,
    'override_title_text' => '',
    'override_title_heading' => 'h2',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 2;
  $pane->locks = array();
  $pane->uuid = '59ec5faa-9f5e-4da3-ac97-5c7d29397eb3';
  $display->content['new-59ec5faa-9f5e-4da3-ac97-5c7d29397eb3'] = $pane;
  $display->panels['column2'][2] = 'new-59ec5faa-9f5e-4da3-ac97-5c7d29397eb3';
  $pane = new stdClass();
  $pane->pid = 'new-b674469e-8a07-4d4b-9d31-5b615a00395d';
  $pane->panel = 'column2';
  $pane->type = 'node_created';
  $pane->subtype = 'node_created';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'format' => 'medium',
    'context' => 'panelizer',
    'override_title' => 1,
    'override_title_text' => 'Contributed date',
    'override_title_heading' => 'h2',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 3;
  $pane->locks = array();
  $pane->uuid = 'b674469e-8a07-4d4b-9d31-5b615a00395d';
  $display->content['new-b674469e-8a07-4d4b-9d31-5b615a00395d'] = $pane;
  $display->panels['column2'][3] = 'new-b674469e-8a07-4d4b-9d31-5b615a00395d';
  $pane = new stdClass();
  $pane->pid = 'new-2c5e0ee6-702e-40a9-a6ba-bb3643514998';
  $pane->panel = 'column2';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_fieldsite';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'above',
    'formatter' => 'og_list_default',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(
      'link' => FALSE,
    ),
    'context' => 'panelizer',
    'override_title' => 0,
    'override_title_text' => '',
    'override_title_heading' => 'h2',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 4;
  $pane->locks = array();
  $pane->uuid = '2c5e0ee6-702e-40a9-a6ba-bb3643514998';
  $display->content['new-2c5e0ee6-702e-40a9-a6ba-bb3643514998'] = $pane;
  $display->panels['column2'][4] = 'new-2c5e0ee6-702e-40a9-a6ba-bb3643514998';
  $pane = new stdClass();
  $pane->pid = 'new-35489b3a-a08e-432c-b24b-ec02c1865df5';
  $pane->panel = 'column2';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_crit_commentary';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'above',
    'formatter' => 'text_default',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(),
    'context' => 'panelizer',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 5;
  $pane->locks = array();
  $pane->uuid = '35489b3a-a08e-432c-b24b-ec02c1865df5';
  $display->content['new-35489b3a-a08e-432c-b24b-ec02c1865df5'] = $pane;
  $display->panels['column2'][5] = 'new-35489b3a-a08e-432c-b24b-ec02c1865df5';
  $pane = new stdClass();
  $pane->pid = 'new-8b3a45d6-bd13-47ff-b543-93b31a8ee97c';
  $pane->panel = 'column2';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_source';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
    'formatter' => 'text_default',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(),
    'context' => array(),
    'override_title' => 0,
    'override_title_text' => '',
    'override_title_heading' => 'h2',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 6;
  $pane->locks = array();
  $pane->uuid = '8b3a45d6-bd13-47ff-b543-93b31a8ee97c';
  $display->content['new-8b3a45d6-bd13-47ff-b543-93b31a8ee97c'] = $pane;
  $display->panels['column2'][6] = 'new-8b3a45d6-bd13-47ff-b543-93b31a8ee97c';
  $pane = new stdClass();
  $pane->pid = 'new-5c4c8936-9d58-40ff-ba17-02c869427059';
  $pane->panel = 'column2';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_language';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
    'formatter' => 'language_default',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(
      'format' => array(
        'name' => 'name',
        'iso' => 0,
        'name_native' => 0,
      ),
    ),
    'context' => array(),
    'override_title' => 0,
    'override_title_text' => '',
    'override_title_heading' => 'h2',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 7;
  $pane->locks = array();
  $pane->uuid = '5c4c8936-9d58-40ff-ba17-02c869427059';
  $display->content['new-5c4c8936-9d58-40ff-ba17-02c869427059'] = $pane;
  $display->panels['column2'][7] = 'new-5c4c8936-9d58-40ff-ba17-02c869427059';
  $pane = new stdClass();
  $pane->pid = 'new-f893c998-f365-4a33-9d57-a87fe8072c4c';
  $pane->panel = 'column2';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:og_group_ref';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
    'formatter' => 'og_list_default',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(),
    'context' => 'panelizer',
    'override_title' => 1,
    'override_title_text' => 'Group Audience',
    'override_title_heading' => 'h2',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 8;
  $pane->locks = array();
  $pane->uuid = 'f893c998-f365-4a33-9d57-a87fe8072c4c';
  $display->content['new-f893c998-f365-4a33-9d57-a87fe8072c4c'] = $pane;
  $display->panels['column2'][8] = 'new-f893c998-f365-4a33-9d57-a87fe8072c4c';
  $pane = new stdClass();
  $pane->pid = 'new-f2aae210-6a0b-4af8-900c-ff3de5cacd1b';
  $pane->panel = 'column2';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_tags';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'above',
    'formatter' => 'taxonomy_term_reference_link',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(),
    'context' => 'panelizer',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 9;
  $pane->locks = array();
  $pane->uuid = 'f2aae210-6a0b-4af8-900c-ff3de5cacd1b';
  $display->content['new-f2aae210-6a0b-4af8-900c-ff3de5cacd1b'] = $pane;
  $display->panels['column2'][9] = 'new-f2aae210-6a0b-4af8-900c-ff3de5cacd1b';
  $pane = new stdClass();
  $pane->pid = 'new-8f68f814-6ada-4b4d-9ff3-47beb8f343da';
  $pane->panel = 'column2';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_location';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'above',
    'formatter' => 'location_default',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(),
    'context' => 'panelizer',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 10;
  $pane->locks = array();
  $pane->uuid = '8f68f814-6ada-4b4d-9ff3-47beb8f343da';
  $display->content['new-8f68f814-6ada-4b4d-9ff3-47beb8f343da'] = $pane;
  $display->panels['column2'][10] = 'new-8f68f814-6ada-4b4d-9ff3-47beb8f343da';
  $pane = new stdClass();
  $pane->pid = 'new-91a1f158-baba-49df-abc5-5b6259fa79e4';
  $pane->panel = 'column2';
  $pane->type = 'citation';
  $pane->subtype = 'citation';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'override_title' => 1,
    'override_title_text' => 'Cite as',
    'override_title_heading' => 'h2',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 11;
  $pane->locks = array();
  $pane->uuid = '91a1f158-baba-49df-abc5-5b6259fa79e4';
  $display->content['new-91a1f158-baba-49df-abc5-5b6259fa79e4'] = $pane;
  $display->panels['column2'][11] = 'new-91a1f158-baba-49df-abc5-5b6259fa79e4';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-f893c998-f365-4a33-9d57-a87fe8072c4c';
  $panelizer->display = $display;
  $export['node:pece_artifact_video:default'] = $panelizer;

  return $export;
}
