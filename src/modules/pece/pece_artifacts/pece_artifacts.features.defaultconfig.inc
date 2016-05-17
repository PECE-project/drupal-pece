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
  $strongarm->name = 'node_expire_enabled_pece_artifact_audio';
  $strongarm->value = 1;
  $export['node_expire_enabled_pece_artifact_audio'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_expire_enabled_pece_artifact_bundle';
  $strongarm->value = 1;
  $export['node_expire_enabled_pece_artifact_bundle'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_expire_enabled_pece_artifact_fieldnote';
  $strongarm->value = 1;
  $export['node_expire_enabled_pece_artifact_fieldnote'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_expire_enabled_pece_artifact_image';
  $strongarm->value = 1;
  $export['node_expire_enabled_pece_artifact_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_expire_enabled_pece_artifact_pdf';
  $strongarm->value = 1;
  $export['node_expire_enabled_pece_artifact_pdf'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_expire_enabled_pece_artifact_text';
  $strongarm->value = 1;
  $export['node_expire_enabled_pece_artifact_text'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_expire_enabled_pece_artifact_video';
  $strongarm->value = 1;
  $export['node_expire_enabled_pece_artifact_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_expire_enabled_pece_artifact_website';
  $strongarm->value = 1;
  $export['node_expire_enabled_pece_artifact_website'] = $strongarm;

  return $export;
}
