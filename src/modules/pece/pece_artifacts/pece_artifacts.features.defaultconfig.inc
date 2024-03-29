<?php

/**
 * @file
 * pece_artifacts.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function pece_artifacts_defaultconfig_features() {
  return array(
    'pece_artifacts' => array(
      'strongarm' => 'strongarm',
    ),
  );
}

/**
 * Implements hook_defaultconfig_strongarm().
 */
function pece_artifacts_defaultconfig_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_expire_ntypes';
  $strongarm->value = array(
    'pece_artifact_audio' => array(
      'default' => '',
      'enabled' => 1,
      'max' => '',
      'required' => 0,
    ),
    'pece_artifact_bundle' => array(
      'default' => '',
      'enabled' => 1,
      'max' => '',
      'required' => 0,
    ),
    'pece_artifact_fieldnote' => array(
      'default' => '',
      'enabled' => 1,
      'max' => '',
      'required' => 0,
    ),
    'pece_artifact_image' => array(
      'default' => '',
      'enabled' => 1,
      'max' => '',
      'required' => 0,
    ),
    'pece_artifact_pdf' => array(
      'default' => '',
      'enabled' => 1,
      'max' => '',
      'required' => 0,
    ),
    'pece_artifact_text' => array(
      'default' => '',
      'enabled' => 1,
      'max' => '',
      'required' => 0,
    ),
    'pece_artifact_video' => array(
      'default' => '',
      'enabled' => 1,
      'max' => '',
      'required' => 0,
    ),
    'pece_artifact_website' => array(
      'default' => '',
      'enabled' => 1,
      'max' => '',
      'required' => 0,
    ),
    'biblio' => array(
      'enabled' => 0,
      'default' => '',
      'max' => '',
      'required' => 0,
      'action_type' => '1',
    ),
  );
  $export['node_expire_ntypes'] = $strongarm;

  return $export;
}
