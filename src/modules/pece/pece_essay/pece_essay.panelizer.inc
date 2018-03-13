<?php
/**
 * @file
 * pece_essay.panelizer.inc
 */

/**
 * Implements hook_panelizer_defaults().
 */
function pece_essay_panelizer_defaults() {
  $export = array();

  $panelizer = new stdClass();
  $panelizer->disabled = FALSE; /* Edit this to true to make a default panelizer disabled initially */
  $panelizer->api_version = 1;
  $panelizer->title = 'Default';
  $panelizer->panelizer_type = 'node';
  $panelizer->panelizer_key = 'pece_essay';
  $panelizer->access = array();
  $panelizer->view_mode = 'page_manager';
  $panelizer->name = 'node:pece_essay:default';
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
  $display->uuid = '72f21b63-b09a-41d9-92c4-07b845d38d1f';
  $display->storage_type = 'panelizer_default';
  $display->storage_id = 'node:pece_essay:default';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-585b6ced-0f96-4825-b9d6-f5b7191a3ce8';
  $pane->panel = 'contentmain';
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
  $pane->uuid = '585b6ced-0f96-4825-b9d6-f5b7191a3ce8';
  $display->content['new-585b6ced-0f96-4825-b9d6-f5b7191a3ce8'] = $pane;
  $display->panels['contentmain'][0] = 'new-585b6ced-0f96-4825-b9d6-f5b7191a3ce8';
  $pane = new stdClass();
  $pane->pid = 'new-976d8cc1-771c-4ae2-9718-10c04ca0070b';
  $pane->panel = 'contentmain';
  $pane->type = 'view_essay_link';
  $pane->subtype = 'view_essay_link';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'destination' => 'essay',
    'context' => 'panelizer',
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
  $pane->uuid = '976d8cc1-771c-4ae2-9718-10c04ca0070b';
  $display->content['new-976d8cc1-771c-4ae2-9718-10c04ca0070b'] = $pane;
  $display->panels['contentmain'][1] = 'new-976d8cc1-771c-4ae2-9718-10c04ca0070b';
  $pane = new stdClass();
  $pane->pid = 'new-6c085e0a-1161-4d4b-b59c-2660d94154ec';
  $pane->panel = 'contentmain';
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
  $pane->position = 2;
  $pane->locks = array();
  $pane->uuid = '6c085e0a-1161-4d4b-b59c-2660d94154ec';
  $display->content['new-6c085e0a-1161-4d4b-b59c-2660d94154ec'] = $pane;
  $display->panels['contentmain'][2] = 'new-6c085e0a-1161-4d4b-b59c-2660d94154ec';
  $pane = new stdClass();
  $pane->pid = 'new-22a8c00a-9a3b-459e-ba15-ea7a1882f925';
  $pane->panel = 'contentmain';
  $pane->type = 'node_links';
  $pane->subtype = 'node_links';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'override_title' => 0,
    'override_title_text' => '',
    'build_mode' => 'full',
    'identifier' => '',
    'link' => 1,
    'context' => 'panelizer',
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
  $pane->uuid = '22a8c00a-9a3b-459e-ba15-ea7a1882f925';
  $display->content['new-22a8c00a-9a3b-459e-ba15-ea7a1882f925'] = $pane;
  $display->panels['contentmain'][3] = 'new-22a8c00a-9a3b-459e-ba15-ea7a1882f925';
  $pane = new stdClass();
  $pane->pid = 'new-beb09bec-1d62-4b84-878b-848a2aa652ac';
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
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 4;
  $pane->locks = array();
  $pane->uuid = 'beb09bec-1d62-4b84-878b-848a2aa652ac';
  $display->content['new-beb09bec-1d62-4b84-878b-848a2aa652ac'] = $pane;
  $display->panels['contentmain'][4] = 'new-beb09bec-1d62-4b84-878b-848a2aa652ac';
  $pane = new stdClass();
  $pane->pid = 'new-a39510d0-0fc1-4725-a5fd-66e1a154a26e';
  $pane->panel = 'sidebar';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_thumbnail';
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
  $pane->uuid = 'a39510d0-0fc1-4725-a5fd-66e1a154a26e';
  $display->content['new-a39510d0-0fc1-4725-a5fd-66e1a154a26e'] = $pane;
  $display->panels['sidebar'][0] = 'new-a39510d0-0fc1-4725-a5fd-66e1a154a26e';
  $pane = new stdClass();
  $pane->pid = 'new-183fc3bf-ff65-4b24-a565-769b4c316a62';
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
  $pane->uuid = '183fc3bf-ff65-4b24-a565-769b4c316a62';
  $display->content['new-183fc3bf-ff65-4b24-a565-769b4c316a62'] = $pane;
  $display->panels['sidebar'][1] = 'new-183fc3bf-ff65-4b24-a565-769b4c316a62';
  $pane = new stdClass();
  $pane->pid = 'new-646183a2-a91b-4ae8-8015-66e2c55c9648';
  $pane->panel = 'sidebar';
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
  $pane->uuid = '646183a2-a91b-4ae8-8015-66e2c55c9648';
  $display->content['new-646183a2-a91b-4ae8-8015-66e2c55c9648'] = $pane;
  $display->panels['sidebar'][2] = 'new-646183a2-a91b-4ae8-8015-66e2c55c9648';
  $pane = new stdClass();
  $pane->pid = 'new-be50b815-c1de-4484-a8a8-f6d6e6e632f1';
  $pane->panel = 'sidebar';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:og_group_ref';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
    'formatter' => 'entityreference_label',
    'delta_limit' => '0',
    'delta_offset' => '0',
    'delta_reversed' => 0,
    'formatter_settings' => array(
      'link' => 0,
    ),
    'context' => array(),
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
  $pane->uuid = 'be50b815-c1de-4484-a8a8-f6d6e6e632f1';
  $display->content['new-be50b815-c1de-4484-a8a8-f6d6e6e632f1'] = $pane;
  $display->panels['sidebar'][3] = 'new-be50b815-c1de-4484-a8a8-f6d6e6e632f1';
  $pane = new stdClass();
  $pane->pid = 'new-40e19591-cf88-4d25-9830-0443bfd0b68d';
  $pane->panel = 'sidebar';
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
  $pane->position = 4;
  $pane->locks = array();
  $pane->uuid = '40e19591-cf88-4d25-9830-0443bfd0b68d';
  $display->content['new-40e19591-cf88-4d25-9830-0443bfd0b68d'] = $pane;
  $display->panels['sidebar'][4] = 'new-40e19591-cf88-4d25-9830-0443bfd0b68d';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $panelizer->display = $display;
  $export['node:pece_essay:default'] = $panelizer;

  $panelizer = new stdClass();
  $panelizer->disabled = FALSE; /* Edit this to true to make a default panelizer disabled initially */
  $panelizer->api_version = 1;
  $panelizer->title = 'Default';
  $panelizer->panelizer_type = 'node';
  $panelizer->panelizer_key = 'pece_essay';
  $panelizer->access = array();
  $panelizer->view_mode = 'free_panel';
  $panelizer->name = 'node:pece_essay:default:free_panel';
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
  $display->layout = 'packery_layout';
  $display->layout_settings = array(
    'packery_items' => '{}',
  );
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'center' => NULL,
      'contentmain' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '%node:title';
  $display->uuid = '43a93860-56bc-43a3-9e34-5642b109ac81';
  $display->storage_type = 'panelizer_entity';
  $display->storage_id = 'node:pece_essay:default:free_panel';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-452edd7e-1b07-4ca3-a0d3-0f2da92ebc5d';
  $pane->panel = 'contentmain';
  $pane->type = 'node_title';
  $pane->subtype = 'node_title';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'link' => 0,
    'markup' => 'h1',
    'id' => '',
    'class' => '',
    'context' => 'panelizer',
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
  $pane->uuid = '452edd7e-1b07-4ca3-a0d3-0f2da92ebc5d';
  $display->content['new-452edd7e-1b07-4ca3-a0d3-0f2da92ebc5d'] = $pane;
  $display->panels['contentmain'][0] = 'new-452edd7e-1b07-4ca3-a0d3-0f2da92ebc5d';
  $pane = new stdClass();
  $pane->pid = 'new-a9879d2c-abf9-4af9-82cc-a75644db3b3a';
  $pane->panel = 'contentmain';
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
      'link' => 0,
      'bypass_access' => 0,
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
  $pane->uuid = 'a9879d2c-abf9-4af9-82cc-a75644db3b3a';
  $display->content['new-a9879d2c-abf9-4af9-82cc-a75644db3b3a'] = $pane;
  $display->panels['contentmain'][1] = 'new-a9879d2c-abf9-4af9-82cc-a75644db3b3a';
  $pane = new stdClass();
  $pane->pid = 'new-49eecf50-cd5c-4c35-9fb5-3bacdc1c1e4b';
  $pane->panel = 'contentmain';
  $pane->type = 'view_essay_link';
  $pane->subtype = 'view_essay_link';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'destination' => 'node',
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
  $pane->uuid = '49eecf50-cd5c-4c35-9fb5-3bacdc1c1e4b';
  $display->content['new-49eecf50-cd5c-4c35-9fb5-3bacdc1c1e4b'] = $pane;
  $display->panels['contentmain'][2] = 'new-49eecf50-cd5c-4c35-9fb5-3bacdc1c1e4b';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = '0';
  $panelizer->display = $display;
  $export['node:pece_essay:default:free_panel'] = $panelizer;

  return $export;
}
