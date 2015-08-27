<?php
/**
 * @file
 * pece_artifacts_fieldnote.panelizer.inc
 */

/**
 * Implements hook_panelizer_defaults().
 */
function pece_artifacts_fieldnote_panelizer_defaults() {
  $export = array();

  $panelizer = new stdClass();
  $panelizer->disabled = FALSE; /* Edit this to true to make a default panelizer disabled initially */
  $panelizer->api_version = 1;
  $panelizer->name = 'node:pece_artifact_fieldnote:default';
  $panelizer->title = 'Default';
  $panelizer->panelizer_type = 'node';
  $panelizer->panelizer_key = 'pece_artifact_fieldnote';
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
  $display->uuid = 'd2e24553-8dde-4d0c-9873-80ead5e416af';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-3d9bbc86-d0fa-4357-9f66-5168769b91f6';
  $pane->panel = 'column1';
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
  $pane->uuid = '3d9bbc86-d0fa-4357-9f66-5168769b91f6';
  $display->content['new-3d9bbc86-d0fa-4357-9f66-5168769b91f6'] = $pane;
  $display->panels['column1'][0] = 'new-3d9bbc86-d0fa-4357-9f66-5168769b91f6';
  $pane = new stdClass();
  $pane->pid = 'new-f23f8aec-8ae7-4285-beae-33409172d76f';
  $pane->panel = 'column1';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_license';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
    'formatter' => 'creative_commons_small_image',
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
  $pane->uuid = 'f23f8aec-8ae7-4285-beae-33409172d76f';
  $display->content['new-f23f8aec-8ae7-4285-beae-33409172d76f'] = $pane;
  $display->panels['column1'][1] = 'new-f23f8aec-8ae7-4285-beae-33409172d76f';
  $pane = new stdClass();
  $pane->pid = 'new-b3cb149c-978a-49f8-8ff2-2ce1d50cbf4f';
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
  $pane->uuid = 'b3cb149c-978a-49f8-8ff2-2ce1d50cbf4f';
  $display->content['new-b3cb149c-978a-49f8-8ff2-2ce1d50cbf4f'] = $pane;
  $display->panels['column1'][2] = 'new-b3cb149c-978a-49f8-8ff2-2ce1d50cbf4f';
  $pane = new stdClass();
  $pane->pid = 'new-9e52c08b-9c89-4f49-af6c-0dc1c9be9740';
  $pane->panel = 'column2';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_authors';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'above',
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
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '9e52c08b-9c89-4f49-af6c-0dc1c9be9740';
  $display->content['new-9e52c08b-9c89-4f49-af6c-0dc1c9be9740'] = $pane;
  $display->panels['column2'][0] = 'new-9e52c08b-9c89-4f49-af6c-0dc1c9be9740';
  $pane = new stdClass();
  $pane->pid = 'new-5a2792fa-97b6-4a64-9079-0d493708217f';
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
      'view_mode' => 'full',
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
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = '5a2792fa-97b6-4a64-9079-0d493708217f';
  $display->content['new-5a2792fa-97b6-4a64-9079-0d493708217f'] = $pane;
  $display->panels['column2'][1] = 'new-5a2792fa-97b6-4a64-9079-0d493708217f';
  $pane = new stdClass();
  $pane->pid = 'new-6249e480-1503-46fd-972c-d2bf5c76027e';
  $pane->panel = 'column2';
  $pane->type = 'node_created';
  $pane->subtype = 'node_created';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'format' => 'panopoly_day',
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
  $pane->uuid = '6249e480-1503-46fd-972c-d2bf5c76027e';
  $display->content['new-6249e480-1503-46fd-972c-d2bf5c76027e'] = $pane;
  $display->panels['column2'][2] = 'new-6249e480-1503-46fd-972c-d2bf5c76027e';
  $pane = new stdClass();
  $pane->pid = 'new-3929e3bf-1991-4a17-abbd-aa153c4c001a';
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
      'view_mode' => 'default',
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
  $pane->position = 3;
  $pane->locks = array();
  $pane->uuid = '3929e3bf-1991-4a17-abbd-aa153c4c001a';
  $display->content['new-3929e3bf-1991-4a17-abbd-aa153c4c001a'] = $pane;
  $display->panels['column2'][3] = 'new-3929e3bf-1991-4a17-abbd-aa153c4c001a';
  $pane = new stdClass();
  $pane->pid = 'new-df31586e-929a-4f08-aa5d-255e729fd1d2';
  $pane->panel = 'column2';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:og_group_ref';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'above',
    'formatter' => 'entityreference_entity_view',
    'delta_limit' => '0',
    'delta_offset' => '0',
    'delta_reversed' => 0,
    'formatter_settings' => array(
      'view_mode' => 'default',
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
  $pane->uuid = 'df31586e-929a-4f08-aa5d-255e729fd1d2';
  $display->content['new-df31586e-929a-4f08-aa5d-255e729fd1d2'] = $pane;
  $display->panels['column2'][4] = 'new-df31586e-929a-4f08-aa5d-255e729fd1d2';
  $pane = new stdClass();
  $pane->pid = 'new-5b5b273c-1d84-4442-b40d-ef6a29a81c97';
  $pane->panel = 'column2';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_tags';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'above',
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
  $pane->position = 5;
  $pane->locks = array();
  $pane->uuid = '5b5b273c-1d84-4442-b40d-ef6a29a81c97';
  $display->content['new-5b5b273c-1d84-4442-b40d-ef6a29a81c97'] = $pane;
  $display->panels['column2'][5] = 'new-5b5b273c-1d84-4442-b40d-ef6a29a81c97';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-b3cb149c-978a-49f8-8ff2-2ce1d50cbf4f';
  $panelizer->display = $display;
  $export['node:pece_artifact_fieldnote:default'] = $panelizer;

  return $export;
}
