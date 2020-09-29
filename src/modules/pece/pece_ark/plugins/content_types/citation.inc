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

  module_load_include('inc', 'pece_profile', 'pece_profile.functions');
  // Prepare response block.
  $block = new stdClass();

  $node = $context['panelizer']->data;
  $ark = ', [ARK].';
  $creator = pece_get_fullname_or_name($node->uid);
  $block->content = array(
    'citation' => array(
      '#theme' => 'html_tag',
      '#tag' => 'div',
      '#value' => t('@creator. "@title", @siteName, Platform for Experimental Collaborative Ethnography, last modified @changed, accessed @accessed@ark', array(
        '@creator' => $creator,
        '@title' => $node->title,
        '@siteName' => variable_get('site_name'),
        '@ark' => $ark,
        '@changed' => format_date($node->changed, 'custom', 'j F Y'),
        '@accessed' => date('j F Y')
      )),
      '#attributes' => array(
        'class' => array('citation'),
      ),
    ),
  );

  return $block;
}
