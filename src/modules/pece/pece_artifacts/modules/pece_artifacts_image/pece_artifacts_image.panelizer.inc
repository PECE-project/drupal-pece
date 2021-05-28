<?php

/**
 * @file
 * pece_artifacts_image.panelizer.inc
 */

/**
 * Implements hook_panelizer_defaults().
 */
function pece_artifacts_image_panelizer_defaults() {
  $export = array();

  $panelizer = new stdClass();
  $panelizer->disabled = FALSE; /* Edit this to true to make a default panelizer disabled initially */
  $panelizer->api_version = 1;
  $panelizer->title = 'Default';
  $panelizer->panelizer_type = 'node';
  $panelizer->panelizer_key = 'pece_artifact_image';
  $panelizer->access = array();
  $panelizer->view_mode = 'page_manager';
  $panelizer->name = 'node:pece_artifact_image:default';
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
  $display->uuid = 'e3b87c57-4f8f-4500-abe6-eabac30d9488';
  $display->storage_type = 'panelizer_default';
  $display->storage_id = 'node:pece_artifact_image:default';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-efde9477-bc4e-4a2a-989c-4dfb0424c728';
  $pane->panel = 'column1';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_media_image';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'above',
    'formatter' => 'image',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(
      'image_link' => '',
      'image_style' => 'pece_artifact_image_large',
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
  $pane->uuid = 'efde9477-bc4e-4a2a-989c-4dfb0424c728';
  $display->content['new-efde9477-bc4e-4a2a-989c-4dfb0424c728'] = $pane;
  $display->panels['column1'][0] = 'new-efde9477-bc4e-4a2a-989c-4dfb0424c728';
  $pane = new stdClass();
  $pane->pid = 'new-252354a8-ac6a-48ab-af71-725c8c11bf05';
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
  $pane->uuid = '252354a8-ac6a-48ab-af71-725c8c11bf05';
  $display->content['new-252354a8-ac6a-48ab-af71-725c8c11bf05'] = $pane;
  $display->panels['column1'][1] = 'new-252354a8-ac6a-48ab-af71-725c8c11bf05';
  $pane = new stdClass();
  $pane->pid = 'new-3e7e2fc5-96cc-468a-a6fd-854870482308';
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
  $pane->position = 2;
  $pane->locks = array();
  $pane->uuid = '3e7e2fc5-96cc-468a-a6fd-854870482308';
  $display->content['new-3e7e2fc5-96cc-468a-a6fd-854870482308'] = $pane;
  $display->panels['column1'][2] = 'new-3e7e2fc5-96cc-468a-a6fd-854870482308';
  $pane = new stdClass();
  $pane->pid = 'new-564d530e-9cd9-4cb5-93ab-e46e43e07491';
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
  $pane->position = 3;
  $pane->locks = array();
  $pane->uuid = '564d530e-9cd9-4cb5-93ab-e46e43e07491';
  $display->content['new-564d530e-9cd9-4cb5-93ab-e46e43e07491'] = $pane;
  $display->panels['column1'][3] = 'new-564d530e-9cd9-4cb5-93ab-e46e43e07491';
  $pane = new stdClass();
  $pane->pid = 'new-99a4124e-0110-44d9-b1e0-f5b61605fef6';
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
        2 => 'panelizer:default:node:pece_artifact_image.page_manager:default',
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
        2 => 'panelizer:default:node:pece_artifact_image.page_manager:default',
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
        4 => 'panelizer:default:node:pece_artifact_image.page_manager:default',
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
        4 => 'panelizer:default:node:pece_artifact_image.page_manager:default',
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
  $pane->position = 4;
  $pane->locks = array();
  $pane->uuid = '99a4124e-0110-44d9-b1e0-f5b61605fef6';
  $display->content['new-99a4124e-0110-44d9-b1e0-f5b61605fef6'] = $pane;
  $display->panels['column1'][4] = 'new-99a4124e-0110-44d9-b1e0-f5b61605fef6';
  $pane = new stdClass();
  $pane->pid = 'new-376597f2-af11-4331-a908-6008a6725e1e';
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
  $pane->position = 5;
  $pane->locks = array();
  $pane->uuid = '376597f2-af11-4331-a908-6008a6725e1e';
  $display->content['new-376597f2-af11-4331-a908-6008a6725e1e'] = $pane;
  $display->panels['column1'][5] = 'new-376597f2-af11-4331-a908-6008a6725e1e';
  $pane = new stdClass();
  $pane->pid = 'new-ba4930d8-5e16-4026-9b1a-21fecaddb26e';
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
  $pane->uuid = 'ba4930d8-5e16-4026-9b1a-21fecaddb26e';
  $display->content['new-ba4930d8-5e16-4026-9b1a-21fecaddb26e'] = $pane;
  $display->panels['column2'][0] = 'new-ba4930d8-5e16-4026-9b1a-21fecaddb26e';
  $pane = new stdClass();
  $pane->pid = 'new-4ac57c1e-9ab9-447c-960d-c8879b96a210';
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
  $pane->uuid = '4ac57c1e-9ab9-447c-960d-c8879b96a210';
  $display->content['new-4ac57c1e-9ab9-447c-960d-c8879b96a210'] = $pane;
  $display->panels['column2'][1] = 'new-4ac57c1e-9ab9-447c-960d-c8879b96a210';
  $pane = new stdClass();
  $pane->pid = 'new-3903181c-f39b-456c-9a1e-57154879198e';
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
      'view_mode' => 'pece_user_reference',
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
  $pane->uuid = '3903181c-f39b-456c-9a1e-57154879198e';
  $display->content['new-3903181c-f39b-456c-9a1e-57154879198e'] = $pane;
  $display->panels['column2'][2] = 'new-3903181c-f39b-456c-9a1e-57154879198e';
  $pane = new stdClass();
  $pane->pid = 'new-b53a508f-5c37-4030-8d34-4b0e4eaaf725';
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
  $pane->uuid = 'b53a508f-5c37-4030-8d34-4b0e4eaaf725';
  $display->content['new-b53a508f-5c37-4030-8d34-4b0e4eaaf725'] = $pane;
  $display->panels['column2'][3] = 'new-b53a508f-5c37-4030-8d34-4b0e4eaaf725';
  $pane = new stdClass();
  $pane->pid = 'new-8b3f8d1d-e6f1-4699-ba57-6a603907e350';
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
      'view_mode' => 'teaser',
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
  $pane->uuid = '8b3f8d1d-e6f1-4699-ba57-6a603907e350';
  $display->content['new-8b3f8d1d-e6f1-4699-ba57-6a603907e350'] = $pane;
  $display->panels['column2'][4] = 'new-8b3f8d1d-e6f1-4699-ba57-6a603907e350';
  $pane = new stdClass();
  $pane->pid = 'new-8b47ea94-17f8-4b32-94fc-0475bbad6977';
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
  $pane->uuid = '8b47ea94-17f8-4b32-94fc-0475bbad6977';
  $display->content['new-8b47ea94-17f8-4b32-94fc-0475bbad6977'] = $pane;
  $display->panels['column2'][5] = 'new-8b47ea94-17f8-4b32-94fc-0475bbad6977';
  $pane = new stdClass();
  $pane->pid = 'new-eb1d2a95-fc8f-47e7-b41a-6594df1ddb5f';
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
  $pane->uuid = 'eb1d2a95-fc8f-47e7-b41a-6594df1ddb5f';
  $display->content['new-eb1d2a95-fc8f-47e7-b41a-6594df1ddb5f'] = $pane;
  $display->panels['column2'][6] = 'new-eb1d2a95-fc8f-47e7-b41a-6594df1ddb5f';
  $pane = new stdClass();
  $pane->pid = 'new-9def9498-36e6-45a7-857e-834523fe9d6f';
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
  $pane->uuid = '9def9498-36e6-45a7-857e-834523fe9d6f';
  $display->content['new-9def9498-36e6-45a7-857e-834523fe9d6f'] = $pane;
  $display->panels['column2'][7] = 'new-9def9498-36e6-45a7-857e-834523fe9d6f';
  $pane = new stdClass();
  $pane->pid = 'new-75c8615a-51a7-40b7-b471-defc7a5deb1c';
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
  $pane->uuid = '75c8615a-51a7-40b7-b471-defc7a5deb1c';
  $display->content['new-75c8615a-51a7-40b7-b471-defc7a5deb1c'] = $pane;
  $display->panels['column2'][8] = 'new-75c8615a-51a7-40b7-b471-defc7a5deb1c';
  $pane = new stdClass();
  $pane->pid = 'new-3fb96209-b8cf-4c28-b98e-dc78a95e5605';
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
  $pane->uuid = '3fb96209-b8cf-4c28-b98e-dc78a95e5605';
  $display->content['new-3fb96209-b8cf-4c28-b98e-dc78a95e5605'] = $pane;
  $display->panels['column2'][9] = 'new-3fb96209-b8cf-4c28-b98e-dc78a95e5605';
  $pane = new stdClass();
  $pane->pid = 'new-72998067-8742-487b-8914-d0677ece81b5';
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
  $pane->uuid = '72998067-8742-487b-8914-d0677ece81b5';
  $display->content['new-72998067-8742-487b-8914-d0677ece81b5'] = $pane;
  $display->panels['column2'][10] = 'new-72998067-8742-487b-8914-d0677ece81b5';
  $pane = new stdClass();
  $pane->pid = 'new-37744c4c-79ee-447a-95df-fa1c4fda0464';
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
  $pane->uuid = '37744c4c-79ee-447a-95df-fa1c4fda0464';
  $display->content['new-37744c4c-79ee-447a-95df-fa1c4fda0464'] = $pane;
  $display->panels['column2'][11] = 'new-37744c4c-79ee-447a-95df-fa1c4fda0464';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-75c8615a-51a7-40b7-b471-defc7a5deb1c';
  $panelizer->display = $display;
  $export['node:pece_artifact_image:default'] = $panelizer;

  return $export;
}
