<?php

/**
 * @file
 * Views integration for nodeorder module.
 */

/**
 * Implements hook_views_data_alter().
 */
function nodeorder_views_data_alter(&$data) {
  // Taxonomy weight.
  $data['taxonomy_index']['weight'] = array(
    'title' => t('Weight in tid'),
    'help' => t('The term weight in tid field'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );
  // Link to order page.
  $data['taxonomy_term_data']['order_link'] = array(
    'field' => array(
      'title' => t('Order link'),
      'help' => t('Provide a simple link to order the nodes related to the term.'),
      'handler' => 'nodeorder_handler_order_link',
    ),
  );
}
