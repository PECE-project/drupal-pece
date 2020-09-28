<?php

/**
 * @file
 * Drush integration for TFA Basic.
 */

/**
 * Implements hook_sql_sync_sanitize().
 */
function tfa_basic_drush_sql_sync_sanitize($site) {
  $sql = "TRUNCATE TABLE tfa_totp_seed;";
  $sql .= "TRUNCATE TABLE tfa_trusted_browser;";
  $sql .= "TRUNCATE TABLE tfa_recovery_code;";
  $sql .= "TRUNCATE TABLE tfa_accepted_code;";
  drush_sql_register_post_sync_op('tfa_basic', dt('Remove sensitive TFA data.'), $sql);

}
