<?php
/**
 * @file
 * pece_node_expiration.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function pece_node_expiration_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: management_node-expire:admin/config/workflow/node_expire/settings.
  $menu_links['management_node-expire:admin/config/workflow/node_expire/settings'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/config/workflow/node_expire/settings',
    'router_path' => 'admin/config/workflow/node_expire/settings',
    'link_title' => 'Node Expire',
    'options' => array(
      'attributes' => array(
        'title' => 'Configure node expire settings.',
      ),
      'identifier' => 'management_node-expire:admin/config/workflow/node_expire/settings',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 2,
    'customized' => 0,
    'parent_identifier' => 'management_workflow:admin/config/workflow',
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Node Expire');

  return $menu_links;
}
