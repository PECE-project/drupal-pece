<?php
/**
 * @file
 * pece_timeline_essay.panelizer.inc
 */

/**
 * Implements hook_panelizer_defaults().
 */
function pece_timeline_essay_panelizer_defaults() {
  $export = array();

  $panelizer = new stdClass();
  $panelizer->disabled = FALSE; /* Edit this to true to make a default panelizer disabled initially */
  $panelizer->api_version = 1;
  $panelizer->title = 'Default';
  $panelizer->panelizer_type = 'node';
  $panelizer->panelizer_key = 'pece_timeline_essay';
  $panelizer->access = array();
  $panelizer->view_mode = 'page_manager';
  $panelizer->name = 'node:pece_timeline_essay:default';
  $panelizer->css_id = '';
  $panelizer->css_class = '';
  $panelizer->css = '';
  $panelizer->no_blocks = FALSE;
  $panelizer->title_element = 'H2';
  $panelizer->link_to_entity = TRUE;
  $panelizer->extra = array();
  $panelizer->pipeline = 'standard';
  $panelizer->contexts = array();
  $panelizer->relationships = array();
  $display = new panels_display();
  $display->layout = 'pece_sidebar_right';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'content' => NULL,
      'sidebar' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '%node:title';
  $display->uuid = 'a3e0917f-abeb-4b76-8706-235bccc5e0ba';
  $display->storage_type = 'panelizer_default';
  $display->storage_id = 'node:pece_timeline_essay:default';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-7df8b395-78e9-46dd-b417-b5405e45ace0';
  $pane->panel = 'content';
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
  $pane->uuid = '7df8b395-78e9-46dd-b417-b5405e45ace0';
  $display->content['new-7df8b395-78e9-46dd-b417-b5405e45ace0'] = $pane;
  $display->panels['content'][0] = 'new-7df8b395-78e9-46dd-b417-b5405e45ace0';
  $pane = new stdClass();
  $pane->pid = 'new-bfbdabdb-79e1-4f4c-a87f-1e9ba9c5bdab';
  $pane->panel = 'content';
  $pane->type = 'views_panes';
  $pane->subtype = 'pece_timeline_essay_items-panel_pane';
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
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = 'bfbdabdb-79e1-4f4c-a87f-1e9ba9c5bdab';
  $display->content['new-bfbdabdb-79e1-4f4c-a87f-1e9ba9c5bdab'] = $pane;
  $display->panels['content'][1] = 'new-bfbdabdb-79e1-4f4c-a87f-1e9ba9c5bdab';
  $pane = new stdClass();
  $pane->pid = 'new-32db6b75-f23c-4c92-969d-d36cadd1d74d';
  $pane->panel = 'content';
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
    'context' => array(),
    'override_title' => 0,
    'override_title_text' => '',
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
  $pane->uuid = '32db6b75-f23c-4c92-969d-d36cadd1d74d';
  $display->content['new-32db6b75-f23c-4c92-969d-d36cadd1d74d'] = $pane;
  $display->panels['content'][2] = 'new-32db6b75-f23c-4c92-969d-d36cadd1d74d';
  $pane = new stdClass();
  $pane->pid = 'new-ece9b0a7-735b-458f-8821-ba2f9159b7eb';
  $pane->panel = 'content';
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
  $pane->uuid = 'ece9b0a7-735b-458f-8821-ba2f9159b7eb';
  $display->content['new-ece9b0a7-735b-458f-8821-ba2f9159b7eb'] = $pane;
  $display->panels['content'][3] = 'new-ece9b0a7-735b-458f-8821-ba2f9159b7eb';
  $pane = new stdClass();
  $pane->pid = 'new-0ef1fc67-4591-4847-afae-c7ef1f118428';
  $pane->panel = 'content';
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
  $pane->uuid = '0ef1fc67-4591-4847-afae-c7ef1f118428';
  $display->content['new-0ef1fc67-4591-4847-afae-c7ef1f118428'] = $pane;
  $display->panels['content'][4] = 'new-0ef1fc67-4591-4847-afae-c7ef1f118428';
  $pane = new stdClass();
  $pane->pid = 'new-53009136-1d9c-4c5f-b1e6-a189bb13bc85';
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
  $pane->uuid = '53009136-1d9c-4c5f-b1e6-a189bb13bc85';
  $display->content['new-53009136-1d9c-4c5f-b1e6-a189bb13bc85'] = $pane;
  $display->panels['sidebar'][0] = 'new-53009136-1d9c-4c5f-b1e6-a189bb13bc85';
  $pane = new stdClass();
  $pane->pid = 'new-bbd7085a-ac37-43ed-bfdf-4a754308eac1';
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
  $pane->uuid = 'bbd7085a-ac37-43ed-bfdf-4a754308eac1';
  $display->content['new-bbd7085a-ac37-43ed-bfdf-4a754308eac1'] = $pane;
  $display->panels['sidebar'][1] = 'new-bbd7085a-ac37-43ed-bfdf-4a754308eac1';
  $pane = new stdClass();
  $pane->pid = 'new-23096cff-7118-4c8f-8a8b-9e538a1c7675';
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
  $pane->uuid = '23096cff-7118-4c8f-8a8b-9e538a1c7675';
  $display->content['new-23096cff-7118-4c8f-8a8b-9e538a1c7675'] = $pane;
  $display->panels['sidebar'][2] = 'new-23096cff-7118-4c8f-8a8b-9e538a1c7675';
  $pane = new stdClass();
  $pane->pid = 'new-c9337ac6-39cf-449e-a111-422a71cc1079';
  $pane->panel = 'sidebar';
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
  $pane->uuid = 'c9337ac6-39cf-449e-a111-422a71cc1079';
  $display->content['new-c9337ac6-39cf-449e-a111-422a71cc1079'] = $pane;
  $display->panels['sidebar'][3] = 'new-c9337ac6-39cf-449e-a111-422a71cc1079';
  $pane = new stdClass();
  $pane->pid = 'new-eb2c503a-41e8-414f-a3a5-962096d340ab';
  $pane->panel = 'sidebar';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_tags';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'above',
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
  $pane->uuid = 'eb2c503a-41e8-414f-a3a5-962096d340ab';
  $display->content['new-eb2c503a-41e8-414f-a3a5-962096d340ab'] = $pane;
  $display->panels['sidebar'][4] = 'new-eb2c503a-41e8-414f-a3a5-962096d340ab';
  $pane = new stdClass();
  $pane->pid = 'new-0e0597c6-b425-45e2-afcd-6186d1c561ad';
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
  $pane->uuid = '0e0597c6-b425-45e2-afcd-6186d1c561ad';
  $display->content['new-0e0597c6-b425-45e2-afcd-6186d1c561ad'] = $pane;
  $display->panels['sidebar'][5] = 'new-0e0597c6-b425-45e2-afcd-6186d1c561ad';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $panelizer->display = $display;
  $export['node:pece_timeline_essay:default'] = $panelizer;

  return $export;
}
