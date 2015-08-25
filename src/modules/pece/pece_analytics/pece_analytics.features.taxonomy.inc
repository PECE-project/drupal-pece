<?php
/**
 * @file
 * pece_analytics.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function pece_analytics_taxonomy_default_vocabularies() {
  return array(
    'pece_structured_analytics' => array(
      'name' => 'Structured Analytics (Questions set)',
      'machine_name' => 'pece_structured_analytics',
      'description' => 'PECE\'s collection of questions',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
