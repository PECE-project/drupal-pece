<?php
/**
 * @file
 * pece_profile.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function pece_profile_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'user_view__panel_context_user_page';
  $handler->task = 'user_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = -30;
  $handler->conf = array(
    'title' => 'User page',
    'no_blocks' => 0,
    'pipeline' => 'ipe',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => 'truco',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(
      0 => array(
        'identifier' => 'Profile2 from user',
        'keyword' => 'profile2',
        'name' => 'profile2_from_user',
        'type' => 'pece_profile_main',
        'context' => 'argument_entity_id:user_1',
        'id' => 1,
      ),
    ),
    'name' => '',
  );
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
  $display->title = '';
  $display->uuid = 'd3b04b95-e4af-43a4-9815-0072d240304b';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-0d66ad3f-43a9-4d70-82bf-7a348d281218';
  $pane->panel = 'content';
  $pane->type = 'entity_field';
  $pane->subtype = 'profile2:field_pece_location';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
    'formatter' => 'location_all',
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
  $pane->uuid = '0d66ad3f-43a9-4d70-82bf-7a348d281218';
  $display->content['new-0d66ad3f-43a9-4d70-82bf-7a348d281218'] = $pane;
  $display->panels['content'][0] = 'new-0d66ad3f-43a9-4d70-82bf-7a348d281218';
  $pane = new stdClass();
  $pane->pid = 'new-17ddb286-969c-4469-92bc-52a7f1b4ca15';
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
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = '17ddb286-969c-4469-92bc-52a7f1b4ca15';
  $display->content['new-17ddb286-969c-4469-92bc-52a7f1b4ca15'] = $pane;
  $display->panels['content'][1] = 'new-17ddb286-969c-4469-92bc-52a7f1b4ca15';
  $pane = new stdClass();
  $pane->pid = 'new-86e7610d-db3f-40ac-81f0-0c98ae5c3371';
  $pane->panel = 'content';
  $pane->type = 'entity_field';
  $pane->subtype = 'profile2:field_pece_biography';
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
  $pane->uuid = '86e7610d-db3f-40ac-81f0-0c98ae5c3371';
  $display->content['new-86e7610d-db3f-40ac-81f0-0c98ae5c3371'] = $pane;
  $display->panels['content'][2] = 'new-86e7610d-db3f-40ac-81f0-0c98ae5c3371';
  $pane = new stdClass();
  $pane->pid = 'new-b6796743-2ed4-4471-8c8b-23d0dae53068';
  $pane->panel = 'sidebar';
  $pane->type = 'entity_field';
  $pane->subtype = 'user:field_user_picture';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'label' => 'title',
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
  $pane->uuid = 'b6796743-2ed4-4471-8c8b-23d0dae53068';
  $display->content['new-b6796743-2ed4-4471-8c8b-23d0dae53068'] = $pane;
  $display->panels['sidebar'][0] = 'new-b6796743-2ed4-4471-8c8b-23d0dae53068';
  $pane = new stdClass();
  $pane->pid = 'new-b3dd7759-da2e-4f4a-adee-f4ef6579ef88';
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
  $pane->uuid = 'b3dd7759-da2e-4f4a-adee-f4ef6579ef88';
  $display->content['new-b3dd7759-da2e-4f4a-adee-f4ef6579ef88'] = $pane;
  $display->panels['sidebar'][1] = 'new-b3dd7759-da2e-4f4a-adee-f4ef6579ef88';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['user_view__panel_context_user_page'] = $handler;

  return $export;
}
