<?php

/**
 * @file
 *
 * This module enables a page to be used as an administrative dashboard
 * Also included are several views for site administration.
 *
 */

/**
 * menu callback for settings page
 */
function total_control_admin_settings() {
  // Redirect on log in.
  $form['total_control_login_redirect'] = array(
    '#type' => 'checkbox',
    '#title' => t('Redirect administrators to Dashboard after log in'),
    '#default_value' => variable_get('total_control_login_redirect', 0),
    '#description' => t('Users with the !permission can be automatically 
      redirected to the Dashboard when they log in.', array('!permission' => 
      l(t('Have Total Control permission'), 'admin/user/permissions'))),
  );
  
  $overridden = ' <strong>' . t('Automatic settings override these options.') . '</strong>';
  $collapse_type = FALSE;
  $collapse_role = FALSE;
  $collapse_auto = TRUE;
  $disable_type_pane = '';
  $disable_type_page = '';
  $disable_role_pane = '';
  $disable_role_page = '';
  $auto_pane_default = variable_get('total_control_auto_panels', array());
  $auto_page_default = variable_get('total_control_auto_pages', array());
  
  $types = node_type_get_types();
  $content_types = array();
  foreach ($types as $machine => $type) {
    $content_types[$machine] = $type->name;
  }
  if (!empty($auto_pane_default) && !($auto_pane_default['type'] === 0)) {
    $disable_type_pane = TRUE;
    $collapse_auto = FALSE;
  }
  
  if (!empty($auto_page_default) && !($auto_page_default['type'] === 0)) {
    $disable_type_page = TRUE;
    $collapse_auto = FALSE;
  }
  if ((!empty($auto_page_default) && !empty($auto_pane_default)) 
    && !($auto_page_default['type'] === 0) && !($auto_pane_default['type'] === 0)) {
    $collapse_type = TRUE;
  }
  
  $roles = user_roles(TRUE);
  $role_options = array();
  $role_defaults = array(2);
  foreach ($roles as $rid => $role) {
    $role_options[$rid] = $role;
  }
  if (!empty($auto_pane_default) 
    && array_key_exists('role', $auto_pane_default) 
    && !($auto_pane_default['role'] === 0)) {
    $disable_role_pane = TRUE;
    $collapse_auto = FALSE;
  }
  if (!empty($auto_page_default) 
    && array_key_exists('role', $auto_page_default) 
    && !($auto_page_default['role'] === 0)) {
    $disable_role_page = TURE;
    $collapse_auto = FALSE;
  }
  if (count($roles) == 1 
    || (array_key_exists('role', $auto_page_default) 
      && (!($auto_page_default['role'] === 0) 
      && !($auto_pane_default['role'] === 0)) 
      && (!empty($auto_page_default) 
      && !empty($auto_pane_default)) )) {
    $collapse_role = TRUE;
  }
  
  $auto_options = array(
    'type' => t('Content Types'), 
    // TODO 'role' => t('User Roles'),
  );

  // Content types, pages and panes.
  $form['types'] = array(
    '#type' => 'fieldset',
    '#title' => t('Types of content: pages and panes'),
    '#collapsible' => TRUE,
    '#collapsed' => $collapse_type,
    );

  $text = t('Checking these boxes will create panes on the dashboard for these content types.');
  $description = ($disable_type_pane) ? $text . $overridden : $text;
  $form['types']['total_control_type_panels'] = array(
    '#type' => 'checkboxes',
    '#title' => t('On the Dashboard'),
    '#options' => $content_types,
    '#description' => $description,
    '#default_value' => variable_get('total_control_type_panels', array()),
    '#disabled' => $disable_type_pane,
    );

  $text = t('Checking these boxes will create administration pages for these content types.');
  $description = ($disable_type_page) ? $text . $overridden : $text;
  $form['types']['total_control_type_pages'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Administration Pages'),
    '#options' => $content_types,
    '#description' => $description,
    '#default_value' => variable_get('total_control_type_pages', array()),
    '#disabled' => $disable_type_page,
    );
  
  // User roles, pages and panes.
  $form['users'] = array(
    '#type' => 'fieldset',
    '#title' => t('Types of users: pages and panes'),
    '#collapsible' => TRUE,
    '#collapsed' => $collapse_role,
    );  
  $form['users']['total_control_role_panels'] = array(
    '#type' => 'checkboxes',
    '#title' => t('On the Dashboard'),
    '#options' => $role_options,
    '#description' => t('Checking these boxes will create panes on the dashboard for these user types.'),
    '#default_value' => variable_get('total_control_role_panels', $role_defaults),
    );
  $form['users']['total_control_role_pages'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Administration Pages'),
    '#options' => $role_options,
    '#description' => t('Checking these boxes will create administration pages for these user types.'),
    '#default_value' => variable_get('total_control_role_pages', $role_defaults),
    );
    
  // Automatically add displays.
  $form['auto'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced Settings: Automatically add pages and panes'),
    '#collapsible' => TRUE,
    '#collapsed' => $collapse_auto,
    );
  $form['auto']['total_control_auto_panels'] = array(
    '#type' => 'checkboxes',
    '#title' => t('On the Dashboard'),
    '#options' => $auto_options,
    '#description' => t('Automatically create panes on the dashboard when new 
      content types are added.'),
    '#default_value' => $auto_pane_default,
    );
  $form['auto']['total_control_auto_pages'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Administration Pages'),
    '#options' => $auto_options,
    '#description' => t('Automatically create administration pages when new 
      content types are added.'),
    '#default_value' => $auto_page_default,
    );
  
  $form['#submit'][] = 'total_control_admin_settings_submit';
  
  return system_settings_form($form);
}

/**
 * Submit function for settings page
 */
function total_control_admin_settings_submit($form, &$form_state) {
  if ($form_state['values']['total_control_role_panels'][2] == 0) {
    // change it back and tell them why
    $form_state['values']['total_control_role_panels'][2] = 2;
    drupal_set_message(t('You can not delete the pane view for users.  To 
      remove it from your dashboard, use the <a href="!panels_interface">Page 
      Manager</a>.', array('!panels_interface' => url('admin/structure/pages'))));
  }
  if ($form_state['values']['total_control_role_pages'][2] == 0) {
    // change it back and tell them why
    $form_state['values']['total_control_role_pages'][2] = 2;
    drupal_set_message(t('You should not delete the page view for all users, 
      use the <a href="!views_interface">Views user interface</a> to disable
      it instead.', array('!views_interface' => url('admin/structure/views'))));
  }

  // Load the views once so we don't have to do it each time.
  $paneview = views_get_view('control_content_panes');
  $pageview = views_get_view('control_content');

  // Adjust content pane displays per Total Control settings.
  foreach ($form_state['values']['total_control_type_panels'] as $machine => $value) {
    if ($machine === $value) {
      $type = node_type_load($machine);
      total_control_add_views_pane_display($paneview, $type->name, $machine);
    }
    else {
      $type = node_type_load($machine);
      total_control_views_delete_pane_display($machine);
    }
  }

  // Adjust page displays per Total Control settings.
  foreach ($form_state['values']['total_control_type_pages'] as $machine => $value) {
    if ($machine === $value) {
      $type = node_type_load($machine);
      total_control_add_views_page_display($pageview, $type->name, $machine);
    }
    else {
      $type = node_type_load($machine);
      total_control_views_delete_page_display($machine);
    }
  }
}
