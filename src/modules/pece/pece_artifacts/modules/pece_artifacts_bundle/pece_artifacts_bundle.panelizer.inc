<?php

/**
 * @file
 * pece_artifacts_bundle.panelizer.inc
 */

/**
 * Implements hook_panelizer_defaults().
 */
function pece_artifacts_bundle_panelizer_defaults() {
  $export = array();

  $panelizer = new stdClass();
  $panelizer->disabled = FALSE; /* Edit this to true to make a default panelizer disabled initially */
  $panelizer->api_version = 1;
  $panelizer->title = 'Default';
  $panelizer->panelizer_type = 'node';
  $panelizer->panelizer_key = 'pece_artifact_bundle';
  $panelizer->access = array();
  $panelizer->view_mode = 'page_manager';
  $panelizer->name = 'node:pece_artifact_bundle:default';
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
  $display->uuid = '3a7a7b8f-cdfe-4bf0-8f90-11878c374373';
  $display->storage_type = 'panelizer_default';
  $display->storage_id = 'node:pece_artifact_bundle:default';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-870bca3c-5c92-427f-837d-4e5c819f1bf5';
  $pane->panel = 'column1';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_artifacts';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
    'formatter' => 'entityreference_entity_view',
    'delta_limit' => '0',
    'delta_offset' => '0',
    'delta_reversed' => 0,
    'formatter_settings' => array(
      'link' => 1,
      'view_mode' => 'meta_content',
      'links' => 1,
      'use_content_language' => 1,
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
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '870bca3c-5c92-427f-837d-4e5c819f1bf5';
  $display->content['new-870bca3c-5c92-427f-837d-4e5c819f1bf5'] = $pane;
  $display->panels['column1'][0] = 'new-870bca3c-5c92-427f-837d-4e5c819f1bf5';
  $pane = new stdClass();
  $pane->pid = 'new-5d5233ac-3dd0-49d7-bd4d-a89dc73604f5';
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
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = '5d5233ac-3dd0-49d7-bd4d-a89dc73604f5';
  $display->content['new-5d5233ac-3dd0-49d7-bd4d-a89dc73604f5'] = $pane;
  $display->panels['column1'][1] = 'new-5d5233ac-3dd0-49d7-bd4d-a89dc73604f5';
  $pane = new stdClass();
  $pane->pid = 'new-b36bb3ea-aa9c-4525-874b-0de0d3152b46';
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
  $pane->uuid = 'b36bb3ea-aa9c-4525-874b-0de0d3152b46';
  $display->content['new-b36bb3ea-aa9c-4525-874b-0de0d3152b46'] = $pane;
  $display->panels['column1'][2] = 'new-b36bb3ea-aa9c-4525-874b-0de0d3152b46';
  $pane = new stdClass();
  $pane->pid = 'new-83d1a4ce-d9e0-4076-baf8-9bcd3db97a74';
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
        2 => 'panelizer:default:node:pece_artifact_bundle.page_manager:default',
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
        2 => 'panelizer:default:node:pece_artifact_bundle.page_manager:default',
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
        4 => 'panelizer:default:node:pece_artifact_bundle.page_manager:default',
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
        4 => 'panelizer:default:node:pece_artifact_bundle.page_manager:default',
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
  $pane->uuid = '83d1a4ce-d9e0-4076-baf8-9bcd3db97a74';
  $display->content['new-83d1a4ce-d9e0-4076-baf8-9bcd3db97a74'] = $pane;
  $display->panels['column1'][3] = 'new-83d1a4ce-d9e0-4076-baf8-9bcd3db97a74';
  $pane = new stdClass();
  $pane->pid = 'new-33074071-9721-4975-8da9-0cda1b4a9c45';
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
  $pane->uuid = '33074071-9721-4975-8da9-0cda1b4a9c45';
  $display->content['new-33074071-9721-4975-8da9-0cda1b4a9c45'] = $pane;
  $display->panels['column1'][4] = 'new-33074071-9721-4975-8da9-0cda1b4a9c45';
  $pane = new stdClass();
  $pane->pid = 'new-be656d7c-9fc4-437f-a138-2ff5387cffb1';
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
  $pane->uuid = 'be656d7c-9fc4-437f-a138-2ff5387cffb1';
  $display->content['new-be656d7c-9fc4-437f-a138-2ff5387cffb1'] = $pane;
  $display->panels['column2'][0] = 'new-be656d7c-9fc4-437f-a138-2ff5387cffb1';
  $pane = new stdClass();
  $pane->pid = 'new-db044ddc-3093-488f-a7f5-9c3c460438ea';
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
  $pane->uuid = 'db044ddc-3093-488f-a7f5-9c3c460438ea';
  $display->content['new-db044ddc-3093-488f-a7f5-9c3c460438ea'] = $pane;
  $display->panels['column2'][1] = 'new-db044ddc-3093-488f-a7f5-9c3c460438ea';
  $pane = new stdClass();
  $pane->pid = 'new-b8f23ee1-c507-473f-a293-da4543618175';
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
  $pane->uuid = 'b8f23ee1-c507-473f-a293-da4543618175';
  $display->content['new-b8f23ee1-c507-473f-a293-da4543618175'] = $pane;
  $display->panels['column2'][2] = 'new-b8f23ee1-c507-473f-a293-da4543618175';
  $pane = new stdClass();
  $pane->pid = 'new-d18c645e-43f1-4328-9d11-6f285e0bd049';
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
  $pane->uuid = 'd18c645e-43f1-4328-9d11-6f285e0bd049';
  $display->content['new-d18c645e-43f1-4328-9d11-6f285e0bd049'] = $pane;
  $display->panels['column2'][3] = 'new-d18c645e-43f1-4328-9d11-6f285e0bd049';
  $pane = new stdClass();
  $pane->pid = 'new-2110e6c2-5e65-45c0-b4e8-4a12bfb5ea1a';
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
  $pane->uuid = '2110e6c2-5e65-45c0-b4e8-4a12bfb5ea1a';
  $display->content['new-2110e6c2-5e65-45c0-b4e8-4a12bfb5ea1a'] = $pane;
  $display->panels['column2'][4] = 'new-2110e6c2-5e65-45c0-b4e8-4a12bfb5ea1a';
  $pane = new stdClass();
  $pane->pid = 'new-1a196ff6-cfac-4023-adfe-4b15cd48f24a';
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
  $pane->uuid = '1a196ff6-cfac-4023-adfe-4b15cd48f24a';
  $display->content['new-1a196ff6-cfac-4023-adfe-4b15cd48f24a'] = $pane;
  $display->panels['column2'][5] = 'new-1a196ff6-cfac-4023-adfe-4b15cd48f24a';
  $pane = new stdClass();
  $pane->pid = 'new-3c37459c-aea2-4ed9-87a0-e54ea998c66f';
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
  $pane->position = 6;
  $pane->locks = array();
  $pane->uuid = '3c37459c-aea2-4ed9-87a0-e54ea998c66f';
  $display->content['new-3c37459c-aea2-4ed9-87a0-e54ea998c66f'] = $pane;
  $display->panels['column2'][6] = 'new-3c37459c-aea2-4ed9-87a0-e54ea998c66f';
  $pane = new stdClass();
  $pane->pid = 'new-f48e3427-ba32-41bb-ae64-47264b06377f';
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
  $pane->position = 7;
  $pane->locks = array();
  $pane->uuid = 'f48e3427-ba32-41bb-ae64-47264b06377f';
  $display->content['new-f48e3427-ba32-41bb-ae64-47264b06377f'] = $pane;
  $display->panels['column2'][7] = 'new-f48e3427-ba32-41bb-ae64-47264b06377f';
  $pane = new stdClass();
  $pane->pid = 'new-92633101-e96f-4ec6-a623-9517242ed1e5';
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
  $pane->position = 8;
  $pane->locks = array();
  $pane->uuid = '92633101-e96f-4ec6-a623-9517242ed1e5';
  $display->content['new-92633101-e96f-4ec6-a623-9517242ed1e5'] = $pane;
  $display->panels['column2'][8] = 'new-92633101-e96f-4ec6-a623-9517242ed1e5';
  $pane = new stdClass();
  $pane->pid = 'new-84cc1349-ab38-4377-8b0d-91cc65ceca00';
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
  $pane->uuid = '84cc1349-ab38-4377-8b0d-91cc65ceca00';
  $display->content['new-84cc1349-ab38-4377-8b0d-91cc65ceca00'] = $pane;
  $display->panels['column2'][9] = 'new-84cc1349-ab38-4377-8b0d-91cc65ceca00';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-3c37459c-aea2-4ed9-87a0-e54ea998c66f';
  $panelizer->display = $display;
  $export['node:pece_artifact_bundle:default'] = $panelizer;

  return $export;
}
