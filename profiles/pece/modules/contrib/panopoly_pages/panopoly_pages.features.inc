<?php
/**
 * @file
 * panopoly_pages.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function panopoly_pages_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  if ($module == "panelizer" && $api == "panelizer") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function panopoly_pages_node_info() {
  $items = array(
    'panopoly_landing_page' => array(
      'name' => t('Landing Page'),
      'base' => 'node_content',
      'description' => t('A primary landing page to display to users on your site.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => t('<p>Here you can set the <em>Landing Page\'s</em> metadata, for example the title, path and menu options.</p>
<p>To add content to the page, first save this form and then click the "Customize this page" button.</p>'),
    ),
    'panopoly_page' => array(
      'name' => t('Content Page'),
      'base' => 'node_content',
      'description' => t('An important page to display to users on your site.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
