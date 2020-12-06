<?php

/**
 * @file
 * pece_amber.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function pece_amber_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: management_amber-dashboard:admin/reports/amber.
  $menu_links['management_amber-dashboard:admin/reports/amber'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/reports/amber',
    'router_path' => 'admin/reports/amber',
    'link_title' => 'Amber Dashboard',
    'options' => array(
      'attributes' => array(
        'title' => 'Amber Dashboard',
      ),
      'identifier' => 'management_amber-dashboard:admin/reports/amber',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'management_reports:admin/reports',
  );
  // Exported menu link: management_amber:admin/config/content/amber.
  $menu_links['management_amber:admin/config/content/amber'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/config/content/amber',
    'router_path' => 'admin/config/content/amber',
    'link_title' => 'Amber',
    'options' => array(
      'attributes' => array(
        'title' => 'Configuration for the Amber module',
      ),
      'identifier' => 'management_amber:admin/config/content/amber',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'management_content-authoring:admin/config/content',
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Amber');
  t('Amber Dashboard');

  return $menu_links;
}
