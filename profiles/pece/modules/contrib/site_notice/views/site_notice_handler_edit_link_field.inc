<?php
/**
 * @file
 * Contains a Views field handler to take care of displaying edit links
 * as fields
 */
class site_notice_handler_edit_link_field extends site_notice_handler_link_field {
  function construct() {
    parent::construct();
  }


  function render($values) {
    $snid = $values->{$this->aliases['snid']};
    $name = $values->{$this->aliases['name']};

    // Access check
    $notice = site_notice_load($snid);
    if (!site_notice_access('edit', $notice)) {
      return;
    }

    $text = !empty($this->options['text']) ? $this->options['text'] : t('edit');
    return l($text, 'admin/content/site-notices/' . $name . '/edit');
  }
}
