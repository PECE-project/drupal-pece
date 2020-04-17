<?php

/**
 * @file
 * pece_core.panelizer.inc
 */

/**
 * Implements hook_panelizer_defaults().
 */
function pece_core_panelizer_defaults() {
  $export = array();

  $panelizer = new stdClass();
  $panelizer->disabled = FALSE; /* Edit this to true to make a default panelizer disabled initially */
  $panelizer->api_version = 1;
  $panelizer->title = 'Default';
  $panelizer->panelizer_type = 'node';
  $panelizer->panelizer_key = 'pece_fieldsite';
  $panelizer->access = array();
  $panelizer->view_mode = 'page_manager';
  $panelizer->name = 'node:pece_fieldsite:default';
  $panelizer->css_id = '';
  $panelizer->css_class = '';
  $panelizer->css = '';
  $panelizer->no_blocks = FALSE;
  $panelizer->title_element = 'H2';
  $panelizer->link_to_entity = TRUE;
  $panelizer->extra = array();
  $panelizer->pipeline = 'standard';
  $panelizer->contexts = array();
  $panelizer->relationships = array();
  $display = new panels_display();
  $display->layout = 'flexible';
  $display->layout_settings = array();
  $display->panel_settings = array();
  $display->cache = array();
  $display->title = '%node:title';
  $display->uuid = 'f068b991-8a3b-40e9-97ba-0ee7623443cc';
  $display->storage_type = 'panelizer_default';
  $display->storage_id = 'node:pece_fieldsite:default';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-fb37583b-4f46-46bc-b223-be8829e77e89';
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
  $pane->uuid = 'fb37583b-4f46-46bc-b223-be8829e77e89';
  $display->content['new-fb37583b-4f46-46bc-b223-be8829e77e89'] = $pane;
  $display->panels['center'][0] = 'new-fb37583b-4f46-46bc-b223-be8829e77e89';
  $pane = new stdClass();
  $pane->pid = 'new-4722dc84-de3a-4d56-a225-3442460dcb8d';
  $pane->panel = 'center';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_researchers';
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
  $pane->uuid = '4722dc84-de3a-4d56-a225-3442460dcb8d';
  $display->content['new-4722dc84-de3a-4d56-a225-3442460dcb8d'] = $pane;
  $display->panels['center'][1] = 'new-4722dc84-de3a-4d56-a225-3442460dcb8d';
  $pane = new stdClass();
  $pane->pid = 'new-b0814a36-434f-4555-91ef-1a2b1ec9da6c';
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
  $pane->uuid = 'b0814a36-434f-4555-91ef-1a2b1ec9da6c';
  $display->content['new-b0814a36-434f-4555-91ef-1a2b1ec9da6c'] = $pane;
  $display->panels['center'][2] = 'new-b0814a36-434f-4555-91ef-1a2b1ec9da6c';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-b0814a36-434f-4555-91ef-1a2b1ec9da6c';
  $panelizer->display = $display;
  $export['node:pece_fieldsite:default'] = $panelizer;

  return $export;
}
