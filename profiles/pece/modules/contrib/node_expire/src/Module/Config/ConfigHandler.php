<?php

/**
 * @file
 * ConfigHandler class.
 */

namespace Drupal\node_expire\Module\Config;

/**
 * ConfigHandler class.
 */
class ConfigHandler {

  /**
   * Returns HandleContentExpiry configuration value.
   */
  public static function getHandleContentExpiry() {
    $val = variable_get('node_expire_handle_content_expiry', 2);
    return $val;
  }

  /**
   * Returns TRUE for node types that have the Node expire feature enabled.
   */
  public static function isExpirable($node_type) {
    $ntypes = variable_get('node_expire_ntypes', array());
    if (!isset($ntypes[$node_type])) {
      return FALSE;
    }
    // TODO: WARNING | Unused variable $ntype.
    if (!$ntype = $ntypes[$node_type]) {
      return FALSE;
    }
    return TRUE;
  }

  /**
   * Gets condition for date entry elements.
   *
   * This depends on value of variable node_expire_date_entry_elements
   * and also is date_popup module of date module installed or not.
   *
   * @return int
   *   0 - use text fields
   *   1 - use date popups
   */
  public static function getDateEntryElements() {
    // No date_popup module.
    if (!module_exists('date_popup')) {
      return 0;
    }

    // Legacy mode.
    if (variable_get('node_expire_handle_content_expiry', 2) == 0) {
      return 0;
    }

    return variable_get('node_expire_date_entry_elements', 0);
  }

  /**
   * Returns PastDateAllowed configuration value.
   */
  public static function getPastDateAllowed() {
    $val = variable_get('node_expire_past_date_allowed', 0);
    return $val;
  }

  /**
   * Returns DateFormat configuration value.
   */
  public static function getDateFormat() {
    $val = variable_get('node_expire_date_format', 'Y-m-d');
    return $val;
  }

}
