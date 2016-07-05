<?php
/**
 * @file
 * pece_backup.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function pece_backup_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: management_backup-and-migrate:admin/config/system/backup_migrate.
  $menu_links['management_backup-and-migrate:admin/config/system/backup_migrate'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/config/system/backup_migrate',
    'router_path' => 'admin/config/system/backup_migrate',
    'link_title' => 'Backup and Migrate',
    'options' => array(
      'attributes' => array(
        'title' => 'Backup/restore your database and files or migrate data to or from another Drupal site.',
      ),
      'identifier' => 'management_backup-and-migrate:admin/config/system/backup_migrate',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'management_system:admin/config/system',
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Backup and Migrate');

  return $menu_links;
}
