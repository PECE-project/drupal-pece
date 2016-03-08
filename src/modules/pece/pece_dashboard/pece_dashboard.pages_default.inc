<?php
/**
 * @file
 * pece_dashboard.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function pece_dashboard_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'dashboard';
  $page->task = 'page';
  $page->admin_title = 'Dashboard';
  $page->admin_description = '';
  $page->path = 'dashboard';
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
  $handler->name = 'page_dashboard__panel';
  $handler->task = 'page';
  $handler->subtask = 'dashboard';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'ipe',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(
      0 => array(
        'identifier' => 'User',
        'keyword' => 'user',
        'name' => 'user',
        'type' => 'current',
        'uid' => '',
        'id' => 1,
      ),
    ),
    'relationships' => array(),
    'name' => 'panel',
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
    'content' => array(
      'style' => 'tabs',
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = 'eb338d0e-e9ec-44fb-b82f-819311de351b';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-db335407-5445-4bcc-aa52-49eb2cec2495';
  $pane->panel = 'content';
  $pane->type = 'views_panes';
  $pane->subtype = 'pece_my_groups-panel_pane_1';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'context' => array(
      0 => 'context_user_1',
    ),
    'view_settings' => 'fields',
    'header_type' => 'none',
    'view_mode' => FALSE,
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = 'db335407-5445-4bcc-aa52-49eb2cec2495';
  $display->content['new-db335407-5445-4bcc-aa52-49eb2cec2495'] = $pane;
  $display->panels['content'][0] = 'new-db335407-5445-4bcc-aa52-49eb2cec2495';
  $pane = new stdClass();
  $pane->pid = 'new-0fdeb287-7a3c-4ae7-bcbc-3e875e8102f6';
  $pane->panel = 'content';
  $pane->type = 'views_panes';
  $pane->subtype = 'pece_my_projects-panel_pane_1';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'view_settings' => 'fields',
    'header_type' => 'none',
    'view_mode' => FALSE,
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = '0fdeb287-7a3c-4ae7-bcbc-3e875e8102f6';
  $display->content['new-0fdeb287-7a3c-4ae7-bcbc-3e875e8102f6'] = $pane;
  $display->panels['content'][1] = 'new-0fdeb287-7a3c-4ae7-bcbc-3e875e8102f6';
  $pane = new stdClass();
  $pane->pid = 'new-caf5f999-9044-4367-b67a-90d64065cf2b';
  $pane->panel = 'content';
  $pane->type = 'views_panes';
  $pane->subtype = 'pece_my_artifacts-panel_pane_1';
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
  $pane->position = 2;
  $pane->locks = array();
  $pane->uuid = 'caf5f999-9044-4367-b67a-90d64065cf2b';
  $display->content['new-caf5f999-9044-4367-b67a-90d64065cf2b'] = $pane;
  $display->panels['content'][2] = 'new-caf5f999-9044-4367-b67a-90d64065cf2b';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['dashboard'] = $page;

  return $pages;

}
