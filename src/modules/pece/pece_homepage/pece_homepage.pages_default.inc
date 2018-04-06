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
  $display->layout = 'pece_douby_double';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'contentmain' => NULL,
      'sidebar' => NULL,
      'contentheader' => NULL,
      'contentcolumn1' => NULL,
      'contentcolumn2' => NULL,
      'sidebartop' => NULL,
      'sidebarbottom' => NULL,
      'contenttop' => NULL,
      'contentbottom' => NULL,
      'contentfooter' => NULL,
    ),
    'sidebar' => array(
      'style' => 'tabs',
    ),
    'contentfooter' => array(
      'style' => '0',
    ),
    'sidebartop' => array(
      'style' => 'tabs',
    ),
    'contenttop' => array(
      'style' => 'tabs',
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '250eb6b6-0525-4d78-8dcb-74d461c55237';
  $display->storage_type = 'page_manager';
  $display->storage_id = 'page_pece_homepage__panel_context_77c9cc3c-508a-40f2-a077-e26300f3d1bc';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-6f6492aa-2956-4da0-b39c-a6f4ed28a172';
  $pane->panel = 'contentbottom';
  $pane->type = 'views_panes';
  $pane->subtype = 'pece_essays-panel_pane_2';
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
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '6f6492aa-2956-4da0-b39c-a6f4ed28a172';
  $display->content['new-6f6492aa-2956-4da0-b39c-a6f4ed28a172'] = $pane;
  $display->panels['contentbottom'][0] = 'new-6f6492aa-2956-4da0-b39c-a6f4ed28a172';
  $pane = new stdClass();
  $pane->pid = 'new-ca214dea-68ff-4597-b5e6-e444ce6a481c';
  $pane->panel = 'contentfooter';
  $pane->type = 'block';
  $pane->subtype = 'pece_about-about_pece_summary';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
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
  $pane->uuid = 'ca214dea-68ff-4597-b5e6-e444ce6a481c';
  $display->content['new-ca214dea-68ff-4597-b5e6-e444ce6a481c'] = $pane;
  $display->panels['contentfooter'][0] = 'new-ca214dea-68ff-4597-b5e6-e444ce6a481c';
  $pane = new stdClass();
  $pane->pid = 'new-757136e6-933a-4425-971d-e1d6c863960a';
  $pane->panel = 'contentheader';
  $pane->type = 'views_panes';
  $pane->subtype = 'frontpage_image_slider-slideshow_front_short';
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
  $pane->uuid = '757136e6-933a-4425-971d-e1d6c863960a';
  $display->content['new-757136e6-933a-4425-971d-e1d6c863960a'] = $pane;
  $display->panels['contentheader'][0] = 'new-757136e6-933a-4425-971d-e1d6c863960a';
  $pane = new stdClass();
  $pane->pid = 'new-080e8884-7f4e-4925-84b0-4910b149a573';
  $pane->panel = 'contentheader';
  $pane->type = 'block';
  $pane->subtype = 'pece_about-about';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
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
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = '080e8884-7f4e-4925-84b0-4910b149a573';
  $display->content['new-080e8884-7f4e-4925-84b0-4910b149a573'] = $pane;
  $display->panels['contentheader'][1] = 'new-080e8884-7f4e-4925-84b0-4910b149a573';
  $pane = new stdClass();
  $pane->pid = 'new-66e4160f-20c2-4f90-92d8-4336eb549591';
  $pane->panel = 'contenttop';
  $pane->type = 'views_panes';
  $pane->subtype = 'pece_recent_essays-panel_pane_1';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'view_settings' => 'fields',
    'header_type' => 'none',
    'view_mode' => 'most_recent',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '66e4160f-20c2-4f90-92d8-4336eb549591';
  $display->content['new-66e4160f-20c2-4f90-92d8-4336eb549591'] = $pane;
  $display->panels['contenttop'][0] = 'new-66e4160f-20c2-4f90-92d8-4336eb549591';
  $pane = new stdClass();
  $pane->pid = 'new-3ba07e97-f81f-465f-8e85-4968c650e130';
  $pane->panel = 'contenttop';
  $pane->type = 'views_panes';
  $pane->subtype = 'pece_recent_artifacts-artifatcs_front_pane';
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
  $pane->uuid = '3ba07e97-f81f-465f-8e85-4968c650e130';
  $display->content['new-3ba07e97-f81f-465f-8e85-4968c650e130'] = $pane;
  $display->panels['contenttop'][1] = 'new-3ba07e97-f81f-465f-8e85-4968c650e130';
  $pane = new stdClass();
  $pane->pid = 'new-b855fa2f-0a4e-489a-9b09-95a85b6335a2';
  $pane->panel = 'sidebarbottom';
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
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = 'b855fa2f-0a4e-489a-9b09-95a85b6335a2';
  $display->content['new-b855fa2f-0a4e-489a-9b09-95a85b6335a2'] = $pane;
  $display->panels['sidebarbottom'][0] = 'new-b855fa2f-0a4e-489a-9b09-95a85b6335a2';
  $pane = new stdClass();
  $pane->pid = 'new-71089302-3df4-415c-a0d7-df52a7e874d3';
  $pane->panel = 'sidebartop';
  $pane->type = 'views_panes';
  $pane->subtype = 'pece_recent_groups-groups_front_pane';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'view_mode' => 'mini_teaser',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '71089302-3df4-415c-a0d7-df52a7e874d3';
  $display->content['new-71089302-3df4-415c-a0d7-df52a7e874d3'] = $pane;
  $display->panels['sidebartop'][0] = 'new-71089302-3df4-415c-a0d7-df52a7e874d3';
  $pane = new stdClass();
  $pane->pid = 'new-888d8c4c-a03c-41af-99d0-78c85c2e3452';
  $pane->panel = 'sidebartop';
  $pane->type = 'views_panes';
  $pane->subtype = 'pece_users-users_front_pane';
  $pane->shown = TRUE;
  $pane->access = array();
  $pane->configuration = array(
    'view_settings' => 'fields',
    'header_type' => 'titles',
    'view_mode' => 'full',
  );
  $pane->cache = array();
  $pane->style = array(
    'settings' => NULL,
  );
  $pane->css = array();
  $pane->extras = array();
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = '888d8c4c-a03c-41af-99d0-78c85c2e3452';
  $display->content['new-888d8c4c-a03c-41af-99d0-78c85c2e3452'] = $pane;
  $display->panels['sidebartop'][1] = 'new-888d8c4c-a03c-41af-99d0-78c85c2e3452';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['pece_homepage'] = $page;

  return $pages;

}
