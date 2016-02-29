<?php

/**
 * @file
 * A panel plugin to provide administrative information about the site's pages
 */

$plugin = array(
  'title' => t('Pages'),
  'description' => t('This is a list of the pages that are available'),
  'content_types' => array('landing_pages'),
  'category' => t('Admin'),
  'required context' => new ctools_context_required(t('Panopoly Admin'), 'string'),
  'single' => TRUE,
);

/**
  * Put the output for you pages type in the blocks pages.
  */
function panopoly_admin_landing_pages_content_type_render($subtype, $conf, $panel_args, $context) {

  $pages = array();

  // Assemble the Landing Page Data
  module_load_include('inc', 'page_manager', 'page_manager.admin');
  $tasks = page_manager_get_tasks_by_type('page');
  $panels_pages = array('operations' => array());
  page_manager_get_pages($tasks, $panels_pages);
  foreach ($panels_pages['rows'] as $id => $info) {
    if (strpos($id, 'panopoly_admin')) { 
      // Exclude any admin pages
    }
    elseif ($info['data']['type']['data'] == 'System') {
      // Exclude any system pages
    }
    elseif ($panels_pages['disabled'][$id] == TRUE) {
      // Exclude any disabled pages
    }
    elseif ($info['data']['type']['data'] == 'Existing') {
      // Exclude PM Existing Pages 
    }
    elseif ($id == 'page-panopoly_search') {
      // Exclude Panopoly Search's main page
    }
    else {
      // Include anything else as a general page
      $pages[] = array(
        'data' => array(
          $info['data']['title'],
          '<em>Landing Page</em>',
          $info['data']['path'],
        ),
      );
    }
  }

  // Assemble the Page Template Data for Nodes, Taxonomy Terms, and Users
  $plugins = panelizer_get_entity_plugins();
  foreach ($plugins as $entity_type => $plugin) {
    if (in_array($entity_type, array('node', 'taxonomy_term', 'user'))) {
      $handler = panelizer_entity_plugin_get_handler($entity_type);
      $entity_info = entity_get_info($entity_type);
      foreach ($handler->plugin['bundles'] as $bundle_type => $bundle) {
        if (!empty($bundle['view modes']['page_manager']) && $bundle['view modes']['page_manager']['status'] == 1 && $bundle['view modes']['page_manager']['default'] == 1) {
          $pages[]  = array(
            'data' => array(
              $entity_info['bundles'][$bundle_type]['label'],
              '<em>' . $entity_info['label'] . ' template' . '</em>',
              (module_exists('pathauto') && pathauto_pattern_load_by_entity($entity_type, $bundle_type)) ? l('/' . pathauto_pattern_load_by_entity($entity_type, $bundle_type), 'admin/config/content/panelizer/' . $entity_type . '/' . $bundle_type . '.page_manager/content') : l('/' . $handler->plugin['entity path'], 'admin/config/content/panelizer/' . $entity_type . '/' . $bundle_type . '.page_manager/content'),
            ),
          );
        }
      }
    }
  }

  // Create the Output
  $pane = new stdClass();  
  if (!empty($pages)) {
    $pane->content = theme('table', array('header' => array(), 'rows' => $pages, 'attributes' => array('class' => 'panels-manage')));
  }
  else {
    $pane->content = t('No pages have yet been created!');
  }
  return $pane;
}
