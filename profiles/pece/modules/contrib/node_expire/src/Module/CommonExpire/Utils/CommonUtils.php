<?php

/**
 * @file
 * CommonUtils class.
 */

namespace Drupal\node_expire\Module\CommonExpire\Utils;

/**
 * CommonUtils class.
 */
class CommonUtils {

  /**
   * Cleans up variables by template.
   */
  public static function doVariablesCleanupByTemplate($template) {
    $result = db_query("
    SELECT name FROM {variable}
    WHERE name LIKE '" . $template . "'");
    foreach ($result as $row) {
      variable_del($row->name);
    }
  }

}
