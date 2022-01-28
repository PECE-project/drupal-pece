<?php

/**
 * @file
 * Editor definition details for the Unicorn test WYSIWYG library.
 */

/**
 * Plugin implementation of hook_editor().
 */
function wysiwyg_test_unicorn_editor() {
  $editor['unicorn'] = array(
    'title' => 'Unicorn',
    'libraries' => array(
      '' => array(
        'title' => 'Default',
        'files' => array(),
      ),
    ),
    'library path' => drupal_get_path('module', 'wysiwyg_test'),
    'version callback' => '_wysiwyg_test_unicorn_version',
    'versions' => array(
      '1.0' => array(),
    ),
  );
  return $editor;
}

/**
 * WYSIWYG editor version callback.
 *
 * @see wysiwyg_test_unicorn_editor()
 */
function _wysiwyg_test_unicorn_version() {
  return '1.0';
}
