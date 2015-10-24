<?php
/**
 * @file
 * PECE theme entity preprocess implementations.
 */

/**
 * Implements hook_preprocess().
 */
function pece_scholarly_lite_preprocess(&$variables, $hook) {
  if (isset($variables['elements']['#entity_type'])) {
    pece_scholarly_lite_preprocess_entity($variables, $hook, $variables['elements']['#entity_type']);
  }
}

/**
 * Implements hook_preprocess_entity().
 */
function pece_scholarly_lite_preprocess_entity(&$variables, $hook) {
  // View-mode based preprocessing.
  if (!empty($variables['elements']['#view_mode'])) {
    // Add view-mode based theme suggestions.
    if (!empty($variables['theme_hook_suggestions'])) {
      array_unshift($variables['theme_hook_suggestions'], $hook . '__' . $variables['elements']['#view_mode']);
    }

    // Add view-mode based class to all entities.
    if (isset($variables['classes_array'])) {
      $variables['classes_array'][] = 'view-mode-' . drupal_html_class($variables['elements']['#view_mode']);
    }
  }
}
