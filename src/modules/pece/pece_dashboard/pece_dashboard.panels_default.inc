<?php

/**
 * @file
 * pece_dashboard.panels_default.inc
 */

/**
 * Implements hook_default_panels_mini().
 */
function pece_dashboard_default_panels_mini() {
  $export = array();

  $mini = new stdClass();
  $mini->disabled = FALSE; /* Edit this to true to make a default mini disabled initially */
  $mini->api_version = 1;
  $mini->name = 'pece_dashb_tab_pece_essay';
  $mini->category = 'PECE';
  $mini->admin_title = 'PECE Dashboard Tab PECE Essay';
  $mini->admin_description = '';
  $mini->requiredcontexts = array();
  $mini->contexts = array(
    0 => array(
      'identifier' => 'User',
      'keyword' => 'user_2',
      'name' => 'user',
      'type' => 'current',
      'uid' => '',
      'id' => 1,
    ),
  );
  $mini->relationships = array();
  $display = new panels_display();
  $display->layout = 'pece_single_column';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'left' => NULL,
      'right' => NULL,
      'contentmain' => array(
        'active' => '0',
        'heightStyle' => 'content',
        'collapsible' => 1,
        'event' => 'click',
        'navigation' => TRUE,
      ),
      'column1' => NULL,
      'column2' => NULL,
    ),
    'contentmain' => array(
      'style' => 'panopoly_accordion',
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = 'd7f2cf53-ac5b-40d3-a484-6f0cc957328c';
  $display->storage_type = 'panels_mini';
  $display->storage_id = 'pece_dashb_tab_pece_essay';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-8c6664e5-a7ab-431d-8c4a-ef7c4bd926dc';
  $pane->panel = 'contentmain';
  $pane->type = 'views_panes';
  $pane->subtype = 'pece_my_essays-panel_pane_1';
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
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '8c6664e5-a7ab-431d-8c4a-ef7c4bd926dc';
  $display->content['new-8c6664e5-a7ab-431d-8c4a-ef7c4bd926dc'] = $pane;
  $display->panels['contentmain'][0] = 'new-8c6664e5-a7ab-431d-8c4a-ef7c4bd926dc';
  $pane = new stdClass();
  $pane->pid = 'new-63cc7ff5-0782-47ee-8bc5-22375a2be02b';
  $pane->panel = 'contentmain';
  $pane->type = 'views_panes';
  $pane->subtype = 'pece_my_essay_contrib-panel_pane_1';
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
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = '63cc7ff5-0782-47ee-8bc5-22375a2be02b';
  $display->content['new-63cc7ff5-0782-47ee-8bc5-22375a2be02b'] = $pane;
  $display->panels['contentmain'][1] = 'new-63cc7ff5-0782-47ee-8bc5-22375a2be02b';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-8c6664e5-a7ab-431d-8c4a-ef7c4bd926dc';
  $mini->display = $display;
  $export['pece_dashb_tab_pece_essay'] = $mini;

  $mini = new stdClass();
  $mini->disabled = FALSE; /* Edit this to true to make a default mini disabled initially */
  $mini->api_version = 1;
  $mini->name = 'pece_dashb_tab_photo_essay';
  $mini->category = 'PECE';
  $mini->admin_title = 'PECE Dashboard Tab Photo Essay';
  $mini->admin_description = '';
  $mini->requiredcontexts = array();
  $mini->contexts = array(
    0 => array(
      'identifier' => 'User',
      'keyword' => 'user_2',
      'name' => 'user',
      'type' => 'current',
      'uid' => '',
      'id' => 1,
    ),
  );
  $mini->relationships = array();
  $display = new panels_display();
  $display->layout = 'pece_single_column';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'left' => NULL,
      'right' => NULL,
      'contentmain' => array(
        'active' => '0',
        'heightStyle' => 'content',
        'collapsible' => 1,
        'event' => 'click',
        'navigation' => TRUE,
      ),
      'column1' => NULL,
      'column2' => NULL,
    ),
    'contentmain' => array(
      'style' => 'panopoly_accordion',
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = 'd7f2cf53-ac5b-40d3-a484-6f0cc957328c';
  $display->storage_type = 'panels_mini';
  $display->storage_id = 'pece_dashb_tab_photo_essay';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-ff9f3d66-ac3a-4dd5-a7d0-2f00a277e451';
  $pane->panel = 'contentmain';
  $pane->type = 'views_panes';
  $pane->subtype = 'pece_my_photo_essays-panel_pane_1';
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
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = 'ff9f3d66-ac3a-4dd5-a7d0-2f00a277e451';
  $display->content['new-ff9f3d66-ac3a-4dd5-a7d0-2f00a277e451'] = $pane;
  $display->panels['contentmain'][0] = 'new-ff9f3d66-ac3a-4dd5-a7d0-2f00a277e451';
  $pane = new stdClass();
  $pane->pid = 'new-e85615fb-894e-4cfb-b075-cf86a011fcd4';
  $pane->panel = 'contentmain';
  $pane->type = 'views_panes';
  $pane->subtype = 'pece_my_photo_essay_contrib-panel_pane_1';
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
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = 'e85615fb-894e-4cfb-b075-cf86a011fcd4';
  $display->content['new-e85615fb-894e-4cfb-b075-cf86a011fcd4'] = $pane;
  $display->panels['contentmain'][1] = 'new-e85615fb-894e-4cfb-b075-cf86a011fcd4';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $mini->display = $display;
  $export['pece_dashb_tab_photo_essay'] = $mini;

  $mini = new stdClass();
  $mini->disabled = FALSE; /* Edit this to true to make a default mini disabled initially */
  $mini->api_version = 1;
  $mini->name = 'pece_dashb_tab_timeline_essay';
  $mini->category = 'PECE';
  $mini->admin_title = 'PECE Dashboard Tab Timeline Essay';
  $mini->admin_description = '';
  $mini->requiredcontexts = array();
  $mini->contexts = array(
    0 => array(
      'identifier' => 'User',
      'keyword' => 'user_2',
      'name' => 'user',
      'type' => 'current',
      'uid' => '',
      'id' => 1,
    ),
  );
  $mini->relationships = array();
  $display = new panels_display();
  $display->layout = 'pece_single_column';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'left' => NULL,
      'right' => NULL,
      'contentmain' => array(
        'active' => '0',
        'heightStyle' => 'content',
        'collapsible' => 1,
        'event' => 'click',
        'navigation' => TRUE,
      ),
      'column1' => NULL,
      'column2' => NULL,
    ),
    'contentmain' => array(
      'style' => 'panopoly_accordion',
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = 'd7f2cf53-ac5b-40d3-a484-6f0cc957328c';
  $display->storage_type = 'panels_mini';
  $display->storage_id = 'pece_dashb_tab_timeline_essay';
  $display->content = array();
  $display->panels = array();
  $pane = new stdClass();
  $pane->pid = 'new-70659719-e31f-41f0-a7b4-a5e83e2d41c2';
  $pane->panel = 'contentmain';
  $pane->type = 'views_panes';
  $pane->subtype = 'pece_my_timeline_essays-panel_pane_1';
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
  $pane->position = 0;
  $pane->locks = array();
  $pane->uuid = '70659719-e31f-41f0-a7b4-a5e83e2d41c2';
  $display->content['new-70659719-e31f-41f0-a7b4-a5e83e2d41c2'] = $pane;
  $display->panels['contentmain'][0] = 'new-70659719-e31f-41f0-a7b4-a5e83e2d41c2';
  $pane = new stdClass();
  $pane->pid = 'new-39d7304d-e431-4233-9898-7a57b253ee7f';
  $pane->panel = 'contentmain';
  $pane->type = 'views_panes';
  $pane->subtype = 'pece_my_timeline_essay_contrib-panel_pane_1';
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
  $pane->position = 1;
  $pane->locks = array();
  $pane->uuid = '39d7304d-e431-4233-9898-7a57b253ee7f';
  $display->content['new-39d7304d-e431-4233-9898-7a57b253ee7f'] = $pane;
  $display->panels['contentmain'][1] = 'new-39d7304d-e431-4233-9898-7a57b253ee7f';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $mini->display = $display;
  $export['pece_dashb_tab_timeline_essay'] = $mini;

  return $export;
}
