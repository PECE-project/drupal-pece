<?php
/**
 * @file
 * Provide context for the status values.
 */
class site_notice_handler_status_field extends views_handler_field {
  function construct() {
    parent::construct();
  }

  function render($values) {
    return SiteNoticeEntity::getOptions('status', $values->site_notice_status);
  }
}
