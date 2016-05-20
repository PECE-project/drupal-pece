<?php

/**
 * Implements hook_install_tasks()
 */
function pece_install_tasks(&$install_state) {
  $tasks = array();

  // ----------------------------------------------------------------
  // Add our custom CSS file for the installation process.
  // ----------------------------------------------------------------

  drupal_add_css(drupal_get_path('profile', 'pece') . '/pece.css');


  // ----------------------------------------------------------------
  // Allow PECE enabling modules to define own install tasks.
  // ----------------------------------------------------------------

  foreach (pece_modules_implements('pece_install_tasks') as $module => $hook) {
    $tasks += $hook($install_state);
  }

  return $tasks;
}

/**
 * Implements hook_install_tasks_alter()
 */
function pece_install_tasks_alter(&$tasks, $install_state) {

  // ----------------------------------------------------------------
  // Magically go one level deeper in solving years of dependency problems.
  // Copied from Panopoly distro.
  // ----------------------------------------------------------------

  $tasks['install_load_profile']['function'] = 'pece_install_load_profile';


  // ----------------------------------------------------------------
  // Allow PECE enabling modules to alter install tasks.
  // ----------------------------------------------------------------

  foreach (pece_modules_implements('pece_install_tasks_alter') as $module => $implementation) {
    $implementation($tasks);
  }
}

/**
 * Helper method to retrieve PECE package modules.
 */
function pece_modules_info() {
  $pece_modules = array();
  $path_to_profile = drupal_get_path('profile', 'pece');
  $path_to_info = $path_to_profile . '/pece.info';
  $profile_info = drupal_parse_info_file($path_to_info);

  if (empty($profile_info['dependencies'])) {
    return $pece_modules;
  }

  foreach ($profile_info['dependencies'] as $module) {
    $module_path = drupal_get_path('module', $module);
    $module_path_to_info = "$module_path/$module.info";
    $module_info = drupal_parse_info_file($module_path_to_info);

    if (!empty($module_info['package']) && $module_info['package'] == 'PECE') {
      $pece_modules[$module] = $module_info;
    }
  }

  return $pece_modules;
}

/**
 * Helper method to get PECE package module implementations.
 */
function pece_modules_implements($hook) {
  $implementations = array();

  foreach (pece_modules_info() as $module => $info) {
    if (drupal_load('module', $module)) {
      $function = "{$module}_{$hook}";
      if (function_exists($function)) {
        $implementations[$module] = $function;
      }
    }
  }

  return $implementations;
}

/**
 * Task handler to load our install profile and enhance the dependency information
 */
function pece_install_load_profile(&$install_state) {
  // Loading the install profile normally
  install_load_profile($install_state);

  // Include any dependencies that we might have missed...
  $dependencies = $install_state['profile_info']['dependencies'];
  foreach ($dependencies as $module) {
    $module_info = drupal_parse_info_file(drupal_get_path('module', $module) . '/' . $module . '.info');
    if (!empty($module_info['dependencies'])) {
      foreach ($module_info['dependencies'] as $dependency) {
        $parts = explode(' (', $dependency, 2);
        $dependencies[] = array_shift($parts);
      }
    }
  }

  $install_state['profile_info']['dependencies'] = array_unique($dependencies);
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function pece_form_install_configure_form_alter(&$form, $form_state) {
  // Hide some messages from various modules that are just too chatty.
  drupal_get_messages('status');
  drupal_get_messages('warning');

  // Set reasonable defaults for site configuration form
  $form['site_information']['site_name']['#default_value'] = 'PECE';
  $form['admin_account']['account']['name']['#default_value'] = 'admin';
  $form['server_settings']['site_default_country']['#default_value'] = 'US';
  $form['server_settings']['date_default_timezone']['#default_value'] = 'America/Los_Angeles'; // West coast, best coast

  // Define a default email address if we can guess a valid one
  if (valid_email_address('admin@' . $_SERVER['HTTP_HOST'])) {
    $form['site_information']['site_mail']['#default_value'] = 'admin@' . $_SERVER['HTTP_HOST'];
    $form['admin_account']['account']['mail']['#default_value'] = 'admin@' . $_SERVER['HTTP_HOST'];
  }
}

/**
 * Implements hook_form_FORM_ID_alter()
 */
function pece_form_apps_profile_apps_select_form_alter(&$form, $form_state) {

  // For some things there are no need
  $form['apps_message']['#access'] = FALSE;
  $form['apps_fieldset']['apps']['#title'] = NULL;

  // Improve style of apps selection form
  if (isset($form['apps_fieldset'])) {
    $manifest = apps_manifest(apps_servers('panopoly'));
    foreach ($manifest['apps'] as $name => $app) {
      if ($name != '#theme') {
        $form['apps_fieldset']['apps']['#options'][$name] = '<strong>' . $app['name'] . '</strong><p><div class="admin-options"><div class="form-item">' . theme('image', array('path' => $app['logo']['path'], 'height' => '32', 'width' => '32')) . '</div>' . $app['description'] . '</div></p>';
      }
    }
  }
}
