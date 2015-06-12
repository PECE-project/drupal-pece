<?php
/**
 * @file
 * pece_projects.panelizer.inc
 */

/**
 * Implements hook_panelizer_defaults().
 */
function pece_projects_panelizer_defaults() {
  $export = array();

  $panelizer = new stdClass();
  $panelizer->disabled = FALSE; /* Edit this to true to make a default panelizer disabled initially */
  $panelizer->api_version = 1;
  $panelizer->name = 'node:pece_project:default';
  $panelizer->title = 'Default';
  $panelizer->panelizer_type = 'node';
  $panelizer->panelizer_key = 'pece_project';
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
  $display->uuid = '8b541f82-dae9-4ee3-9ce4-9fa3b2e1b7d7';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-a77825f5-1453-4982-85f0-836b51a319d6';
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
  $pane->uuid = 'a77825f5-1453-4982-85f0-836b51a319d6';
  $display->content['new-a77825f5-1453-4982-85f0-836b51a319d6'] = $pane;
  $display->panels['center'][0] = 'new-a77825f5-1453-4982-85f0-836b51a319d6';
  $pane = new stdClass();
  $pane->pid = 'new-5a86dd1e-8739-4c0e-b829-d4cc96f09f44';
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
  $pane->uuid = '5a86dd1e-8739-4c0e-b829-d4cc96f09f44';
  $display->content['new-5a86dd1e-8739-4c0e-b829-d4cc96f09f44'] = $pane;
  $display->panels['center'][1] = 'new-5a86dd1e-8739-4c0e-b829-d4cc96f09f44';
  $pane = new stdClass();
  $pane->pid = 'new-cc466668-d474-4110-8277-ed131c7cf71f';
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
  $pane->uuid = 'cc466668-d474-4110-8277-ed131c7cf71f';
  $display->content['new-cc466668-d474-4110-8277-ed131c7cf71f'] = $pane;
  $display->panels['center'][2] = 'new-cc466668-d474-4110-8277-ed131c7cf71f';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-cc466668-d474-4110-8277-ed131c7cf71f';
  $panelizer->display = $display;
  $export['node:pece_project:default'] = $panelizer;

  return $export;
}
