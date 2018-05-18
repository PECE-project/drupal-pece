<?php
/**
 * @file
 * Create a dropdown for the status filter.
 */
class site_notice_handler_status_filter extends views_handler_filter_many_to_one {
  function op_helper() {
    if ($this->value === 0) {
      return;
    }
    $this->helper->add_filter();
  }

  function get_value_options() {
    if (isset($this->value_options)) {
      return;
    }

    $this->value_options = SiteNoticeEntity::getOptions('status');
  }
}
