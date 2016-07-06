<?php
/**
 * @file
 * PECE theme entity preprocess implementations.
 */

/**
 * Implements template_preprocess().
 */
function pece_scholarly_lite_preprocess(&$variables, $hook) {
  if (isset($variables['elements']['#entity_type'])) {
    pece_scholarly_lite_preprocess_entity($variables, $hook, $variables['elements']['#entity_type']);

    switch ($variables['elements']['#entity_type']) {
      case 'pece_photo_essay_item':
        pece_scholarly_lite_preprocess_entity__pece_photo_essay_item($variables);
        break;
    }
  }
}

/**
 * Implements template_preprocess_entity().
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

/**
 * Implements template_preprocess_entity__pece_photo_essay_item().
 */
function pece_scholarly_lite_preprocess_entity__pece_photo_essay_item(&$variables) {
  $item = entity_metadata_wrapper('pece_photo_essay_item', $variables['pece_photo_essay_item']);
  $artifact = entity_metadata_wrapper('node', $item->field_image_artifact->value());
  $artifact_image = $artifact->field_pece_media_image->value();

  $variables['artifact_url'] = url('node/' . $artifact->getIdentifier());
  $variables['artifact_title'] = $artifact->label();
  $variables['artifact_image'] = array(
    '#theme' => 'image_formatter',
    '#item' => $artifact_image,
  );
}
