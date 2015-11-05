<?php
/**
 * @file
 * pece_core.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function pece_core_default_page_manager_pages() {
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
  $display->layout = 'radix_boxton';
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
  $pane->pid = 'new-50a1accd-2ccd-4319-b127-15b29007da9d';
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
  $pane->style = array();
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '50a1accd-2ccd-4319-b127-15b29007da9d';
  $display->content['new-50a1accd-2ccd-4319-b127-15b29007da9d'] = $pane;
  $display->panels['contentmain'][0] = 'new-50a1accd-2ccd-4319-b127-15b29007da9d';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['pece_homepage'] = $page;

  return $pages;

}
