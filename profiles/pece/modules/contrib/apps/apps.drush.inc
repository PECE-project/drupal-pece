<?php

/**
 * @file
 * Apps module drush integration.
 */

/**
 * Implements hook_drush_command().
 */
function apps_drush_command() {
  $items = array();

  $items['apps-server-list'] = array(
    'description' => "List all the available servers for your site.",
    'drupal dependencies' => array('apps'),
    'aliases' => array('asl', 'apps-servers'),
  );
  $items['apps-list'] = array(
    'description' => "List Apps from a server.",
    'arguments' => array(
      'server' => 'A space-delimited list of server keys.',
    ),
    'drupal dependencies' => array('apps'),
    'aliases' => array('al'),
  );
  $items['apps-install'] = array(
    'description' => "Install App.",
    'arguments' => array(
      'app' => 'A space-delimited list of apps to install.',
    ),
    'drupal dependencies' => array('apps'),
    'aliases' => array('ai'),
  );
  return $items;
}

/**
 * Implements hook_drush_help().
 */
function apps_drush_help($section) {
  switch ($section) {
    case 'drush:apps-server-list':
      return dt("List all the servers that provide apps for your site.");

    case 'drush:apps-list':
      return dt("List all the available apps for your site.");

    case 'drush:apps-install':
      return dt("Install an App to your site.");

  }
}

/**
 * Get a list of all app servers configured.
 */
function drush_apps_server_list() {
  module_load_include('inc', 'apps', 'apps.manifest');
  $servers = apps_servers();
  $rows = array(array(dt('Key'), dt('Name'), dt('desc'), dt('URL')));
  foreach ($servers as $k => $server) {
    $rows[] = array(
      $k,
      $server['title'],
      $server['description'],
      $server['manifest'],
    );
  }
  drush_print_table($rows, TRUE);
}

/**
 * Get a list of all apps available.
 */
function drush_apps_list() {
  $servers = func_get_args();
  module_load_include('inc', 'apps', 'apps.manifest');
  $servers = !empty($servers) ? $servers : array_keys(apps_servers());
  $rows = array(
    array(
      dt('Key'),
      dt('Name'),
      dt('version'),
      dt('server'),
      dt('status'),
    ),
  );
  foreach ($servers as $server) {
    $apps = apps_apps($server);
    foreach ($apps as $k => $app) {
      $status = '';
      switch ($app['status']) {
        case APPS_INCOMPATIBLE:
          $status = 'Incompatible';
          break;

        case APPS_DISABLED:
          $status = 'Disabled';
          break;

        case APPS_ENABLED:
          $status = 'Enabled';
          break;

        case APPS_INSTALLABLE:
          $status = 'Installable';
          break;
      }
      $rows[] = array(
        $k,
        $app['name'],
        $app['version'],
        $server,
        $status,
      );
    }
    unset($apps);
  }
  drush_print_table($rows, TRUE);
}

/**
 * Return a list of all apps available for installation.
 */
function drush_apps_installable_apps() {
  module_load_include('inc', 'apps', 'apps.manifest');

  $apps_list = array();
  $servers = apps_servers();
  foreach ($servers as $server) {
    $apps = apps_apps($server);
    foreach ($apps as $key => $app) {
      if ($app['status'] == APPS_DISABLED || $app['status'] == APPS_INSTALLABLE) {
        $apps_list[$key] = $app['server']['name'];
      }
    }
  }
  return $apps_list;
}

/**
 * Install an app, or list.
 */
function drush_apps_install() {
  module_load_include('inc', 'apps', 'apps.installer');
  $apps = func_get_args();
  $installable = drush_apps_installable_apps();
  $to_install = array();

  // Verify that all apps are installable,
  foreach ($apps as $app) {
    if (array_key_exists($app, $installable)) {
      $to_install[$app] = $installable[$app];
    }
    else {
      drush_log(dt('App @app is not available for installation', array('@app' => $app)), 'error');
    }
  }

  // If we have no installable apps, list all apps that are installable.
  if (empty($to_install)) {
    $type = drush_choice($installable, 'Enter a number to choose which App to install.', '!key');
    if ($type === FALSE) {
      return;
    }
    $to_install[$type] = $installable[$type];
  }

  // For each app we want to download its dependencies and itself.
  foreach ($to_install as $app => $server) {
    drush_print(dt('Install @app for server @server', array('@app' => $app, '@server' => $server)));
    $downloadables = apps_download_apps_list(apps_app_load($server, $app));
    foreach ($downloadables as $downloadable) {
      $download = array('url' => $downloadable['url']);
      $name = $downloadable['name'];
      $download_location = variable_get('apps_install_path', APPS_INSTALL_PATH) . "/" . $name;
      $parts = explode('.', DRUSH_VERSION);
      if ($parts[0] < 6 && !($parts[0] == 5 && $parts[1] > 9)) {
        $downloaded = make_download_file($name, $download, $download_location);
      }
      else {
        $downloaded = make_download_file($name, 'file', $download, $download_location);
      }
      if (!$downloaded) {
        drush_log(dt('One of the dependencies of @app failed to download, canceling installation', array('@app' => $app)), 'error');
        return;
      };
    }
    // As there are now new modules, we have to reset the module data static
    // cache.
    drupal_static_reset('system_rebuild_module_data');
    drush_invoke('pm-enable', $app);
  }
}
