<?php

/**
 * @file
 * ActionTypeEnum class.
 */

namespace Drupal\node_expire\Module\CommonExpire\Actions;

/**
 * ActionTypeEnum class.
 */
class ActionTypeEnum {
  const NONE = 0;
  const RULES_EVENT = 1;
  const NODE_PUBLISH = 2;
  const NODE_UNPUBLISH = 3;
  const NODE_STICKY = 4;
  const NODE_UNSTICKY = 5;
  const NODE_PROMOTE_TO_FRONT = 6;
  const NODE_REMOVE_FROM_FRONT = 7;

}
