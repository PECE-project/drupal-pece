<?php
/**
 * @file
 * Helper functions for the pece_artifacts module.
 */

function pece_artifacts_alter_artifact_form(&$form, &$form_state) {
  // Hide the comment settings fieldset.
  $form['comment_settings']['#access'] = FALSE;
  // We cannot allow the content to be authored by anonymous.
  $form['author']['name']['#required'] = TRUE;
}