<?php

/**
 * @file
 *
 * "Site overview" panel pane. Displays a summary of both content and user 
 * statistics.
 *
 */

$plugin = array(
  'single' => TRUE,
  'title' => t('Overview - Content & User accounts'),
  'defaults' => array('types' => NULL, 'comments' => NULL, 'spam' => 1, 'user' => NULL, 'roles' => NULL),
  'icon' => 'cog.png',
  'description' => t('An overview of both content and users in one pane'),
  'category' => t('Dashboard'),
  'edit text' => t('Configure'),
);

/**
 * 'Admin title' callback for the content type.
 */
function total_control_overview_content_type_admin_title($subtype = NULL, $conf = NULL, $context = NULL) {
  return t('Content and User overview');
}

/**
 * 'Admin info' callback for the content type.
 */
function total_control_overview_content_type_admin_info($subtype = NULL, $conf = NULL, $context = NULL) {
  $block = new stdClass();
  $block->title = t('An overview of both content and users in one pane');

  return $block;
}

/**
 * Run-time rendering of the body of the block.
 */
function total_control_overview_content_type_render($subtype, $conf, $panel_args, &$context) {
  // Content Overview.
  $overview_cnt = total_control_get_content_overview($conf);

  // User Overview.  
  $overview_usr = array();
  $user_data = total_control_get_user_overview($conf);
  $users_all = format_plural($user_data['all'], '1 total user', '@count total users');
  $users_active = format_plural($user_data['active'], '1 active', '@count active');
  $users_blocked = format_plural($user_data['blocked'], '1 blocked', '@count blocked');
  $overview_usr[] = $users_all . ' | ' . $users_active . ' | ' . $users_blocked;

  // Roles Overview.
  foreach ($user_data['roles'] as $rid => $data) {
    $overview_usr['role_' . $rid] = format_plural($user_data['roles'][$rid]['count'], '1 user account', '@count user accounts');
    $overview_usr['role_' . $rid] .= ' with the role: ' . $user_data['roles'][$rid]['name'];
  } 

  $block = new stdClass();
  $block->module = t('total_control');
  $block->title = t('Content and User overview');
  $block->content = theme('total_control_overview', array('content' => $overview_cnt, 'users' => $overview_usr));

  return $block;
}

/**
 * 'Edit form' callback for the content type.
 */
function total_control_overview_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];  
  // Add content settings to form.
  total_control_add_content_pane_settings($form, $conf);
  // Add user settings to form.
  total_control_add_user_pane_settings($form, $conf);

  return $form;
}

/**
 * 'Edit form' submit callback for the content type.
 */
function total_control_overview_content_type_edit_form_submit($form, &$form_state) {
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}
