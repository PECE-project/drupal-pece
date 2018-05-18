<?php
/**
 * @file
 * This field handler aggregates operations that can be done on a notice
 * under a single field providing a more flexible way to present them in a view
 */
class site_notice_handler_site_notice_operations_field extends views_handler_field {
  function construct() {
    parent::construct();
    $this->additional_fields['snid'] = 'snid';
    $this->additional_fields['name'] = 'name';
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    $links = menu_contextual_links('site_notice', 'admin/content/site-notices', array($this->get_value($values, 'snid')));

    if (!empty($links)) {
      return theme('links', array('links' => $links, 'attributes' => array('class' => array('links', 'inline', 'operations'))));
    }
  }
}
