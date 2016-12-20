<?php

/**
 * @file
 * Contains \views_plugin_pager_infinite_scroll.
 */

/**
 * The plugin to handle the infinite scroll pager.
 *
 * @ingroup views_pager_plugins
 */
class views_plugin_pager_infinite_scroll extends views_plugin_pager_full {

  /**
   * {@inheritdoc}
   */
  function option_definition() {
    $options['manual_load'] = array('default' => 0);
    $options['text'] = array('default' => 'Show More', 'translatable' => TRUE);
    $options['items_per_page'] = array('default' => 10);
    $options['offset'] = array('default' => 0);
    return $options;
  }

  /**
   * {@inheritdoc}
   */
  function options_form(&$form, &$form_state) {
    $form['items_per_page'] = array(
      '#title' => t('Items to display'),
      '#type' => 'textfield',
      '#description' => t('The number of items to display. Enter 0 for no limit.'),
      '#default_value' => $this->options['items_per_page'],
    );
    $form['offset'] = array(
      '#type' => 'textfield',
      '#title' => t('Offset'),
      '#description' => t('The number of items to skip. For example, if this field is 3, the first 3 items will be skipped and not displayed.'),
      '#default_value' => $this->options['offset'],
    );
    $form['manual_load'] = array(
      '#type' => 'checkbox',
      '#title' => t('Load subsequent pages manually instead of automatically'),
      '#description' => t('When checked, use a link to trigger loading of subsequent pages instead of window scroll.'),
      '#default_value' => $this->options['manual_load'],
    );
    $form['text'] = array(
      '#type' => 'textfield',
      '#title' => t('Manual load label'),
      '#required' => FALSE,
      '#description' => t('Label to use on the manual link.'),
      '#default_value' => $this->options['text'],
      '#process' => array('ctools_dependent_process'),
      '#dependency' => array(
        'edit-pager-options-manual-load' => array(1),
      ),
    );
  }

  /**
   * {@inheritdoc}
   */
  function options_validate(&$form, &$form_state) {
  }

  /**
   * {@inheritdoc}
   */
  function summary_title() {
    return t('Infinite Scroll: @parent', array('@parent' => parent::summary_title()));
  }

  /**
   * {@inheritdoc}
   */
  function render($input) {
    $this->view->set_use_ajax(TRUE);
    $pager_theme = views_theme_functions('views_infinite_scroll_pager', $this->view, $this->display);
    $settings = array(
      'views_infinite_scroll' => array(
        'img_path' => url(drupal_get_path('module', 'views_infinite_scroll') . '/images/ajax-loader.gif'),
      ),
    );
    drupal_add_js($settings, array('type' => 'setting', 'scope' => JS_DEFAULT));
    drupal_add_js(drupal_get_path('module', 'views_infinite_scroll') . '/views-infinite-scroll.js', array('scope' => 'footer'));
    return theme($pager_theme, array('text' => $this->options['text'], 'manual_load' => $this->options['manual_load']));
  }
}
