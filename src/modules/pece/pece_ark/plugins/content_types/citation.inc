<?php

$plugin = array(
  'single' => TRUE,
  'top level' => TRUE,
  'title' => t('Content citation'),
  'description' => t('Add citation on Essay page.'),
  'category' => t('PECE'),
  'render callback' => 'pece_ark_citation_pane_render',
  'all contexts' => TRUE,
  //'required context' => new ctools_context_required(t('Node'), 'node'),
  'edit form' => 'pece_ark_citation_pane_edit_form',
);

/**
 * An edit form for the pane's settings.
 */
function pece_ark_citation_pane_edit_form(&$form, &$form_state) {
  return $form;
}
/**
 * Submit callback for Essay link pane edit form.
 */
function pece_ark_citation_pane_edit_form_submit(&$form, &$form_state) {
  return $form;
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
      '#value' => 'teste',
      '#attributes' => array(
        'class' => array('citation'),
      ),
    ),
  );

  return $block;
}
