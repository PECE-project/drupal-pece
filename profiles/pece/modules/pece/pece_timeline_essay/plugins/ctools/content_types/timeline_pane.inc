<?php

$plugin = array(
  'single' => TRUE,
  'top level' => TRUE,
  'title' => t('Timeline Essay Pane'),
  'description' => t('Timeline Essay'),
  'category' => t('PECE'),
  'render callback' => 'pece_timeline_essay_timeline_pane_render',
  'required context' => new ctools_context_required(t('Node'), 'node', array(
    'type' => 'pece_timeline_essay',
  )),
  'edit form' => 'pece_timeline_essay_timeline_pane_edit_form',
  'defaults' => array(
    'destination' => null,
  ),
);

/**
 * Configure Essay link pane.
 */
function pece_timeline_essay_timeline_pane_edit_form($form, &$form_state) {
  $conf = drupal_array_merge_deep(
    $form_state['plugin']['defaults'],
    $form_state['conf'],
    $form_state['values']
  );

  // Remove common unnecessary fields.
  unset($form['override_title']);
  unset($form['override_title_text']);
  unset($form['override_title_heading']);
  unset($form['override_title_markup']);

  return $form;
}

/**
 * Submit callback for Essay link pane edit form.
 */
function pece_timeline_essay_timeline_pane_edit_form_submit(&$form, &$form_state) {
  $form_state['conf']['destination'] = $form_state['values']['destination'];
}

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info
 */
function pece_timeline_essay_timeline_pane_render($subtype, $conf, $args, $context) {
  drupal_add_library('pece_timeline_essay', 'timelinejs');
  // Prepare response block.
  $block = new stdClass();
  $node = $context->data;
  $timeline_events = pece_timeline_essay_get_tl_items($node);
  $TLEvents = json_encode($timeline_events);

  $block->content = theme('timelinejs', array('events' => $TLEvents));
  return $block;
}
