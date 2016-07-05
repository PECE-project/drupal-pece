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
      'strongarm' => 'strongarm',
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
      'files' => array(
        'exclude_filepaths' => '',
      ),
      'archive' => array(
        'exclude_filepaths' => '/tmp',
      ),
      'pece_bkp' => array(
        'exclude_filepaths' => 'backup_migrate
                                styles
                                css
                                js
                                ctools
                                less',
      ),
      'db' => array(
        'nodata_tables' => array(
          0 => 'cache',
          1 => 'cache_admin_menu',
          2 => 'cache_browscap',
          3 => 'cache_content',
          4 => 'cache_filter',
          5 => 'cache_calendar_ical',
          6 => 'cache_location',
          7 => 'cache_menu',
          8 => 'cache_page',
          9 => 'cache_reptag',
          10 => 'cache_views',
          11 => 'cache_views_data',
          12 => 'cache_block',
          13 => 'cache_update',
          14 => 'cache_form',
          15 => 'cache_bootstrap',
          16 => 'cache_field',
          17 => 'cache_image',
          18 => 'cache_path',
          19 => 'sessions',
          20 => 'search_dataset',
          21 => 'search_index',
          22 => 'search_keywords_log',
          23 => 'search_total',
          24 => 'watchdog',
          25 => 'accesslog',
          26 => 'devel_queries',
          27 => 'devel_times',
        ),
        'exclude_tables' => array(),
        'utils_lock_tables' => FALSE,
      ),
    ),
    'utils_disable_query_log' => TRUE,
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
  $item->destination_id = 'scheduled';
  $item->copy_destination_id = '';
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
 * Implements hook_defaultconfig_strongarm().
 */
function pece_backup_defaultconfig_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'backup_migrate_profile_id';
  $strongarm->value = '';
  $export['backup_migrate_profile_id'] = $strongarm;

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
    'roles' => array(),
    'module' => 'backup_migrate',
  );

  // Exported permission: 'access backup files'.
  $permissions['access backup files'] = array(
    'name' => 'access backup files',
    'roles' => array(),
    'module' => 'backup_migrate',
  );

  // Exported permission: 'administer backup and migrate'.
  $permissions['administer backup and migrate'] = array(
    'name' => 'administer backup and migrate',
    'roles' => array(),
    'module' => 'backup_migrate',
  );

  // Exported permission: 'delete backup files'.
  $permissions['delete backup files'] = array(
    'name' => 'delete backup files',
    'roles' => array(),
    'module' => 'backup_migrate',
  );

  // Exported permission: 'perform backup'.
  $permissions['perform backup'] = array(
    'name' => 'perform backup',
    'roles' => array(),
    'module' => 'backup_migrate',
  );

  // Exported permission: 'restore from backup'.
  $permissions['restore from backup'] = array(
    'name' => 'restore from backup',
    'roles' => array(),
    'module' => 'backup_migrate',
  );

  return $permissions;
}
