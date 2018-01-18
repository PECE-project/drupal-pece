<?php
/**
 * Implements hook_form_FORM_ID_alter().
 *
 * @param $form
 *   The form.
 * @param $form_state
 *   The form state.
 */
function pece_scholarly_lite_form_system_theme_settings_alter(&$form, &$form_state) {
  
  $form['mtt_settings']['tabs']['looknfeel']['custom_color_scheme'] = array(
    '#type' => 'checkbox',
    '#title' => t('Custom Color Scheme'),
    '#description'   => t('Select the color scheme you prefer.'),
    '#default_value' => theme_get_setting('custom_color_scheme'),
  );

  $form['mtt_settings']['tabs']['looknfeel']['color_scheme_settings'] = array(
    '#type' => 'container',
    '#states' => array(
      'invisible' => array(
       ':input[name="custom_color_scheme"]' => array('checked' => FALSE),
      ),
    ),
  );
  $form['mtt_settings']['tabs']['looknfeel']['color_scheme_settings']['color_primary'] = array(
    '#type' => 'textfield',
    '#title' => t('Primary Color'),
    '#description'   => t('Select the primary color. e.g. #A1A1A1'),
    '#default_value' => theme_get_setting('color_primary'),
  );

  $form['mtt_settings']['tabs']['looknfeel']['color_scheme_settings']['color_secondary'] = array(
    '#type' => 'textfield',
    '#title' => t('Secondary Color'),
    '#description'   => t('Select the secondary color. e.g. #A1A1A1'),
    '#default_value' => theme_get_setting('color_secondary'),

  );

  $form['mtt_settings']['tabs']['looknfeel']['color_scheme_settings']['color_tertiary'] = array(
    '#type' => 'textfield',
    '#title' => t('Tertiary Color'),
    '#description'   => t('Enter the terteary color. e.g. #A1A1A1'),
    '#default_value' => theme_get_setting('color_tertiary'),
  );

 $form['#submit'] = array('pece_color_settings_submit');
}

function pece_color_settings_submit($form, $form_state) {
  $theme_path = drupal_get_path('theme', 'pece_scholarly_lite');
  $base_style = file_get_contents($theme_path . '/assets/overrides/scheme_override.base.css'); 
  
  if ($wrapper = file_stream_wrapper_get_instance_by_uri('public://')) {
    $realpath = $wrapper->realpath();
    dsm($realpath);
    // file_prepare_directory($new_folder, FILE_CREATE_DIRECTORY);
    $new_folder = 'public://pece_scholarly_lite/';
  }

  $scheme_override = str_replace('_color_primary_', $form_state['values']['color_primary'], $base_style);
  $scheme_override = str_replace('_color_secondary_', $form_state['values']['color_secondary'], $scheme_override);
  $scheme_override = str_replace('_color_tertiary_', $form_state['values']['color_tertiary'], $scheme_override);
  $overrides_path = 'public://pece_scholarly_lite/scheme_override.css';
  
  if (file_put_contents($overrides_path, $scheme_override)) {
    drupal_set_message(t('Custom color scheme succesfully created.'));
  } else {
    drupal_set_message(t('Error on saving Custom color scheme.'), 'error');
  }
}