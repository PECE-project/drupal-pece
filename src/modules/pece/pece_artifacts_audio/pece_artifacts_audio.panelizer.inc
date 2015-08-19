<?php
/**
 * @file
 * pece_artifacts_audio.panelizer.inc
 */

/**
 * Implements hook_panelizer_defaults().
 */
function pece_artifacts_audio_panelizer_defaults() {
  $export = array();

  $panelizer = new stdClass();
  $panelizer->disabled = FALSE; /* Edit this to true to make a default panelizer disabled initially */
  $panelizer->api_version = 1;
  $panelizer->name = 'node:pece_artifact_audio:default';
  $panelizer->title = 'Default';
  $panelizer->panelizer_type = 'node';
  $panelizer->panelizer_key = 'pece_artifact_audio';
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
  $display->uuid = '841250bf-f505-4eeb-9ee2-17a979f74169';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-de356e48-1de5-4977-8fb1-60d5aff5826d';
  $pane->panel = 'column1';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_media_audio';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'above',
    'formatter' => 'file_default',
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
  $pane->uuid = 'de356e48-1de5-4977-8fb1-60d5aff5826d';
  $display->content['new-de356e48-1de5-4977-8fb1-60d5aff5826d'] = $pane;
  $display->panels['column1'][0] = 'new-de356e48-1de5-4977-8fb1-60d5aff5826d';
  $pane = new stdClass();
  $pane->pid = 'new-65dcfe30-f78e-409d-b1e2-d20d3f5e6c0e';
  $pane->panel = 'column1';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_file_format';
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
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = '65dcfe30-f78e-409d-b1e2-d20d3f5e6c0e';
  $display->content['new-65dcfe30-f78e-409d-b1e2-d20d3f5e6c0e'] = $pane;
  $display->panels['column1'][1] = 'new-65dcfe30-f78e-409d-b1e2-d20d3f5e6c0e';
  $pane = new stdClass();
  $pane->pid = 'new-f94c9d24-f084-4a5c-bf49-c8431e8bd228';
  $pane->panel = 'column1';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_media_duration';
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
  $pane->position = 2;
  $pane->locks = array();
  $pane->uuid = 'f94c9d24-f084-4a5c-bf49-c8431e8bd228';
  $display->content['new-f94c9d24-f084-4a5c-bf49-c8431e8bd228'] = $pane;
  $display->panels['column1'][2] = 'new-f94c9d24-f084-4a5c-bf49-c8431e8bd228';
  $pane = new stdClass();
  $pane->pid = 'new-c95df1ec-ab36-4166-8df2-093919075841';
  $pane->panel = 'column1';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_license';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'above',
    'formatter' => 'creative_commons_small_image',
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
  $pane->position = 3;
  $pane->locks = array();
  $pane->uuid = 'c95df1ec-ab36-4166-8df2-093919075841';
  $display->content['new-c95df1ec-ab36-4166-8df2-093919075841'] = $pane;
  $display->panels['column1'][3] = 'new-c95df1ec-ab36-4166-8df2-093919075841';
  $pane = new stdClass();
  $pane->pid = 'new-7f2e508b-27da-4739-8660-27a3a68616d8';
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
  $pane->position = 4;
  $pane->locks = array();
  $pane->uuid = '7f2e508b-27da-4739-8660-27a3a68616d8';
  $display->content['new-7f2e508b-27da-4739-8660-27a3a68616d8'] = $pane;
  $display->panels['column1'][4] = 'new-7f2e508b-27da-4739-8660-27a3a68616d8';
  $pane = new stdClass();
  $pane->pid = 'new-b9f5451d-261b-4d80-af97-d7c28723b9ec';
  $pane->panel = 'column2';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_authors';
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
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = 'b9f5451d-261b-4d80-af97-d7c28723b9ec';
  $display->content['new-b9f5451d-261b-4d80-af97-d7c28723b9ec'] = $pane;
  $display->panels['column2'][0] = 'new-b9f5451d-261b-4d80-af97-d7c28723b9ec';
  $pane = new stdClass();
  $pane->pid = 'new-644245a4-f2ab-4ddc-aa8c-2c3a56148dfa';
  $pane->panel = 'column2';
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
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = '644245a4-f2ab-4ddc-aa8c-2c3a56148dfa';
  $display->content['new-644245a4-f2ab-4ddc-aa8c-2c3a56148dfa'] = $pane;
  $display->panels['column2'][1] = 'new-644245a4-f2ab-4ddc-aa8c-2c3a56148dfa';
  $pane = new stdClass();
  $pane->pid = 'new-d9ace7e7-8692-42f0-b3fd-fa6dfbbdf1ac';
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
  $pane->uuid = 'd9ace7e7-8692-42f0-b3fd-fa6dfbbdf1ac';
  $display->content['new-d9ace7e7-8692-42f0-b3fd-fa6dfbbdf1ac'] = $pane;
  $display->panels['column2'][2] = 'new-d9ace7e7-8692-42f0-b3fd-fa6dfbbdf1ac';
  $pane = new stdClass();
  $pane->pid = 'new-c7b234e7-9d4d-4f22-a94a-14ad46182050';
  $pane->panel = 'column2';
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
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 3;
  $pane->locks = array();
  $pane->uuid = 'c7b234e7-9d4d-4f22-a94a-14ad46182050';
  $display->content['new-c7b234e7-9d4d-4f22-a94a-14ad46182050'] = $pane;
  $display->panels['column2'][3] = 'new-c7b234e7-9d4d-4f22-a94a-14ad46182050';
  $pane = new stdClass();
  $pane->pid = 'new-d7808060-7af0-448f-ac3a-ea2578df7130';
  $pane->panel = 'column2';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_crit_commentary';
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
  $pane->position = 4;
  $pane->locks = array();
  $pane->uuid = 'd7808060-7af0-448f-ac3a-ea2578df7130';
  $display->content['new-d7808060-7af0-448f-ac3a-ea2578df7130'] = $pane;
  $display->panels['column2'][4] = 'new-d7808060-7af0-448f-ac3a-ea2578df7130';
  $pane = new stdClass();
  $pane->pid = 'new-83e90775-d800-4b69-b9a6-26a58bd90538';
  $pane->panel = 'column2';
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
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 5;
  $pane->locks = array();
  $pane->uuid = '83e90775-d800-4b69-b9a6-26a58bd90538';
  $display->content['new-83e90775-d800-4b69-b9a6-26a58bd90538'] = $pane;
  $display->panels['column2'][5] = 'new-83e90775-d800-4b69-b9a6-26a58bd90538';
  $pane = new stdClass();
  $pane->pid = 'new-6baf265d-6729-410a-b9b6-b6c996190fac';
  $pane->panel = 'column2';
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
  $pane->position = 6;
  $pane->locks = array();
  $pane->uuid = '6baf265d-6729-410a-b9b6-b6c996190fac';
  $display->content['new-6baf265d-6729-410a-b9b6-b6c996190fac'] = $pane;
  $display->panels['column2'][6] = 'new-6baf265d-6729-410a-b9b6-b6c996190fac';
  $pane = new stdClass();
  $pane->pid = 'new-8c00c587-26fa-4b5a-aade-f640e42cdcec';
  $pane->panel = 'column2';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_location';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'above',
    'formatter' => 'location_default',
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
  $pane->position = 7;
  $pane->locks = array();
  $pane->uuid = '8c00c587-26fa-4b5a-aade-f640e42cdcec';
  $display->content['new-8c00c587-26fa-4b5a-aade-f640e42cdcec'] = $pane;
  $display->panels['column2'][7] = 'new-8c00c587-26fa-4b5a-aade-f640e42cdcec';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-7f2e508b-27da-4739-8660-27a3a68616d8';
  $panelizer->display = $display;
  $export['node:pece_artifact_audio:default'] = $panelizer;

  return $export;
}
