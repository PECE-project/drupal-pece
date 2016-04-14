<?php
/**
 * @file
 * Helper functions for the pece_artifacts module.
 */

/**
 * Get the available Artifacts.
 */
function pece_artifacts_fetch_all() {
  $artifacts = module_invoke_all('pece_artifact_info');
  drupal_alter('pece_artifact_info', $artifacts);
  return $artifacts;
}
