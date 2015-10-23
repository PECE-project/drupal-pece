<?php
/**
 * @file
 * pece_groups.panelizer.inc
 */

/**
 * Implements hook_panelizer_defaults().
 */
function pece_groups_panelizer_defaults() {
  $export = array();

  $panelizer = new stdClass();
  $panelizer->disabled = FALSE; /* Edit this to true to make a default panelizer disabled initially */
  $panelizer->api_version = 1;
  $panelizer->name = 'node:pece_group:default';
  $panelizer->title = 'Default';
  $panelizer->panelizer_type = 'node';
  $panelizer->panelizer_key = 'pece_group';
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
  $display->layout = 'radix_selby_flipped';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'sidebar' => NULL,
      'contentheader' => NULL,
      'contentcolumn1' => NULL,
      'contentcolumn2' => NULL,
      'contentfooter' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '%node:title';
  $display->uuid = 'b4c3d33e-c154-4059-952c-205805c5bd26';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-147bf60e-4dea-4d25-b657-e75f17702188';
  $pane->panel = 'contentheader';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:group_email';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'inline',
    'formatter' => 'group_email',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(),
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
  $pane->uuid = '147bf60e-4dea-4d25-b657-e75f17702188';
  $display->content['new-147bf60e-4dea-4d25-b657-e75f17702188'] = $pane;
  $display->panels['contentheader'][0] = 'new-147bf60e-4dea-4d25-b657-e75f17702188';
  $pane = new stdClass();
  $pane->pid = 'new-da3a554d-9286-4257-87ee-60945f7205a6';
  $pane->panel = 'contentheader';
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
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = 'da3a554d-9286-4257-87ee-60945f7205a6';
  $display->content['new-da3a554d-9286-4257-87ee-60945f7205a6'] = $pane;
  $display->panels['contentheader'][1] = 'new-da3a554d-9286-4257-87ee-60945f7205a6';
  $pane = new stdClass();
  $pane->pid = 'new-cd10a770-62ad-42d7-a128-12872c386dda';
  $pane->panel = 'sidebar';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:group_group';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'hidden',
    'formatter' => 'og_group_subscribe',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(
      'field_name' => 'og_user_node',
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
  $pane->uuid = 'cd10a770-62ad-42d7-a128-12872c386dda';
  $display->content['new-cd10a770-62ad-42d7-a128-12872c386dda'] = $pane;
  $display->panels['sidebar'][0] = 'new-cd10a770-62ad-42d7-a128-12872c386dda';
  $pane = new stdClass();
  $pane->pid = 'new-36b646b6-7ed2-477d-9aac-94cefa8a7ae5';
  $pane->panel = 'sidebar';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_media_image';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'hidden',
    'formatter' => 'image',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(
      'image_link' => '',
      'image_style' => '',
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
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = '36b646b6-7ed2-477d-9aac-94cefa8a7ae5';
  $display->content['new-36b646b6-7ed2-477d-9aac-94cefa8a7ae5'] = $pane;
  $display->panels['sidebar'][1] = 'new-36b646b6-7ed2-477d-9aac-94cefa8a7ae5';
  $pane = new stdClass();
  $pane->pid = 'new-34af642e-2d59-4854-8cb0-4097d7998ef2';
  $pane->panel = 'sidebar';
  $pane->type = 'views_panes';
  $pane->subtype = 'og_members-panel_pane_1';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'context' => array(
      0 => 'panelizer',
    ),
    'override_title' => '',
    'override_title_text' => '',
    'override_title_heading' => 'h2',
    'view_settings' => 'fields',
    'header_type' => 'none',
    'view_mode' => 'full',
    'widget_title' => 'Members',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 2;
  $pane->locks = array();
  $pane->uuid = '34af642e-2d59-4854-8cb0-4097d7998ef2';
  $display->content['new-34af642e-2d59-4854-8cb0-4097d7998ef2'] = $pane;
  $display->panels['sidebar'][2] = 'new-34af642e-2d59-4854-8cb0-4097d7998ef2';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-da3a554d-9286-4257-87ee-60945f7205a6';
  $panelizer->display = $display;
  $export['node:pece_group:default'] = $panelizer;

  return $export;
}
