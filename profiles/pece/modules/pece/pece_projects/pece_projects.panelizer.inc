<?php

/**
 * @file
 * pece_projects.panelizer.inc
 */

/**
 * Implements hook_panelizer_defaults().
 */
function pece_projects_panelizer_defaults() {
  $export = array();

  $panelizer = new stdClass();
  $panelizer->disabled = FALSE; /* Edit this to true to make a default panelizer disabled initially */
  $panelizer->api_version = 1;
  $panelizer->title = 'Default';
  $panelizer->panelizer_type = 'node';
  $panelizer->panelizer_key = 'pece_project';
  $panelizer->access = array();
  $panelizer->view_mode = 'page_manager';
  $panelizer->name = 'node:pece_project:default';
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
  $display->layout = 'pece_pond';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'content' => NULL,
      'sidebar' => NULL,
      'header' => NULL,
      'column1' => NULL,
      'column2' => NULL,
      'column3' => NULL,
      'secondarycolumn1' => NULL,
      'secondarycolumn2' => NULL,
      'secondarycolumn3' => NULL,
      'footer' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '%node:title';
  $display->uuid = '8b541f82-dae9-4ee3-9ce4-9fa3b2e1b7d7';
  $display->storage_type = 'panelizer_default';
  $display->storage_id = 'node:pece_project:default';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-f28266f3-a92d-4efe-b331-bb8b162a6233';
  $pane->panel = 'column1';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:body';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
    'formatter' => 'text_default',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(),
    'context' => array(),
    'override_title' => 1,
    'override_title_text' => 'About Project',
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
  $display->panels['column1'][0] = 'new-f28266f3-a92d-4efe-b331-bb8b162a6233';
  $pane = new stdClass();
  $pane->pid = 'new-04845ccd-f590-4fd7-aa76-82c25007f149';
  $pane->panel = 'column1';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_contributors';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
    'formatter' => 'entityreference_entity_view',
    'delta_limit' => '0',
    'delta_offset' => '0',
    'delta_reversed' => 0,
    'formatter_settings' => array(
      'view_mode' => 'mini_teaser',
      'links' => 1,
      'use_content_language' => 1,
    ),
    'context' => array(),
    'override_title' => 1,
    'override_title_text' => 'Researchers',
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
  $pane->uuid = '04845ccd-f590-4fd7-aa76-82c25007f149';
  $display->content['new-04845ccd-f590-4fd7-aa76-82c25007f149'] = $pane;
  $display->panels['column1'][1] = 'new-04845ccd-f590-4fd7-aa76-82c25007f149';
  $pane = new stdClass();
  $pane->pid = 'new-2b52b029-b5ba-4da5-acbb-731453e8df52';
  $pane->panel = 'column1';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_multiple_link';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
    'formatter' => 'link_default',
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
  $pane->uuid = '2b52b029-b5ba-4da5-acbb-731453e8df52';
  $display->content['new-2b52b029-b5ba-4da5-acbb-731453e8df52'] = $pane;
  $display->panels['column1'][2] = 'new-2b52b029-b5ba-4da5-acbb-731453e8df52';
  $pane = new stdClass();
  $pane->pid = 'new-97fd7e57-30de-4dea-9005-882ba1cc2d57';
  $pane->panel = 'column1';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_funding_agency';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
    'formatter' => 'link_default',
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
  $pane->position = 3;
  $pane->locks = array();
  $pane->uuid = '97fd7e57-30de-4dea-9005-882ba1cc2d57';
  $display->content['new-97fd7e57-30de-4dea-9005-882ba1cc2d57'] = $pane;
  $display->panels['column1'][3] = 'new-97fd7e57-30de-4dea-9005-882ba1cc2d57';
  $pane = new stdClass();
  $pane->pid = 'new-19b628ee-ff63-4688-b360-d8bedccfd1d2';
  $pane->panel = 'column1';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_start_end_date';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
    'formatter' => 'date_default',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(
      'format_type' => 'full_date',
      'multiple_number' => '',
      'multiple_from' => '',
      'multiple_to' => '',
      'fromto' => 'both',
      'show_remaining_days' => 0,
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
  $pane->position = 4;
  $pane->locks = array();
  $pane->uuid = '19b628ee-ff63-4688-b360-d8bedccfd1d2';
  $display->content['new-19b628ee-ff63-4688-b360-d8bedccfd1d2'] = $pane;
  $display->panels['column1'][4] = 'new-19b628ee-ff63-4688-b360-d8bedccfd1d2';
  $pane = new stdClass();
  $pane->pid = 'new-6a768da4-0275-4c43-b05b-ee2aafc9402a';
  $pane->panel = 'column1';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_basic_file_file';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
    'formatter' => 'file_default',
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
  $pane->position = 5;
  $pane->locks = array();
  $pane->uuid = '6a768da4-0275-4c43-b05b-ee2aafc9402a';
  $display->content['new-6a768da4-0275-4c43-b05b-ee2aafc9402a'] = $pane;
  $display->panels['column1'][5] = 'new-6a768da4-0275-4c43-b05b-ee2aafc9402a';
  $pane = new stdClass();
  $pane->pid = 'new-c8138ce1-7262-4733-8c69-9d45cc3a2446';
  $pane->panel = 'column1';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_consent_form';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
    'formatter' => 'file_default',
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
  $pane->position = 6;
  $pane->locks = array();
  $pane->uuid = 'c8138ce1-7262-4733-8c69-9d45cc3a2446';
  $display->content['new-c8138ce1-7262-4733-8c69-9d45cc3a2446'] = $pane;
  $display->panels['column1'][6] = 'new-c8138ce1-7262-4733-8c69-9d45cc3a2446';
  $pane = new stdClass();
  $pane->pid = 'new-5c8af8f8-5697-471b-9b4e-7eacdc83e017';
  $pane->panel = 'column1';
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
  $pane->position = 7;
  $pane->locks = array();
  $pane->uuid = '5c8af8f8-5697-471b-9b4e-7eacdc83e017';
  $display->content['new-5c8af8f8-5697-471b-9b4e-7eacdc83e017'] = $pane;
  $display->panels['column1'][7] = 'new-5c8af8f8-5697-471b-9b4e-7eacdc83e017';
  $pane = new stdClass();
  $pane->pid = 'new-39ee3cf3-4256-45e8-99e9-030a737c2d80';
  $pane->panel = 'column2';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_featured_essays';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
    'formatter' => 'entityreference_entity_view',
    'delta_limit' => '0',
    'delta_offset' => '0',
    'delta_reversed' => 0,
    'formatter_settings' => array(
      'view_mode' => 'mini_teaser',
      'links' => 0,
      'use_content_language' => 1,
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
  $pane->uuid = '39ee3cf3-4256-45e8-99e9-030a737c2d80';
  $display->content['new-39ee3cf3-4256-45e8-99e9-030a737c2d80'] = $pane;
  $display->panels['column2'][0] = 'new-39ee3cf3-4256-45e8-99e9-030a737c2d80';
  $pane = new stdClass();
  $pane->pid = 'new-8a5889fe-22cd-4a0a-a2e2-d10806e29ac2';
  $pane->panel = 'column3';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_proj_lead';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
    'formatter' => 'entityreference_entity_view',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(
      'view_mode' => 'mini_teaser',
      'links' => 0,
      'use_content_language' => 1,
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
  $pane->uuid = '8a5889fe-22cd-4a0a-a2e2-d10806e29ac2';
  $display->content['new-8a5889fe-22cd-4a0a-a2e2-d10806e29ac2'] = $pane;
  $display->panels['column3'][0] = 'new-8a5889fe-22cd-4a0a-a2e2-d10806e29ac2';
  $pane = new stdClass();
  $pane->pid = 'new-5d52b27f-f8f3-490d-a943-c77953e3a84c';
  $pane->panel = 'column3';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_design_group';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
    'formatter' => 'entityreference_entity_view',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(
      'view_mode' => 'mini_teaser',
      'links' => 0,
      'use_content_language' => 1,
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
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = '5d52b27f-f8f3-490d-a943-c77953e3a84c';
  $display->content['new-5d52b27f-f8f3-490d-a943-c77953e3a84c'] = $pane;
  $display->panels['column3'][1] = 'new-5d52b27f-f8f3-490d-a943-c77953e3a84c';
  $pane = new stdClass();
  $pane->pid = 'new-a18a2709-b38d-4db3-8ee6-262eb9c5ed48';
  $pane->panel = 'column3';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_groups';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
    'formatter' => 'entityreference_entity_view',
    'delta_limit' => '0',
    'delta_offset' => '0',
    'delta_reversed' => 0,
    'formatter_settings' => array(
      'view_mode' => 'mini_teaser',
      'links' => 0,
      'use_content_language' => 1,
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
  $pane->position = 2;
  $pane->locks = array();
  $pane->uuid = 'a18a2709-b38d-4db3-8ee6-262eb9c5ed48';
  $display->content['new-a18a2709-b38d-4db3-8ee6-262eb9c5ed48'] = $pane;
  $display->panels['column3'][2] = 'new-a18a2709-b38d-4db3-8ee6-262eb9c5ed48';
  $pane = new stdClass();
  $pane->pid = 'new-205ec2ff-1f7d-4de6-aa1d-c89ce6eb16ca';
  $pane->panel = 'column3';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_proj_struct_analytics';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
    'formatter' => 'taxonomy_term_reference_link',
    'delta_limit' => '0',
    'delta_offset' => '0',
    'delta_reversed' => 0,
    'formatter_settings' => array(
      'view_mode' => 'default',
      'links' => 0,
      'use_content_language' => 1,
      'data_element_key' => '',
      'skip_safe' => 0,
      'skip_empty_values' => 0,
      'term_name' => 1,
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
  $pane->position = 3;
  $pane->locks = array();
  $pane->uuid = '205ec2ff-1f7d-4de6-aa1d-c89ce6eb16ca';
  $display->content['new-205ec2ff-1f7d-4de6-aa1d-c89ce6eb16ca'] = $pane;
  $display->panels['column3'][3] = 'new-205ec2ff-1f7d-4de6-aa1d-c89ce6eb16ca';
  $pane = new stdClass();
  $pane->pid = 'new-f1557425-da7e-497c-aaad-c833c71e7245';
  $pane->panel = 'column3';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_substantive_logic';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
    'formatter' => 'entityreference_entity_view',
    'delta_limit' => '0',
    'delta_offset' => '0',
    'delta_reversed' => 0,
    'formatter_settings' => array(
      'view_mode' => 'mini_teaser',
      'links' => 0,
      'use_content_language' => 1,
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
  $pane->position = 4;
  $pane->locks = array();
  $pane->uuid = 'f1557425-da7e-497c-aaad-c833c71e7245';
  $display->content['new-f1557425-da7e-497c-aaad-c833c71e7245'] = $pane;
  $display->panels['column3'][4] = 'new-f1557425-da7e-497c-aaad-c833c71e7245';
  $pane = new stdClass();
  $pane->pid = 'new-5a98bfe7-3c07-4ee1-b69f-8f029b2cd7bb';
  $pane->panel = 'column3';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_proj_notes';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
    'formatter' => 'services',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(
      'data_element_key' => '',
      'skip_safe' => 0,
      'skip_empty_values' => 0,
      'skip_text_format' => 1,
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
  $pane->position = 5;
  $pane->locks = array();
  $pane->uuid = '5a98bfe7-3c07-4ee1-b69f-8f029b2cd7bb';
  $display->content['new-5a98bfe7-3c07-4ee1-b69f-8f029b2cd7bb'] = $pane;
  $display->panels['column3'][5] = 'new-5a98bfe7-3c07-4ee1-b69f-8f029b2cd7bb';
  $pane = new stdClass();
  $pane->pid = 'new-ace70d71-8c8c-477c-b5da-95c2552c33b6';
  $pane->panel = 'header';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_proj_img';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'hidden',
    'formatter' => 'image',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(
      'image_style' => 'panopoly_image_full',
      'image_link' => '',
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
  $pane->uuid = 'ace70d71-8c8c-477c-b5da-95c2552c33b6';
  $display->content['new-ace70d71-8c8c-477c-b5da-95c2552c33b6'] = $pane;
  $display->panels['header'][0] = 'new-ace70d71-8c8c-477c-b5da-95c2552c33b6';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $panelizer->display = $display;
  $export['node:pece_project:default'] = $panelizer;

  return $export;
}
