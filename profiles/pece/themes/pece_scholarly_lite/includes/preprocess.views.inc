<?php
/**
 * @file
 * PECE theme views preprocess implementations.
 */

/**
 * Implements theme_preprocess_views_view().
 */
function pece_scholarly_lite_preprocess_views_view(&$variables) {
  $view = $variables['view'];
  $variables['content_attributes_array']['class'][] = 'view-content';

  // Style theme specific preprocessing.
  if (isset($view->style_plugin->definition['theme'])) {
    switch ($view->style_plugin->definition['theme']) {
      case 'views_view_unformatted':
        $variables['content_attributes_array']['class'][] = 'row';
        break;
    }
  }
}

/**
 * Implements hook_preprocess_views_view_unformatted().
 */
function pece_scholarly_lite_preprocess_views_view_unformatted(&$variables) {
  $view = $variables['view'];
  $additional_row_classes = array('col-xs-12', 'views-row');

  // View specific preprocessing.
  switch ($view->name) {
    case 'child_groups':
      $additional_row_classes[] = 'col-md-2';
      break;
  }

  // Re-create row classes strings.
  foreach ($variables['rows'] as $id => $content) {
    if (isset($variables['classes'][$id])) {
      $variables['classes'][$id] = $additional_row_classes + $variables['classes'][$id];
      $variables['classes_array'][$id] = implode(' ', $variables['classes'][$id]);
    }
  }
}
