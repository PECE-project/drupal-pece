<?php

/**
 * @file
 * pece_essay.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function pece_essay_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'pece_essay_items';
  $page->task = 'page';
  $page->admin_title = 'PECE Essay items';
  $page->admin_description = 'PECE Essay items page.';
  $page->path = 'node/%node/essay';
  $page->access = array(
    'plugins' => array(
      0 => array(
        'context' => array(
          0 => 'logged-in-user',
          1 => 'argument_entity_id:node_1',
        ),
        'name' => 'node_access',
        'not' => FALSE,
        'settings' => array(
          'type' => 'view',
        ),
      ),
    ),
    'settings' => NULL,
    'type' => 'none',
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
  $handler->name = 'page_pece_essay_items__panel';
  $handler->task = 'page';
  $handler->subtask = 'pece_essay_items';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'body_classes_to_add' => '',
    'body_classes_to_remove' => '',
    'contexts' => array(),
    'css' => '',
    'css_id' => '',
    'name' => 'panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'relationships' => array(),
    'title' => 'Panel',
  );
  $display = new panels_display();
  $display->layout = 'pece_single_column';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'contentmain' => NULL,
      'default' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = 'a4f82d2e-9915-4954-a69f-efa53ae63412';
  $display->storage_type = 'page_manager';
  $display->storage_id = 'page_pece_essay_items__panel';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-407a69e2-f7a4-4225-b610-7ddfeb335175';
  $pane->panel = 'contentmain';
  $pane->type = 'entity_view';
  $pane->subtype = 'node';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'context' => 'argument_entity_id:node_1',
    'override_title' => 0,
    'override_title_heading' => 'h2',
    'override_title_text' => '',
    'view_mode' => 'free_panel',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '407a69e2-f7a4-4225-b610-7ddfeb335175';
  $display->content['new-407a69e2-f7a4-4225-b610-7ddfeb335175'] = $pane;
  $display->panels['contentmain'][0] = 'new-407a69e2-f7a4-4225-b610-7ddfeb335175';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['pece_essay_items'] = $page;

  return $pages;

}
