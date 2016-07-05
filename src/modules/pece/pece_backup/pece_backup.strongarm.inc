<?php
/**
 * @file
 * pece_backup.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function pece_backup_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'backup_migrate_profile_id';
  $strongarm->value = '';
  $export['backup_migrate_profile_id'] = $strongarm;

  return $export;
}
