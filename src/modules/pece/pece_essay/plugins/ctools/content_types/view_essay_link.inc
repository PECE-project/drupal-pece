<?php

$plugin = array(
  'single' => TRUE,
  'top level' => TRUE,
  'title' => t('Essay link'),
  'description' => t('Configurable link to PECE Essay'),
  'category' => t('PECE'),
  'render callback' => 'pece_essay_view_essay_link_pane_render',
  'required context' => new ctools_context_required(t('Node'), 'node', array(
    'type' => 'pece_essay',
  )),
  'edit form' => 'pece_essay_view_essay_link_pane_edit_form',
  'defaults' => array(
    'destination' => null,
  ),
);

/**
 * Configure Essay link pane.
 */
function pece_essay_view_essay_link_pane_edit_form($form, &$form_state) {
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

  $form['destination'] = array(
    '#type' => 'select',
    '#title' => t('Link destination'),
    '#options' => array(
      'node' => t('Essay summary'),
      'essay' => t('Essay board'),
    ),
    '#default_value' => $conf['destination'],
  );

  return $form;
}

/**
 * Submit callback for Essay link pane edit form.
 */
function pece_essay_view_essay_link_pane_edit_form_submit(&$form, &$form_state) {
  $form_state['conf']['destination'] = $form_state['values']['destination'];
}

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info
 */
function pece_essay_view_essay_link_pane_render($subtype, $conf, $args, $context) {
  // Prepare response block.
  $block = new stdClass();
  $node = $context->data;
  $path = "node/{$node->nid}" . ($conf['destination'] === 'essay' ? '/essay' : '');
  $text = $conf['destination'] === 'essay' ? t('View Essay') : t('Return to PECE Essay Landing Page');
  $path_alias = drupal_get_path_alias($path);

  $block->content = array(
    'link' => array(
      '#theme' => 'link',
      '#text' => $text,
      '#path' => $path_alias,
      '#options' => array(
        'attributes' => array(
          'class' => array('essay-link', 'destination-' . $conf['destination']),
        ),
        'html' => FALSE,
      ),
    ),
  );

  return $block;
}
