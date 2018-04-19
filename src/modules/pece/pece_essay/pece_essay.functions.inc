<?php

/**
 * Helper function to override title pane config form for panelizer's
 * free_panel display on PECE Essay board.
 */
function _pece_essay_override_essay_board_title_config_form(&$form, &$form_state, $form_id) {
  if ($form_id != 'ctools_node_title_content_type_edit_form' &&
      strpos(current_path(), 'free_panel') !== FALSE)
    return;

  if (!empty($form['override_title']) && !empty($form['markup'])) {
    $form['override_title']['#default_value'] = 1;
    $form['markup']['#default_value'] = 'h1';
    $form['link']['#default_value'] = FALSE;
  }
}

/**
 * Helper function to set default value and override contributors pane formatter
 * config form for panelizer's free_panel display on PECE Essay board.
 */
function _pece_essay_override_essay_board_contributors_config_form(&$form, &$form_state, $form_id) {
  if ($form_id != 'ctools_entity_field_content_type_formatter_options' &&
    strpos(current_path(), 'free_panel') !== FALSE)
    return;

  // Prevent user to change the default values for this pane.
  $form['override_title']['#disabled'] = 'disabled';
  $form['override_title_text']['#disabled'] = 'disabled';
  $form['override_title_heading']['#disabled'] = 'disabled';
  $form['label']['#disabled'] = 'disabled';
  $form['formatter']['#disabled'] = 'disabled';

  $form['override_title']['#type'] = 'hidden';
  $form['override_title_text']['#type'] = 'hidden';
  $form['override_title_heading']['#type'] = 'hidden';
  $form['label']['#type'] = 'hidden';
  $form['formatter']['#type'] = 'hidden';

  if (!empty($form['formatter'])) {
    $form['formatter']['#default_value'] = 'og_list_default';
  }
}

/**
 * Helper function to override contributors pane styles config form for
 * panelizer's free_panel display on PECE Essay board.
 */
function _pece_essay_override_essay_board_contributors_config_styles_form(&$form, &$form_state, $form_id) {
  if ($form_id != 'ctools_entity_field_content_type_formatter_styles'  &&
    strpos(current_path(), 'free_panel') !== FALSE)
    return;

  // Prevent user to change the default values for this pane.
  $form['delta_offset']['#disabled'] = 'disabled';
  $form['delta_limit']['#disabled'] = 'disabled';
  $form['delta_reversed']['#disabled'] = 'disabled';

  $form['delta_offset']['#type'] = 'hidden';
  $form['delta_limit']['#type'] = 'hidden';
  $form['delta_reversed']['#type'] = 'hidden';
}
