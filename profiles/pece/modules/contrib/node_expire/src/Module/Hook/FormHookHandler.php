<?php

/**
 * @file
 * FormHookHandler class.
 */

namespace Drupal\node_expire\Module\Hook;


use Drupal\node_expire\Module\CommonExpire\Actions\ActionsHelper;
use Drupal\node_expire\Module\CommonExpire\Actions\ActionTypeEnum;
use Drupal\node_expire\Module\Config\ConfigHandler;
use Drupal\node_expire\Module\Utils\TimestampUtils;


/**
 * FormHookHandler class.
 */
class FormHookHandler {

  /**
   * Implements hook_form_node_type_form_alter().
   *
   * Enable/Disable expiration feature on node types.
   */
  public static function hookFormNodeTypeFormAlter(&$form, &$form_state) {
    if (user_access('administer node expire')) {
      $ntypes = variable_get('node_expire_ntypes', array());
      $node_type  = $form['#node_type']->type;
      $handle_content_expiry = ConfigHandler::getHandleContentExpiry();
      if ($handle_content_expiry != 0) {
        // TODO: make both branches via common function.
        $form['workflow']['node_expire_type_cfg_enabled'] = array(
          '#title' => t('Enable Node Expiry'),
          '#description' => t('Allow nodes to expire after a certain amount of time.'),
          '#type' => 'checkbox',
          '#default_value' => empty($ntypes[$node_type]['enabled']) ? '' : $ntypes[$node_type]['enabled'],
        );

        // Visibility.
        $states = array(
          'visible' => array(
            ':input[name="node_expire_type_cfg_enabled"]' => array('checked' => TRUE),
          ),
        );

        $form['workflow']['node_expire_container'] = array(
          '#type' => 'fieldset',
          '#title' => t('Node Expire'),
          '#collapsible' => TRUE,
          '#collapsed' => FALSE,
          '#states' => $states,
        );

        // Text fields.
        // $form['workflow']['node_expire_container']['node_expire'] = array(
        $form['workflow']['node_expire_container']['node_expire_type_cfg_default'] = array(
          '#title' => t('Default expiration date'),
          '#description' => t('Default date to consider the node expired.') . ' ' . t('Format: PHP <a href="http://www.php.net/strtotime" target="_blank">strtotime format</a>.'),
          '#type' => 'textfield',
          // TODO: Create special class method(s) for default values.
          '#default_value' => empty($ntypes[$node_type]['default']) ? '' : TimestampUtils::dateStrFromCfgDefault($ntypes[$node_type]['default']),
          '#states' => $states,
        );
        $form['workflow']['node_expire_container']['node_expire_type_cfg_max'] = array(
          '#title' => t('Expiration date limit'),
          '#description' => t('The max date to consider the node expired.') . ' ' . t('Format: PHP <a href="http://www.php.net/strtotime" target="_blank">strtotime format</a>.') . ' ' . t('Leave it blank if this there is no limit date.'),
          '#type' => 'textfield',
          // TODO: Create special class method(s) for default values.
          '#default_value' => empty($ntypes[$node_type]['max']) ? '' : TimestampUtils::dateStrFromCfgDefault($ntypes[$node_type]['max']),
          '#states' => $states,
        );

        $form['workflow']['node_expire_container']['node_expire_type_cfg_required'] = array(
          '#title' => t('Expiration date required'),
          '#type' => 'checkbox',
          '#default_value' => !empty($ntypes[$node_type]['required']),
          '#states' => $states,
        );
        $options = ActionsHelper::getActionOptions();
        $form['workflow']['node_expire_container']['node_expire_type_cfg_action_type'] = array(
          '#type'          => 'select',
          '#title'         => t('Action to do'),
          '#default_value' => self::getActionType($ntypes, $node_type),
          '#options'       => $options,
          '#description'   => t('Action to do.'),
          '#states' => $states,
        );
      }
      else {
        $form['workflow']['node_expire_type_cfg_default'] = array(
          '#title' => t('Default expiration date'),
          '#description' => t('Default date to consider the node expired.') . ' ' . t('Format: PHP <a href="http://www.php.net/strtotime" target="_blank">strtotime format</a>.') . ' ' . t('Leave it blank if this content type never expires.'),
          '#type' => 'textfield',

          '#default_value' => empty($ntypes[$node_type]['default']) ? '' : $ntypes[$node_type]['default'],
        );
        $form['workflow']['node_expire_type_cfg_max'] = array(
          '#title' => t('Expiration date limit'),
          '#description' => t('The max date to consider the node expired.') . ' ' . t('Format: PHP <a href="http://www.php.net/strtotime" target="_blank">strtotime format</a>.') . ' ' . t('Leave it blank if this there is no limit date.'),
          '#type' => 'textfield',

          '#default_value' => empty($ntypes[$node_type]['max']) ? '' : $ntypes[$node_type]['max'],
        );
        $form['workflow']['node_expire_type_cfg_required'] = array(
          '#title' => t('Expiration date required'),
          '#type' => 'checkbox',
          '#default_value' => !empty($ntypes[$node_type]['required']),
        );
      }
      // Add special validate/submit functions.
      // Referenced in the bottom of node_expire.module
      // module_load_include('ntype.inc', 'node_expire');
      $form['#validate'][]  = '_node_expire_form_node_type_form_alter_validate';
      $form['#submit'][]    = '_node_expire_form_node_type_form_alter_submit';
    }
  }

  /**
   * Returns Action Type for particular Node Type.
   */
  private static function getActionType(&$ntypes, $node_type) {
    // TODO: Make use of similar function from common config classes.
    if (!isset($ntypes[$node_type]['action_type'])) {
      return ActionsHelper::filterForRules(ActionTypeEnum::RULES_EVENT);
    }
    else {
      return ActionsHelper::filterForRules($ntypes[$node_type]['action_type']);
    }
  }

  /**
   * Implements hook_form_alter().
   *
   * Adds expiration options to the node entry forms.
   */
  public static function hookFormAlter(&$form, &$form_state, $form_id) {
    if ((isset($form['type'])) &&
      (isset($form['type']['#value']) && is_string($form['type']['#value'])) &&
      ($form['type']['#value'] . '_node_form' == $form_id) &&
      ($ntypes = variable_get('node_expire_ntypes', array())) &&
      (isset($ntypes[$form['type']['#value']])) &&
      ($ntype = $ntypes[$form['type']['#value']])) {
      self::doFormAlter($ntype, $form, $form_state, $form_id);
    }
  }

  /**
   * Implements hook_form_alter().
   *
   * Adds expiration options to the node entry forms.
   */
  private static function doFormAlter(&$ntype, &$form, &$form_state, $form_id) {
    // Check if the Node expire feature is enabled for the node type.
    $node = isset($form['#node']) ? $form['#node'] : NULL;

    $handle_content_expiry = ConfigHandler::getHandleContentExpiry();
    if ($handle_content_expiry != 0) {
      if (empty($ntype['enabled'])) {
        return;
      }
      // Replace not set to default string.
      if (!isset($node->expire)) {
        // $ntype = isset($ntypes[$node->type]) ? $ntypes[$node->type] : NULL;
        $node->expire = TimestampUtils::dateDbToStr('', $ntype);
      }
    }
    else {
      // Replace not set to empty string.
      if (!isset($node->expire)) {
        $node->expire = '';
      }
      // Convert the timestamp into a human readable date - legacy branch.
      if (is_numeric($node->expire)) {
        $node->expire = format_date($node->expire, 'custom',
          ConfigHandler::getDateFormat());
      }
    }

    // This supports node to never expire.
    if (empty($ntype['default']) && empty($node->expire)) {
      $ntype['required'] = FALSE;
    }
    if (user_access('edit node expire')) {
      if (ConfigHandler::getDateEntryElements()) {
        // Date popups.
        // TODO: Edit format description sting.
        $expire_field = array(
          '#title' => t('Expiration date'),
          '#description' => t('Time date to consider the node expired. Format: %time (%format).',
            array(
              '%time' => format_date(REQUEST_TIME, 'custom', ConfigHandler::getDateFormat()),
              '%format' => ConfigHandler::getDateFormat(),
            )
          ),
          '#type' => 'date_popup',
          '#date_format' => ConfigHandler::getDateFormat(),
          '#required' => $ntype['required'],
          '#default_value' => $node->expire,
        );
      }
      else {
        // Text fields.
        // TODO: Edit format description sting.
        $expire_field = array(
          '#title' => t('Expiration date'),
          '#description' => t('Time date to consider the node expired. Format: %time (%format).',
            array(
              '%time' => format_date(REQUEST_TIME, 'custom', ConfigHandler::getDateFormat()),
              '%format' => ConfigHandler::getDateFormat(),
            )
          ),
          '#type' => 'textfield',
          '#maxlength' => 25,
          '#required' => $ntype['required'],
          '#default_value' => $node->expire,
        );
      }
    }
    else {
      $expire_field = array(
        '#type' => 'value',
        '#value' => $node->expire,
      );
    }

    // If we use hidden value, do not create fieldset.
    if ($expire_field['#type'] == 'value') {
      $form['options1'] = array();
      $form['options1']['expire'] = &$expire_field;
    }
    // If the form doesn't have the publishing options we'll create our own.
    elseif (!$form['options']['#access']) {
      $form['options1'] = array(
        '#type' => 'fieldset',
        '#title' => t('Publishing options'),
        '#collapsible' => TRUE,
        '#collapsed' => FALSE,
        '#weight' => 95,
      );
      $form['options1']['expire'] = &$expire_field;
    }
    else {
      $form['options']['expire'] = &$expire_field;
    }

    if (isset($node->expired)) {
      $form['node_expire'] = array(
        '#type' => 'value',
        '#value' => TRUE,
      );
    }
  }

}
