<?php
/**
 * @file
 * pece_frontpage_slideshow.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function pece_frontpage_slideshow_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'frontpage_image_slider';
  $view->description = '';
  $view->tag = 'PECE';
  $view->base_table = 'node';
  $view->human_name = 'PECE Frontpage Image Slider';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '8';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Image */
  $handler->display->display_options['fields']['field_pece_slideshow_image']['id'] = 'field_pece_slideshow_image';
  $handler->display->display_options['fields']['field_pece_slideshow_image']['table'] = 'field_data_field_pece_slideshow_image';
  $handler->display->display_options['fields']['field_pece_slideshow_image']['field'] = 'field_pece_slideshow_image';
  $handler->display->display_options['fields']['field_pece_slideshow_image']['label'] = '';
  $handler->display->display_options['fields']['field_pece_slideshow_image']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_pece_slideshow_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_pece_slideshow_image']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_pece_slideshow_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_pece_slideshow_image']['settings'] = array(
    'image_style' => '',
    'image_link' => '',
  );
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'frontpage_image_slideshow' => 'frontpage_image_slideshow',
  );

  /* Display: Content pane */
  $handler = $view->new_display('panel_pane', 'Content pane', 'panel_pane_1');
  $translatables['frontpage_image_slider'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Content pane'),
    t('View panes'),
  );
  $export['frontpage_image_slider'] = $view;

  return $export;
}
