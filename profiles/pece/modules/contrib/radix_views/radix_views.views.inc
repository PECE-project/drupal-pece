<?php
/**
 * @file
 * Style plugin to render rows using a Bootstrap grid.
 */

/**
 * Implements hook_views_plugins().
 */
function radix_views_views_plugins() {
  $module_path = drupal_get_path('module', 'radix_views');

  return array(
    'style' => array(
      'radix_views_grid_plugin_style' => array(
        'title' => t('Radix Grid'),
        'help' => t('Radix Grid Style'),
        'path' => $module_path . '/plugins',
        'handler' => 'RadixViewsGridPluginStyle',
        'parent' => 'default',
        'theme' => 'radix_views_grid_plugin_style',
        'theme path' => $module_path . '/templates',
        'theme file' => 'radix_views.theme.inc',
        'uses row plugin' => TRUE,
        'uses grouping' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
      ),
    ),
  );
}
