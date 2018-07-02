<?php

/**
 * @file dashboard.inc
 *
 * Default panel page for the Total Control Admin Dashboard.
 *
 */

/**
 * Specialized implementation of hook_page_manager_tasks(). 
 * See api-task.html for more information.
 */
function total_control_dashboard_page_manager_tasks() {
  return array(
    // This is a 'page' task and will fall under the page admin UI
    'task type' => 'page',
    'title' => t('Total Control Admin Dashboard'),
    'description' => t('The total control task creates the administrative dashboard.'),
    'admin title' => 'Total Control Admin Dashboard', // translated by menu system
    'admin description' => 'The total control task creates the administrative dashboard.',
    'admin path' => 'admin/dashboard',
    'task admin' => 'total_control_dashboard_task_admin',
    'hook menu' => 'total_control_dashboard_menu',
    // This is task uses 'context' handlers and must implement these to give the
    // handler data it needs.
    'handler type' => 'context',
    'get arguments' => 'total_control_dashboard_get_arguments',
    'get context placeholders' => 'total_control_dashboard_get_contexts',
  );
}

/**
 * Menu Callback.
 */
function total_control_dashboard_menu(&$items) {
  $items['admin/dashboard'] = array(
    'title' => 'Dashboard',
    'description' => 'Administrative Dashboard',
    'page callback' => 'total_control_dashboard',
    'file path' => drupal_get_path('module', 'total_control') . '/plugins/tasks',
    'file' => 'dashboard.inc',
    'access arguments' => array('have total control'),
    'weight' => -50,
  );
  $items['admin/dashboard/all'] = array(
    'title' => 'Dashboard',
    'description' => 'Administrative Dashboard',
    'weight' => -50,
    'type' => MENU_DEFAULT_LOCAL_TASK,
  );
  
  return $items;
}

/**
 * Page Callback.
 */
function total_control_dashboard() {
  $task = page_manager_get_task('dashboard');
  ctools_include('context');
  ctools_include('context-task-handler');
  $contexts = ctools_context_handler_get_task_contexts($task, '', array());
  $output = ctools_context_handler_render($task, '', $contexts, array());
  
  return $output;
}

/**
 * Callback to add items to the page_manager task administration form.
 */
function total_control_dashboard_task_admin(&$form, &$form_state) {
}

/**
 * Callback to get arguments provided by this task handler.
 */
function total_control_dashboard_get_arguments($task, $subtask_id) {
  // We can return arguments here.
  return array();
}

/**
 * Callback to get context placeholders provided by this handler.
 */
function total_control_dashboard_get_contexts($task, $subtask_id) {
  // TODO - send the user object through as the context.
  return array();
}