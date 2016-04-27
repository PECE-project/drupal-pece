<?php

/**
 * Implements hook_install_tasks()
 */
function pece_install_tasks(&$install_state) {
  $tasks = array();

  // Add our custom CSS file for the installation process.
  drupal_add_css(drupal_get_path('profile', 'pece') . '/pece.css');

  // Add the PECE settings step to the installation process.
  $tasks = $tasks + pece_run_kw_manifests_install_task($install_state);

  return $tasks;
}

/**
 * Add an install task to run Kraftwagen manifests.
 */
function pece_run_kw_manifests_install_task(&$install_task) {
  $tasks['pece_run_kw_manifests'] = array(
    'display_name' => t('PECE Settings'),
  );
  return $tasks;
}

/**
 * Helper function to run the Kraftwagen manifests programatically.
 */
function pece_run_kw_manifests() {

  // Set the page title
  drupal_set_title(t('PECE Settings'));

  module_load_include('install', 'pece');
  pece_manifest_define_themes();
  pece_manifest_set_frontpage();

  // $manifests = pece_kw_manifests_info();
  // if (!empty($manifests)) {
  //   var_dump($manifests);
  //   kw_manifests_run($manifests['theme']);
  //   kw_manifests_run($manifests['set_frontpage']);
  //   // foreach ($manifests as $manifest) {
  //   //   kw_manifests_run($manifest);
  //   // }
  // }
}

/**
 * Implements hook_install_tasks_alter()
 */
function pece_install_tasks_alter(&$tasks, $install_state) {
  // Magically go one level deeper in solving years of dependency problems
  require_once(drupal_get_path('module', 'panopoly_core') . '/panopoly_core.profile.inc');
  $tasks['install_load_profile']['function'] = 'panopoly_core_install_load_profile';

  // If we only offer one language, define a callback to set this
  require_once(drupal_get_path('module', 'panopoly_core') . '/panopoly_core.profile.inc');
  if (!(count(install_find_locales($install_state['parameters']['profile'])) > 1)) {
    $tasks['install_select_locale']['function'] = 'panopoly_core_install_locale_selection';
  }
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
