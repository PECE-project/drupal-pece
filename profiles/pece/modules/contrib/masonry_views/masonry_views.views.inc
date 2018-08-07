<?php
/**
 * @file
 * Provide views data and handlers for masonry_views.module.
 */

/**
 * Implements hook_views_plugins().
 */
function masonry_views_views_plugins() {
  return array(
    'style' => array(
      'masonry_views' => array(
        'title' => t('Masonry'),
        'handler' => 'views_plugin_style_masonry_views',
        'uses options' => TRUE,
        'help' => t("Display content in a Masonry layout."),
        'theme' => 'views_view_masonry',
        'type' => 'normal',
        'uses row plugin' => TRUE,
        'uses row class' => TRUE,
        'uses grouping' => FALSE,
      ),
    ),
  );
}

