<?php

/**
 * @file
 * Content type that is marked as advanced.
 */

$plugin = array(
  'title' => t('Advanced Pane'),
  'description' => t('An "advanced" pane for testing exclusion of such panes.'),
  'category' => t('Panopoly Test Advanced'),
  'single' => TRUE,
  'render callback' => 'panopoly_test_advanced_content_type_render',
  'edit form' => 'panopoly_test_advanced_content_type_edit_form',
  'defaults' => array(
    'who' => 'mortals',
  ),
);

function panopoly_test_advanced_content_type_edit_form($form, &$form_state) {
  // Build the configuration form
  $conf = $form_state['conf'];
  $form['who'] = array(
    '#type' => 'textfield',
    '#title' => t("Who shan't touch this holy pane?"),
    '#required' => TRUE,
    '#default_value' => !empty($conf['who']) ? $conf['who'] : '',
  );
  return $form;
}

function panopoly_test_advanced_content_type_edit_form_submit($form, &$form_state) {
  $form_state['conf']['who'] = $form_state['values']['who'];
}

function panopoly_test_advanced_content_type_render($subtype, $conf, $args, $context) {
  $pane = new stdClass();
  $pane->title = t('Advanced pane');
  $pane->content = t('This pane is not for mere %who.', array('%who' => $conf['who']));
  return $pane;
}
