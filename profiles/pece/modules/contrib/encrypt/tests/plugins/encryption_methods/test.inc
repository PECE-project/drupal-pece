<?php

/**
 * @file
 * An example encryption method just for tests.
 *
 * @ingroup encrypt
 */

$plugin = array(
  'title' => t('Test Method'),
  'description' => t('This is just a test encryption method.'),
  'encrypt callback' => 'encrypt_test_encryption_methods_test',
  'dependency callback' => '_encrypt_test_method_dependencies',
);

/**
 * Callback for encryption.
 *
 * Just return the text since we're not concerned with testing encryption.
 */
function encrypt_test_encryption_methods_test($op = 'encrypt', $text = '', $options = array()) {
  return $text;
}

/**
 * Dependency callback.
 *
 * Can be forced to trigger failure/success with a variable.
 */
function _encrypt_test_method_dependencies() {
  $errors = array();

  if (variable_get('encrypt_test_trigger_unmet_deps', TRUE)) {
    $errors[] = t('This is an unmet dependency.');
  }

  return $errors;
}
