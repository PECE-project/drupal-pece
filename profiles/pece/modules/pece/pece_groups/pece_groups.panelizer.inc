<?php

/**
 * @file
 * pece_groups.panelizer.inc
 */

/**
 * Implements hook_panelizer_defaults().
 */
function pece_groups_panelizer_defaults() {
  $export = array();

  $panelizer = new stdClass();
  $panelizer->disabled = FALSE; /* Edit this to true to make a default panelizer disabled initially */
  $panelizer->api_version = 1;
  $panelizer->title = 'Default';
  $panelizer->panelizer_type = 'node';
  $panelizer->panelizer_key = 'pece_group';
  $panelizer->access = array();
  $panelizer->view_mode = 'page_manager';
  $panelizer->name = 'node:pece_group:default';
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
  $display->layout = 'pece_sidebar_right';
  $display->layout_settings = array(
    'sidebar' => array(
      'size' => 'col-md-8',
    ),
  );
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'sidebar' => NULL,
      'contentheader' => NULL,
      'contentcolumn1' => NULL,
      'contentcolumn2' => NULL,
      'contentfooter' => NULL,
      'content' => NULL,
    ),
    'content' => array(
      'style' => 'tabs',
    ),
  );
  $display->cache = array();
  $display->title = '%node:title';
  $display->uuid = 'b4c3d33e-c154-4059-952c-205805c5bd26';
  $display->storage_type = 'panelizer_default';
  $display->storage_id = 'node:pece_group:default';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-da3a554d-9286-4257-87ee-60945f7205a6';
  $pane->panel = 'content';
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
  $pane->uuid = 'da3a554d-9286-4257-87ee-60945f7205a6';
  $display->content['new-da3a554d-9286-4257-87ee-60945f7205a6'] = $pane;
  $display->panels['content'][0] = 'new-da3a554d-9286-4257-87ee-60945f7205a6';
  $pane = new stdClass();
  $pane->pid = 'new-978f5cdc-34de-4a57-ae97-adc4cdd1d352';
  $pane->panel = 'content';
  $pane->type = 'views_panes';
  $pane->subtype = 'child_groups-main';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'context' => array(
      0 => 'panelizer',
    ),
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
  $pane->uuid = '978f5cdc-34de-4a57-ae97-adc4cdd1d352';
  $display->content['new-978f5cdc-34de-4a57-ae97-adc4cdd1d352'] = $pane;
  $display->panels['content'][1] = 'new-978f5cdc-34de-4a57-ae97-adc4cdd1d352';
  $pane = new stdClass();
  $pane->pid = 'new-b54d0a10-862b-4dfe-ba1f-c793fe0b5b05';
  $pane->panel = 'content';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:og_group_ref';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
    'formatter' => 'entityreference_entity_view',
    'delta_limit' => '0',
    'delta_offset' => '0',
    'delta_reversed' => 0,
    'formatter_settings' => array(
      'link' => 1,
      'view_mode' => 'mini_teaser',
      'links' => 0,
    ),
    'context' => array(),
    'override_title' => 1,
    'override_title_text' => 'Parent groups',
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
  $pane->uuid = 'b54d0a10-862b-4dfe-ba1f-c793fe0b5b05';
  $display->content['new-b54d0a10-862b-4dfe-ba1f-c793fe0b5b05'] = $pane;
  $display->panels['content'][2] = 'new-b54d0a10-862b-4dfe-ba1f-c793fe0b5b05';
  $pane = new stdClass();
  $pane->pid = 'new-7798b8eb-06d7-4157-bd88-2cb73808b87a';
  $pane->panel = 'content';
  $pane->type = 'views_panes';
  $pane->subtype = 'pece_group_artifacts-panel_pane_1';
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
  $pane->position = 3;
  $pane->locks = array();
  $pane->uuid = '7798b8eb-06d7-4157-bd88-2cb73808b87a';
  $display->content['new-7798b8eb-06d7-4157-bd88-2cb73808b87a'] = $pane;
  $display->panels['content'][3] = 'new-7798b8eb-06d7-4157-bd88-2cb73808b87a';
  $pane = new stdClass();
  $pane->pid = 'new-9ac50c3a-d647-4db6-9917-fded9074b390';
  $pane->panel = 'content';
  $pane->type = 'views_panes';
  $pane->subtype = 'pece_group_memos-panel_pane_1';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'context' => array(
      0 => 'panelizer',
    ),
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
  $pane->position = 4;
  $pane->locks = array();
  $pane->uuid = '9ac50c3a-d647-4db6-9917-fded9074b390';
  $display->content['new-9ac50c3a-d647-4db6-9917-fded9074b390'] = $pane;
  $display->panels['content'][4] = 'new-9ac50c3a-d647-4db6-9917-fded9074b390';
  $pane = new stdClass();
  $pane->pid = 'new-a9177a5a-db7c-418e-bfa8-62b18010b5de';
  $pane->panel = 'content';
  $pane->type = 'views_panes';
  $pane->subtype = 'pece_group_field_diary-panel_pane_1';
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
  $pane->uuid = 'a9177a5a-db7c-418e-bfa8-62b18010b5de';
  $display->content['new-a9177a5a-db7c-418e-bfa8-62b18010b5de'] = $pane;
  $display->panels['content'][5] = 'new-a9177a5a-db7c-418e-bfa8-62b18010b5de';
  $pane = new stdClass();
  $pane->pid = 'new-3cd51d0e-9eb4-4c13-8f57-3c1dc0ca8935';
  $pane->panel = 'content';
  $pane->type = 'views_panes';
  $pane->subtype = 'pece_group_essays-panels_pane';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'view_settings' => 'rendered_entity',
    'header_type' => 'none',
    'view_mode' => 'mini_teaser',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 6;
  $pane->locks = array();
  $pane->uuid = '3cd51d0e-9eb4-4c13-8f57-3c1dc0ca8935';
  $display->content['new-3cd51d0e-9eb4-4c13-8f57-3c1dc0ca8935'] = $pane;
  $display->panels['content'][6] = 'new-3cd51d0e-9eb4-4c13-8f57-3c1dc0ca8935';
  $pane = new stdClass();
  $pane->pid = 'new-cd10a770-62ad-42d7-a128-12872c386dda';
  $pane->panel = 'sidebar';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:group_group';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'hidden',
    'formatter' => 'og_group_subscribe',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(
      'field_name' => 'og_user_node',
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
  $pane->uuid = 'cd10a770-62ad-42d7-a128-12872c386dda';
  $display->content['new-cd10a770-62ad-42d7-a128-12872c386dda'] = $pane;
  $display->panels['sidebar'][0] = 'new-cd10a770-62ad-42d7-a128-12872c386dda';
  $pane = new stdClass();
  $pane->pid = 'new-36b646b6-7ed2-477d-9aac-94cefa8a7ae5';
  $pane->panel = 'sidebar';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_media_image';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'hidden',
    'formatter' => 'file_rendered',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(
      'image_link' => '',
      'image_style' => '',
      'file_view_mode' => 'default',
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
  $pane->uuid = '36b646b6-7ed2-477d-9aac-94cefa8a7ae5';
  $display->content['new-36b646b6-7ed2-477d-9aac-94cefa8a7ae5'] = $pane;
  $display->panels['sidebar'][1] = 'new-36b646b6-7ed2-477d-9aac-94cefa8a7ae5';
  $pane = new stdClass();
  $pane->pid = 'new-f8ec13a1-a56d-453b-a928-808fa85c4eb4';
  $pane->panel = 'sidebar';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_project_ref';
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
    'context' => array(),
    'override_title' => 1,
    'override_title_text' => 'Projects',
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
  $pane->uuid = 'f8ec13a1-a56d-453b-a928-808fa85c4eb4';
  $display->content['new-f8ec13a1-a56d-453b-a928-808fa85c4eb4'] = $pane;
  $display->panels['sidebar'][2] = 'new-f8ec13a1-a56d-453b-a928-808fa85c4eb4';
  $pane = new stdClass();
  $pane->pid = 'new-147bf60e-4dea-4d25-b657-e75f17702188';
  $pane->panel = 'sidebar';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:group_email';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
    'formatter' => 'group_email',
    'delta_limit' => 0,
    'delta_offset' => '0',
    'delta_reversed' => FALSE,
    'formatter_settings' => array(),
    'context' => 'panelizer',
    'override_title' => 0,
    'override_title_text' => 'Email',
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
  $pane->uuid = '147bf60e-4dea-4d25-b657-e75f17702188';
  $display->content['new-147bf60e-4dea-4d25-b657-e75f17702188'] = $pane;
  $display->panels['sidebar'][3] = 'new-147bf60e-4dea-4d25-b657-e75f17702188';
  $pane = new stdClass();
  $pane->pid = 'new-a2336045-1156-4c77-8d7d-1b75cfb3ae46';
  $pane->panel = 'sidebar';
  $pane->type = 'entity_field';
  $pane->subtype = 'node:field_pece_substantive_logic';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
    'formatter' => 'og_list_default',
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
  $pane->position = 4;
  $pane->locks = array();
  $pane->uuid = 'a2336045-1156-4c77-8d7d-1b75cfb3ae46';
  $display->content['new-a2336045-1156-4c77-8d7d-1b75cfb3ae46'] = $pane;
  $display->panels['sidebar'][4] = 'new-a2336045-1156-4c77-8d7d-1b75cfb3ae46';
  $pane = new stdClass();
  $pane->pid = 'new-34af642e-2d59-4854-8cb0-4097d7998ef2';
  $pane->panel = 'sidebar';
  $pane->type = 'views_panes';
  $pane->subtype = 'pece_group_members-panel_pane_1';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'context' => array(
      0 => 'panelizer',
    ),
    'override_title' => '',
    'override_title_text' => '',
    'override_title_heading' => 'h2',
    'view_settings' => 'rendered_entity',
    'header_type' => 'none',
    'view_mode' => 'mini_teaser',
    'widget_title' => 'Members',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 5;
  $pane->locks = array();
  $pane->uuid = '34af642e-2d59-4854-8cb0-4097d7998ef2';
  $display->content['new-34af642e-2d59-4854-8cb0-4097d7998ef2'] = $pane;
  $display->panels['sidebar'][5] = 'new-34af642e-2d59-4854-8cb0-4097d7998ef2';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-da3a554d-9286-4257-87ee-60945f7205a6';
  $panelizer->display = $display;
  $export['node:pece_group:default'] = $panelizer;

  return $export;
}
