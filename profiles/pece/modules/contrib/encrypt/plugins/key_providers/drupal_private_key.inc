<?php

/**
 * @file
 * Plugin definition for the Drupal Private Key key provider.
 * THIS PROVIDER IS DEPRECATED AND SHOULD NOT BE USED FOR ENCRYPTION.
 */

$plugin = encrypt_drupal_private_key_encrypt_key_providers();

/**
 * Implements MODULE_FILENAME_encrypt_key_providers().
 */
function encrypt_drupal_private_key_encrypt_key_providers() {
  return array(
    'title' => t('Drupal Private Key'),
    'description' => t("Use Drupal's private key from the database."),
    'key callback' => 'encrypt_get_drupal_private_key',
    'settings form' => NULL,
    'static key' => TRUE,
    'deprecated' => TRUE,
  );
}

/**
 * Callback method to return Drupal's private key.
 */
function encrypt_get_drupal_private_key() {
  return drupal_get_private_key();
}
