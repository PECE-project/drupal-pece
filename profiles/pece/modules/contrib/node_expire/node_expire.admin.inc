<?php

/**
 * @file
 * Administration page callbacks for the node_expire module.
 */

use Drupal\node_expire\Module\Hook\AdminHookHandler;

/**
 * Administrative settings.
 *
 * @return array
 *   An array containing form items to place on the module settings page.
 */
function node_expire_admin_settings() {
  return AdminHookHandler::hookAdminSettings();
}

/**
 * Validation for the administrative settings form.
 *
 * @param object $form
 *   An associative array containing the structure of the form.
 * @param object $form_state
 *   A keyed array containing the current state of the form.
 */
function node_expire_admin_settings_validate($form, &$form_state) {
  AdminHookHandler::hookAdminSettingsValidate($form, $form_state);
}
