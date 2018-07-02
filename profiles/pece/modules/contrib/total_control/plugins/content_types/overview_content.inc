<?php

/**
 * @file
 *
 * "Content overview" panels content type. Displays a summary of content 
 * statistics including: number pieces of each type of content, number of
 * comments, number of blocked comments (spam) and configuration links.
 *
 */
 
$plugin = array(
  'single' => TRUE,
  'title' => t('Overview - Content'),
  'defaults' => array('types' => array(), 'comments' => array(), 'spam' => 0),
  'icon' => 'cog.png',
  'description' => t('Displays a summary of content statistics including: 
    number pieces of each type of content, number of comments, number of 
    blocked comments (spam), and if ') . l(t('allowed'), 
    'admin/settings/total_control') . t(', content-type configuration links.'),
  'category' => t('Dashboard'),
  'edit text' => t('Configure'),
);

/**
 * 'Admin title' callback for the content type.
 */
function total_control_overview_content_content_type_admin_title($subtype = NULL, $conf = NULL, $context = NULL) {
  return t('Content overview');
}

/**
 * 'Admin info' callback for the content type.
 */
function total_control_overview_content_content_type_admin_info($subtype = NULL, $conf = NULL, $context = NULL) {
  $block = new stdClass();
  $block->title = t('Displays a summary of content statistics including: 
    number pieces of each type of content, number of comments, number of 
    blocked comments (spam), and if ') . l(t('allowed'), 
    'admin/config/control') . t(', content-type configuration links.');

  return $block;
}

/**
 * Run-time rendering of the body of the block.
 */
function total_control_overview_content_content_type_render($subtype, $conf, $panel_args, &$context) {
  $items = total_control_get_content_overview($conf);

  $block = new stdClass();
  $block->module = t('total_control');
  $block->title = total_control_overview_content_content_type_admin_title();
  $block->content = theme('total_control_overview_content', array('overview' => $items));

  return $block;
}

/**
 * 'Edit form' callback for the content type.
 */
function total_control_overview_content_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
  // Add content settings to form.
  total_control_add_content_pane_settings($form, $conf);

  return $form;
}

/**
 * 'Edit form' submit callback for the content type.
 */
function total_control_overview_content_content_type_edit_form_submit($form, &$form_state) {
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  } 
}
