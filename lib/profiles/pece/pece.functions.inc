<?php

Use \Spyc;
/**
 * Parse a YAML stream.
 *
 * @param $input
 *   The YAML stream.
 *
 * @return mixed
 *   Array of parsed YAML elements (or FALSE on failure).
 */
function pece_parse_yaml(String $input = '') {
  if (function_exists('yaml_parse')) {
    return yaml_parse($input);
  }

  // Load fallback library.
  if (!function_exists('spyc_load')) {
    \Drupal::messenger()->addError('Parse YAML: Unable to find a YAML parser.');
    return FALSE;
  }

  try {
    $spyc = new Spyc();
    $parsed = $spyc->load($input);
  }
  catch (Exception $exception) {
    \Drupal::messenger()->addError('Failed parsing YAML stream.');
    \Drupal::logger('pece')->error($exception->getMessage());
    return FALSE;
  }
  return $parsed;
}
