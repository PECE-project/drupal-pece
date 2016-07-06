<?php

/**
 * @file
 * NodeHookHandler class.
 */

namespace Drupal\node_expire\Module\Hook;

use Drupal\node_expire\Module\Config\ConfigHandler;
use Drupal\node_expire\Module\Db\DbHandler;
use Drupal\node_expire\Module\Utils\TimestampUtils;

/**
 * NodeHookHandler class.
 */
class NodeHookHandler {

  /**
   * Implements hook_node_load().
   */
  public static function hookNodeLoad($nodes, $types) {
    self::doNodeLoad($nodes, $types);
  }

  /**
   * Implements hook_node_prepare().
   */
  public static function hookNodePrepare($node) {
    // Only deal with node types that have the Node expire feature enabled.
    $ntypes = variable_get('node_expire_ntypes', array());
    if (!isset($ntypes[$node->type])) {
      return;
    }
    if (!$ntype = $ntypes[$node->type]) {
      return;
    }
    self::doNodePrepare($ntype, $node);
  }


  /**
   * Implements hook_node_validate().
   */
  public static function hookNodeValidate($node) {
    // Only deal with node types that have the Node expire feature enabled.
    $ntypes = variable_get('node_expire_ntypes', array());
    if (!isset($ntypes[$node->type])) {
      return;
    }
    if (!$ntype = $ntypes[$node->type]) {
      return;
    }
    module_load_include('nodeapi.inc', 'node_expire');
    self::doNodeValidate($ntype, $node);
  }

  /**
   * Implements hook_nodeapi_update().
   */
  public static function hookNodeUpdate($node) {
    // Only deal with node types that have the Node expire feature enabled.
    $ntypes = variable_get('node_expire_ntypes', array());
    if (!isset($ntypes[$node->type])) {
      return;
    }
    if (!$ntype = $ntypes[$node->type]) {
      return;
    }
    module_load_include('nodeapi.inc', 'node_expire');
    self::doNodeUpdateInsert($ntype, $node);
  }

  /**
   * Implements hook_nodeapi_insert().
   */
  public static function hookNodeInsert($node) {
    // Only deal with node types that have the Node expire feature enabled.
    $ntypes = variable_get('node_expire_ntypes', array());
    if (!isset($ntypes[$node->type])) {
      return;
    }
    if (!$ntype = $ntypes[$node->type]) {
      return;
    }
    module_load_include('nodeapi.inc', 'node_expire');
    self::doNodeUpdateInsert($ntype, $node);
  }

  /**
   * Implements hook_nodeapi_delete().
   */
  public static function hookNodeDelete($node) {
    // Only deal with node types that have the Node expire feature enabled.
    $ntypes = variable_get('node_expire_ntypes', array());
    if (!isset($ntypes[$node->type])) {
      return;
    }
    // TODO: WARNING | Unused variable $ntype.
    if (!$ntype = $ntypes[$node->type]) {
      return;
    }
    DbHandler::deleteNodeExpire($node->nid);
  }

  /**
   * Implements hook_node_load().
   */
  private static function doNodeLoad($nodes, $types) {
    // Only deal with node types that have the Node expire feature enabled.
    $ntypes = variable_get('node_expire_ntypes', array());
    $node_expire_enabled = array();

    // Check if node_expire are enabled for each node.
    // If node_expires are not enabled, do nothing.
    foreach ($nodes as $node) {
      // Store whether node_expires are enabled for this node.
      if ((isset($ntypes[$node->type])) and ($ntypes = $ntypes[$node->type])) {
        $node_expire_enabled[] = $node->nid;
      }
    }

    // For nodes with node_expire enabled, fetch information from the database.
    if (!empty($node_expire_enabled)) {
      $handle_content_expiry = ConfigHandler::getHandleContentExpiry();
      $result = DbHandler::selectForNodeLoad($node_expire_enabled);
      foreach ($result as $record) {
        if ($handle_content_expiry == 0) {
          $nodes[$record->nid]->expire = $record->expire;
        }
        else {
          $ntype = isset($ntypes[$record->type]) ? $ntypes[$record->type] : NULL;
          $nodes[$record->nid]->expire = TimestampUtils::dateDbToStr($record->expire, $ntype);
        }
        $nodes[$record->nid]->expired = $record->expired;
        $nodes[$record->nid]->lastnotify = $record->lastnotify;
      }
    }
  }

  /**
   * Implements hook_node_prepare().
   */
  private static function doNodePrepare(&$ntype, $node) {
    // To prevent default value 1969-12-31 check also $ntypes['default'].
    if (!isset($node->expire) && $ntype['default']) {
      $node->expire = TimestampUtils::dateStrFromCfgDefault($ntype['default'],
        FALSE);
    }
    // This gives a way to users without edit exipration permission
    // to update nodes with default expiration.
    if (isset($node->expire) && !user_access('edit node expire')) {
      $node->expire = TimestampUtils::dateStrFromCfgDefault($ntype['default'],
        FALSE);
    }
  }

  /**
   * Implements hook_node_validate().
   */
  private static function doNodeValidate(&$ntype, $node) {

    $handle_content_expiry = ConfigHandler::getHandleContentExpiry();
    if ($handle_content_expiry != 0) {
      if (!isset($ntype['enabled']) || !$ntype['enabled']) {
        return;
      }
    }

    // The only restriction we have is that the node can't expire in the past.
    if ($node->expire == '') {
      if (!empty($ntype['required']) && $ntype['default']) {
        form_set_error('expire_date', t('You must choose an expiration date.'));
      }
    }
    // TODO: WARNING | Variable $expire is undefined.
    elseif (!$expire = strtotime($node->expire) or $expire <= 0) {
      form_set_error('expire_date', t('You have to specify a valid expiration date.'));
    }
    elseif (variable_get('node_expire_past_date_allowed', 0) == 0 && $expire <= REQUEST_TIME) {
      form_set_error('expire_date', t("You can't expire a node in the past!"));
    }
    elseif (!empty($ntype['max']) and $expire > strtotime($ntype['max'])) {
      form_set_error('expire_date', t('It must expire before %date.',
        array(
          '%date' => format_date(strtotime($ntype['max']), 'custom', ConfigHandler::getDateFormat()),
        )));
    }
  }

  /**
   * Implements hook_node_update() and hook_node_insert().
   */
  private static function doNodeUpdateInsert(&$ntype, $node) {
    $handle_content_expiry = ConfigHandler::getHandleContentExpiry();
    if ($handle_content_expiry == 0) {
      // Old (legacy) style of processing.
      // Has the expiration been removed, or does it exist?
      if (isset($node->expire)) {
        DbHandler::deleteNodeExpire($node->nid);
        // Should we create a new record?
        if ($node->expire) {
          if (strtotime($node->expire)) {
            $node->expire = strtotime($node->expire);
          }
          $node->expired = FALSE;
          drupal_write_record('node_expire', $node);
        }
      }
    }
    else {
      if (!isset($ntype['enabled']) || !$ntype['enabled']) {
        return;
      }

      // Create a proper $node_expire stdClass.
      $node_expire = new \stdClass();
      $node_expire->nid = $node->nid;

      // For compatibility with Node Clone module.
      // Set default $node->expire value if it is not set.
      if (!isset($node->expire)) {
        // _node_expire_node_prepare($ntype, $node);
        self::doNodePrepare($ntype, $node);
      }

      // Expire.
      $date_expire = TimestampUtils::dateStrToDb($node->expire, $ntype);
      $node_expire->expire = $date_expire;

      // Lastnotify.
      if (isset($node->lastnotify)) {
        $node_expire->lastnotify = $node->lastnotify;
      }
      else {
        // Default value.
        $node_expire->lastnotify = 0;
      }

      // Expired.
      if (isset($node->expired)) {
        $node_expire->new_record = 0;
        $node_expire->expired = $node->expired;
        if ($node_expire->expire >= NODE_EXPIRE_NO_EXPIRE) {
          // No expiry for this node.
          $node_expire->expired = 0;
        }
      }
      elseif (isset($node->original->expired)) {
        // For VBO (Views Bulk Operations) compatibility.
        // With VBO it is necessary to get all Node expire information
        // from $node->original instead of $node.
        $node_expire->new_record = 0;
        $node_expire->expired = $node->original->expired;
        // Also get other Node expire values.
        // Expire.
        $date_expire = TimestampUtils::dateStrToDb($node->original->expire, $ntype);
        $node_expire->expire = $date_expire;
        // Lastnotify.
        if (isset($node->original->lastnotify)) {
          $node_expire->lastnotify = $node->original->lastnotify;
        }
        else {
          // Default value.
          $node_expire->lastnotify = 0;
        }

        if ($node_expire->expire >= NODE_EXPIRE_NO_EXPIRE) {
          // No expiry for this node.
          $node_expire->expired = 0;
        }
      }
      else {
        // No record in the database yet.
        $node_expire->new_record = 1;
        // Default value.
        $node_expire->expired = 0;
      }

      // Write the record.
      DbHandler::writeRecord($node_expire, $node->nid);
    }
  }

}
