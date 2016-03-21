<?php
/**
 * @file
 * Drupal Ipsum API functions.
 */

/**
 * Implements hook_drupal_ipsum_vocabularies().
 *
 * This hook allows you to specify additional vocabularies for use with the
 * Drupal Ipsum text generation class.
 *
 * It expects one or more arrays who's key is the vocabulary machine name and
 * who's values are an array with the following keys:
 *  - 'title' => The full vocabulary title
 *  - 'words' => A simple array of words that make up the vocabulary
 */
function hook_drupal_ipsum_vocabularies() {
  return array(
    'foo' => array( // vocabulary machine_name
      'title' => 'Foo Example Vocabulary',
      'words' => array(
        'foo',
        'bar',
        'baz',
      ),
    ),
  );
}