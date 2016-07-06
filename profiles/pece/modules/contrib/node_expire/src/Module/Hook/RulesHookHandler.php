<?php

/**
 * @file
 * RulesHookHandler class.
 */

namespace Drupal\node_expire\Module\Hook;

/**
 * RulesHookHandler class.
 */
class RulesHookHandler {

  /**
   * Implements hook_rules_action_info().
   *
   * @ingroup rules
   */
  public static function hookRulesActionInfo() {
    return array(
      'node_expire_unset_expired' => array(
        'arguments' => array(
          'node' => array('type' => 'node', 'label' => t('content expired')),
        ),
        'label' => t('Unset the expired flag'),
        'module' => 'node_expire',
      ),
      'node_expire_update_lastnotify' => array(
        'arguments' => array(
          'node' => array(
            'type' => 'node',
            'label' => t('content expired'),
          ),
        ),
        'label' => t('Update lastnotify'),
        'module' => 'node_expire',
      ),
    );
  }

  /**
   * Implements hook_rules_condition_info().
   *
   * @ingroup rules
   */
  public static function hookRulesConditionInfo() {
    return array(
      'node_expire_rules_expired_check' => array(
        'arguments' => array(
          'node' => array('type' => 'node', 'label' => t('Content')),
        ),
        'label' => t('Content is expired'),
        'help' => 'Evaluates to TRUE, if the given content has one of the selected content types.',
        'module' => 'node_expire',
      ),
      'node_expire_rules_expired_check_lastnotify' => array(
        'arguments' => array(
          'node' => array(
            'type' => 'node',
            'label' => t('Content'),
          ),
        ),
        'label' => t('Content is expired: Check lastnotify'),
        'help' => 'Evaluates to TRUE, if the given content is expired and lastnotified 2 weeks ago.',
        'module' => 'node_expire',
      ),
      'node_expire_rules_expired_check_lastnotify_is_set' => array(
        'arguments' => array(
          'node'      => array('type' => 'node', 'label' => t('Content')),
        ),
        'label'     => t('Content is expired: Check lastnotify is set'),
        'help'      => 'Evaluates to TRUE, if the given content is expired and lastnotified is set.',
        'module' => 'node_expire',
      ),
    );
  }

  /**
   * Implements hook_rules_event_info().
   *
   * @ingroup rules
   */
  public static function hookRulesEventInfo() {
    $events['node_expired'] = array(
      'label' => t('content expired'),
      'group' => t('Node'),
      'variables' => array(
        'node' => array(
          'type' => 'node',
          'label' => t('Node'),
        ),
      ),
    );
    return $events;
  }

}
