<?php

/**
 * @file
 * Simple content type that has no dependencies on anything else.
 */

$plugin = array(
  'title' => t('Simple Pane'),
  'description' => t('A simple pane for testing.'),
  'category' => t('Panopoly Test'),
  'single' => TRUE,
  'render callback' => 'panopoly_test_simple_content_type_render',
  'edit form' => 'panopoly_test_simple_content_type_edit_form',
  'defaults' => array(),
);

function panopoly_test_simple_content_type_edit_form($form, &$form_state) {
  // Build the configuration form
  $conf = $form_state['conf'];
  return $form;
}

function panopoly_test_simple_content_type_edit_form_submit($form, &$form_state) {
  // TODO
}

function panopoly_test_simple_content_type_render($subtype, $conf, $args, $context) {
  $pane = new stdClass();
  $pane->title = t('Simple pane');
  $pane->content = t('Abracadabra! Here is a simple pane.');
  return $pane;
}
