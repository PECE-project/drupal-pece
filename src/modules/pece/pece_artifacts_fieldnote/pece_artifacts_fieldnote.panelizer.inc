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
  $display->uuid = 'd2e24553-8dde-4d0c-9873-80ead5e416af';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-df31586e-929a-4f08-aa5d-255e729fd1d2';
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
  $pane->uuid = 'df31586e-929a-4f08-aa5d-255e729fd1d2';
  $display->content['new-df31586e-929a-4f08-aa5d-255e729fd1d2'] = $pane;
  $display->panels['center'][0] = 'new-df31586e-929a-4f08-aa5d-255e729fd1d2';
  $pane = new stdClass();
  $pane->pid = 'new-3d9bbc86-d0fa-4357-9f66-5168769b91f6';
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
  $pane->uuid = '3d9bbc86-d0fa-4357-9f66-5168769b91f6';
  $display->content['new-3d9bbc86-d0fa-4357-9f66-5168769b91f6'] = $pane;
  $display->panels['center'][1] = 'new-3d9bbc86-d0fa-4357-9f66-5168769b91f6';
  $pane = new stdClass();
  $pane->pid = 'new-5a2792fa-97b6-4a64-9079-0d493708217f';
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
  $pane->uuid = '5a2792fa-97b6-4a64-9079-0d493708217f';
  $display->content['new-5a2792fa-97b6-4a64-9079-0d493708217f'] = $pane;
  $display->panels['center'][2] = 'new-5a2792fa-97b6-4a64-9079-0d493708217f';
  $pane = new stdClass();
  $pane->pid = 'new-1d29b762-fc3b-450c-a5d5-625c01fbcdc6';
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
  $pane->uuid = '1d29b762-fc3b-450c-a5d5-625c01fbcdc6';
  $display->content['new-1d29b762-fc3b-450c-a5d5-625c01fbcdc6'] = $pane;
  $display->panels['center'][3] = 'new-1d29b762-fc3b-450c-a5d5-625c01fbcdc6';
  $pane = new stdClass();
  $pane->pid = 'new-d2a33265-d654-4e8a-8fd0-296de5dfb225';
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
  $pane->uuid = 'd2a33265-d654-4e8a-8fd0-296de5dfb225';
  $display->content['new-d2a33265-d654-4e8a-8fd0-296de5dfb225'] = $pane;
  $display->panels['center'][4] = 'new-d2a33265-d654-4e8a-8fd0-296de5dfb225';
  $pane = new stdClass();
  $pane->pid = 'new-3929e3bf-1991-4a17-abbd-aa153c4c001a';
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
  $pane->uuid = '3929e3bf-1991-4a17-abbd-aa153c4c001a';
  $display->content['new-3929e3bf-1991-4a17-abbd-aa153c4c001a'] = $pane;
  $display->panels['center'][5] = 'new-3929e3bf-1991-4a17-abbd-aa153c4c001a';
  $pane = new stdClass();
  $pane->pid = 'new-fc90575f-19c4-4b7b-ab50-ff23226d1286';
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
  $pane->uuid = 'fc90575f-19c4-4b7b-ab50-ff23226d1286';
  $display->content['new-fc90575f-19c4-4b7b-ab50-ff23226d1286'] = $pane;
  $display->panels['center'][6] = 'new-fc90575f-19c4-4b7b-ab50-ff23226d1286';
  $pane = new stdClass();
  $pane->pid = 'new-b3cb149c-978a-49f8-8ff2-2ce1d50cbf4f';
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
  $pane->uuid = 'b3cb149c-978a-49f8-8ff2-2ce1d50cbf4f';
  $display->content['new-b3cb149c-978a-49f8-8ff2-2ce1d50cbf4f'] = $pane;
  $display->panels['center'][7] = 'new-b3cb149c-978a-49f8-8ff2-2ce1d50cbf4f';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-b3cb149c-978a-49f8-8ff2-2ce1d50cbf4f';
  $panelizer->display = $display;
  $export['node:pece_artifact_fieldnote:default'] = $panelizer;

  return $export;
}
