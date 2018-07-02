<?php

/**
 * @file
 *
 * "User overview" content type. Displays a summary of user statistics 
 * including: number of total users, active users, blocked users, and 
 * users in each role.
 *
 */

$plugin = array(
  'single' => TRUE,
  'title' => t('Overview - User accounts'),
  'defaults' => array('user' => NULL, 'roles' => NULL),
  'icon' => 'cog.png',
  'description' => t('Displays a summary of user statistics including: number 
    of total users, active users, blocked users, and users in each role.'),
  'category' => t('Dashboard'),
  'edit text' => t('Configure'),
);

/**
 * 'Admin title' callback for the content type.
 */
function total_control_overview_user_content_type_admin_title($subtype = NULL, $conf = NULL, $context = NULL) {
  return t('Overview of user accounts');
}

/**
 * 'Admin info' callback for the content type.
 */
function total_control_overview_user_content_type_admin_info($subtype = NULL, $conf = NULL, $context = NULL) {
  $block = new stdClass();
  $block->title = t('Displays a summary of user statistics including: number 
    of total users, active users, blocked users, and users in each role.');

  return $block;
} 

/**
 * Run-time rendering of the body of the block.
 */
function total_control_overview_user_content_type_render($subtype, $conf, $panel_args, &$context) {
  $user_data = total_control_get_user_overview($conf);

  $overview = array();
  $overview['all'] = format_plural($user_data['all'], '1 user account', '@count total user accounts');
  $overview['active'] = format_plural($user_data['active'], '1 active user account', '@count active user accounts');
  $overview['blocked'] = format_plural($user_data['blocked'], '1 blocked user account', '@count blocked user accounts');

  foreach ($user_data['roles'] as $rid => $data) {
    $overview['roles_' . $rid]  = format_plural($user_data['roles'][$rid]['count'], '1 user account', '@count user accounts');
    $overview['roles_' . $rid] .= ' with the role: ' . $user_data['roles'][$rid]['name'];
  }

  $block = new stdClass();
  $block->module = t('total_control');
  $block->title = t('Overview of user accounts');
  $block->content = theme('total_control_overview_user', array('overview' => $overview));

  return $block;
}

/**
 * 'Edit form' callback for the content type.
 */
function total_control_overview_user_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  // Add user settings to form.
  total_control_add_user_pane_settings($form, $conf);

  return $form;
}

/**
 * 'Edit form' submit callback for the content type.
 */
function total_control_overview_user_content_type_edit_form_submit($form, &$form_state) {
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}
