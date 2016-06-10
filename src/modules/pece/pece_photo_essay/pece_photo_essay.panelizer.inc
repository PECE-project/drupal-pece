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
  $display->uuid = '36c2a679-957e-4fab-aac8-254257e98f5d';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-2f0e3de8-2596-4666-9856-831bcf3da444';
  $pane->panel = 'column1';
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
  $display->panels['column1'][0] = 'new-2f0e3de8-2596-4666-9856-831bcf3da444';
  $pane = new stdClass();
  $pane->pid = 'new-2bd44870-b23c-4661-9697-bc4dfa6b3637';
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
  $pane->uuid = '2bd44870-b23c-4661-9697-bc4dfa6b3637';
  $display->content['new-2bd44870-b23c-4661-9697-bc4dfa6b3637'] = $pane;
  $display->panels['column1'][1] = 'new-2bd44870-b23c-4661-9697-bc4dfa6b3637';
  $pane = new stdClass();
  $pane->pid = 'new-2d9eb81a-bdcb-4499-b34d-2d6e3b5d035e';
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
  $pane->uuid = '2d9eb81a-bdcb-4499-b34d-2d6e3b5d035e';
  $display->content['new-2d9eb81a-bdcb-4499-b34d-2d6e3b5d035e'] = $pane;
  $display->panels['column1'][2] = 'new-2d9eb81a-bdcb-4499-b34d-2d6e3b5d035e';
  $pane = new stdClass();
  $pane->pid = 'new-352aff2a-90ee-4862-9f8f-4acdb1489217';
  $pane->panel = 'column1';
  $pane->type = 'annotation';
  $pane->subtype = 'annotation';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'map' => array(
      'path' => 'panels/ajax',
      'load_functions' => '',
      'to_arg_functions' => '',
      'access_callback' => 'user_access',
      'access_arguments' => 'a:1:{i:0;s:14:"access content";}',
      'page_callback' => 'panels_ajax_router',
      'page_arguments' => array(
        0 => 'editor',
        1 => 'add-pane',
        2 => 'panelizer:default:node:pece_photo_essay.page_manager:default',
        3 => 'column1',
        4 => 'annotation',
        5 => 'annotation',
        6 => 'form',
      ),
      'delivery_callback' => 'ajax_deliver',
      'fit' => '3',
      'number_parts' => '2',
      'context' => '0',
      'tab_parent' => '',
      'tab_root' => 'panels/ajax',
      'title' => '',
      'title_callback' => 't',
      'title_arguments' => '',
      'theme_callback' => 'ajax_base_page_theme',
      'theme_arguments' => array(
        0 => 'editor',
        1 => 'add-pane',
        2 => 'panelizer:default:node:pece_photo_essay.page_manager:default',
        3 => 'column1',
        4 => 'annotation',
        5 => 'annotation',
        6 => 'form',
      ),
      'type' => '0',
      'description' => '',
      'position' => '',
      'weight' => '0',
      'include_file' => '',
      'href' => 'panels/ajax',
      'tab_root_href' => 'panels/ajax',
      'tab_parent_href' => '',
      'options' => array(),
      'access' => TRUE,
      'localized_options' => array(),
      'original_map' => array(
        0 => 'panels',
        1 => 'ajax',
        2 => 'editor',
        3 => 'add-pane',
        4 => 'panelizer:default:node:pece_photo_essay.page_manager:default',
        5 => 'column1',
        6 => 'annotation',
        7 => 'annotation',
        8 => 'form',
      ),
      'map' => array(
        0 => 'panels',
        1 => 'ajax',
        2 => 'editor',
        3 => 'add-pane',
        4 => 'panelizer:default:node:pece_photo_essay.page_manager:default',
        5 => 'column1',
        6 => 'annotation',
        7 => 'annotation',
        8 => 'form',
      ),
    ),
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
  $pane->uuid = '352aff2a-90ee-4862-9f8f-4acdb1489217';
  $display->content['new-352aff2a-90ee-4862-9f8f-4acdb1489217'] = $pane;
  $display->panels['column1'][3] = 'new-352aff2a-90ee-4862-9f8f-4acdb1489217';
  $pane = new stdClass();
  $pane->pid = 'new-5402eb09-be5b-4d1b-aef7-6d081c273add';
  $pane->panel = 'column1';
  $pane->type = 'block';
  $pane->subtype = 'views-aec56592c4c370bf6d475d08ee3d819d';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'inherit_path' => 1,
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
  $pane->uuid = '5402eb09-be5b-4d1b-aef7-6d081c273add';
  $display->content['new-5402eb09-be5b-4d1b-aef7-6d081c273add'] = $pane;
  $display->panels['column1'][4] = 'new-5402eb09-be5b-4d1b-aef7-6d081c273add';
  $pane = new stdClass();
  $pane->pid = 'new-b423cf9e-d0ac-42b8-a67c-a651cb7fac2e';
  $pane->panel = 'column1';
  $pane->type = 'views_panes';
  $pane->subtype = 'pece_annotations-pece_artifact_user_annotations';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'view_settings' => 'fields',
    'header_type' => 'none',
    'view_mode' => 'teaser',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 5;
  $pane->locks = array();
  $pane->uuid = 'b423cf9e-d0ac-42b8-a67c-a651cb7fac2e';
  $display->content['new-b423cf9e-d0ac-42b8-a67c-a651cb7fac2e'] = $pane;
  $display->panels['column1'][5] = 'new-b423cf9e-d0ac-42b8-a67c-a651cb7fac2e';
  $pane = new stdClass();
  $pane->pid = 'new-dc6e5b94-6f57-4e35-9466-eb778e9a628f';
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
  $pane->uuid = 'dc6e5b94-6f57-4e35-9466-eb778e9a628f';
  $display->content['new-dc6e5b94-6f57-4e35-9466-eb778e9a628f'] = $pane;
  $display->panels['column2'][0] = 'new-dc6e5b94-6f57-4e35-9466-eb778e9a628f';
  $pane = new stdClass();
  $pane->pid = 'new-4942ee38-5548-4fc7-bf2d-e628a2b43111';
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
  $pane->uuid = '4942ee38-5548-4fc7-bf2d-e628a2b43111';
  $display->content['new-4942ee38-5548-4fc7-bf2d-e628a2b43111'] = $pane;
  $display->panels['column2'][1] = 'new-4942ee38-5548-4fc7-bf2d-e628a2b43111';
  $pane = new stdClass();
  $pane->pid = 'new-abe834ba-55f2-4e27-b77f-e60fdcea7593';
  $pane->panel = 'column2';
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
  $pane->position = 2;
  $pane->locks = array();
  $pane->uuid = 'abe834ba-55f2-4e27-b77f-e60fdcea7593';
  $display->content['new-abe834ba-55f2-4e27-b77f-e60fdcea7593'] = $pane;
  $display->panels['column2'][2] = 'new-abe834ba-55f2-4e27-b77f-e60fdcea7593';
  $pane = new stdClass();
  $pane->pid = 'new-40d13bc7-9265-4dea-8c9b-8a9f4b7526d0';
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
  $pane->uuid = '40d13bc7-9265-4dea-8c9b-8a9f4b7526d0';
  $display->content['new-40d13bc7-9265-4dea-8c9b-8a9f4b7526d0'] = $pane;
  $display->panels['column2'][3] = 'new-40d13bc7-9265-4dea-8c9b-8a9f4b7526d0';
  $pane = new stdClass();
  $pane->pid = 'new-4d045da6-f11e-4578-8891-fea90aec1786';
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
  $pane->uuid = '4d045da6-f11e-4578-8891-fea90aec1786';
  $display->content['new-4d045da6-f11e-4578-8891-fea90aec1786'] = $pane;
  $display->panels['column2'][4] = 'new-4d045da6-f11e-4578-8891-fea90aec1786';
  $pane = new stdClass();
  $pane->pid = 'new-3bb2d2f2-cdd7-4215-bcce-e5605514d91f';
  $pane->panel = 'column2';
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
  $pane->position = 5;
  $pane->locks = array();
  $pane->uuid = '3bb2d2f2-cdd7-4215-bcce-e5605514d91f';
  $display->content['new-3bb2d2f2-cdd7-4215-bcce-e5605514d91f'] = $pane;
  $display->panels['column2'][5] = 'new-3bb2d2f2-cdd7-4215-bcce-e5605514d91f';
  $pane = new stdClass();
  $pane->pid = 'new-4edb92fb-9e4f-4090-abf3-3fbfcbf361ea';
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
  $pane->uuid = '4edb92fb-9e4f-4090-abf3-3fbfcbf361ea';
  $display->content['new-4edb92fb-9e4f-4090-abf3-3fbfcbf361ea'] = $pane;
  $display->panels['column2'][6] = 'new-4edb92fb-9e4f-4090-abf3-3fbfcbf361ea';
  $pane = new stdClass();
  $pane->pid = 'new-4f030fd6-7936-4e3e-87d7-987bd0f00e9d';
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
  $pane->uuid = '4f030fd6-7936-4e3e-87d7-987bd0f00e9d';
  $display->content['new-4f030fd6-7936-4e3e-87d7-987bd0f00e9d'] = $pane;
  $display->panels['column2'][7] = 'new-4f030fd6-7936-4e3e-87d7-987bd0f00e9d';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-3bb2d2f2-cdd7-4215-bcce-e5605514d91f';
  $panelizer->display = $display;
  $export['node:pece_photo_essay:default'] = $panelizer;

  return $export;
}
