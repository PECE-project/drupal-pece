<?php
/**
 * @file
 * pece_artifacts_image.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function pece_artifacts_image_defaultconfig_features() {
  return array(
    'pece_artifacts_image' => array(
      'strongarm' => 'strongarm',
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_strongarm().
 */
function pece_artifacts_image_defaultconfig_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'image_jpeg_quality';
  $strongarm->value = '80';
  $export['image_jpeg_quality'] = $strongarm;

  return $export;
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function pece_artifacts_image_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create pece_artifact_image content'.
  $permissions['create pece_artifact_image content'] = array(
    'name' => 'create pece_artifact_image content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any pece_artifact_image content'.
  $permissions['delete any pece_artifact_image content'] = array(
    'name' => 'delete any pece_artifact_image content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own pece_artifact_image content'.
  $permissions['delete own pece_artifact_image content'] = array(
    'name' => 'delete own pece_artifact_image content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any pece_artifact_image content'.
  $permissions['edit any pece_artifact_image content'] = array(
    'name' => 'edit any pece_artifact_image content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own pece_artifact_image content'.
  $permissions['edit own pece_artifact_image content'] = array(
    'name' => 'edit own pece_artifact_image content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  return $permissions;
}
