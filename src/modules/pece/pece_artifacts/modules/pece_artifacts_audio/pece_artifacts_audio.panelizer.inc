<?php

/**
 * @file
 * pece_artifacts_audio.panelizer.inc
 */

/**
 * Implements hook_panelizer_defaults().
 */
function pece_artifacts_audio_panelizer_defaults() {
  $export = array();

  $panelizer = new stdClass();
  $panelizer->disabled = FALSE; /* Edit this to true to make a default panelizer disabled initially */
  $panelizer->api_version = 1;
  $panelizer->title = 'Default';
  $panelizer->panelizer_type = 'node';
  $panelizer->panelizer_key = 'pece_artifact_audio';
  $panelizer->access = array();
  $panelizer->view_mode = 'page_manager';
  $panelizer->name = 'node:pece_artifact_audio:default';
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
  $display->uuid = '841250bf-f505-4eeb-9ee2-17a979f74169';
  $display->storage_type = 'panelizer_default';
  $display->storage_id = 'node:pece_artifact_audio:default';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-de356e48-1de5-4977-8fb1-60d5aff5826d';
  $pane->panel = 'column1';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_media_audio';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'above',
    'formatter' => 'file_audio',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(
      'controls' => 1,
      'autoplay' => 0,
      'loop' => 0,
      'multiple_file_behavior' => 'tags',
      'text' => 'Download [file:name]',
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
  $pane->uuid = 'de356e48-1de5-4977-8fb1-60d5aff5826d';
  $display->content['new-de356e48-1de5-4977-8fb1-60d5aff5826d'] = $pane;
  $display->panels['column1'][0] = 'new-de356e48-1de5-4977-8fb1-60d5aff5826d';
  $pane = new stdClass();
  $pane->pid = 'new-65dcfe30-f78e-409d-b1e2-d20d3f5e6c0e';
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
  $pane->uuid = '65dcfe30-f78e-409d-b1e2-d20d3f5e6c0e';
  $display->content['new-65dcfe30-f78e-409d-b1e2-d20d3f5e6c0e'] = $pane;
  $display->panels['column1'][1] = 'new-65dcfe30-f78e-409d-b1e2-d20d3f5e6c0e';
  $pane = new stdClass();
  $pane->pid = 'new-f94c9d24-f084-4a5c-bf49-c8431e8bd228';
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
  $pane->uuid = 'f94c9d24-f084-4a5c-bf49-c8431e8bd228';
  $display->content['new-f94c9d24-f084-4a5c-bf49-c8431e8bd228'] = $pane;
  $display->panels['column1'][2] = 'new-f94c9d24-f084-4a5c-bf49-c8431e8bd228';
  $pane = new stdClass();
  $pane->pid = 'new-c95df1ec-ab36-4166-8df2-093919075841';
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
  $pane->uuid = 'c95df1ec-ab36-4166-8df2-093919075841';
  $display->content['new-c95df1ec-ab36-4166-8df2-093919075841'] = $pane;
  $display->panels['column1'][3] = 'new-c95df1ec-ab36-4166-8df2-093919075841';
  $pane = new stdClass();
  $pane->pid = 'new-7f2e508b-27da-4739-8660-27a3a68616d8';
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
  $pane->uuid = '7f2e508b-27da-4739-8660-27a3a68616d8';
  $display->content['new-7f2e508b-27da-4739-8660-27a3a68616d8'] = $pane;
  $display->panels['column1'][4] = 'new-7f2e508b-27da-4739-8660-27a3a68616d8';
  $pane = new stdClass();
  $pane->pid = 'new-eee1ad7f-2679-4275-96e3-5001fbbc6d13';
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
        2 => 'panelizer:default:node:pece_artifact_audio.page_manager:default',
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
        2 => 'panelizer:default:node:pece_artifact_audio.page_manager:default',
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
        4 => 'panelizer:default:node:pece_artifact_audio.page_manager:default',
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
        4 => 'panelizer:default:node:pece_artifact_audio.page_manager:default',
        5 => 'column1',
        6 => 'annotation',
        7 => 'annotation',
        8 => 'form',
      ),
    ),
    'override_title' => 1,
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
  $pane->uuid = 'eee1ad7f-2679-4275-96e3-5001fbbc6d13';
  $display->content['new-eee1ad7f-2679-4275-96e3-5001fbbc6d13'] = $pane;
  $display->panels['column1'][5] = 'new-eee1ad7f-2679-4275-96e3-5001fbbc6d13';
  $pane = new stdClass();
  $pane->pid = 'new-604715e3-a09b-4b01-a67b-b8d1955d1fe8';
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
  $pane->uuid = '604715e3-a09b-4b01-a67b-b8d1955d1fe8';
  $display->content['new-604715e3-a09b-4b01-a67b-b8d1955d1fe8'] = $pane;
  $display->panels['column1'][6] = 'new-604715e3-a09b-4b01-a67b-b8d1955d1fe8';
  $pane = new stdClass();
  $pane->pid = 'new-b9f5451d-261b-4d80-af97-d7c28723b9ec';
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
  $pane->uuid = 'b9f5451d-261b-4d80-af97-d7c28723b9ec';
  $display->content['new-b9f5451d-261b-4d80-af97-d7c28723b9ec'] = $pane;
  $display->panels['column2'][0] = 'new-b9f5451d-261b-4d80-af97-d7c28723b9ec';
  $pane = new stdClass();
  $pane->pid = 'new-c5b2a06e-fd7b-450d-bc14-b6478eb17448';
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
  $pane->uuid = 'c5b2a06e-fd7b-450d-bc14-b6478eb17448';
  $display->content['new-c5b2a06e-fd7b-450d-bc14-b6478eb17448'] = $pane;
  $display->panels['column2'][1] = 'new-c5b2a06e-fd7b-450d-bc14-b6478eb17448';
  $pane = new stdClass();
  $pane->pid = 'new-644245a4-f2ab-4ddc-aa8c-2c3a56148dfa';
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
  $pane->position = 2;
  $pane->locks = array();
  $pane->uuid = '644245a4-f2ab-4ddc-aa8c-2c3a56148dfa';
  $display->content['new-644245a4-f2ab-4ddc-aa8c-2c3a56148dfa'] = $pane;
  $display->panels['column2'][2] = 'new-644245a4-f2ab-4ddc-aa8c-2c3a56148dfa';
  $pane = new stdClass();
  $pane->pid = 'new-d9ace7e7-8692-42f0-b3fd-fa6dfbbdf1ac';
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
  $pane->uuid = 'd9ace7e7-8692-42f0-b3fd-fa6dfbbdf1ac';
  $display->content['new-d9ace7e7-8692-42f0-b3fd-fa6dfbbdf1ac'] = $pane;
  $display->panels['column2'][3] = 'new-d9ace7e7-8692-42f0-b3fd-fa6dfbbdf1ac';
  $pane = new stdClass();
  $pane->pid = 'new-c7b234e7-9d4d-4f22-a94a-14ad46182050';
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
  $pane->uuid = 'c7b234e7-9d4d-4f22-a94a-14ad46182050';
  $display->content['new-c7b234e7-9d4d-4f22-a94a-14ad46182050'] = $pane;
  $display->panels['column2'][4] = 'new-c7b234e7-9d4d-4f22-a94a-14ad46182050';
  $pane = new stdClass();
  $pane->pid = 'new-d7808060-7af0-448f-ac3a-ea2578df7130';
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
  $pane->uuid = 'd7808060-7af0-448f-ac3a-ea2578df7130';
  $display->content['new-d7808060-7af0-448f-ac3a-ea2578df7130'] = $pane;
  $display->panels['column2'][5] = 'new-d7808060-7af0-448f-ac3a-ea2578df7130';
  $pane = new stdClass();
  $pane->pid = 'new-cefb8dbe-1660-4471-a605-c467be523c69';
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
  $pane->uuid = 'cefb8dbe-1660-4471-a605-c467be523c69';
  $display->content['new-cefb8dbe-1660-4471-a605-c467be523c69'] = $pane;
  $display->panels['column2'][6] = 'new-cefb8dbe-1660-4471-a605-c467be523c69';
  $pane = new stdClass();
  $pane->pid = 'new-d3cc462d-2568-46e2-be3d-914feb4f55a2';
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
  $pane->uuid = 'd3cc462d-2568-46e2-be3d-914feb4f55a2';
  $display->content['new-d3cc462d-2568-46e2-be3d-914feb4f55a2'] = $pane;
  $display->panels['column2'][7] = 'new-d3cc462d-2568-46e2-be3d-914feb4f55a2';
  $pane = new stdClass();
  $pane->pid = 'new-83e90775-d800-4b69-b9a6-26a58bd90538';
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
  $pane->uuid = '83e90775-d800-4b69-b9a6-26a58bd90538';
  $display->content['new-83e90775-d800-4b69-b9a6-26a58bd90538'] = $pane;
  $display->panels['column2'][8] = 'new-83e90775-d800-4b69-b9a6-26a58bd90538';
  $pane = new stdClass();
  $pane->pid = 'new-6baf265d-6729-410a-b9b6-b6c996190fac';
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
  $pane->uuid = '6baf265d-6729-410a-b9b6-b6c996190fac';
  $display->content['new-6baf265d-6729-410a-b9b6-b6c996190fac'] = $pane;
  $display->panels['column2'][9] = 'new-6baf265d-6729-410a-b9b6-b6c996190fac';
  $pane = new stdClass();
  $pane->pid = 'new-8c00c587-26fa-4b5a-aade-f640e42cdcec';
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
  $pane->uuid = '8c00c587-26fa-4b5a-aade-f640e42cdcec';
  $display->content['new-8c00c587-26fa-4b5a-aade-f640e42cdcec'] = $pane;
  $display->panels['column2'][10] = 'new-8c00c587-26fa-4b5a-aade-f640e42cdcec';
  $pane = new stdClass();
  $pane->pid = 'new-9558acde-048c-433b-b1f0-50b95bdf3a89';
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
  $pane->uuid = '9558acde-048c-433b-b1f0-50b95bdf3a89';
  $display->content['new-9558acde-048c-433b-b1f0-50b95bdf3a89'] = $pane;
  $display->panels['column2'][11] = 'new-9558acde-048c-433b-b1f0-50b95bdf3a89';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-7f2e508b-27da-4739-8660-27a3a68616d8';
  $panelizer->display = $display;
  $export['node:pece_artifact_audio:default'] = $panelizer;

  return $export;
}
