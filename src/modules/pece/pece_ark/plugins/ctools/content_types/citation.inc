<?php

$plugin = array(
  'single' => TRUE,
  'top level' => TRUE,
  'title' => t('Content citation'),
  'description' => t('Add citation on Essay page.'),
  'category' => t('PECE'),
  'render callback' => 'pece_ark_citation_pane_render',
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'edit form' => 'pece_ark_citation_pane_edit_form',
);

/**
 * Configure Essay link pane.
 */
function pece_ark_citation($form, &$form_state) {
  $conf = drupal_array_merge_deep(
    $form_state['plugin']['defaults'],
    $form_state['conf'],
    $form_state['values']
  );

  // Remove common unecessary fields.
  unset($form['override_title']);
  unset($form['override_title_text']);
  unset($form['override_title_heading']);
  unset($form['override_title_markup']);


  $form['custom_heading'] = array(
    '#type' => 'textfield',
    '#title' => t('Heading'),
    '#default_value' => $form_state['conf']['custom_heading'],
  );

  return $form;
}

/**
 * Submit callback for Essay link pane edit form.
 */
function pece_essay_custom_heading_pane_edit_form_submit(&$form, &$form_state) {
  $form_state['conf']['custom_heading'] = $form_state['values']['custom_heading'];
}

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info
 */
function pece_ark_citation_pane_render($subtype, $conf, $args, $context) {
  // Prepare response block.
  $block = new stdClass();

  $block->content = array(
    'heading' => array(
      '#theme' => 'html_tag',
      '#tag' => 'h2',
      '#value' => $conf['custom_heading'],
      '#attributes' => array(
        'class' => array('essay-heading'),
      ),
    ),
  );

  return $block;
}
