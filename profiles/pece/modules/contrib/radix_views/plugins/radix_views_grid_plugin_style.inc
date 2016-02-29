<?php
/**
 * @file
 * Plugin style for radix_views_grid_plugin_style.
 */

/**
 * Class to define a style plugin handler.
 */
class RadixViewsGridPluginStyle extends views_plugin_style {
  /**
   * Set default options
   */
  function option_definition() {
    $options = parent::option_definition();
    $options += array(
      'views_group_col_class' => array('default' => 'col-md-12'),
      'views_row_col_class' => array('default' => 'col-md-12'),
    );

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    // Show this option only if grouping is enabled.
    if (!empty($form['grouping'])) {
      $form['views_group_col_class'] = array(
        '#type' => 'textfield',
        '#title' => t('Group column class'),
        '#description' => t('The grid class to use for the group. Example: col-xs-12, col-md-6, col-lg-4.'),
        '#required' => TRUE,
        '#default_value' => $this->options['views_group_col_class'],
      );
    } else {
      $form['views_group_col_class'] = array(
        '#type' => 'hidden',
        '#value' => $this->options['views_group_col_class']['default'],
      );
    }

    $form['views_row_col_class'] = array(
      '#type' => 'textfield',
      '#title' => t('Column class'),
      '#description' => t('The grid class to use for each views result. Example col-xs-12, col-md-6, col-lg-4.'),
      '#required' => TRUE,
      '#default_value' => $this->options['views_row_col_class'],
    );
  }
}
