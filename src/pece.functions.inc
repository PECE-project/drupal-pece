<?php

/**
 * Parse a YAML stream.
 *
 * @param $input
 *   The YAML stream.
 *
 * @return mixed
 *   Array of parsed YAML elements (or FALSE on failure).
 */
function pece_parse_yaml($input = '') {
  if (function_exists('yaml_parse')) {
    return yaml_parse($input);
  }

  // Load fallback library.
  if ($path_to_spyc_library = libraries_get_path('spyc-master')) {
    include_once $path_to_spyc_library . '/Spyc.php';
  }

  if (!function_exists('spyc_load')) {
    drupal_set_message(t('Parse YAML: Unable to find a YAML parser.'), 'error', FALSE);
    return FALSE;
  }

  try {
    $parsed = spyc_load($input);
  } catch(Exception $exception) {
    drupal_set_message(t('Failed parsing YAML stream. ') . $exception->getMessage(), 'error');
    return FALSE;
  }
  return $parsed;
}
