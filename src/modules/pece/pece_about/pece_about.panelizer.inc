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
  $panelizer->name = 'node:pece_about_page:default';
  $panelizer->title = 'Default';
  $panelizer->panelizer_type = 'node';
  $panelizer->panelizer_key = 'pece_about_page';
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
  $display->panel_settings = array(
    'style_settings' => array(
      'center' => NULL,
      'default' => NULL,
    ),
    'center' => array(
      'style' => 'tabs',
    ),
  );
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
    'override_title' => 1,
    'override_title_text' => 'About',
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
  $pane->uuid = 'c4d5814d-3380-4ecf-8dab-ba85dc6e8508';
  $display->content['new-c4d5814d-3380-4ecf-8dab-ba85dc6e8508'] = $pane;
  $display->panels['center'][0] = 'new-c4d5814d-3380-4ecf-8dab-ba85dc6e8508';
  $pane = new stdClass();
  $pane->pid = 'new-29e60bf9-293c-4b61-9044-39bda5713315';
  $pane->panel = 'center';
  $pane->type = 'views_panes';
  $pane->subtype = 'pece_projects-panel_pane_1';
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
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = '29e60bf9-293c-4b61-9044-39bda5713315';
  $display->content['new-29e60bf9-293c-4b61-9044-39bda5713315'] = $pane;
  $display->panels['center'][1] = 'new-29e60bf9-293c-4b61-9044-39bda5713315';
  $pane = new stdClass();
  $pane->pid = 'new-ec93cab7-50dc-4a12-b657-d656cbaa33f8';
  $pane->panel = 'center';
  $pane->type = 'views_panes';
  $pane->subtype = 'pece_users-all_users';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'view_settings' => 'fields',
    'header_type' => 'titles',
    'view_mode' => 'full',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 2;
  $pane->locks = array();
  $pane->uuid = 'ec93cab7-50dc-4a12-b657-d656cbaa33f8';
  $display->content['new-ec93cab7-50dc-4a12-b657-d656cbaa33f8'] = $pane;
  $display->panels['center'][2] = 'new-ec93cab7-50dc-4a12-b657-d656cbaa33f8';
  $pane = new stdClass();
  $pane->pid = 'new-2ff1e7a4-22c4-4857-b200-04eaa413fb24';
  $pane->panel = 'center';
  $pane->type = 'views_panes';
  $pane->subtype = 'pece_substantive_logic-panel_pane_1';
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
  $pane->position = 3;
  $pane->locks = array();
  $pane->uuid = '2ff1e7a4-22c4-4857-b200-04eaa413fb24';
  $display->content['new-2ff1e7a4-22c4-4857-b200-04eaa413fb24'] = $pane;
  $display->panels['center'][3] = 'new-2ff1e7a4-22c4-4857-b200-04eaa413fb24';
  $pane = new stdClass();
  $pane->pid = 'new-40eb639e-d834-48ee-be0d-a1035b4f1031';
  $pane->panel = 'center';
  $pane->type = 'views_panes';
  $pane->subtype = 'pece_design_logic-panel_pane_1';
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
  $pane->uuid = '40eb639e-d834-48ee-be0d-a1035b4f1031';
  $display->content['new-40eb639e-d834-48ee-be0d-a1035b4f1031'] = $pane;
  $display->panels['center'][4] = 'new-40eb639e-d834-48ee-be0d-a1035b4f1031';
  $pane = new stdClass();
  $pane->pid = 'new-03f81496-52f8-4d9c-842f-e17a5c8045ad';
  $pane->panel = 'center';
  $pane->type = 'block';
  $pane->subtype = 'pece_about-about_pece';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
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
  $pane->uuid = '03f81496-52f8-4d9c-842f-e17a5c8045ad';
  $display->content['new-03f81496-52f8-4d9c-842f-e17a5c8045ad'] = $pane;
  $display->panels['center'][5] = 'new-03f81496-52f8-4d9c-842f-e17a5c8045ad';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $panelizer->display = $display;
  $export['node:pece_about_page:default'] = $panelizer;

  return $export;
}
