<?php

/**
 * @file
 * CommonHookHandler class.
 */

namespace Drupal\node_expire\Module\Hook;

use Drupal\node_expire\Module\CommonExpire\Actions\ActionsHandler;
use Drupal\node_expire\Module\Config\ConfigHandler;
use Drupal\node_expire\Module\Config\NodeTypesConfigHandler;
use Drupal\node_expire\Module\Db\DbHandler;

/**
 * CommonHookHandler class.
 */
class CommonHookHandler {

  /**
   * Implements hook_cron().
   */
  public static function hookCron() {
    $handle_content_expiry = ConfigHandler::getHandleContentExpiry();
    if ($handle_content_expiry != 2) {
      $result = DbHandler::selectExpired();
    }
    else {
      $result = DbHandler::selectExpiredNonFlagged();
    }
    // $nids = array();
    // Create NodeTypesConfigHandler once for whole cycle.
    $config_handler = new NodeTypesConfigHandler();
    foreach ($result as $record) {
      // Try to handle the record.
      try {
        // $nids[] = $record->nid;
        $node_type = $record->type;
        $action_type = $config_handler->getActionType($node_type);
        $nid = $record->nid;
        DbHandler::setExpired($nid);
        // $node = node_load($record->nid);
        // rules_invoke_event('node_expired', $node);
        ActionsHandler::doAction($action_type, $nid);
      }
      catch (\Exception $e) {
        // TODO: Add configurable logging.
      }
    }
  }

  /**
   * Implements hook_menu().
   */
  public static function hookMenu() {
    $items['admin/config/workflow/node_expire/settings'] = array(
      'title' => 'Node Expire',
      'description' => 'Configure node expire settings.',
      'page callback' => 'drupal_get_form',
      'page arguments' => array('node_expire_admin_settings'),
      'access arguments' => array('administer site configuration'),
      'type' => MENU_NORMAL_ITEM,
      'file' => 'node_expire.admin.inc',
      'weight' => 2,
    );

    return $items;
  }

  /**
   * Implements hook_permission().
   */
  public static function hookPermission() {
    return array(
      'administer node expire' => array(
        'title' => t('Administer node expire'),
        'description' => t('Administer node expire functionality.'),
      ),
      'edit node expire' => array(
        'title' => t('Edit node expire'),
        'description' => t('Edit node expiration dates.'),
      ),
    );
  }

}
