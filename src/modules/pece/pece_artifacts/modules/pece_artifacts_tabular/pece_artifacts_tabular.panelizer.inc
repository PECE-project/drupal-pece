<?php

/**
 * @file
 * pece_artifacts_tabular.panelizer.inc
 */

/**
 * Implements hook_panelizer_defaults().
 */
function pece_artifacts_tabular_panelizer_defaults() {
  $export = array();

  $panelizer = new stdClass();
  $panelizer->disabled = FALSE; /* Edit this to true to make a default panelizer disabled initially */
  $panelizer->api_version = 1;
  $panelizer->title = 'Default';
  $panelizer->panelizer_type = 'node';
  $panelizer->panelizer_key = 'pece_artifact_tabular';
  $panelizer->access = array();
  $panelizer->view_mode = 'page_manager';
  $panelizer->name = 'node:pece_artifact_tabular:default';
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
  $display->layout = 'pece_sidebar_right';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'column1' => NULL,
      'column2' => NULL,
      'content' => NULL,
      'sidebar' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '%node:title';
  $display->uuid = '6ae2f024-3fb5-4bec-896a-32c3ba9cf39c';
  $display->storage_type = 'panelizer_default';
  $display->storage_id = 'node:pece_artifact_tabular:default';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-80e68ddc-59aa-4666-90de-47f1259a7c16';
  $pane->panel = 'content';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_media_tabular';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'above',
    'formatter' => 'direct_download_accessible_icon',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(
      'pdf_width' => '525',
      'pdf_height' => '650',
      'renderer' => 'direct',
      'download' => 0,
      'colorbox' => FALSE,
      'colorbox_link_text' => '',
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
  $pane->uuid = '80e68ddc-59aa-4666-90de-47f1259a7c16';
  $display->content['new-80e68ddc-59aa-4666-90de-47f1259a7c16'] = $pane;
  $display->panels['content'][0] = 'new-80e68ddc-59aa-4666-90de-47f1259a7c16';
  $pane = new stdClass();
  $pane->pid = 'new-b3e2d7f5-2fd7-4d4e-8716-cc6f8f049822';
  $pane->panel = 'content';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_media_tablr_attach';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
    'formatter' => 'direct_download_accessible_icon',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(
      'text' => 'Download [file:name]',
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
  $pane->uuid = 'b3e2d7f5-2fd7-4d4e-8716-cc6f8f049822';
  $display->content['new-b3e2d7f5-2fd7-4d4e-8716-cc6f8f049822'] = $pane;
  $display->panels['content'][1] = 'new-b3e2d7f5-2fd7-4d4e-8716-cc6f8f049822';
  $pane = new stdClass();
  $pane->pid = 'new-896e11b7-f8e9-4d0c-83de-897c130c0352';
  $pane->panel = 'content';
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
  $pane->position = 2;
  $pane->locks = array();
  $pane->uuid = '896e11b7-f8e9-4d0c-83de-897c130c0352';
  $display->content['new-896e11b7-f8e9-4d0c-83de-897c130c0352'] = $pane;
  $display->panels['content'][2] = 'new-896e11b7-f8e9-4d0c-83de-897c130c0352';
  $pane = new stdClass();
  $pane->pid = 'new-896c59b5-c169-48c3-b003-ebf63af9f1d8';
  $pane->panel = 'content';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_bibliography';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'hidden',
    'formatter' => 'entityreference_label',
    'delta_limit' => '0',
    'delta_offset' => '0',
    'delta_reversed' => 0,
    'formatter_settings' => array(
      'link' => 1,
    ),
    'context' => array(),
    'override_title' => 1,
    'override_title_text' => 'Citation',
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
  $pane->uuid = '896c59b5-c169-48c3-b003-ebf63af9f1d8';
  $display->content['new-896c59b5-c169-48c3-b003-ebf63af9f1d8'] = $pane;
  $display->panels['content'][3] = 'new-896c59b5-c169-48c3-b003-ebf63af9f1d8';
  $pane = new stdClass();
  $pane->pid = 'new-39810e4e-8c07-4693-83a0-beb6fbe25478';
  $pane->panel = 'content';
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
  $pane->uuid = '39810e4e-8c07-4693-83a0-beb6fbe25478';
  $display->content['new-39810e4e-8c07-4693-83a0-beb6fbe25478'] = $pane;
  $display->panels['content'][4] = 'new-39810e4e-8c07-4693-83a0-beb6fbe25478';
  $pane = new stdClass();
  $pane->pid = 'new-ffab934f-fac6-4d10-a1eb-05d24e0dd9ca';
  $pane->panel = 'content';
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
        2 => 'panelizer:default:node:pece_artifact_tabular.page_manager:default',
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
        2 => 'panelizer:default:node:pece_artifact_tabular.page_manager:default',
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
        4 => 'panelizer:default:node:pece_artifact_tabular.page_manager:default',
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
        4 => 'panelizer:default:node:pece_artifact_tabular.page_manager:default',
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
  $pane->uuid = 'ffab934f-fac6-4d10-a1eb-05d24e0dd9ca';
  $display->content['new-ffab934f-fac6-4d10-a1eb-05d24e0dd9ca'] = $pane;
  $display->panels['content'][5] = 'new-ffab934f-fac6-4d10-a1eb-05d24e0dd9ca';
  $pane = new stdClass();
  $pane->pid = 'new-3a26e734-dc3e-4358-85d9-037c15c3aae4';
  $pane->panel = 'content';
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
  $pane->uuid = '3a26e734-dc3e-4358-85d9-037c15c3aae4';
  $display->content['new-3a26e734-dc3e-4358-85d9-037c15c3aae4'] = $pane;
  $display->panels['content'][6] = 'new-3a26e734-dc3e-4358-85d9-037c15c3aae4';
  $pane = new stdClass();
  $pane->pid = 'new-688d01be-8903-4488-8143-73d1dc0c1904';
  $pane->panel = 'sidebar';
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
  $pane->uuid = '688d01be-8903-4488-8143-73d1dc0c1904';
  $display->content['new-688d01be-8903-4488-8143-73d1dc0c1904'] = $pane;
  $display->panels['sidebar'][0] = 'new-688d01be-8903-4488-8143-73d1dc0c1904';
  $pane = new stdClass();
  $pane->pid = 'new-33382424-8477-489f-9d15-32df183ff280';
  $pane->panel = 'sidebar';
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
  $pane->uuid = '33382424-8477-489f-9d15-32df183ff280';
  $display->content['new-33382424-8477-489f-9d15-32df183ff280'] = $pane;
  $display->panels['sidebar'][1] = 'new-33382424-8477-489f-9d15-32df183ff280';
  $pane = new stdClass();
  $pane->pid = 'new-b8a8a580-8ae9-4147-a5d7-797f899bad76';
  $pane->panel = 'sidebar';
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
  $pane->uuid = 'b8a8a580-8ae9-4147-a5d7-797f899bad76';
  $display->content['new-b8a8a580-8ae9-4147-a5d7-797f899bad76'] = $pane;
  $display->panels['sidebar'][2] = 'new-b8a8a580-8ae9-4147-a5d7-797f899bad76';
  $pane = new stdClass();
  $pane->pid = 'new-490eb1a8-9342-435f-ac8d-99dfcb3bcfa0';
  $pane->panel = 'sidebar';
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
  $pane->uuid = '490eb1a8-9342-435f-ac8d-99dfcb3bcfa0';
  $display->content['new-490eb1a8-9342-435f-ac8d-99dfcb3bcfa0'] = $pane;
  $display->panels['sidebar'][3] = 'new-490eb1a8-9342-435f-ac8d-99dfcb3bcfa0';
  $pane = new stdClass();
  $pane->pid = 'new-85d35ff3-d01f-498c-a20e-4e818c4522b6';
  $pane->panel = 'sidebar';
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
  $pane->uuid = '85d35ff3-d01f-498c-a20e-4e818c4522b6';
  $display->content['new-85d35ff3-d01f-498c-a20e-4e818c4522b6'] = $pane;
  $display->panels['sidebar'][4] = 'new-85d35ff3-d01f-498c-a20e-4e818c4522b6';
  $pane = new stdClass();
  $pane->pid = 'new-454c0083-a8b3-4f77-be8b-20d08b886181';
  $pane->panel = 'sidebar';
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
  $pane->uuid = '454c0083-a8b3-4f77-be8b-20d08b886181';
  $display->content['new-454c0083-a8b3-4f77-be8b-20d08b886181'] = $pane;
  $display->panels['sidebar'][5] = 'new-454c0083-a8b3-4f77-be8b-20d08b886181';
  $pane = new stdClass();
  $pane->pid = 'new-659b6ee4-24bb-4118-a3b3-b2d89060a29e';
  $pane->panel = 'sidebar';
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
  $pane->uuid = '659b6ee4-24bb-4118-a3b3-b2d89060a29e';
  $display->content['new-659b6ee4-24bb-4118-a3b3-b2d89060a29e'] = $pane;
  $display->panels['sidebar'][6] = 'new-659b6ee4-24bb-4118-a3b3-b2d89060a29e';
  $pane = new stdClass();
  $pane->pid = 'new-ee4a62e3-6e47-41bf-a0e4-ab31eb2d63ec';
  $pane->panel = 'sidebar';
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
  $pane->uuid = 'ee4a62e3-6e47-41bf-a0e4-ab31eb2d63ec';
  $display->content['new-ee4a62e3-6e47-41bf-a0e4-ab31eb2d63ec'] = $pane;
  $display->panels['sidebar'][7] = 'new-ee4a62e3-6e47-41bf-a0e4-ab31eb2d63ec';
  $pane = new stdClass();
  $pane->pid = 'new-d0a3de04-2a7a-40b5-9206-ecb5de6d1acf';
  $pane->panel = 'sidebar';
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
  $pane->uuid = 'd0a3de04-2a7a-40b5-9206-ecb5de6d1acf';
  $display->content['new-d0a3de04-2a7a-40b5-9206-ecb5de6d1acf'] = $pane;
  $display->panels['sidebar'][8] = 'new-d0a3de04-2a7a-40b5-9206-ecb5de6d1acf';
  $pane = new stdClass();
  $pane->pid = 'new-bf3ca5a2-1407-45ac-a50e-891f0ead2e4c';
  $pane->panel = 'sidebar';
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
  $pane->uuid = 'bf3ca5a2-1407-45ac-a50e-891f0ead2e4c';
  $display->content['new-bf3ca5a2-1407-45ac-a50e-891f0ead2e4c'] = $pane;
  $display->panels['sidebar'][9] = 'new-bf3ca5a2-1407-45ac-a50e-891f0ead2e4c';
  $pane = new stdClass();
  $pane->pid = 'new-b69eb20f-9c51-4c67-9c58-b9d0660ef9ce';
  $pane->panel = 'sidebar';
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
  $pane->uuid = 'b69eb20f-9c51-4c67-9c58-b9d0660ef9ce';
  $display->content['new-b69eb20f-9c51-4c67-9c58-b9d0660ef9ce'] = $pane;
  $display->panels['sidebar'][10] = 'new-b69eb20f-9c51-4c67-9c58-b9d0660ef9ce';
  $pane = new stdClass();
  $pane->pid = 'new-b67ca15e-4113-45c7-b81d-ae1e47290f51';
  $pane->panel = 'sidebar';
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
  $pane->uuid = 'b67ca15e-4113-45c7-b81d-ae1e47290f51';
  $display->content['new-b67ca15e-4113-45c7-b81d-ae1e47290f51'] = $pane;
  $display->panels['sidebar'][11] = 'new-b67ca15e-4113-45c7-b81d-ae1e47290f51';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $panelizer->display = $display;
  $export['node:pece_artifact_tabular:default'] = $panelizer;

  return $export;
}
