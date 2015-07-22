<?php
/**
 * @file
 * pece_core.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function pece_core_taxonomy_default_vocabularies() {
  return array(
    'pece_tags' => array(
      'name' => 'Tags',
      'machine_name' => 'pece_tags',
      'description' => 'Tags for PECE contents',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
