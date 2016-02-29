<?php

/**
 * @file
 * Theme and preprocess functions for radix_views.
 */

/**
 * Template preprocess theme function to print the Radix grid.
 */
function template_preprocess_radix_views_grid_plugin_style(&$variables) {
  $view = $variables['view'];
  $options = $view->style_plugin->options;

  // Add options to template.
  foreach ($options as $option => $value) {
    if (is_array($value)) {
      $value = !empty($value['default']) ? $value['default'] : $value;
    }
    $variables[$option] = $value;
  }

  // By default, use regex for Bootstrap.
  $grid_regex = 'col\-[xs|sm|md|lg]*\-([0-9]{1,2})';

  // Get grid regex from a Radix-based theme.
  if (function_exists('radix_get_grid_regex')) {
    $grid_regex = radix_get_grid_regex();
  }

  // Get views group col size from class.
  if (preg_match("/$grid_regex/", $variables['views_group_col_class'], $matches)) {
    $variables['views_group_col_class_size'] = $matches[1];
    $variables['views_group_col_size'] = floor(12 / $matches[1]);
  }

  // Get views row col size from class.
  if (preg_match("/$grid_regex/", $variables['views_row_col_class'], $matches)) {
    $variables['views_row_col_class_size'] = $matches[1];
    $variables['views_row_col_size'] = floor(12 / $matches[1]);

    // Split rows.
    $variables['rows'] = array_chunk($variables['rows'] , $variables['views_row_col_size']);
  }

  // Determine if views has grouping and add to template.
  $variables['has_grouping'] = !empty($variables['grouping']);
}
