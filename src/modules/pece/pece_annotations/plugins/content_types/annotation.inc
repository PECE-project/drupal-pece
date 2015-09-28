<?php

$plugin = array(
  'single' => TRUE,
  // Title to show up on the pane screen.
  'title' => t('Annotate link'),
  // Description to show up on the pane screen.
  'description' => t('Show the Annotate link'),
  // A category to put this under.
  'category' => array(t('PECE'), -9),
  // A function that will return the settings form for the pane.
  'edit form' => 'pece_annotations_annotation_pane_edit_form',
  // A function that will return the renderable content.
  'render callback' => 'pece_annotations_annotation_pane_render',
  // A function that will return the information displayed on the admin screen (optional).
  // 'admin info' => 'custom_panes_plugins_custom_pane_admin_info',
  // Array of defaults for the settings form.
  'defaults' => array(
    'map' => menu_get_item(),
  ),
  'all contexts' => TRUE, // This is NEEDED to be able to use substitution strings in your pane.
);

/**
 * An edit form for the pane's settings.
 */
function pece_annotations_annotation_pane_edit_form($form, &$form_state) {
  return $form;
}

/**
 * Submit form.
 */
function pece_annotations_annotation_pane_edit_form_submit(&$form, &$form_state) {
  return $form;
}

/**
 * Run-time rendering of the body of the block (content type)
 * See ctools_plugin_examples for more advanced info
 */
function pece_annotations_annotation_pane_render($subtype, $conf, $args, $contexts) {

  global $user;

  if (!user_access('create pece_annotation content', $user)) {
    return FALSE;
  }

  // Prepare response block.
  $block = new stdClass();

  // Get panelizer context.
  $context = reset($contexts);

  // Get information about the context being used.
  $context_type = isset($context->keyword) ? $context->keyword : null;
  $node_type    = $context_type == 'node' ? $context->data->type : null;

  $artifacts = array(
    'pece_artifact_audio',
    'pece_artifact_fieldnote',
    'pece_artifact_image',
    'pece_artifact_pdf',
    'pece_artifact_text',
    'pece_artifact_video',
    'pece_artifact_website',
  );

  // Check for device node context.
  if (!in_array($node_type, $artifacts)) {

    // Alert admin of wrong context.
    $block->content = t('This pane might not be used in this context.');

  } else {

    $node = $context->data;

    $options = array(
      'attributes' => array(
        'class' => array('add-link'),
      ),
    );

    pece_core_modal_presets('Annotate', '500', '350');

    // Use CTools API to generate the link.
    $alt = t('Annotate %title', array('%title' => $node->title));
    $content['annotate_link'] = array(
      '#markup' => ctools_ajax_text_button(t('Annotate'), 'annotation/add/nojs/' . $node->nid . '/form', $alt, 'ctools-modal-annotate annotate-link'),
    );

    $block->content = $content;
  }

  return $block;
}
