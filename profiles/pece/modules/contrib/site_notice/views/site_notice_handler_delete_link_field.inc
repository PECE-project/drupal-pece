<?php
/**
 * @file
 * Contains a Views field handler to take care of displaying deletes links
 * as fields
 */
class site_notice_handler_delete_link_field extends site_notice_handler_link_field {
  function construct() {
    parent::construct();
  }


  function render($values) {
    $snid = $values->{$this->aliases['snid']};
    $name = $values->{$this->aliases['name']};

    // Access check
    $notice = site_notice_load($snid);
    if (!site_notice_access('delete', $notice)) {
      return;
    }

    $text = !empty($this->options['text']) ? $this->options['text'] : t('delete');
    return l($text, 'admin/content/site-notices/' . $name . '/delete');
  }
}
