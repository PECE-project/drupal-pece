<?php
/**
 * @file
 * pece_annotations.panelizer.inc
 */

/**
 * Implements hook_panelizer_defaults().
 */
function pece_annotations_panelizer_defaults() {
  $export = array();

  $panelizer = new stdClass();
  $panelizer->disabled = FALSE; /* Edit this to true to make a default panelizer disabled initially */
  $panelizer->api_version = 1;
  $panelizer->title = 'Default';
  $panelizer->panelizer_type = 'node';
  $panelizer->panelizer_key = 'pece_analytic';
  $panelizer->access = array();
  $panelizer->view_mode = 'page_manager';
  $panelizer->name = 'node:pece_analytic:default';
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
  $display->layout = 'flexible';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'center' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '%node:title';
  $display->uuid = '0a934801-c6b7-4a6c-8234-e885bbfdcc10';
  $display->storage_type = 'panelizer_default';
  $display->storage_id = 'node:pece_analytic:default';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-d861abaa-a14d-48f1-8c82-ba800ef81ec8';
  $pane->panel = 'center';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_uri';
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
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = 'd861abaa-a14d-48f1-8c82-ba800ef81ec8';
  $display->content['new-d861abaa-a14d-48f1-8c82-ba800ef81ec8'] = $pane;
  $display->panels['center'][0] = 'new-d861abaa-a14d-48f1-8c82-ba800ef81ec8';
  $pane = new stdClass();
  $pane->pid = 'new-a976a601-cf42-496f-a6d2-09dbc2487946';
  $pane->panel = 'center';
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
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = 'a976a601-cf42-496f-a6d2-09dbc2487946';
  $display->content['new-a976a601-cf42-496f-a6d2-09dbc2487946'] = $pane;
  $display->panels['center'][1] = 'new-a976a601-cf42-496f-a6d2-09dbc2487946';
  $pane = new stdClass();
  $pane->pid = 'new-e83cc559-2080-4c1b-bd67-2d3e78a04add';
  $pane->panel = 'center';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_struct_analytics';
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
    'context' => 'panelizer',
    'override_title' => 1,
    'override_title_text' => 'Structured Analytic',
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
  $pane->uuid = 'e83cc559-2080-4c1b-bd67-2d3e78a04add';
  $display->content['new-e83cc559-2080-4c1b-bd67-2d3e78a04add'] = $pane;
  $display->panels['center'][2] = 'new-e83cc559-2080-4c1b-bd67-2d3e78a04add';
  $pane = new stdClass();
  $pane->pid = 'new-d6ccd130-c8e4-4165-9351-2aab864798df';
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
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array(
    'css_class' => 'link-wrapper',
  );
  $pane->extras = array();
  $pane->position = 3;
  $pane->locks = array();
  $pane->uuid = 'd6ccd130-c8e4-4165-9351-2aab864798df';
  $display->content['new-d6ccd130-c8e4-4165-9351-2aab864798df'] = $pane;
  $display->panels['center'][3] = 'new-d6ccd130-c8e4-4165-9351-2aab864798df';
  $pane = new stdClass();
  $pane->pid = 'new-73a6eab8-a57f-43fa-80cb-1b7c510e2069';
  $pane->panel = 'center';
  $pane->type = 'views_panes';
  $pane->subtype = 'pece_annotations-pece_question_annotations';
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
  $pane->uuid = '73a6eab8-a57f-43fa-80cb-1b7c510e2069';
  $display->content['new-73a6eab8-a57f-43fa-80cb-1b7c510e2069'] = $pane;
  $display->panels['center'][4] = 'new-73a6eab8-a57f-43fa-80cb-1b7c510e2069';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $panelizer->display = $display;
  $export['node:pece_analytic:default'] = $panelizer;

  return $export;
}
