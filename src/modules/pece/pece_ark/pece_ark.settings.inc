<?php

/**
 * Build a form to save values.
 */
function pece_ark_settings_form() {

  $form = array();

  $form['ark-form-settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Setup Ark Module settings'),
    '#weight' => 0,
    '#description' => t('Set the parameters for the Ark Module settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE
  );

  $form['ark-form-settings']['ark_composite_who_field'] = array(
      '#type' => 'textfield',
      '#size'=> 65,
      '#title' => t('Set the machine name of the fields that will compose the "who" field. Pelase add the fields separated by comma.'),
      '#default_value' => variable_get('ark_composite_who_field', implode(',', ARK_COMPOSITE_WHO_FIELD)),
      '#maxlength' => 1024,
      '#required' => TRUE,
      '#description' => implode(',', ARK_COMPOSITE_WHO_FIELD),
  );

  $form['ark-form-settings']['ark_indexing_limit'] = array(
    '#type' => 'textfield',
    '#size'=> 65,
    '#title' => t('Set the limit of nodes to be processed at the same time during the bach process for crating local and remote ARK ID\'s.'),
    '#default_value' => variable_get('ark_indexing_limit', ARK_INDEXING_LIMIT),
    '#maxlength' => 1024,
    '#required' => TRUE,
    '#description' => 'Ex.: ' . ARK_INDEXING_LIMIT,
  );

  $form['ark-form-settings']['ark_authors_name_separator'] = array(
    '#type' => 'textfield',
    '#size'=> 65,
    '#title' => t('Set the separator simbol to delimit the authors names.'),
    '#default_value' => variable_get('ark_authors_name_separator', ARK_DEFAULT_AUTHORS_NAME_SEPARATOR),
    '#maxlength' => 1024,
    '#required' => TRUE,
    '#description' => 'Ex.: ' . ARK_DEFAULT_AUTHORS_NAME_SEPARATOR,
  );

  return system_settings_form($form);
}
