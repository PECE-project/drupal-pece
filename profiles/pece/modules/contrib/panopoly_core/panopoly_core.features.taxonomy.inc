<?php
/**
 * @file
 * panopoly_core.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function panopoly_core_taxonomy_default_vocabularies() {
  return array(
    'panopoly_categories' => array(
      'name' => 'Categories',
      'machine_name' => 'panopoly_categories',
      'description' => 'This is a sitewide taxonomy of categories to organize the content on your site!',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
