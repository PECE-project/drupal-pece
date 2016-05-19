<?php
/**
 * @file
 * pece_biblio.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function pece_biblio_taxonomy_default_vocabularies() {
  return array(
    'pece_biblio_collections' => array(
      'name' => 'Bibliography collections',
      'machine_name' => 'pece_biblio_collections',
      'description' => 'Collections of bibliography items.',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
