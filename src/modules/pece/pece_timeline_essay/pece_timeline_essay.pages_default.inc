<?php

/**
 * @file
 * pece_timeline_essay.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function pece_timeline_essay_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'pece_timeline_essay_items';
  $page->task = 'page';
  $page->admin_title = 'PECE Timeline Essay Items';
  $page->admin_description = 'PECE Timeline Essay Items Page';
  $page->path = 'node/%node/timeline';
  $page->access = array(
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array();
  $page->arguments = array(
    'node' => array(
      'id' => 1,
      'identifier' => 'Node: ID',
      'name' => 'entity_id:node',
      'settings' => array(),
    ),
  );
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_pece_timeline_essay_items__panel';
  $handler->task = 'page';
  $handler->subtask = 'pece_timeline_essay_items';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'name' => 'panel',
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
  $display->uuid = 'be6612a9-dd82-420c-bb66-11f36e430c57';
  $display->storage_type = 'page_manager';
  $display->storage_id = 'page_pece_timeline_essay_items__panel';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-d1fa258b-22b9-45b9-931f-e7c6d8504e7c';
  $pane->panel = 'contentmain';
  $pane->type = 'entity_view';
  $pane->subtype = 'node';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'view_mode' => 'free_panel',
    'context' => 'argument_entity_id:node_1',
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
  $pane->uuid = 'd1fa258b-22b9-45b9-931f-e7c6d8504e7c';
  $display->content['new-d1fa258b-22b9-45b9-931f-e7c6d8504e7c'] = $pane;
  $display->panels['contentmain'][0] = 'new-d1fa258b-22b9-45b9-931f-e7c6d8504e7c';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['pece_timeline_essay_items'] = $page;

  return $pages;

}
