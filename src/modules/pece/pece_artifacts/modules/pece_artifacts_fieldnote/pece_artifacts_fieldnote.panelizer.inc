<?php

/**
 * @file
 * pece_artifacts_fieldnote.panelizer.inc
 */

/**
 * Implements hook_panelizer_defaults().
 */
function pece_artifacts_fieldnote_panelizer_defaults() {
  $export = array();

  $panelizer = new stdClass();
  $panelizer->disabled = FALSE; /* Edit this to true to make a default panelizer disabled initially */
  $panelizer->api_version = 1;
  $panelizer->title = 'Default';
  $panelizer->panelizer_type = 'node';
  $panelizer->panelizer_key = 'pece_artifact_fieldnote';
  $panelizer->access = array();
  $panelizer->view_mode = 'page_manager';
  $panelizer->name = 'node:pece_artifact_fieldnote:default';
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
  $display->uuid = 'd2e24553-8dde-4d0c-9873-80ead5e416af';
  $display->storage_type = 'panelizer_default';
  $display->storage_id = 'node:pece_artifact_fieldnote:default';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-3d9bbc86-d0fa-4357-9f66-5168769b91f6';
  $pane->panel = 'column1';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:body';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'hidden',
    'formatter' => 'text_default',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(),
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
  $pane->uuid = '3d9bbc86-d0fa-4357-9f66-5168769b91f6';
  $display->content['new-3d9bbc86-d0fa-4357-9f66-5168769b91f6'] = $pane;
  $display->panels['column1'][0] = 'new-3d9bbc86-d0fa-4357-9f66-5168769b91f6';
  $pane = new stdClass();
  $pane->pid = 'new-f23f8aec-8ae7-4285-beae-33409172d76f';
  $pane->panel = 'column1';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_license';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
    'formatter' => 'creative_commons_small_image',
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
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = 'f23f8aec-8ae7-4285-beae-33409172d76f';
  $display->content['new-f23f8aec-8ae7-4285-beae-33409172d76f'] = $pane;
  $display->panels['column1'][1] = 'new-f23f8aec-8ae7-4285-beae-33409172d76f';
  $pane = new stdClass();
  $pane->pid = 'new-b3cb149c-978a-49f8-8ff2-2ce1d50cbf4f';
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
  $pane->position = 2;
  $pane->locks = array();
  $pane->uuid = 'b3cb149c-978a-49f8-8ff2-2ce1d50cbf4f';
  $display->content['new-b3cb149c-978a-49f8-8ff2-2ce1d50cbf4f'] = $pane;
  $display->panels['column1'][2] = 'new-b3cb149c-978a-49f8-8ff2-2ce1d50cbf4f';
  $pane = new stdClass();
  $pane->pid = 'new-bb5c9d01-797f-4724-8437-2c4d91dc08a9';
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
        2 => 'panelizer:default:node:pece_artifact_fieldnote.page_manager:default',
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
        2 => 'panelizer:default:node:pece_artifact_fieldnote.page_manager:default',
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
        4 => 'panelizer:default:node:pece_artifact_fieldnote.page_manager:default',
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
        4 => 'panelizer:default:node:pece_artifact_fieldnote.page_manager:default',
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
  $pane->position = 3;
  $pane->locks = array();
  $pane->uuid = 'bb5c9d01-797f-4724-8437-2c4d91dc08a9';
  $display->content['new-bb5c9d01-797f-4724-8437-2c4d91dc08a9'] = $pane;
  $display->panels['column1'][3] = 'new-bb5c9d01-797f-4724-8437-2c4d91dc08a9';
  $pane = new stdClass();
  $pane->pid = 'new-5b9d5fa0-e696-4a06-93d3-a3435b97bfbc';
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
  $pane->position = 4;
  $pane->locks = array();
  $pane->uuid = '5b9d5fa0-e696-4a06-93d3-a3435b97bfbc';
  $display->content['new-5b9d5fa0-e696-4a06-93d3-a3435b97bfbc'] = $pane;
  $display->panels['column1'][4] = 'new-5b9d5fa0-e696-4a06-93d3-a3435b97bfbc';
  $pane = new stdClass();
  $pane->pid = 'new-9e52c08b-9c89-4f49-af6c-0dc1c9be9740';
  $pane->panel = 'column2';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_authors';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'above',
    'formatter' => 'taxonomy_term_reference_link',
    'delta_limit' => '0',
    'delta_offset' => '0',
    'delta_reversed' => 0,
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
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '9e52c08b-9c89-4f49-af6c-0dc1c9be9740';
  $display->content['new-9e52c08b-9c89-4f49-af6c-0dc1c9be9740'] = $pane;
  $display->panels['column2'][0] = 'new-9e52c08b-9c89-4f49-af6c-0dc1c9be9740';
  $pane = new stdClass();
  $pane->pid = 'new-3e25314a-2645-4bfc-90b1-be5da2e9bf21';
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
  $pane->uuid = '3e25314a-2645-4bfc-90b1-be5da2e9bf21';
  $display->content['new-3e25314a-2645-4bfc-90b1-be5da2e9bf21'] = $pane;
  $display->panels['column2'][1] = 'new-3e25314a-2645-4bfc-90b1-be5da2e9bf21';
  $pane = new stdClass();
  $pane->pid = 'new-5a2792fa-97b6-4a64-9079-0d493708217f';
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
      'view_mode' => 'full',
      'links' => 1,
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
  $pane->uuid = '5a2792fa-97b6-4a64-9079-0d493708217f';
  $display->content['new-5a2792fa-97b6-4a64-9079-0d493708217f'] = $pane;
  $display->panels['column2'][2] = 'new-5a2792fa-97b6-4a64-9079-0d493708217f';
  $pane = new stdClass();
  $pane->pid = 'new-6249e480-1503-46fd-972c-d2bf5c76027e';
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
  $pane->uuid = '6249e480-1503-46fd-972c-d2bf5c76027e';
  $display->content['new-6249e480-1503-46fd-972c-d2bf5c76027e'] = $pane;
  $display->panels['column2'][3] = 'new-6249e480-1503-46fd-972c-d2bf5c76027e';
  $pane = new stdClass();
  $pane->pid = 'new-3929e3bf-1991-4a17-abbd-aa153c4c001a';
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
      'view_mode' => 'default',
      'links' => 1,
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
  $pane->uuid = '3929e3bf-1991-4a17-abbd-aa153c4c001a';
  $display->content['new-3929e3bf-1991-4a17-abbd-aa153c4c001a'] = $pane;
  $display->panels['column2'][4] = 'new-3929e3bf-1991-4a17-abbd-aa153c4c001a';
  $pane = new stdClass();
  $pane->pid = 'new-e09d0abb-a76b-4f1b-8b4e-38b321e63610';
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
  $pane->position = 5;
  $pane->locks = array();
  $pane->uuid = 'e09d0abb-a76b-4f1b-8b4e-38b321e63610';
  $display->content['new-e09d0abb-a76b-4f1b-8b4e-38b321e63610'] = $pane;
  $display->panels['column2'][5] = 'new-e09d0abb-a76b-4f1b-8b4e-38b321e63610';
  $pane = new stdClass();
  $pane->pid = 'new-b0132243-6554-4770-8428-782aa93b9288';
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
  $pane->position = 6;
  $pane->locks = array();
  $pane->uuid = 'b0132243-6554-4770-8428-782aa93b9288';
  $display->content['new-b0132243-6554-4770-8428-782aa93b9288'] = $pane;
  $display->panels['column2'][6] = 'new-b0132243-6554-4770-8428-782aa93b9288';
  $pane = new stdClass();
  $pane->pid = 'new-df31586e-929a-4f08-aa5d-255e729fd1d2';
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
    'delta_reversed' => 0,
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
  $pane->position = 7;
  $pane->locks = array();
  $pane->uuid = 'df31586e-929a-4f08-aa5d-255e729fd1d2';
  $display->content['new-df31586e-929a-4f08-aa5d-255e729fd1d2'] = $pane;
  $display->panels['column2'][7] = 'new-df31586e-929a-4f08-aa5d-255e729fd1d2';
  $pane = new stdClass();
  $pane->pid = 'new-5b5b273c-1d84-4442-b40d-ef6a29a81c97';
  $pane->panel = 'column2';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_tags';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'above',
    'formatter' => 'taxonomy_term_reference_link',
    'delta_limit' => '0',
    'delta_offset' => '0',
    'delta_reversed' => 0,
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
  $pane->position = 8;
  $pane->locks = array();
  $pane->uuid = '5b5b273c-1d84-4442-b40d-ef6a29a81c97';
  $display->content['new-5b5b273c-1d84-4442-b40d-ef6a29a81c97'] = $pane;
  $display->panels['column2'][8] = 'new-5b5b273c-1d84-4442-b40d-ef6a29a81c97';
  $pane = new stdClass();
  $pane->pid = 'new-a84573cd-098c-4994-9502-75571e64896d';
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
  $pane->position = 9;
  $pane->locks = array();
  $pane->uuid = 'a84573cd-098c-4994-9502-75571e64896d';
  $display->content['new-a84573cd-098c-4994-9502-75571e64896d'] = $pane;
  $display->panels['column2'][9] = 'new-a84573cd-098c-4994-9502-75571e64896d';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-b3cb149c-978a-49f8-8ff2-2ce1d50cbf4f';
  $panelizer->display = $display;
  $export['node:pece_artifact_fieldnote:default'] = $panelizer;

  return $export;
}
