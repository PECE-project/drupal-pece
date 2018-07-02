<?php

/**
 * @file pece_admin.pages_default.inc
 *
 * Default panel page for the PECE Admin Dashboard.
 *
 */

/**
 * Implements hook_default_page_manager_pages()
 *
 * PECE Admin Dashboard variant to override Total Control defaults.
 */
function pece_admin_default_page_manager_handlers() {
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_dashboard__pece-admin-dashboard';
  $handler->task = 'page';
  $handler->subtask = 'dashboard';
  $handler->handler = 'panel_context';
  $handler->weight = -2;
  $handler->conf = array(
    'title' => 'PECE Admin Dashboard',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'name' => 'pece-admin-dashboard',
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'role',
          'settings' => array(
            'rids' => array(
              0 => 3,
            ),
          ),
          'context' => 'logged-in-user',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = 'twocol_stacked';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'middle' => NULL,
      'top' => NULL,
      'left' => NULL,
      'right' => NULL,
      'bottom' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = 'Dashboard';
  $display->uuid = '5625033c-7ecb-4000-94aa-eab886720f53';
  $display->storage_type = 'page_manager';
  $display->storage_id = 'page_dashboard__pece-admin-dashboard';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-f01630c0-1af8-4c8e-8e65-3812698d5971';
  $pane->panel = 'left';
  $pane->type = 'views_panes';
  $pane->subtype = 'control_users_panes-pane_tc_new_users';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'items_per_page' => '10',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = 'f01630c0-1af8-4c8e-8e65-3812698d5971';
  $display->content['new-f01630c0-1af8-4c8e-8e65-3812698d5971'] = $pane;
  $display->panels['left'][0] = 'new-f01630c0-1af8-4c8e-8e65-3812698d5971';
  $pane = new stdClass();
  $pane->pid = 'new-9e0a7392-4e02-4d9e-ad8d-4d3d8743d6c2';
  $pane->panel = 'left';
  $pane->type = 'views_panes';
  $pane->subtype = 'control_content_panes-pane_tc_new';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'items_per_page' => '10',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 1;
  $pane->locks = '';
  $pane->uuid = '9e0a7392-4e02-4d9e-ad8d-4d3d8743d6c2';
  $display->content['new-9e0a7392-4e02-4d9e-ad8d-4d3d8743d6c2'] = $pane;
  $display->panels['left'][1] = 'new-9e0a7392-4e02-4d9e-ad8d-4d3d8743d6c2';
  $pane = new stdClass();
  $pane->pid = 'new-f33de7fb-6fbd-441b-aadc-f2172b4662d9';
  $pane->panel = 'right';
  $pane->type = 'overview_content';
  $pane->subtype = 'overview_content';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'types' => array(
      'article' => 'article',
      'page' => 'page',
      'project' => 'project',
      'video' => 'video',
    ),
    'comments' => array(
      'article' => 'article',
      'page' => 0,
      'project' => 0,
      'video' => 0,
    ),
    'spam' => 0,
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = '';
  $pane->uuid = 'f33de7fb-6fbd-441b-aadc-f2172b4662d9';
  $display->content['new-f33de7fb-6fbd-441b-aadc-f2172b4662d9'] = $pane;
  $display->panels['right'][0] = 'new-f33de7fb-6fbd-441b-aadc-f2172b4662d9';
  $pane = new stdClass();
  $pane->pid = 'new-f89feb93-9a9e-41ea-bcb1-7b7084721d42';
  $pane->panel = 'right';
  $pane->type = 'create';
  $pane->subtype = 'create';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'types' => array(
      'article' => 'article',
      'project' => 'project',
      'page' => 0,
    ),
    'override_title' => 0,
    'override_title_text' => '',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 1;
  $pane->locks = '';
  $pane->uuid = 'f89feb93-9a9e-41ea-bcb1-7b7084721d42';
  $display->content['new-f89feb93-9a9e-41ea-bcb1-7b7084721d42'] = $pane;
  $display->panels['right'][1] = 'new-f89feb93-9a9e-41ea-bcb1-7b7084721d42';
  $pane = new stdClass();
  $pane->pid = 'new-7f08602b-0dde-46cf-ba0e-eec99b5272a4';
  $pane->panel = 'right';
  $pane->type = 'menus';
  $pane->subtype = 'menus';
  $pane->shown = FALSE;
  $pane->access = array();
  $pane->configuration = array(
    'item1' => NULL,
    'item2' => NULL,
    'override_title' => 0,
    'override_title_text' => '',
    'menus' => array(
      'main-menu' => 'main-menu',
      'navigation' => 'navigation',
      'devel' => 0,
      'management' => 0,
      'user-menu' => 0,
    ),
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 2;
  $pane->locks = '';
  $pane->uuid = '7f08602b-0dde-46cf-ba0e-eec99b5272a4';
  $display->content['new-7f08602b-0dde-46cf-ba0e-eec99b5272a4'] = $pane;
  $display->panels['right'][2] = 'new-7f08602b-0dde-46cf-ba0e-eec99b5272a4';
  $pane = new stdClass();
  $pane->pid = 'new-bc784d1e-0b7d-43c3-9612-9e17b6c77a6d';
  $pane->panel = 'right';
  $pane->type = 'node_types';
  $pane->subtype = 'node_types';
  $pane->shown = FALSE;
  $pane->access = array();
  $pane->configuration = array(
    'types' => array(
      'article' => 'article',
      'page' => 'page',
      'project' => 'project',
      'video' => 'video',
    ),
    'override_title' => 0,
    'override_title_text' => '',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 3;
  $pane->locks = '';
  $pane->uuid = 'bc784d1e-0b7d-43c3-9612-9e17b6c77a6d';
  $display->content['new-bc784d1e-0b7d-43c3-9612-9e17b6c77a6d'] = $pane;
  $display->panels['right'][3] = 'new-bc784d1e-0b7d-43c3-9612-9e17b6c77a6d';
  $pane = new stdClass();
  $pane->pid = 'new-3e3b9307-cc42-4cc0-84c5-6e39e91b430c';
  $pane->panel = 'right';
  $pane->type = 'taxonomy';
  $pane->subtype = 'taxonomy';
  $pane->shown = FALSE;
  $pane->access = array();
  $pane->configuration = array(
    'vids' => array(
      0 => '2',
      1 => '1',
    ),
    'override_title' => 0,
    'override_title_text' => '',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 4;
  $pane->locks = '';
  $pane->uuid = '3e3b9307-cc42-4cc0-84c5-6e39e91b430c';
  $display->content['new-3e3b9307-cc42-4cc0-84c5-6e39e91b430c'] = $pane;
  $display->panels['right'][4] = 'new-3e3b9307-cc42-4cc0-84c5-6e39e91b430c';
  $pane = new stdClass();
  $pane->pid = 'new-03d675f6-fe9f-487d-aab3-64ab6dde6ea7';
  $pane->panel = 'right';
  $pane->type = 'panel_pages';
  $pane->subtype = 'panel_pages';
  $pane->shown = FALSE;
  $pane->access = array();
  $pane->configuration = array(
    'item1' => NULL,
    'item2' => NULL,
    'override_title' => 0,
    'override_title_text' => '',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 5;
  $pane->locks = '';
  $pane->uuid = '03d675f6-fe9f-487d-aab3-64ab6dde6ea7';
  $display->content['new-03d675f6-fe9f-487d-aab3-64ab6dde6ea7'] = $pane;
  $display->panels['right'][5] = 'new-03d675f6-fe9f-487d-aab3-64ab6dde6ea7';
  $pane = new stdClass();
  $pane->pid = 'new-79421119-3bf0-4793-bd21-714e1d58491b';
  $pane->panel = 'top';
  $pane->type = 'welcome';
  $pane->subtype = 'welcome';
  $pane->shown = FALSE;
  $pane->access = array();
  $pane->configuration = array();
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = '';
  $pane->uuid = '79421119-3bf0-4793-bd21-714e1d58491b';
  $display->content['new-79421119-3bf0-4793-bd21-714e1d58491b'] = $pane;
  $display->panels['top'][0] = 'new-79421119-3bf0-4793-bd21-714e1d58491b';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;

  return array($handler->name => $handler);
}