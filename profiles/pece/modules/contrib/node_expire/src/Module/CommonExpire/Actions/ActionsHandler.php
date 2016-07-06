<?php

/**
 * @file
 * ActionsHandler class.
 */

namespace Drupal\node_expire\Module\CommonExpire\Actions;

use Drupal\node_expire\Module\CommonExpire\Exception\ExpireException;
use Drupal\node_expire\Module\CommonExpire\Node\NodeHelper;

/**
 * ActionsHandler class.
 */
class ActionsHandler {

  /**
   * Executes particular action with the node..
   */
  public static function doAction($action_type, $nid) {

    switch ($action_type) {
      case ActionTypeEnum::NONE:
        // Do nothing.
        break;

      case ActionTypeEnum::RULES_EVENT:
        if (module_exists('rules')) {
          $node = node_load($nid);
          rules_invoke_event('node_expired', $node);
        }
        else {
          throw new ExpireException(t('Module Rules is not installed.'));
        }
        break;

      case ActionTypeEnum::NODE_PUBLISH:
        NodeHelper::publishNode($nid);
        break;

      case ActionTypeEnum::NODE_UNPUBLISH:
        NodeHelper::unpublishNode($nid);
        break;

      case ActionTypeEnum::NODE_STICKY:
        NodeHelper::makeNodeSticky($nid);
        break;

      case ActionTypeEnum::NODE_UNSTICKY:
        NodeHelper::makeNodeUnsticky($nid);
        break;

      case ActionTypeEnum::NODE_PROMOTE_TO_FRONT:
        NodeHelper::promoteNode($nid);
        break;

      case ActionTypeEnum::NODE_REMOVE_FROM_FRONT:
        NodeHelper::unpromoteNode($nid);
        break;

      default:
        // Do nothing.
        break;
    }

  }

}
