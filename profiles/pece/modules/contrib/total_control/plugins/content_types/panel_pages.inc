<?php

/**
 * @file
 *
 * "Panel Pages" panels content pane. It shows users with permissions the
 * panel pages on the site, and provides links directly to the "content" tab.
 *
 */

$plugin = array(
  'single' => TRUE,
  'title' => t('Admin - Panel Pages'),
  'defaults' => array(),
  'icon' => 'cog.png',
  'description' => t('Provides links to administer panel pages.'),
  'category' => t('Dashboard'),
  'edit text' => t('Configure'),
);

/**
 * 'Admin title' callback for the content type.
 */
function total_control_panel_pages_content_type_admin_title($subtype = NULL, $conf = NULL, $context = NULL) {
  return t('Administer Panel pages');
}

/**
 * 'Admin info' callback for the content type.
 */
function total_control_panel_pages_content_type_admin_info($subtype = NULL, $conf = NULL, $context = NULL) {
  $block = new stdClass();
  $block->title = t('Provides links to administer panel pages.');

  return $block;
}

/**
 * Run-time rendering of the body of the block.
 */
function total_control_panel_pages_content_type_render($subtype, $conf, $args, &$context) {
  $items = array();

  // Get panels pages.
  module_load_include('inc', 'page_manager', 'page_manager.admin');
  $tasks = page_manager_get_tasks_by_type('page');
  $pages = array('operations' => array());

  page_manager_get_pages($tasks, $pages);
  $count = 0; // TODO setting.

  $header = array('page' => t('Page'), 'options' => t('Operations'));
  $rows = array();

  foreach ($pages['rows'] as $id => $info) {
    // Only show enabled panels on the pane. // TODO: config setting?
    if (array_key_exists('data', $info['data']['operations'])
      && (stristr((string)$info['data']['operations']['data'], 'Enable') == FALSE)) {
      $rows[] = array(
        'data' => array(
          $info['data']['title'],
          $info['data']['operations'],
        ),
        'class' => $info['class'],
      );

      // Only show a certain number.
      if (++$count >= 10) {
        break;
      }
    }
  }

  // Build a link to the page manager UI.
  $link = '';
  if (user_access('use page manager')) {
    $link = l(t('Page manager administration'), 'admin/structure/pages');
  }

  $block = new stdClass();
  $block->title = t('Administer Panel pages');
  $block->module = t('total_control');
  $block->content = theme('total_control_admin_table', array('header' => $header, 'rows' => $rows, 'link' => $link));

  return $block;

}

/**
 * 'Edit form' callback for the content type.
 */
function total_control_panel_pages_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  return $form;
}

/**
 * 'Edit form' submit callback for the content type.
 */
function total_control_panel_pages_content_type_edit_form_submit($form, &$form_state) {
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}
