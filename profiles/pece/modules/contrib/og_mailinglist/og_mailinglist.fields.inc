<?php

/**
 * @file
 * Defines group_email field type.
 */

require_once 'og_mailinglist_common.inc';

/**
 * Group email field.
 */
define('OG_MAILINGLIST_EMAIL_FIELD', 'group_email');

/**
 * Implements hook_field_create_instance().
 *
 * Adds group_email field to any OG group which is created after enabling
 * og_mailinglist module. OG group is created by adding group_group field.
 */
function og_mailinglist_field_create_instance($instance) {
  if ($instance['field_name'] == OG_GROUP_FIELD) {
    og_create_field(OG_MAILINGLIST_EMAIL_FIELD, 'node', $instance['bundle']);
  }
}

/**
 * Implements hook_og_fields_info().
 */
function og_mailinglist_og_fields_info() {
  return array(
    OG_MAILINGLIST_EMAIL_FIELD => array(
      'type' => array('group'),
      'property_type' => 'group',
      'default_formatter' => 'group_email',
      'default_widget' => 'group_email',
      'description' => t('Group email address prefix. This field is required on group nodes for OG Mailinglist.'),
      'field' => array(
        'field_name' => OG_MAILINGLIST_EMAIL_FIELD,
        'type' => 'group_email',
        'no_ui' => TRUE,
        'cardinality' => 1,
      ),
      'instance' => array(
        'label' => t('Group Email'),
        'description' => t('Choose an email address prefix for your group. It may contain only lowercase letters, numbers, dashes and underscores. e.g. "my-group".'),
        'required' => TRUE,
        'widget' => array(
          'module' => 'og_mailinglist',
        ),
      ),
    ),
  );
}

/**
 * Implements hook_field_info().
 */
function og_mailinglist_field_info() {
  return array(
    'group_email' => array(
      'label' => t('Group Email'),
      'description' => t('Choose an email address prefix for your group. It may contain only lowercase letters, numbers, dashes and underscores. e.g. "my-group".'),
      'default_widget' => 'group_email',
      'default_formatter' => 'group_email',
      'no_ui' => True,
    ),
  );
}

/**
 * Implements hook_field_validate().
 *
 * Possible error codes:
 * - 'wrong_characters': The value contains characters which are not allowed.
 * - 'not_unique': Such a value is already present.
 */
function og_mailinglist_field_validate($entity_type, $entity, $field, $instance, $langcode, $items, &$errors) {
  if  (!empty($node->op) && $node->op === $node->delete) {
    return;
  }

  foreach ($items as $delta => $item) {
    if ($item['value'] != '') {
      if (!preg_match('!^[\.a-z0-9_-]+$!', $item['value'])) {
        $errors[$field['field_name']][$langcode][$delta][] = array(
          'error' => 'wrong_characters',
          'message' => t('Only lowercase letters, numbers, dashes and underscores are allowed in %name, e.g. "my-group"', array('%name' => $instance['label'])),
        );
      }
      else {
        $db = $field['storage']['details']['sql']['FIELD_LOAD_CURRENT'];
        $db_table = key($db);
        $db_field = $db[$db_table]['value'];

        $query = db_select($db_table);
        $query->condition($db_field, $item['value']);
        if (!empty($entity->nid)) {
          $query->condition('entity_id', $entity->nid, '!=');
        }
        $result = $query->countQuery()->execute()->fetchField();

        if ($result > 0) {
          $errors[$field['field_name']][$langcode][$delta][] = array(
            'error' => 'not_unique',
            'message' => t('%name: this group email address is already taken. Please choose another.', array('%name' => $instance['label'])),
          );
        }
      }
    }
  }
}

/**
 * Implements hook_field_is_empty().
 */
function og_mailinglist_field_is_empty($item, $field) {
  if (empty($item['value'])) {
    return TRUE;
  }
  return FALSE;
}

/**
 * Implements hook_field_formatter_info().
 */
function og_mailinglist_field_formatter_info() {
  return array(
    'group_email' => array(
      'label' => t('Group email'),
      'field types' => array('group_email'),
    ),
    'group_email_link' => array(
      'label' => t('Group email link'),
      'field types' => array('group_email'),
    ),
  );
}

/**
 * Implements hook_field_formatter_prepare_view().
 */
function og_mailinglist_field_formatter_prepare_view($entity_type, $entities, $field, $instances, $langcode, $items, $displays) {
  $server = og_mailinglist_server();
  foreach ($items as $delta => $item) {
    foreach ($item as $id => $inst) {
      $items[$delta][$id]['value'] = $inst['value'] . '@' . $server;
    }
  }
}

/**
 * Implements hook_field_formatter_view().
 */
function og_mailinglist_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();

  foreach ($items as $delta => $item) {
    if ($display['type'] == 'group_email_link') {
      $element[$delta] = array('#markup' => l($item['value'], 'mailto:' . $item['value']));
    }
    else {
      $element[$delta] = array('#markup' => $item['value']);
    }
  }
  return $element;
}

/**
 * Implements hook_field_widget_info().
 */
function og_mailinglist_field_widget_info() {
  return array(
    'group_email' => array(
      'label' => t('Group email'),
      'field types' => array('group_email'),
    ),
  );
}

/**
 * Implements hook_field_widget_form().
 */
function og_mailinglist_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {
  $value = isset($items[$delta]['value']) ? $items[$delta]['value'] : '';
  $suffix = '@' . og_mailinglist_server();

  $element += array(
    '#type' => 'textfield',
    '#default_value' => $value,
    '#size' => 24,
    '#maxlength' => 64,
    '#field_suffix' => $suffix,
  );
  $element['#element_validate'][] = 'og_mailinglist_field_widget_validate';

  return array('value' => $element);
}

/**
 * FAPI validation of an individual email element.
 */
function og_mailinglist_field_widget_validate($element, &$form_state) {
  if  (!empty($node->op) && $node->op === $node->delete) {
    return;
  }

  $instance = field_widget_instance($element, $form_state);
  $value = $element['#value'];

  // Reject invalid characters.
  if (!empty($value)) {
    if (!preg_match('!^[\.a-z0-9_-]+$!', $value)) {
      $message = t('Only lowercase letters, numbers, dashes and underscores are allowed in %name, e.g. "my-group"',
        array('%name' => $instance['label']));
      form_error($element, $message);
    }

    form_set_value($element, $value, $form_state);
  }
}

/**
 * Implements hook_field_widget_error().
 */
function og_mailinglist_field_widget_error($element, $error, $form, &$form_state) {
  form_error($element['value'], $error['message']);
}
