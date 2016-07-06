<?php

/**
 * @file
 * ActionsHelper class.
 */

namespace Drupal\node_expire\Module\CommonExpire\Actions;

/**
 * ActionsHelper class.
 */
class ActionsHelper {

  /**
   * Makes Action options array for Form UI.
   */
  public static function getActionOptions() {
    $arr = array();

    // 0.
    $arr[ActionTypeEnum::NONE] = t('None (do nothing)');

    // 1.
    if (module_exists('rules')) {
      $arr[ActionTypeEnum::RULES_EVENT] = t('Invoke Rules event');
    }

    // 2.
    $arr[ActionTypeEnum::NODE_PUBLISH] = t('Node publish');
    // 3.
    $arr[ActionTypeEnum::NODE_UNPUBLISH] = t('Node unpublish');
    // 4.
    $arr[ActionTypeEnum::NODE_STICKY] = t('Make node sticky');
    // 5.
    $arr[ActionTypeEnum::NODE_UNSTICKY] = t('Make node unsticky');
    // 6.
    $arr[ActionTypeEnum::NODE_PROMOTE_TO_FRONT] = t('Promote node to front page');
    // 7.
    $arr[ActionTypeEnum::NODE_REMOVE_FROM_FRONT] = t('Remove node from front page');

    return $arr;
  }

  /**
   * Converts Action type RULES_EVENT to NONE if Rules module is not installed.
   */
  public static function filterForRules($in) {
    $out = $in;
    if ($out == ActionTypeEnum::RULES_EVENT) {
      if (!module_exists('rules')) {
        $out = ActionTypeEnum::NONE;
      }
    }
    return $out;
  }

}
