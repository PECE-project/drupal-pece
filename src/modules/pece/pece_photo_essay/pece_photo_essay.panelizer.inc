<?php
/**
 * @file
 * pece_photo_essay.panelizer.inc
 */

/**
 * Implements hook_panelizer_defaults().
 */
function pece_photo_essay_panelizer_defaults() {
  $export = array();

  $panelizer = new stdClass();
  $panelizer->disabled = FALSE; /* Edit this to true to make a default panelizer disabled initially */
  $panelizer->api_version = 1;
  $panelizer->name = 'node:pece_photo_essay:default';
  $panelizer->title = 'Default';
  $panelizer->panelizer_type = 'node';
  $panelizer->panelizer_key = 'pece_photo_essay';
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
  $display->layout = 'radix_bryant_flipped';
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
  $display->uuid = '36c2a679-957e-4fab-aac8-254257e98f5d';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-2f0e3de8-2596-4666-9856-831bcf3da444';
  $pane->panel = 'contentmain';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:body';
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
  $pane->uuid = '2f0e3de8-2596-4666-9856-831bcf3da444';
  $display->content['new-2f0e3de8-2596-4666-9856-831bcf3da444'] = $pane;
  $display->panels['contentmain'][0] = 'new-2f0e3de8-2596-4666-9856-831bcf3da444';
  $pane = new stdClass();
  $pane->pid = 'new-a844c7a8-fa96-4828-aac2-f0587b2ddd87';
  $pane->panel = 'contentmain';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_photo_essay_items';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'hidden',
    'formatter' => 'entityreference_entity_view',
    'delta_limit' => '0',
    'delta_offset' => '0',
    'delta_reversed' => 0,
    'formatter_settings' => array(
      'view_mode' => 'full',
      'links' => 0,
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
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = 'a844c7a8-fa96-4828-aac2-f0587b2ddd87';
  $display->content['new-a844c7a8-fa96-4828-aac2-f0587b2ddd87'] = $pane;
  $display->panels['contentmain'][1] = 'new-a844c7a8-fa96-4828-aac2-f0587b2ddd87';
  $pane = new stdClass();
  $pane->pid = 'new-2bd44870-b23c-4661-9697-bc4dfa6b3637';
  $pane->panel = 'contentmain';
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
  $pane->uuid = '2bd44870-b23c-4661-9697-bc4dfa6b3637';
  $display->content['new-2bd44870-b23c-4661-9697-bc4dfa6b3637'] = $pane;
  $display->panels['contentmain'][2] = 'new-2bd44870-b23c-4661-9697-bc4dfa6b3637';
  $pane = new stdClass();
  $pane->pid = 'new-2d9eb81a-bdcb-4499-b34d-2d6e3b5d035e';
  $pane->panel = 'contentmain';
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
  $pane->uuid = '2d9eb81a-bdcb-4499-b34d-2d6e3b5d035e';
  $display->content['new-2d9eb81a-bdcb-4499-b34d-2d6e3b5d035e'] = $pane;
  $display->panels['contentmain'][3] = 'new-2d9eb81a-bdcb-4499-b34d-2d6e3b5d035e';
  $pane = new stdClass();
  $pane->pid = 'new-b26e3694-148a-4067-b99b-f8227a7d3e1e';
  $pane->panel = 'contentmain';
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
  $pane->style = array();
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 4;
  $pane->locks = array();
  $pane->uuid = 'b26e3694-148a-4067-b99b-f8227a7d3e1e';
  $display->content['new-b26e3694-148a-4067-b99b-f8227a7d3e1e'] = $pane;
  $display->panels['contentmain'][4] = 'new-b26e3694-148a-4067-b99b-f8227a7d3e1e';
  $pane = new stdClass();
  $pane->pid = 'new-d037d200-1f9e-45a9-8191-ddbc80d172f3';
  $pane->panel = 'sidebar';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_thumbnail';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
    'formatter' => 'image',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(
      'file_view_mode' => 'default',
      'image_style' => '',
      'image_link' => '',
    ),
    'context' => array(),
    'override_title' => 1,
    'override_title_text' => '',
    'override_title_heading' => 'h2',
  );
  $pane->cache = array();
  $pane->style = array();
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = 'd037d200-1f9e-45a9-8191-ddbc80d172f3';
  $display->content['new-d037d200-1f9e-45a9-8191-ddbc80d172f3'] = $pane;
  $display->panels['sidebar'][0] = 'new-d037d200-1f9e-45a9-8191-ddbc80d172f3';
  $pane = new stdClass();
  $pane->pid = 'new-dc6e5b94-6f57-4e35-9466-eb778e9a628f';
  $pane->panel = 'sidebar';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_authors';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
    'formatter' => 'taxonomy_term_reference_link',
    'delta_limit' => '0',
    'delta_offset' => '0',
    'delta_reversed' => 0,
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
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = 'dc6e5b94-6f57-4e35-9466-eb778e9a628f';
  $display->content['new-dc6e5b94-6f57-4e35-9466-eb778e9a628f'] = $pane;
  $display->panels['sidebar'][1] = 'new-dc6e5b94-6f57-4e35-9466-eb778e9a628f';
  $pane = new stdClass();
  $pane->pid = 'new-4942ee38-5548-4fc7-bf2d-e628a2b43111';
  $pane->panel = 'sidebar';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_contributors';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
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
  $pane->position = 2;
  $pane->locks = array();
  $pane->uuid = '4942ee38-5548-4fc7-bf2d-e628a2b43111';
  $display->content['new-4942ee38-5548-4fc7-bf2d-e628a2b43111'] = $pane;
  $display->panels['sidebar'][2] = 'new-4942ee38-5548-4fc7-bf2d-e628a2b43111';
  $pane = new stdClass();
  $pane->pid = 'new-abe834ba-55f2-4e27-b77f-e60fdcea7593';
  $pane->panel = 'sidebar';
  $pane->type = 'node_created';
  $pane->subtype = 'node_created';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'format' => 'panopoly_day',
    'context' => 'panelizer',
    'override_title' => 1,
    'override_title_text' => 'Created date',
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
  $pane->uuid = 'abe834ba-55f2-4e27-b77f-e60fdcea7593';
  $display->content['new-abe834ba-55f2-4e27-b77f-e60fdcea7593'] = $pane;
  $display->panels['sidebar'][3] = 'new-abe834ba-55f2-4e27-b77f-e60fdcea7593';
  $pane = new stdClass();
  $pane->pid = 'new-3bb2d2f2-cdd7-4215-bcce-e5605514d91f';
  $pane->panel = 'sidebar';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:og_group_ref';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
    'formatter' => 'og_list_default',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(),
    'context' => 'panelizer',
    'override_title' => 1,
    'override_title_text' => 'Group Audience',
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
  $pane->uuid = '3bb2d2f2-cdd7-4215-bcce-e5605514d91f';
  $display->content['new-3bb2d2f2-cdd7-4215-bcce-e5605514d91f'] = $pane;
  $display->panels['sidebar'][4] = 'new-3bb2d2f2-cdd7-4215-bcce-e5605514d91f';
  $pane = new stdClass();
  $pane->pid = 'new-4edb92fb-9e4f-4090-abf3-3fbfcbf361ea';
  $pane->panel = 'sidebar';
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
  $pane->position = 5;
  $pane->locks = array();
  $pane->uuid = '4edb92fb-9e4f-4090-abf3-3fbfcbf361ea';
  $display->content['new-4edb92fb-9e4f-4090-abf3-3fbfcbf361ea'] = $pane;
  $display->panels['sidebar'][5] = 'new-4edb92fb-9e4f-4090-abf3-3fbfcbf361ea';
  $pane = new stdClass();
  $pane->pid = 'new-4f030fd6-7936-4e3e-87d7-987bd0f00e9d';
  $pane->panel = 'sidebar';
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
  $pane->position = 6;
  $pane->locks = array();
  $pane->uuid = '4f030fd6-7936-4e3e-87d7-987bd0f00e9d';
  $display->content['new-4f030fd6-7936-4e3e-87d7-987bd0f00e9d'] = $pane;
  $display->panels['sidebar'][6] = 'new-4f030fd6-7936-4e3e-87d7-987bd0f00e9d';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-3bb2d2f2-cdd7-4215-bcce-e5605514d91f';
  $panelizer->display = $display;
  $export['node:pece_photo_essay:default'] = $panelizer;

  return $export;
}
