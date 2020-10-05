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
  $panelizer->title = 'Default';
  $panelizer->panelizer_type = 'node';
  $panelizer->panelizer_key = 'pece_photo_essay';
  $panelizer->access = array();
  $panelizer->view_mode = 'page_manager';
  $panelizer->name = 'node:pece_photo_essay:default';
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
  $display->layout = 'radix_bryant_flipped';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'column1' => NULL,
      'column2' => NULL,
      'sidebar' => NULL,
      'contentmain' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '%node:title';
  $display->uuid = '36c2a679-957e-4fab-aac8-254257e98f5d';
  $display->storage_type = 'panelizer_default';
  $display->storage_id = 'node:pece_photo_essay:default';
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
  $pane->style = array(
    'settings' => NULL,
  );
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
  $pane->shown = FALSE;
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
  $pane->position = 4;
  $pane->locks = array();
  $pane->uuid = 'b26e3694-148a-4067-b99b-f8227a7d3e1e';
  $display->content['new-b26e3694-148a-4067-b99b-f8227a7d3e1e'] = $pane;
  $display->panels['contentmain'][4] = 'new-b26e3694-148a-4067-b99b-f8227a7d3e1e';
  $pane = new stdClass();
  $pane->pid = 'new-f0467b40-b946-4baf-a68a-4ac8705eaa1a';
  $pane->panel = 'contentmain';
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
        3 => 'contentmain',
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
        3 => 'contentmain',
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
        5 => 'contentmain',
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
        5 => 'contentmain',
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
  $pane->position = 5;
  $pane->locks = array();
  $pane->uuid = 'f0467b40-b946-4baf-a68a-4ac8705eaa1a';
  $display->content['new-f0467b40-b946-4baf-a68a-4ac8705eaa1a'] = $pane;
  $display->panels['contentmain'][5] = 'new-f0467b40-b946-4baf-a68a-4ac8705eaa1a';
  $pane = new stdClass();
  $pane->pid = 'new-47933042-098a-4709-922d-8efa4b4dbf1a';
  $pane->panel = 'contentmain';
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
  $pane->position = 6;
  $pane->locks = array();
  $pane->uuid = '47933042-098a-4709-922d-8efa4b4dbf1a';
  $display->content['new-47933042-098a-4709-922d-8efa4b4dbf1a'] = $pane;
  $display->panels['contentmain'][6] = 'new-47933042-098a-4709-922d-8efa4b4dbf1a';
  $pane = new stdClass();
  $pane->pid = 'new-5420ae40-7ef2-4739-af25-5502609f6dac';
  $pane->panel = 'contentmain';
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
  $pane->position = 7;
  $pane->locks = array();
  $pane->uuid = '5420ae40-7ef2-4739-af25-5502609f6dac';
  $display->content['new-5420ae40-7ef2-4739-af25-5502609f6dac'] = $pane;
  $display->panels['contentmain'][7] = 'new-5420ae40-7ef2-4739-af25-5502609f6dac';
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
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = 'd037d200-1f9e-45a9-8191-ddbc80d172f3';
  $display->content['new-d037d200-1f9e-45a9-8191-ddbc80d172f3'] = $pane;
  $display->panels['sidebar'][0] = 'new-d037d200-1f9e-45a9-8191-ddbc80d172f3';
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
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = '4942ee38-5548-4fc7-bf2d-e628a2b43111';
  $display->content['new-4942ee38-5548-4fc7-bf2d-e628a2b43111'] = $pane;
  $display->panels['sidebar'][1] = 'new-4942ee38-5548-4fc7-bf2d-e628a2b43111';
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
  $pane->position = 2;
  $pane->locks = array();
  $pane->uuid = 'abe834ba-55f2-4e27-b77f-e60fdcea7593';
  $display->content['new-abe834ba-55f2-4e27-b77f-e60fdcea7593'] = $pane;
  $display->panels['sidebar'][2] = 'new-abe834ba-55f2-4e27-b77f-e60fdcea7593';
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
  $pane->position = 3;
  $pane->locks = array();
  $pane->uuid = '3bb2d2f2-cdd7-4215-bcce-e5605514d91f';
  $display->content['new-3bb2d2f2-cdd7-4215-bcce-e5605514d91f'] = $pane;
  $display->panels['sidebar'][3] = 'new-3bb2d2f2-cdd7-4215-bcce-e5605514d91f';
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
  $pane->position = 4;
  $pane->locks = array();
  $pane->uuid = '4edb92fb-9e4f-4090-abf3-3fbfcbf361ea';
  $display->content['new-4edb92fb-9e4f-4090-abf3-3fbfcbf361ea'] = $pane;
  $display->panels['sidebar'][4] = 'new-4edb92fb-9e4f-4090-abf3-3fbfcbf361ea';
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
  $pane->position = 5;
  $pane->locks = array();
  $pane->uuid = '4f030fd6-7936-4e3e-87d7-987bd0f00e9d';
  $display->content['new-4f030fd6-7936-4e3e-87d7-987bd0f00e9d'] = $pane;
  $display->panels['sidebar'][5] = 'new-4f030fd6-7936-4e3e-87d7-987bd0f00e9d';
  $pane = new stdClass();
  $pane->pid = 'new-1ba9abd1-ca82-43bf-acd1-c4f2704f7674';
  $pane->panel = 'sidebar';
  $pane->type = 'citation';
  $pane->subtype = 'citation';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'override_title' => 1,
    'override_title_text' => 'Cite as',
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
  $pane->uuid = '1ba9abd1-ca82-43bf-acd1-c4f2704f7674';
  $display->content['new-1ba9abd1-ca82-43bf-acd1-c4f2704f7674'] = $pane;
  $display->panels['sidebar'][6] = 'new-1ba9abd1-ca82-43bf-acd1-c4f2704f7674';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-3bb2d2f2-cdd7-4215-bcce-e5605514d91f';
  $panelizer->display = $display;
  $export['node:pece_photo_essay:default'] = $panelizer;

  return $export;
}
