<?php
/**
 * @file
 * pece_homepage.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function pece_homepage_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'pece_homepage';
  $page->task = 'page';
  $page->admin_title = 'PECE Homepage';
  $page->admin_description = 'The default home page for PECE.';
  $page->path = 'home';
  $page->access = array();
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_pece_homepage__panel_context_77c9cc3c-508a-40f2-a077-e26300f3d1bc';
  $handler->task = 'page';
  $handler->subtask = 'pece_homepage';
  $handler->handler = 'panel_context';
  $handler->weight = 1;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'ipe',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => '',
  );
  $display = new panels_display();
  $display->layout = 'pece_single_column';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'contentmain' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '250eb6b6-0525-4d78-8dcb-74d461c55237';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-560f4d04-bb3b-4cbe-849d-bf9c24985c5b';
  $pane->panel = 'contentmain';
  $pane->type = 'views_panes';
  $pane->subtype = 'frontpage_image_slider-panel_pane_1';
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
    'style' => 'slider',
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '560f4d04-bb3b-4cbe-849d-bf9c24985c5b';
  $display->content['new-560f4d04-bb3b-4cbe-849d-bf9c24985c5b'] = $pane;
  $display->panels['contentmain'][0] = 'new-560f4d04-bb3b-4cbe-849d-bf9c24985c5b';
  $pane = new stdClass();
  $pane->pid = 'new-288c4df0-c9d8-4bfd-ab6b-0a76ef42dd9c';
  $pane->panel = 'contentmain';
  $pane->type = 'views_panes';
  $pane->subtype = 'pece_recent_groups-panel_pane_1';
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
  $pane->uuid = '288c4df0-c9d8-4bfd-ab6b-0a76ef42dd9c';
  $display->content['new-288c4df0-c9d8-4bfd-ab6b-0a76ef42dd9c'] = $pane;
  $display->panels['contentmain'][1] = 'new-288c4df0-c9d8-4bfd-ab6b-0a76ef42dd9c';
  $pane = new stdClass();
  $pane->pid = 'new-183fcc55-068e-452b-bffd-45dcc4711c15';
  $pane->panel = 'contentmain';
  $pane->type = 'views_panes';
  $pane->subtype = 'pece_recent_artifacts-panel_pane_1';
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
  $pane->position = 2;
  $pane->locks = array();
  $pane->uuid = '183fcc55-068e-452b-bffd-45dcc4711c15';
  $display->content['new-183fcc55-068e-452b-bffd-45dcc4711c15'] = $pane;
  $display->panels['contentmain'][2] = 'new-183fcc55-068e-452b-bffd-45dcc4711c15';
  $pane = new stdClass();
  $pane->pid = 'new-b855fa2f-0a4e-489a-9b09-95a85b6335a2';
  $pane->panel = 'contentmain';
  $pane->type = 'block';
  $pane->subtype = 'tagclouds-3';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
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
  $pane->uuid = 'b855fa2f-0a4e-489a-9b09-95a85b6335a2';
  $display->content['new-b855fa2f-0a4e-489a-9b09-95a85b6335a2'] = $pane;
  $display->panels['contentmain'][3] = 'new-b855fa2f-0a4e-489a-9b09-95a85b6335a2';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['pece_homepage'] = $page;

  return $pages;

}
