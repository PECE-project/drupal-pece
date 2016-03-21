<?php

/**
 * @file
 * Node type integration.
 */

/**
 * Implements hook_form_alter().
 */
function _node_expire_form_node_type_form_alter_validate(&$form, &$form_state) {
  $node_expire = &$form_state['values']['node_expire'];
  if (!empty($node_expire) and !strtotime($node_expire)) {
    form_set_error('node_expire',
      t('This values should be in PHP <a href="http://www.php.net/strtotime" target="_blank">strtotime format</a>.'));
  }

  $node_expire_max = &$form_state['values']['node_expire_max'];
  if (!empty($node_expire_max)) {
    if (!strtotime($node_expire_max)) {
      form_set_error('node_expire_max',
        t('This values should be in PHP <a href="http://www.php.net/strtotime" target="_blank">strtotime format</a>.'));
    }
    elseif (strtotime($node_expire) > strtotime($node_expire_max)) {
      form_set_error('node_expire_max',
        t('This value cannot be earlier then the default value.'));
    }
  }

  $node_expire_required = &$form_state['values']['node_expire_required'];
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
function _node_expire_form_node_type_form_alter_submit(&$form, &$form_state) {
  $ntypes = variable_get('node_expire_ntypes', array());

  $handle_content_expiry = variable_get('node_expire_handle_content_expiry', 2);
  if ($handle_content_expiry != 0) {
    $ntypes[$form_state['values']['type']]['enabled']   = $form_state['values']['node_expire_enabled'];
  }

  $ntypes[$form_state['values']['type']]['default']   = $form_state['values']['node_expire'];
  $ntypes[$form_state['values']['type']]['max']       = $form_state['values']['node_expire_max'];
  $ntypes[$form_state['values']['type']]['required']  = $form_state['values']['node_expire_required'];

  variable_set('node_expire_ntypes', $ntypes);
}
