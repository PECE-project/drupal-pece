<?php
/**
 * @file
 * pece_about.panelizer.inc
 */

/**
 * Implements hook_panelizer_defaults().
 */
function pece_about_panelizer_defaults() {
  $export = array();

  $panelizer = new stdClass();
  $panelizer->disabled = FALSE; /* Edit this to true to make a default panelizer disabled initially */
  $panelizer->api_version = 1;
  $panelizer->name = 'node:pece_page:default';
  $panelizer->title = 'Default';
  $panelizer->panelizer_type = 'node';
  $panelizer->panelizer_key = 'pece_page';
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
  $display->uuid = '786493dd-4065-45d4-8313-9224db4e5f9e';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-c4d5814d-3380-4ecf-8dab-ba85dc6e8508';
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
  $pane->uuid = 'c4d5814d-3380-4ecf-8dab-ba85dc6e8508';
  $display->content['new-c4d5814d-3380-4ecf-8dab-ba85dc6e8508'] = $pane;
  $display->panels['center'][0] = 'new-c4d5814d-3380-4ecf-8dab-ba85dc6e8508';
  $pane = new stdClass();
  $pane->pid = 'new-80a25787-32bc-4a5f-ad84-e3cabaa35371';
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
  $pane->uuid = '80a25787-32bc-4a5f-ad84-e3cabaa35371';
  $display->content['new-80a25787-32bc-4a5f-ad84-e3cabaa35371'] = $pane;
  $display->panels['center'][1] = 'new-80a25787-32bc-4a5f-ad84-e3cabaa35371';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-80a25787-32bc-4a5f-ad84-e3cabaa35371';
  $panelizer->display = $display;
  $export['node:pece_page:default'] = $panelizer;

  return $export;
}
