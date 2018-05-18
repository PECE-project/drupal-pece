<?php
/**
 * @file
 * Providing extra functionality for the Site Notice UI via views.
 */

/**
 * Implements hook_views_data()
 */
function site_notice_views_data_alter(&$data) {
  $data['site_notice']['status']['field'] = array(
    'title' => t('Status'),
    'help' => t('The position the notice appears in if enabled.'),
    'handler' => 'site_notice_handler_status_field',
  );
  $data['site_notice']['status']['filter'] = array(
    'title' => t('Status'),
    'help' => t('The position the notice appears in if enabled.'),
    'handler' => 'site_notice_handler_status_filter',
  );


  $data['site_notice']['link_site_notice'] = array(
    'field' => array(
      'title' => t('Link'),
      'help' => t('Provide a link to the site notice.'),
      'handler' => 'site_notice_handler_link_field',
    ),
  );
  $data['site_notice']['edit_site_notice'] = array(
    'field' => array(
      'title' => t('Edit Link'),
      'help' => t('Provide a link to the edit form for the site notice.'),
      'handler' => 'site_notice_handler_edit_link_field',
    ),
  );
  $data['site_notice']['delete_site_notice'] = array(
    'field' => array(
      'title' => t('Delete Link'),
      'help' => t('Provide a link to delete the site notice.'),
      'handler' => 'site_notice_handler_delete_link_field',
    ),
  );
  $data['site_notice']['operations'] = array(
    'field' => array(
      'title' => t('Operations links'),
      'help' => t('Display all operations available for this notice.'),
      'handler' => 'site_notice_handler_site_notice_operations_field',
    ),
  );
  $data['site_notice']['enable_notice'] = array(
    'field' => array(
      'title' => t('Enable/Disable Link'),
      'help' => t('Provide a link to enable or disable the site notice.'),
      'handler' => 'site_notice_handler_enable_link_field',
    ),
  );
}

/**
 * Implements hook_views_default_views().
 */
function site_notice_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'site_notices';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'site_notice';
  $view->human_name = 'Site Notices';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Site Notices';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access administration pages';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '25';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['row_class'] = '[status_1]';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'status' => 'status',
    'created' => 'created',
    'changed' => 'changed',
    'link_site_notice' => 'link_site_notice',
    'edit_site_notice' => 'link_site_notice',
    'enable_notice' => 'link_site_notice',
    'delete_site_notice' => 'link_site_notice',
    'status_1' => 'status_1',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'changed' => array(
      'sortable' => 0,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'link_site_notice' => array(
      'align' => '',
      'separator' => ' | ',
      'empty_column' => 0,
    ),
    'edit_site_notice' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'enable_notice' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'delete_site_notice' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status_1' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  $handler->display->display_options['style_options']['empty_table'] = TRUE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'No Results';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'There are no notices that match this criteria.';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  /* Field: Site Notice: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'site_notice';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  /* Field: Site Notice: Status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'site_notice';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  /* Field: Site Notice: Date created */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'site_notice';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Created';
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  /* Field: Site Notice: Date changed */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'site_notice';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'Updated';
  $handler->display->display_options['fields']['changed']['date_format'] = 'short';
  /* Field: Site Notice: Link */
  $handler->display->display_options['fields']['link_site_notice']['id'] = 'link_site_notice';
  $handler->display->display_options['fields']['link_site_notice']['table'] = 'site_notice';
  $handler->display->display_options['fields']['link_site_notice']['field'] = 'link_site_notice';
  $handler->display->display_options['fields']['link_site_notice']['label'] = 'Operations';
  $handler->display->display_options['fields']['link_site_notice']['text'] = 'View';
  /* Field: Site Notice: Edit Link */
  $handler->display->display_options['fields']['edit_site_notice']['id'] = 'edit_site_notice';
  $handler->display->display_options['fields']['edit_site_notice']['table'] = 'site_notice';
  $handler->display->display_options['fields']['edit_site_notice']['field'] = 'edit_site_notice';
  $handler->display->display_options['fields']['edit_site_notice']['label'] = '';
  $handler->display->display_options['fields']['edit_site_notice']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['edit_site_notice']['text'] = 'Edit';
  /* Field: Site Notice: Enable/Disable Link */
  $handler->display->display_options['fields']['enable_notice']['id'] = 'enable_notice';
  $handler->display->display_options['fields']['enable_notice']['table'] = 'site_notice';
  $handler->display->display_options['fields']['enable_notice']['field'] = 'enable_notice';
  $handler->display->display_options['fields']['enable_notice']['label'] = '';
  $handler->display->display_options['fields']['enable_notice']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['enable_notice']['text_on'] = 'Disable';
  $handler->display->display_options['fields']['enable_notice']['text_off'] = 'Enable';
  /* Field: Site Notice: Delete Link */
  $handler->display->display_options['fields']['delete_site_notice']['id'] = 'delete_site_notice';
  $handler->display->display_options['fields']['delete_site_notice']['table'] = 'site_notice';
  $handler->display->display_options['fields']['delete_site_notice']['field'] = 'delete_site_notice';
  $handler->display->display_options['fields']['delete_site_notice']['label'] = '';
  $handler->display->display_options['fields']['delete_site_notice']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['delete_site_notice']['text'] = 'Delete';
  /* Field: Status token for row class */
  $handler->display->display_options['fields']['status_1']['id'] = 'status_1';
  $handler->display->display_options['fields']['status_1']['table'] = 'site_notice';
  $handler->display->display_options['fields']['status_1']['field'] = 'status';
  $handler->display->display_options['fields']['status_1']['ui_name'] = 'Status token for row class';
  $handler->display->display_options['fields']['status_1']['label'] = '';
  $handler->display->display_options['fields']['status_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['status_1']['element_label_colon'] = FALSE;
  /* Sort criterion: Site Notice: Date changed */
  $handler->display->display_options['sorts']['changed']['id'] = 'changed';
  $handler->display->display_options['sorts']['changed']['table'] = 'site_notice';
  $handler->display->display_options['sorts']['changed']['field'] = 'changed';
  $handler->display->display_options['sorts']['changed']['order'] = 'DESC';
  /* Filter criterion: Site Notice: Status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'site_notice';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['status']['expose']['label'] = 'Status';
  $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
  $handler->display->display_options['filters']['status']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );

  /* Display: Page: Content Listing */
  $handler = $view->new_display('page', 'Page: Content Listing', 'page');
  $handler->display->display_options['display_description'] = 'Full listing of all site notices.';
  $handler->display->display_options['path'] = 'admin/content/site-notices';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Site Notices';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'tab';
  $handler->display->display_options['tab_options']['title'] = 'Site Notices';
  $handler->display->display_options['tab_options']['description'] = 'Manage site notices.';
  $handler->display->display_options['tab_options']['weight'] = '0';

  $export['site_notices'] = $view;

  return $export;
}
