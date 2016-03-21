<?php

/**
 * @file
 * Views module integration.
 */

/**
 * Implements hook_views_data().
 */
function node_expire_views_data() {
  // Join to 'node' as a base table.
  $data['node_expire']['table']['group']  = t('Node');
  $data['node_expire']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
  );

  $data['node_expire']['expire'] = array(
    'title' => t('Expire date'),
    'help' => t('Date of when the content expire.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );
  $data['node_expire']['expired'] = array(
    'title' => t('Expired'),
    'help' => t('Whether the content is expired.'),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_boolean_operator',
      'label' => t('Expired'),
      'type' => 'yes-no',
      'accept_null' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  return $data;
}
