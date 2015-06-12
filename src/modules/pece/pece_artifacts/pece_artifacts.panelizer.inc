<?php
/**
 * @file
 * pece_artifacts.panelizer.inc
 */

/**
 * Implements hook_panelizer_defaults().
 */
function pece_artifacts_panelizer_defaults() {
  $export = array();

  $panelizer = new stdClass();
  $panelizer->disabled = FALSE; /* Edit this to true to make a default panelizer disabled initially */
  $panelizer->api_version = 1;
  $panelizer->name = 'node:pece_artifact:default';
  $panelizer->title = 'Default';
  $panelizer->panelizer_type = 'node';
  $panelizer->panelizer_key = 'pece_artifact';
  $panelizer->no_blocks = FALSE;
  $panelizer->css_id = '';
  $panelizer->css = '';
  $panelizer->pipeline = 'standard';
  $panelizer->contexts = array();
  $panelizer->relationships = array();
  $panelizer->access = array();
  $panelizer->view_mode = 'page_manager';
  $panelizer->css_class = '';
  $panelizer->title_element = 'H2';
  $panelizer->link_to_entity = TRUE;
  $panelizer->extra = array();
  $display = new panels_display();
  $display->layout = 'flexible';
  $display->layout_settings = array();
  $display->panel_settings = array();
  $display->cache = array();
  $display->title = '%node:title';
  $display->uuid = '003e28f4-414b-425f-a7f0-5445462c9337';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-eb3e0897-1d9f-453e-ad8c-389796bd5be1';
  $pane->panel = 'center';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:og_group_ref';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'above',
    'formatter' => 'og_list_default',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(),
    'context' => 'panelizer',
  );
  $pane->cache = array();
  $pane->style = array();
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = 'eb3e0897-1d9f-453e-ad8c-389796bd5be1';
  $display->content['new-eb3e0897-1d9f-453e-ad8c-389796bd5be1'] = $pane;
  $display->panels['center'][0] = 'new-eb3e0897-1d9f-453e-ad8c-389796bd5be1';
  $pane = new stdClass();
  $pane->pid = 'new-680119d6-2670-4662-b2eb-2eb0e5442325';
  $pane->panel = 'center';
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
  );
  $pane->cache = array();
  $pane->style = array();
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '680119d6-2670-4662-b2eb-2eb0e5442325';
  $display->content['new-680119d6-2670-4662-b2eb-2eb0e5442325'] = $pane;
  $display->panels['center'][1] = 'new-680119d6-2670-4662-b2eb-2eb0e5442325';
  $pane = new stdClass();
  $pane->pid = 'new-cb6c67f2-6b90-4b41-885e-cc85bd3cb5b7';
  $pane->panel = 'center';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_contributors';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'above',
    'formatter' => 'entityreference_label',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(
      'link' => FALSE,
    ),
    'context' => 'panelizer',
  );
  $pane->cache = array();
  $pane->style = array();
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = 'cb6c67f2-6b90-4b41-885e-cc85bd3cb5b7';
  $display->content['new-cb6c67f2-6b90-4b41-885e-cc85bd3cb5b7'] = $pane;
  $display->panels['center'][2] = 'new-cb6c67f2-6b90-4b41-885e-cc85bd3cb5b7';
  $pane = new stdClass();
  $pane->pid = 'new-f98d75b6-3599-439b-92eb-125f0f133d0f';
  $pane->panel = 'center';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_lisence';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'above',
    'formatter' => 'entityreference_label',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(
      'link' => FALSE,
    ),
    'context' => 'panelizer',
  );
  $pane->cache = array();
  $pane->style = array();
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = 'f98d75b6-3599-439b-92eb-125f0f133d0f';
  $display->content['new-f98d75b6-3599-439b-92eb-125f0f133d0f'] = $pane;
  $display->panels['center'][3] = 'new-f98d75b6-3599-439b-92eb-125f0f133d0f';
  $pane = new stdClass();
  $pane->pid = 'new-0a41b978-ae6e-4b07-b4d7-8107254206f5';
  $pane->panel = 'center';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_annotations';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'above',
    'formatter' => 'entityreference_label',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(
      'link' => FALSE,
    ),
    'context' => 'panelizer',
  );
  $pane->cache = array();
  $pane->style = array();
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '0a41b978-ae6e-4b07-b4d7-8107254206f5';
  $display->content['new-0a41b978-ae6e-4b07-b4d7-8107254206f5'] = $pane;
  $display->panels['center'][4] = 'new-0a41b978-ae6e-4b07-b4d7-8107254206f5';
  $pane = new stdClass();
  $pane->pid = 'new-506a3d5c-6240-4c1f-99a2-05550b3e4317';
  $pane->panel = 'center';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_fieldsite';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'above',
    'formatter' => 'entityreference_label',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(
      'link' => FALSE,
    ),
    'context' => 'panelizer',
  );
  $pane->cache = array();
  $pane->style = array();
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '506a3d5c-6240-4c1f-99a2-05550b3e4317';
  $display->content['new-506a3d5c-6240-4c1f-99a2-05550b3e4317'] = $pane;
  $display->panels['center'][5] = 'new-506a3d5c-6240-4c1f-99a2-05550b3e4317';
  $pane = new stdClass();
  $pane->pid = 'new-6b2dea44-d3e4-4699-bd94-712ec2f0190b';
  $pane->panel = 'center';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_project';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'above',
    'formatter' => 'entityreference_label',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(
      'link' => FALSE,
    ),
    'context' => 'panelizer',
  );
  $pane->cache = array();
  $pane->style = array();
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '6b2dea44-d3e4-4699-bd94-712ec2f0190b';
  $display->content['new-6b2dea44-d3e4-4699-bd94-712ec2f0190b'] = $pane;
  $display->panels['center'][6] = 'new-6b2dea44-d3e4-4699-bd94-712ec2f0190b';
  $pane = new stdClass();
  $pane->pid = 'new-1acee996-8b71-485a-915f-483aaf8f1105';
  $pane->panel = 'center';
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
  $pane->style = array();
  $pane->css = array(
    'css_class' => 'link-wrapper',
  );
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '1acee996-8b71-485a-915f-483aaf8f1105';
  $display->content['new-1acee996-8b71-485a-915f-483aaf8f1105'] = $pane;
  $display->panels['center'][7] = 'new-1acee996-8b71-485a-915f-483aaf8f1105';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-1acee996-8b71-485a-915f-483aaf8f1105';
  $panelizer->display = $display;
  $export['node:pece_artifact:default'] = $panelizer;

  return $export;
}
