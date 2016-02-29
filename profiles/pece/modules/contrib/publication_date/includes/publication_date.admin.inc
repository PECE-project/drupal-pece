<?php

/**
 * @file
 * Publication date administration forms.
 */

/**
 * Publication date administration page for calback.
 */
function publication_date_admin_form($form, &$form_state) {
  // Publication Date Popup Configuration.
  $form['popup_config'] = array(
    '#type' => 'fieldset',
    '#title' => t('Date Popup Configuration'),
    '#description' => t('Publication date can use the date popup field widget provided by the <a href="@project-link">Date</a> project, if enabled.', array('@project-link' => 'http://drupal.org/project/date')),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['popup_config']['publication_date_popup_enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use date popup field'),
    '#default_value' => variable_get('publication_date_popup_enable', 1),
  );
  $form['popup_config']['publication_date_popup_year_start'] = array(
    '#type' => 'textfield',
    '#title' => t('Starting year'),
    '#default_value' => variable_get('publication_date_popup_year_start', '6'),
    '#field_prefix' => '-',
    '#field_suffix' => 'years from now',
    '#maxlength' => 10,
    '#size' => 3,
    '#element_validate' => array('element_validate_integer_positive'),
  );
  $form['popup_config']['publication_date_popup_year_end'] = array(
    '#type' => 'textfield',
    '#title' => t('Ending year'),
    '#default_value' => variable_get('publication_date_popup_year_end', '1'),
    '#field_prefix' => '+',
    '#field_suffix' => 'years from now',
    '#maxlength' => 10,
    '#size' => 3,
    '#element_validate' => array('element_validate_integer_positive'),
  );

  return system_settings_form($form);
}
