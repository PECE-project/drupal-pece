<?php

/**
 * @file
 * pece_annotations.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function pece_annotations_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_pece_annotation';
  $strongarm->value = 0;
  $export['comment_anonymous_pece_annotation'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_pece_annotation';
  $strongarm->value = 1;
  $export['comment_default_mode_pece_annotation'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_pece_annotation';
  $strongarm->value = '50';
  $export['comment_default_per_page_pece_annotation'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_pece_annotation';
  $strongarm->value = 1;
  $export['comment_form_location_pece_annotation'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_pece_annotation';
  $strongarm->value = '1';
  $export['comment_pece_annotation'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_pece_annotation';
  $strongarm->value = '1';
  $export['comment_preview_pece_annotation'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_pece_annotation';
  $strongarm->value = 1;
  $export['comment_subject_field_pece_annotation'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__pece_annotation';
  $strongarm->value = array(
    'extra_fields' => array(
      'display' => array(
        'card' => array(
          'card' => array(
            'visible' => TRUE,
            'weight' => '1',
          ),
          'card_full_text' => array(
            'visible' => TRUE,
            'weight' => '1',
          ),
          'default' => array(
            'visible' => TRUE,
            'weight' => '1',
          ),
        ),
      ),
      'form' => array(
        'locations' => array(
          'weight' => '8',
        ),
        'path' => array(
          'weight' => '7',
        ),
        'title' => array(
          'weight' => '0',
        ),
      ),
    ),
    'view_modes' => array(
      'card' => array(
        'custom_settings' => TRUE,
      ),
      'diff_standard' => array(
        'custom_settings' => FALSE,
      ),
      'featured' => array(
        'custom_settings' => TRUE,
      ),
      'free_panel' => array(
        'custom_settings' => TRUE,
      ),
      'full' => array(
        'custom_settings' => FALSE,
      ),
      'highlighted' => array(
        'custom_settings' => TRUE,
      ),
      'meta_content' => array(
        'custom_settings' => TRUE,
      ),
      'mini_teaser' => array(
        'custom_settings' => TRUE,
      ),
      'most_recent' => array(
        'custom_settings' => TRUE,
      ),
      'rss' => array(
        'custom_settings' => FALSE,
      ),
      'search_index' => array(
        'custom_settings' => FALSE,
      ),
      'search_result' => array(
        'custom_settings' => FALSE,
      ),
      'teaser' => array(
        'custom_settings' => TRUE,
      ),
      'token' => array(
        'custom_settings' => FALSE,
      ),
    ),
  );
  $export['field_bundle_settings_node__pece_annotation'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_pece_annotation';
  $strongarm->value = '0';
  $export['language_content_type_pece_annotation'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_pece_annotation';
  $strongarm->value = array();
  $export['menu_options_pece_annotation'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_pece_annotation';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_pece_annotation'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_pece_annotation';
  $strongarm->value = array(
    0 => 'status',
    1 => 'revision',
  );
  $export['node_options_pece_annotation'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_pece_annotation';
  $strongarm->value = '1';
  $export['node_preview_pece_annotation'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_pece_annotation';
  $strongarm->value = 0;
  $export['node_submitted_pece_annotation'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_defaults_node_pece_analytic';
  $strongarm->value = array(
    'status' => 1,
    'view modes' => array(
      'card' => array(
        'choice' => 0,
        'default' => 0,
        'status' => 0,
        'substitute' => 0,
      ),
      'default' => array(
        'choice' => 0,
        'default' => 0,
        'status' => 0,
        'substitute' => 0,
      ),
      'featured' => array(
        'choice' => 0,
        'default' => 0,
        'status' => 0,
        'substitute' => 0,
      ),
      'free_panel' => array(
        'choice' => 0,
        'default' => 0,
        'status' => 0,
        'substitute' => 0,
      ),
      'highlighted' => array(
        'choice' => 0,
        'default' => 0,
        'status' => 0,
        'substitute' => 0,
      ),
      'meta_content' => array(
        'choice' => 0,
        'default' => 0,
        'status' => 0,
        'substitute' => 0,
      ),
      'mini_teaser' => array(
        'choice' => 0,
        'default' => 0,
        'status' => 0,
        'substitute' => 0,
      ),
      'most_recent' => array(
        'choice' => 0,
        'default' => 0,
        'status' => 0,
        'substitute' => 0,
      ),
      'page_manager' => array(
        'choice' => 0,
        'default' => 1,
        'status' => 1,
        'substitute' => '',
      ),
      'teaser' => array(
        'choice' => 0,
        'default' => 0,
        'status' => 0,
        'substitute' => 0,
      ),
    ),
  );
  $export['panelizer_defaults_node_pece_analytic'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_node:pece_analytic:page_manager_selection';
  $strongarm->value = 'node:pece_analytic:default';
  $export['panelizer_node:pece_analytic:page_manager_selection'] = $strongarm;

  return $export;
}
