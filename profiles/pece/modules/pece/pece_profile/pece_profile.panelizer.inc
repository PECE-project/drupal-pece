<?php
/**
 * @file
 * pece_profile.panelizer.inc
 */

/**
 * Implements hook_panelizer_defaults().
 */
function pece_profile_panelizer_defaults() {
  $export = array();

  $panelizer = new stdClass();
  $panelizer->disabled = FALSE; /* Edit this to true to make a default panelizer disabled initially */
  $panelizer->api_version = 1;
  $panelizer->name = 'user:user:default';
  $panelizer->title = 'Default';
  $panelizer->panelizer_type = 'user';
  $panelizer->panelizer_key = 'user';
  $panelizer->no_blocks = FALSE;
  $panelizer->css_id = '';
  $panelizer->css = '';
  $panelizer->pipeline = 'ipe';
  $panelizer->contexts = array();
  $panelizer->relationships = array(
    0 => array(
      'identifier' => 'Profile2 from user',
      'keyword' => 'profile2',
      'name' => 'profile2_from_user',
      'type' => 'pece_profile_main',
      'context' => 'panelizer',
      'id' => 1,
    ),
  );
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
      'center' => NULL,
      'content' => NULL,
      'sidebar' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '7c7384b3-1db8-473f-ac38-d05b54aa466a';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-803083b1-1afa-4deb-83da-2dcc2cd66b35';
  $pane->panel = 'content';
  $pane->type = 'entity_field';
  $pane->subtype = 'profile2:field_pece_institution';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
    'formatter' => 'text_plain',
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
  $pane->uuid = '803083b1-1afa-4deb-83da-2dcc2cd66b35';
  $display->content['new-803083b1-1afa-4deb-83da-2dcc2cd66b35'] = $pane;
  $display->panels['content'][0] = 'new-803083b1-1afa-4deb-83da-2dcc2cd66b35';
  $pane = new stdClass();
  $pane->pid = 'new-253c9e83-1a9d-4acc-9d79-2b0f2a54dfde';
  $pane->panel = 'content';
  $pane->type = 'entity_field';
  $pane->subtype = 'profile2:field_pece_location';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
    'formatter' => 'location_default',
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
  $pane->uuid = '253c9e83-1a9d-4acc-9d79-2b0f2a54dfde';
  $display->content['new-253c9e83-1a9d-4acc-9d79-2b0f2a54dfde'] = $pane;
  $display->panels['content'][1] = 'new-253c9e83-1a9d-4acc-9d79-2b0f2a54dfde';
  $pane = new stdClass();
  $pane->pid = 'new-eabd8fe0-16c8-4f57-af6e-0fddf0bd0fff';
  $pane->panel = 'content';
  $pane->type = 'entity_field';
  $pane->subtype = 'profile2:field_pece_position';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
    'formatter' => 'text_plain',
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
  $pane->position = 2;
  $pane->locks = array();
  $pane->uuid = 'eabd8fe0-16c8-4f57-af6e-0fddf0bd0fff';
  $display->content['new-eabd8fe0-16c8-4f57-af6e-0fddf0bd0fff'] = $pane;
  $display->panels['content'][2] = 'new-eabd8fe0-16c8-4f57-af6e-0fddf0bd0fff';
  $pane = new stdClass();
  $pane->pid = 'new-f1199169-08bf-4ef6-aab7-30decf0fb092';
  $pane->panel = 'content';
  $pane->type = 'entity_field';
  $pane->subtype = 'profile2:field_pece_biography';
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
  $pane->uuid = 'f1199169-08bf-4ef6-aab7-30decf0fb092';
  $display->content['new-f1199169-08bf-4ef6-aab7-30decf0fb092'] = $pane;
  $display->panels['content'][3] = 'new-f1199169-08bf-4ef6-aab7-30decf0fb092';
  $pane = new stdClass();
  $pane->pid = 'new-5ed93436-5e5b-45e8-ae87-d0c72c83d2e5';
  $pane->panel = 'content';
  $pane->type = 'entity_field';
  $pane->subtype = 'profile2:field_gpg_key';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
    'formatter' => 'file_download_link',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(
      'text' => 'Download [file:name]',
    ),
    'context' => array(),
    'override_title' => 0,
    'override_title_text' => '',
    'override_title_heading' => 'h2',
  );
  $pane->cache = array();
  $pane->style = array();
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 4;
  $pane->locks = array();
  $pane->uuid = '5ed93436-5e5b-45e8-ae87-d0c72c83d2e5';
  $display->content['new-5ed93436-5e5b-45e8-ae87-d0c72c83d2e5'] = $pane;
  $display->panels['content'][4] = 'new-5ed93436-5e5b-45e8-ae87-d0c72c83d2e5';
  $pane = new stdClass();
  $pane->pid = 'new-fd495f89-8481-43a1-bde6-4855cf0989d3';
  $pane->panel = 'sidebar';
  $pane->type = 'entity_field';
  $pane->subtype = 'user:field_user_picture';
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
  $pane->uuid = 'fd495f89-8481-43a1-bde6-4855cf0989d3';
  $display->content['new-fd495f89-8481-43a1-bde6-4855cf0989d3'] = $pane;
  $display->panels['sidebar'][0] = 'new-fd495f89-8481-43a1-bde6-4855cf0989d3';
  $pane = new stdClass();
  $pane->pid = 'new-2be4d262-6916-4b83-b8c7-52378afecd96';
  $pane->panel = 'sidebar';
  $pane->type = 'entity_field';
  $pane->subtype = 'profile2:field_pece_tags';
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
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = '2be4d262-6916-4b83-b8c7-52378afecd96';
  $display->content['new-2be4d262-6916-4b83-b8c7-52378afecd96'] = $pane;
  $display->panels['sidebar'][1] = 'new-2be4d262-6916-4b83-b8c7-52378afecd96';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $panelizer->display = $display;
  $export['user:user:default'] = $panelizer;

  return $export;
}
