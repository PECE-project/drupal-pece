<?php
/**
 * @file
 * pece_memo.panelizer.inc
 */

/**
 * Implements hook_panelizer_defaults().
 */
function pece_memo_panelizer_defaults() {
  $export = array();

  $panelizer = new stdClass();
  $panelizer->disabled = FALSE; /* Edit this to true to make a default panelizer disabled initially */
  $panelizer->api_version = 1;
  $panelizer->name = 'node:pece_memo:default';
  $panelizer->title = 'Default';
  $panelizer->panelizer_type = 'node';
  $panelizer->panelizer_key = 'pece_memo';
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
  $display->layout = 'radix_sutro';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'center' => NULL,
      'left' => NULL,
      'right' => NULL,
      'header' => NULL,
      'column1' => NULL,
      'column2' => NULL,
      'footer' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '%node:title';
  $display->uuid = 'a1c90f19-4908-4a48-a0a3-8513676046ce';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-4e462123-c132-40bb-b135-2c4f7419fdad';
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
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '4e462123-c132-40bb-b135-2c4f7419fdad';
  $display->content['new-4e462123-c132-40bb-b135-2c4f7419fdad'] = $pane;
  $display->panels['column1'][0] = 'new-4e462123-c132-40bb-b135-2c4f7419fdad';
  $pane = new stdClass();
  $pane->pid = 'new-df63ce61-a32a-4352-9a3f-4f987969a903';
  $pane->panel = 'column1';
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
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = 'df63ce61-a32a-4352-9a3f-4f987969a903';
  $display->content['new-df63ce61-a32a-4352-9a3f-4f987969a903'] = $pane;
  $display->panels['column1'][1] = 'new-df63ce61-a32a-4352-9a3f-4f987969a903';
  $pane = new stdClass();
  $pane->pid = 'new-921aab6a-9aa5-4d92-b1fd-4449c91d2404';
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
  $pane->position = 2;
  $pane->locks = array();
  $pane->uuid = '921aab6a-9aa5-4d92-b1fd-4449c91d2404';
  $display->content['new-921aab6a-9aa5-4d92-b1fd-4449c91d2404'] = $pane;
  $display->panels['column1'][2] = 'new-921aab6a-9aa5-4d92-b1fd-4449c91d2404';
  $pane = new stdClass();
  $pane->pid = 'new-19561de0-3867-47b2-9e78-c71b55b64bbc';
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
  $pane->position = 3;
  $pane->locks = array();
  $pane->uuid = '19561de0-3867-47b2-9e78-c71b55b64bbc';
  $display->content['new-19561de0-3867-47b2-9e78-c71b55b64bbc'] = $pane;
  $display->panels['column1'][3] = 'new-19561de0-3867-47b2-9e78-c71b55b64bbc';
  $pane = new stdClass();
  $pane->pid = 'new-4499b7a5-dbed-488e-bd0e-fb39a00004f2';
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
  $pane->uuid = '4499b7a5-dbed-488e-bd0e-fb39a00004f2';
  $display->content['new-4499b7a5-dbed-488e-bd0e-fb39a00004f2'] = $pane;
  $display->panels['column2'][0] = 'new-4499b7a5-dbed-488e-bd0e-fb39a00004f2';
  $pane = new stdClass();
  $pane->pid = 'new-d371f78e-acc4-4b09-8808-2601c06e774f';
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
  $pane->uuid = 'd371f78e-acc4-4b09-8808-2601c06e774f';
  $display->content['new-d371f78e-acc4-4b09-8808-2601c06e774f'] = $pane;
  $display->panels['column2'][1] = 'new-d371f78e-acc4-4b09-8808-2601c06e774f';
  $pane = new stdClass();
  $pane->pid = 'new-38da2f73-c5aa-4edc-916a-04744472fb60';
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
  $pane->uuid = '38da2f73-c5aa-4edc-916a-04744472fb60';
  $display->content['new-38da2f73-c5aa-4edc-916a-04744472fb60'] = $pane;
  $display->panels['column2'][2] = 'new-38da2f73-c5aa-4edc-916a-04744472fb60';
  $pane = new stdClass();
  $pane->pid = 'new-f50053eb-5c59-46d8-9281-a53343f023be';
  $pane->panel = 'column2';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:og_group_ref';
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
    'override_title_text' => 'Groups audience',
    'override_title_heading' => 'h3',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 3;
  $pane->locks = array();
  $pane->uuid = 'f50053eb-5c59-46d8-9281-a53343f023be';
  $display->content['new-f50053eb-5c59-46d8-9281-a53343f023be'] = $pane;
  $display->panels['column2'][3] = 'new-f50053eb-5c59-46d8-9281-a53343f023be';
  $pane = new stdClass();
  $pane->pid = 'new-859a8aa5-18e2-45b8-80a4-98fab270a108';
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
  $pane->position = 4;
  $pane->locks = array();
  $pane->uuid = '859a8aa5-18e2-45b8-80a4-98fab270a108';
  $display->content['new-859a8aa5-18e2-45b8-80a4-98fab270a108'] = $pane;
  $display->panels['column2'][4] = 'new-859a8aa5-18e2-45b8-80a4-98fab270a108';
  $pane = new stdClass();
  $pane->pid = 'new-e5ca1b4e-b0c0-49f0-8271-56350342f6d3';
  $pane->panel = 'footer';
  $pane->type = 'node_comment_wrapper';
  $pane->subtype = 'node_comment_wrapper';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'mode' => '1',
    'comments_per_page' => '50',
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
  $pane->uuid = 'e5ca1b4e-b0c0-49f0-8271-56350342f6d3';
  $display->content['new-e5ca1b4e-b0c0-49f0-8271-56350342f6d3'] = $pane;
  $display->panels['footer'][0] = 'new-e5ca1b4e-b0c0-49f0-8271-56350342f6d3';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $panelizer->display = $display;
  $export['node:pece_memo:default'] = $panelizer;

  return $export;
}
