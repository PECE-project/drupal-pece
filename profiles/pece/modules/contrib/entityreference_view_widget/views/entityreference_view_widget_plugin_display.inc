<?php

/**
 * @file
 * File: entityreference_view_widget_plugin_display.inc.
 */

/**
 * Plugin display.
 *
 * Provides the "Entityreference View Widget" display which configures
 * the view for inclusion in the widget.
 *
 * @codingStandardsIgnoreStart
 */
class entityreference_view_widget_plugin_display extends views_plugin_display {
  /**
   * Option definition.
   */
  public function option_definition() {
    // @codingStandardsIgnoreEnd
    $options = parent::option_definition();

    $options['style_plugin']['default'] = 'table';
    $options['use_ajax']['default'] = TRUE;
    $options['defaults']['default']['use_ajax'] = FALSE;
    $options['defaults']['default']['style_plugin'] = FALSE;
    $options['defaults']['default']['style_options'] = FALSE;

    $options['defaults']['default']['row_plugin'] = FALSE;
    $options['defaults']['default']['row_options'] = FALSE;

    // Set the display title to an empty string (not used in this display type).
    $options['title']['default'] = '';
    $options['defaults']['default']['title'] = FALSE;

    $options['hide_left'] = array('default' => FALSE);
    return $options;
  }

}
