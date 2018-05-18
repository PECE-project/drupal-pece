<?php
/**
 * @file
 * Contains a Views field handler to take care of displaying links to entities
 * as fields.
 */
class site_notice_handler_enable_link_field extends views_handler_field {
  function construct() {
    parent::construct();
    $this->additional_fields['snid'] = 'snid';
    $this->additional_fields['name'] = 'name';
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['text_on'] = array('default' => '', 'translatable' => TRUE);
    $options['text_off'] = array('default' => '', 'translatable' => TRUE);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['text_on'] = array(
      '#type' => 'textfield',
      '#title' => t('Text to display when enabled'),
      '#default_value' => $this->options['text_on'],
    );
    $form['text_off'] = array(
      '#type' => 'textfield',
      '#title' => t('Text to display when disabled'),
      '#default_value' => $this->options['text_off'],
    );
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    $snid = $values->{$this->aliases['snid']};
    $name = $values->{$this->aliases['name']};

    // Access check
    $notice = site_notice_load($snid);
    if (!site_notice_access('edit', $notice)) {
      return;
    }

    // Generate text by status
    if ($notice->status) {
      $text = !empty($this->options['text_on']) ? $this->options['text_on'] : t('disable');
      $action = 'disable';
    }
    else{
      $text = !empty($this->options['text_off']) ? $this->options['text_off'] : t('enable');
      $action = 'enable';
    }

    return l($text, 'admin/content/site-notices/' . $name . '/' . $action, array('query' => drupal_get_destination()));
  }
}
