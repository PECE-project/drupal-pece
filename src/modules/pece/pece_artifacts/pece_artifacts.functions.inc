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
  $artifacts = array(
    'pece_artifact_audio',
    'pece_artifact_fieldnote',
    'pece_artifact_image',
    'pece_artifact_pdf',
    'pece_artifact_text',
    'pece_artifact_video',
    'pece_artifact_website',
  );

  return $artifacts;
}
