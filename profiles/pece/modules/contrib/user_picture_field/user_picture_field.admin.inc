<?php

/**
 * @file
 * user_picture_field callback
 */ 

function user_picture_field_config_form() {
  $form['user_picture_field_source_entity'] = array(
    '#type' => 'select',
    '#title' => t('Machine name of source entity'),
    '#default_value' => variable_get('user_picture_field_source_entity', 'user'),
    '#options' => array(
      'user' => t('User'),
      'profile2' => t('Profile2'),
    ),
    '#required' => TRUE,
  );
  $form['user_picture_field_source_bundle'] = array(
    '#type' => 'textfield',
    '#title' => t('Machine name of source bundle'),
    '#default_value' => variable_get('user_picture_field_source_bundle', ''),
    '#maxlength' => 255,
    '#states' => array(
      'visible' => array(
        ':input[name="user_picture_field_source_entity"]' => array('value' => 'profile2'),
      ),
    ),
  );
  $form['user_picture_field_source_field'] = array(
    '#type' => 'textfield',
    '#title' => t('Machine name of source field that used as user picture'),
    '#default_value' => variable_get('user_picture_field_source_field', 'field_user_avatar'),
    '#maxlength' => 255,
    '#required' => TRUE,
  );  
  return system_settings_form($form, TRUE);
}