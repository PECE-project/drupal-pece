<?php
/**
 * @file
 * pece_artifacts_pdf.panelizer.inc
 */

/**
 * Implements hook_panelizer_defaults().
 */
function pece_artifacts_pdf_panelizer_defaults() {
  $export = array();

  $panelizer = new stdClass();
  $panelizer->disabled = FALSE; /* Edit this to true to make a default panelizer disabled initially */
  $panelizer->api_version = 1;
  $panelizer->name = 'node:pece_artifact_pdf:default';
  $panelizer->title = 'Default';
  $panelizer->panelizer_type = 'node';
  $panelizer->panelizer_key = 'pece_artifact_pdf';
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
  $display->uuid = '5ae2f024-3fb5-4bec-896a-32c3ba9cf39c';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-90e68ddc-59aa-4666-90de-47f1259a7c16';
  $pane->panel = 'column1';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_media_pdf';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'above',
    'formatter' => 'file_default',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(
      'file_view_mode' => 'default',
      'text' => 'Download [file:name]',
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
  $pane->uuid = '90e68ddc-59aa-4666-90de-47f1259a7c16';
  $display->content['new-90e68ddc-59aa-4666-90de-47f1259a7c16'] = $pane;
  $display->panels['column1'][0] = 'new-90e68ddc-59aa-4666-90de-47f1259a7c16';
  $pane = new stdClass();
  $pane->pid = 'new-796e11b7-f8e9-4d0c-83de-897c130c0352';
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
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = '796e11b7-f8e9-4d0c-83de-897c130c0352';
  $display->content['new-796e11b7-f8e9-4d0c-83de-897c130c0352'] = $pane;
  $display->panels['column1'][1] = 'new-796e11b7-f8e9-4d0c-83de-897c130c0352';
  $pane = new stdClass();
  $pane->pid = 'new-29810e4e-8c07-4693-83a0-beb6fbe25478';
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
  $pane->uuid = '29810e4e-8c07-4693-83a0-beb6fbe25478';
  $display->content['new-29810e4e-8c07-4693-83a0-beb6fbe25478'] = $pane;
  $display->panels['column1'][2] = 'new-29810e4e-8c07-4693-83a0-beb6fbe25478';
  $pane = new stdClass();
  $pane->pid = 'new-588d01be-8903-4488-8143-73d1dc0c1904';
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
  $pane->uuid = '588d01be-8903-4488-8143-73d1dc0c1904';
  $display->content['new-588d01be-8903-4488-8143-73d1dc0c1904'] = $pane;
  $display->panels['column2'][0] = 'new-588d01be-8903-4488-8143-73d1dc0c1904';
  $pane = new stdClass();
  $pane->pid = 'new-a8a8a580-8ae9-4147-a5d7-797f899bad76';
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
  $pane->uuid = 'a8a8a580-8ae9-4147-a5d7-797f899bad76';
  $display->content['new-a8a8a580-8ae9-4147-a5d7-797f899bad76'] = $pane;
  $display->panels['column2'][1] = 'new-a8a8a580-8ae9-4147-a5d7-797f899bad76';
  $pane = new stdClass();
  $pane->pid = 'new-390eb1a8-9342-435f-ac8d-99dfcb3bcfa0';
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
  $pane->uuid = '390eb1a8-9342-435f-ac8d-99dfcb3bcfa0';
  $display->content['new-390eb1a8-9342-435f-ac8d-99dfcb3bcfa0'] = $pane;
  $display->panels['column2'][2] = 'new-390eb1a8-9342-435f-ac8d-99dfcb3bcfa0';
  $pane = new stdClass();
  $pane->pid = 'new-75d35ff3-d01f-498c-a20e-4e818c4522b6';
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
  $pane->uuid = '75d35ff3-d01f-498c-a20e-4e818c4522b6';
  $display->content['new-75d35ff3-d01f-498c-a20e-4e818c4522b6'] = $pane;
  $display->panels['column2'][3] = 'new-75d35ff3-d01f-498c-a20e-4e818c4522b6';
  $pane = new stdClass();
  $pane->pid = 'new-354c0083-a8b3-4f77-be8b-20d08b886181';
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
  $pane->uuid = '354c0083-a8b3-4f77-be8b-20d08b886181';
  $display->content['new-354c0083-a8b3-4f77-be8b-20d08b886181'] = $pane;
  $display->panels['column2'][4] = 'new-354c0083-a8b3-4f77-be8b-20d08b886181';
  $pane = new stdClass();
  $pane->pid = 'new-c0a3de04-2a7a-40b5-9206-ecb5de6d1acf';
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
  $pane->uuid = 'c0a3de04-2a7a-40b5-9206-ecb5de6d1acf';
  $display->content['new-c0a3de04-2a7a-40b5-9206-ecb5de6d1acf'] = $pane;
  $display->panels['column2'][5] = 'new-c0a3de04-2a7a-40b5-9206-ecb5de6d1acf';
  $pane = new stdClass();
  $pane->pid = 'new-af3ca5a2-1407-45ac-a50e-891f0ead2e4c';
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
  $pane->uuid = 'af3ca5a2-1407-45ac-a50e-891f0ead2e4c';
  $display->content['new-af3ca5a2-1407-45ac-a50e-891f0ead2e4c'] = $pane;
  $display->panels['column2'][6] = 'new-af3ca5a2-1407-45ac-a50e-891f0ead2e4c';
  $pane = new stdClass();
  $pane->pid = 'new-f3154cf9-17e8-48a8-94f9-b25946040a24';
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
  $pane->uuid = 'f3154cf9-17e8-48a8-94f9-b25946040a24';
  $display->content['new-f3154cf9-17e8-48a8-94f9-b25946040a24'] = $pane;
  $display->panels['column2'][7] = 'new-f3154cf9-17e8-48a8-94f9-b25946040a24';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-29810e4e-8c07-4693-83a0-beb6fbe25478';
  $panelizer->display = $display;
  $export['node:pece_artifact_pdf:default'] = $panelizer;

  return $export;
}
