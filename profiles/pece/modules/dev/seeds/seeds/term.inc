<?php

/**
 * @file
 * Term seed implementation.
 */

/**
 * Create a term seed.
 */
function seeds_term_seed_create($data = array()) {

  $map_properties = array(
    'type' => 'vid',
  );

  foreach ($map_properties as $from => $to) {
    if (!empty($data[$from]) && empty($data[$to])) {
      $data[$to] = $data[$from];
      unset($data[$from]);
    }
  }

  $vocabularies = taxonomy_get_vocabularies();

  // Defaults.
  $data += array(
    'name' => 'default_term',
    'vid' => !empty($vocabularies) ? array_keys($vocabularies)[0] : 0,
  );
  // Make sure to handle vocabulary ids from machine names.
  if (!empty($data['vid']) && !is_numeric($data['vid'])) {
    foreach ($vocabularies as $vid => $info) {
      if ($info->machine_name == $data['vid']) {
        $data['vid'] = $vid;
      }
    }
  }

  // Return existing term, if available.
  if ($existing_term = _seeds_term_find($data)) {
    return array_shift($existing_term);
  }

  $data = (object) $data;
  return taxonomy_term_save($data) ? $data : NULL;
}

/**
 * Remove a term seed.
 */
function seeds_term_seed_remove($data = array(), $value = array()) {
  $term = _seeds_term_find($value);
  return taxonomy_term_delete($term->tid) == 3;
}

/**
 * Helper method to find a term by it's possible unique properties.
 */
function _seeds_term_find($info) {
  // Ways to find the term
  $lookup_properties = array(
    'tid' => 'taxonomy_term_load',
    'name' => 'taxonomy_get_term_by_name',
  );

  // Return existing term, if available.
  foreach ($lookup_properties as $property => $loader) {
    if (!empty($info[$property]) && function_exists($loader) && $existing_term = $loader($info[$property])) {
      return $existing_term;
    }
  }

  return NULL;
}
