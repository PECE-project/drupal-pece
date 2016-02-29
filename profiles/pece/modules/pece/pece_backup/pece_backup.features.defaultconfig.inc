<?php
/**
 * @file
 * pece_backup.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function pece_backup_defaultconfig_features() {
  return array(
    'pece_backup' => array(
      'exportables_backup_migrate_profiles' => 'exportables_backup_migrate_profiles',
      'exportables_backup_migrate_schedules' => 'exportables_backup_migrate_schedules',
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_exportables_backup_migrate_profiles().
 */
function pece_backup_defaultconfig_exportables_backup_migrate_profiles() {
  $export = array();

  $item = new stdClass();
  $item->disabled = FALSE; /* Edit this to true to make a default item disabled initially */
  $item->api_version = 1;
  $item->machine_name = 'pece_backup';
  $item->name = 'PECE Backup';
  $item->filename = '[site:name]';
  $item->append_timestamp = TRUE;
  $item->timestamp_format = 'Y-m-d\\TH-i-s';
  $item->filters = array(
    'compression' => 'gzip',
    'encryption' => 'aes',
    'notify_success_enable' => 1,
    'notify_success_email' => '[site:mail]',
    'notify_failure_enable' => 1,
    'notify_failure_email' => '[site:mail]',
    'utils_site_offline' => 1,
    'utils_site_offline_message' => '[site:name] is in maintenance mode. 
     We should be back shortly. Thank you for your patience.',
    'utils_description' => 'PECE Backup file',
    'use_cli' => 0,
    'ignore_errors' => 0,
    'sources' => array(
      'db' => array(
        'exclude_tables' => array(),
        'nodata_tables' => array(
          'cache' => 'cache',
          'cache_admin_menu' => 'cache_admin_menu',
          'cache_block' => 'cache_block',
          'cache_bootstrap' => 'cache_bootstrap',
          'cache_field' => 'cache_field',
          'cache_filter' => 'cache_filter',
          'cache_form' => 'cache_form',
          'cache_image' => 'cache_image',
          'cache_location' => 'cache_location',
          'cache_menu' => 'cache_menu',
          'cache_page' => 'cache_page',
          'cache_path' => 'cache_path',
          'cache_update' => 'cache_update',
          'cache_views' => 'cache_views',
          'cache_views_data' => 'cache_views_data',
          'search_dataset' => 'search_dataset',
          'search_index' => 'search_index',
          'search_total' => 'search_total',
          'sessions' => 'sessions',
          'watchdog' => 'watchdog',
        ),
        'utils_lock_tables' => 0,
      ),
      'db:legacy:default' => array(
        'exclude_tables' => array(),
        'nodata_tables' => array(
          'accesslog' => 'accesslog',
          'cache' => 'cache',
          'cache_admin_menu' => 'cache_admin_menu',
          'cache_block' => 'cache_block',
          'cache_bootstrap' => 'cache_bootstrap',
          'cache_field' => 'cache_field',
          'cache_filter' => 'cache_filter',
          'cache_form' => 'cache_form',
          'cache_image' => 'cache_image',
          'cache_location' => 'cache_location',
          'cache_menu' => 'cache_menu',
          'cache_page' => 'cache_page',
          'cache_path' => 'cache_path',
          'cache_update' => 'cache_update',
          'cache_views' => 'cache_views',
          'cache_views_data' => 'cache_views_data',
          'search_dataset' => 'search_dataset',
          'search_index' => 'search_index',
          'search_total' => 'search_total',
          'sessions' => 'sessions',
          'watchdog' => 'watchdog',
        ),
        'utils_lock_tables' => 0,
      ),
      'files' => array(
        'exclude_filepaths' => '',
      ),
      'archive' => array(
        'exclude_filepaths' => '/tmp',
      ),
    ),
  );
  $export['pece_backup'] = $item;

  return $export;
}

/**
 * Implements hook_defaultconfig_exportables_backup_migrate_schedules().
 */
function pece_backup_defaultconfig_exportables_backup_migrate_schedules() {
  $export = array();

  $item = new stdClass();
  $item->disabled = FALSE; /* Edit this to true to make a default item disabled initially */
  $item->api_version = 1;
  $item->machine_name = 'pece_backup';
  $item->name = 'PECE Backup';
  $item->source_id = 'archive';
  $item->destination_id = 'pece_bkp';
  $item->copy_destination_id = 'local_dir';
  $item->profile_id = 'pece_backup';
  $item->keep = 0;
  $item->period = 604800;
  $item->enabled = TRUE;
  $item->cron = 'builtin';
  $item->cron_schedule = '0 4 * * 6';
  $export['pece_backup'] = $item;

  return $export;
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function pece_backup_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access backup and migrate'.
  $permissions['access backup and migrate'] = array(
    'name' => 'access backup and migrate',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'backup_migrate',
  );

  // Exported permission: 'access backup files'.
  $permissions['access backup files'] = array(
    'name' => 'access backup files',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'backup_migrate',
  );

  // Exported permission: 'administer backup and migrate'.
  $permissions['administer backup and migrate'] = array(
    'name' => 'administer backup and migrate',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'backup_migrate',
  );

  // Exported permission: 'delete backup files'.
  $permissions['delete backup files'] = array(
    'name' => 'delete backup files',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'backup_migrate',
  );

  // Exported permission: 'perform backup'.
  $permissions['perform backup'] = array(
    'name' => 'perform backup',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'backup_migrate',
  );

  // Exported permission: 'restore from backup'.
  $permissions['restore from backup'] = array(
    'name' => 'restore from backup',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'backup_migrate',
  );

  return $permissions;
}
