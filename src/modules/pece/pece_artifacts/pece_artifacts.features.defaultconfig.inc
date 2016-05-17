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
      'enabled' => 1,
      'default' => '',
      'max' => '',
      'required' => 0,
    ),
    'pece_artifact_bundle' => array(
      'enabled' => 1,
      'default' => '',
      'max' => '',
      'required' => 0,
    ),
    'pece_artifact_fieldnote' => array(
      'enabled' => 1,
      'default' => '',
      'max' => '',
      'required' => 0,
    ),
    'pece_artifact_image' => array(
      'enabled' => 1,
      'default' => '',
      'max' => '',
      'required' => 0,
    ),
    'pece_artifact_pdf' => array(
      'enabled' => 1,
      'default' => '',
      'max' => '',
      'required' => 0,
    ),
    'pece_artifact_text' => array(
      'enabled' => 1,
      'default' => '',
      'max' => '',
      'required' => 0,
    ),
    'pece_artifact_video' => array(
      'enabled' => 1,
      'default' => '',
      'max' => '',
      'required' => 0,
    ),
    'pece_artifact_website' => array(
      'enabled' => 1,
      'default' => '',
      'max' => '',
      'required' => 0,
    ),
  );
  $export['node_expire_ntypes'] = $strongarm;

  return $export;
}
