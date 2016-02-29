<?php
/**
 * @file
 * pece_api.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function pece_api_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: management_services-security-update:admin/config/services/services-security.
  $menu_links['management_services-security-update:admin/config/services/services-security'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/config/services/services-security',
    'router_path' => 'admin/config/services/services-security',
    'link_title' => 'Services Security update',
    'options' => array(
      'attributes' => array(
        'title' => 'Services module security updates',
      ),
      'identifier' => 'management_services-security-update:admin/config/services/services-security',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'management_web-services:admin/config/services',
  );
  // Exported menu link: management_services:admin/structure/services.
  $menu_links['management_services:admin/structure/services'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/structure/services',
    'router_path' => 'admin/structure/services',
    'link_title' => 'Services',
    'options' => array(
      'attributes' => array(
        'title' => 'Manage Services',
      ),
      'identifier' => 'management_services:admin/structure/services',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'management_structure:admin/structure',
  );
  // Exported menu link: management_web-services:admin/config/services.
  $menu_links['management_web-services:admin/config/services'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/config/services',
    'router_path' => 'admin/config/services',
    'link_title' => 'Web services',
    'options' => array(
      'attributes' => array(
        'title' => 'Tools related to web services.',
      ),
      'identifier' => 'management_web-services:admin/config/services',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'management_configuration:admin/config',
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Services');
  t('Services Security update');
  t('Web services');

  return $menu_links;
}
