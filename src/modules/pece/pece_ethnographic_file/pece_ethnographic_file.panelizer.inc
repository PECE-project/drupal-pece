<?php
/**
 * @file
 * pece_ethnographic_file.panelizer.inc
 */

/**
 * Implements hook_panelizer_defaults().
 */
function pece_ethnographic_file_panelizer_defaults() {
  $export = array();

  $panelizer = new stdClass();
  $panelizer->disabled = FALSE; /* Edit this to true to make a default panelizer disabled initially */
  $panelizer->api_version = 1;
  $panelizer->name = 'node:pece_ethnographic_file:default';
  $panelizer->title = 'Default';
  $panelizer->panelizer_type = 'node';
  $panelizer->panelizer_key = 'pece_ethnographic_file';
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
  $display->uuid = '72f21b63-b09a-41d9-92c4-07b845d38d1f';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-89a292e4-07f9-4fc3-93b2-e94df2e6b927';
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
  $pane->uuid = '89a292e4-07f9-4fc3-93b2-e94df2e6b927';
  $display->content['new-89a292e4-07f9-4fc3-93b2-e94df2e6b927'] = $pane;
  $display->panels['column1'][0] = 'new-89a292e4-07f9-4fc3-93b2-e94df2e6b927';
  $pane = new stdClass();
  $pane->pid = 'new-024f4cbd-6ced-4b30-ad0c-2897949116dd';
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
  $pane->uuid = '024f4cbd-6ced-4b30-ad0c-2897949116dd';
  $display->content['new-024f4cbd-6ced-4b30-ad0c-2897949116dd'] = $pane;
  $display->panels['column1'][1] = 'new-024f4cbd-6ced-4b30-ad0c-2897949116dd';
  $pane = new stdClass();
  $pane->pid = 'new-9bc811d5-df0b-42af-8a41-8d45ecc9df0a';
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
  $pane->uuid = '9bc811d5-df0b-42af-8a41-8d45ecc9df0a';
  $display->content['new-9bc811d5-df0b-42af-8a41-8d45ecc9df0a'] = $pane;
  $display->panels['column1'][2] = 'new-9bc811d5-df0b-42af-8a41-8d45ecc9df0a';
  $pane = new stdClass();
  $pane->pid = 'new-115575c1-e4a9-42df-83d2-0f31033fa466';
  $pane->panel = 'column1';
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
  $pane->position = 3;
  $pane->locks = array();
  $pane->uuid = '115575c1-e4a9-42df-83d2-0f31033fa466';
  $display->content['new-115575c1-e4a9-42df-83d2-0f31033fa466'] = $pane;
  $display->panels['column1'][3] = 'new-115575c1-e4a9-42df-83d2-0f31033fa466';
  $pane = new stdClass();
  $pane->pid = 'new-5c2c611f-1174-46d6-89ab-15fd2ecbe1ed';
  $pane->panel = 'column2';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_thumbnail';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'hidden',
    'formatter' => 'image',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(
      'image_style' => '',
      'image_link' => '',
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
  $pane->uuid = '5c2c611f-1174-46d6-89ab-15fd2ecbe1ed';
  $display->content['new-5c2c611f-1174-46d6-89ab-15fd2ecbe1ed'] = $pane;
  $display->panels['column2'][0] = 'new-5c2c611f-1174-46d6-89ab-15fd2ecbe1ed';
  $pane = new stdClass();
  $pane->pid = 'new-9a78d626-4665-4aab-b9b4-48ef8ac5f1e3';
  $pane->panel = 'column2';
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
  $pane->uuid = '9a78d626-4665-4aab-b9b4-48ef8ac5f1e3';
  $display->content['new-9a78d626-4665-4aab-b9b4-48ef8ac5f1e3'] = $pane;
  $display->panels['column2'][1] = 'new-9a78d626-4665-4aab-b9b4-48ef8ac5f1e3';
  $pane = new stdClass();
  $pane->pid = 'new-32b24b4b-b832-4f32-9d44-73508dfeb48b';
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
  $pane->uuid = '32b24b4b-b832-4f32-9d44-73508dfeb48b';
  $display->content['new-32b24b4b-b832-4f32-9d44-73508dfeb48b'] = $pane;
  $display->panels['column2'][2] = 'new-32b24b4b-b832-4f32-9d44-73508dfeb48b';
  $pane = new stdClass();
  $pane->pid = 'new-36382d2c-2136-4885-a305-c4b9301dd90c';
  $pane->panel = 'column2';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:og_group_ref';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
    'formatter' => 'og_list_default',
    'delta_limit' => '0',
    'delta_offset' => '0',
    'delta_reversed' => 0,
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
  $pane->uuid = '36382d2c-2136-4885-a305-c4b9301dd90c';
  $display->content['new-36382d2c-2136-4885-a305-c4b9301dd90c'] = $pane;
  $display->panels['column2'][3] = 'new-36382d2c-2136-4885-a305-c4b9301dd90c';
  $pane = new stdClass();
  $pane->pid = 'new-7d30b425-f2bf-43e6-b405-58bccfb8d1dc';
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
  $pane->uuid = '7d30b425-f2bf-43e6-b405-58bccfb8d1dc';
  $display->content['new-7d30b425-f2bf-43e6-b405-58bccfb8d1dc'] = $pane;
  $display->panels['column2'][4] = 'new-7d30b425-f2bf-43e6-b405-58bccfb8d1dc';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-36382d2c-2136-4885-a305-c4b9301dd90c';
  $panelizer->display = $display;
  $export['node:pece_ethnographic_file:default'] = $panelizer;

  return $export;
}
