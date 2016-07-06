<?php

/**
 * @file
 * FormHookHelper class.
 */

namespace Drupal\node_expire\Module\Hook;


use Drupal\node_expire\Module\CommonExpire\Actions\ActionsHelper;
use Drupal\node_expire\Module\Config\ConfigHandler;
use Drupal\node_expire\Module\Utils\ModuleUtils;
use Drupal\node_expire\Module\Utils\TimestampUtils;

/**
 * FormHookHelper class.
 */
class FormHookHelper {


  /**
   * Implements hook_form_alter().
   */
  public static function doFormNodeTypeFormAlterValidate(&$form, &$form_state) {
    $node_expire = &$form_state['values']['node_expire_type_cfg_default'];
    if (!empty($node_expire) and !strtotime($node_expire)) {
      form_set_error('node_expire',
        t('This values should be in PHP <a href="http://www.php.net/strtotime" target="_blank">strtotime format</a>.'));
    }

    $node_expire_max = &$form_state['values']['node_expire_type_cfg_max'];
    if (!empty($node_expire_max)) {
      if (!strtotime($node_expire_max)) {
        form_set_error('node_expire_max',
          t('This values should be in PHP <a href="http://www.php.net/strtotime" target="_blank">strtotime format</a>.'));
      }
      elseif (strtotime($node_expire) > strtotime($node_expire_max)) {
        form_set_error('node_expire_max',
          t('This value cannot be earlier then the maximum value.'));
      }
    }

    $node_expire_required = &$form_state['values']['node_expire_type_cfg_required'];
    if (!empty($node_expire_required)) {
      if (empty($node_expire)) {
        form_set_error('node_expire',
          t('Default expiration date should be set with expiration date required.'));
      }
    }
  }

  /**
   * Implements hook_form_alter().
   */
  public static function doFormNodeTypeFormAlterSubmit(&$form, &$form_state) {
    $ntypes = variable_get('node_expire_ntypes', array());

    $handle_content_expiry = ConfigHandler::getHandleContentExpiry();
    if ($handle_content_expiry != 0) {
      $ntypes[$form_state['values']['type']]['enabled']   = $form_state['values']['node_expire_type_cfg_enabled'];
    }

    // TODO: replace ['node_expire'] => ['node_expire_default'],
    // after that optimize.
    $ntypes[$form_state['values']['type']]['default']
      = TimestampUtils::dateStrToCfgDefault($form_state['values']['node_expire_type_cfg_default']);
    $ntypes[$form_state['values']['type']]['max']
      = TimestampUtils::dateStrToCfgDefault($form_state['values']['node_expire_type_cfg_max']);
    $ntypes[$form_state['values']['type']]['required']
      = $form_state['values']['node_expire_type_cfg_required'];
    $ntypes[$form_state['values']['type']]['action_type']
      = ActionsHelper::filterForRules($form_state['values']['node_expire_type_cfg_action_type']);

    variable_set('node_expire_ntypes', $ntypes);

    ModuleUtils::doVariablesCleanup();
  }

}
