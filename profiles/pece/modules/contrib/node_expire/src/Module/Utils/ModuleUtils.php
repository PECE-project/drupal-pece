<?php

/**
 * @file
 * ModuleUtils class.
 */

namespace Drupal\node_expire\Module\Utils;

use Drupal\node_expire\Module\CommonExpire\Utils\CommonUtils;

/**
 * ModuleUtils class.
 */
class ModuleUtils {

  /**
   * Cleans up redundant plain variables.
   */
  public static function doVariablesCleanup() {
    // TODO: Optimize and find out source of node_expire_page	N; .
    // TODO: Add some common name like node_expire_type_cfg_
    // for easy cleanup.
    // Delete node type related variables.
    CommonUtils::doVariablesCleanupByTemplate('node_expire_type_cfg_%');
  }

  /**
   * Utility function to display debug info.
   *
   * Display debug info and write it into log.
   *
   * @param object $data
   *   Data to display.
   */
  public static function debug($data = array()) {
    drupal_set_message(filter_xss_admin('<pre>' . print_r($data, TRUE) . '</pre>'));
    watchdog('node_expire', '<pre>' . print_r($data, TRUE) . '</pre>');
  }

}
