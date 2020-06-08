<?php

/**
 * @file
 * Definition of nodeorder_handler_order_link.
 */

class nodeorder_handler_order_link extends views_handler_field_term_link_edit {
  /**
   * {@inheritdoc}
   */
  function render($values) {
    // Check there is an actual value, as on a relationship there may not be.
    if ($tid = $this->get_value($values, 'tid')) {
      if (nodeorder_order_access($tid)) {
        $text = !empty($this->options['text']) ? $this->options['text'] : t('order');
        return l($text, 'taxonomy/term/'. $tid . '/order', array('query' => drupal_get_destination()));
      }
    }
  }
}
