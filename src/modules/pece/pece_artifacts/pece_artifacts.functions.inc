<?php
/**
 * @file
 * Helper functions for the pece_artifacts module.
 */

/**
 * Default form alter for PECE's artifacts.
 */
function pece_artifacts_alter_artifact_form(&$form, &$form_state) {
  // Hide the comment settings fieldset.
  $form['comment_settings']['#access'] = FALSE;
  // We cannot allow the content to be authored by anonymous.
  $form['author']['name']['#required'] = TRUE;
}

/**
 * Get the available Artifacts.
 */
function pece_artifacts_fetch_all() {
  $artifacts = module_invoke_all('pece_artifact_info');
  drupal_alter('pece_artifact_info', $artifacts);
  return $artifacts;
}
