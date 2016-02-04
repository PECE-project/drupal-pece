<?php
/**
 * @file
 * pece_substantive_logic.panelizer.inc
 */

/**
 * Implements hook_panelizer_defaults().
 */
function pece_substantive_logic_panelizer_defaults() {
  $export = array();

  $panelizer = new stdClass();
  $panelizer->disabled = FALSE; /* Edit this to true to make a default panelizer disabled initially */
  $panelizer->api_version = 1;
  $panelizer->name = 'node:pece_sub_logic:default';
  $panelizer->title = 'Default';
  $panelizer->panelizer_type = 'node';
  $panelizer->panelizer_key = 'pece_sub_logic';
  $panelizer->no_blocks = FALSE;
  $panelizer->css_id = '';
  $panelizer->css = '';
  $panelizer->pipeline = 'ipe';
  $panelizer->contexts = array();
  $panelizer->relationships = array();
  $panelizer->access = array();
  $panelizer->view_mode = 'page_manager';
  $panelizer->css_class = '';
  $panelizer->title_element = 'H2';
  $panelizer->link_to_entity = TRUE;
  $panelizer->extra = array();
  $display = new panels_display();
  $display->layout = 'pece_sidebar_right';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'content' => NULL,
      'sidebar' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '%node:title';
  $display->uuid = '8b541f82-dae9-4ee3-9ce4-9fa3b2e1b7d7';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-f28266f3-a92d-4efe-b331-bb8b162a6233';
  $pane->panel = 'content';
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
  $pane->uuid = 'f28266f3-a92d-4efe-b331-bb8b162a6233';
  $display->content['new-f28266f3-a92d-4efe-b331-bb8b162a6233'] = $pane;
  $display->panels['content'][0] = 'new-f28266f3-a92d-4efe-b331-bb8b162a6233';
  $pane = new stdClass();
  $pane->pid = 'new-9d8ab1d1-5b78-4921-90d5-28a48ebe9bd1';
  $pane->panel = 'sidebar';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_basic_image_image';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'hidden',
    'formatter' => 'file_rendered',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(
      'file_view_mode' => 'default',
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
  $pane->uuid = '9d8ab1d1-5b78-4921-90d5-28a48ebe9bd1';
  $display->content['new-9d8ab1d1-5b78-4921-90d5-28a48ebe9bd1'] = $pane;
  $display->panels['sidebar'][0] = 'new-9d8ab1d1-5b78-4921-90d5-28a48ebe9bd1';
  $pane = new stdClass();
  $pane->pid = 'new-43eafd6e-9355-4822-a1c3-79b1c6ea165a';
  $pane->panel = 'sidebar';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_sub_logic_cit_link';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
    'formatter' => 'link_default',
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
  $pane->uuid = '43eafd6e-9355-4822-a1c3-79b1c6ea165a';
  $display->content['new-43eafd6e-9355-4822-a1c3-79b1c6ea165a'] = $pane;
  $display->panels['sidebar'][1] = 'new-43eafd6e-9355-4822-a1c3-79b1c6ea165a';
  $pane = new stdClass();
  $pane->pid = 'new-5c8af8f8-5697-471b-9b4e-7eacdc83e017';
  $pane->panel = 'sidebar';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_tags';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
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
  $pane->position = 2;
  $pane->locks = array();
  $pane->uuid = '5c8af8f8-5697-471b-9b4e-7eacdc83e017';
  $display->content['new-5c8af8f8-5697-471b-9b4e-7eacdc83e017'] = $pane;
  $display->panels['sidebar'][2] = 'new-5c8af8f8-5697-471b-9b4e-7eacdc83e017';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $panelizer->display = $display;
  $export['node:pece_sub_logic:default'] = $panelizer;

  return $export;
}
