<?php
/**
 * @file
 * PECE theme field preprocess implementations.
 */

/**
 * Implements template_preprocess_field().
 */
function pece_scholarly_lite_preprocess_field(&$variables) {
  switch ($variables['element']['#field_name']) {
    case 'field_pece_photo_essay_items':
      pece_scholarly_lite_preprocess_field__field_pece_photo_essay_items($variables);
      break;
  }
}

/**
 * Implements template_preprocess_field__field_pece_photo_essay_items().
 */
function pece_scholarly_lite_preprocess_field__field_pece_photo_essay_items(&$variables) {
  $element = $variables['element'];
  $node = $element['#object'];
  $theme_path = drupal_get_path('theme', 'pece_scholarly_lite');

  if (empty($variables['attributes_array']['id'])) {
    $variables['attributes_array']['id'] = drupal_html_id('photo-essay-' . $node->nid);
  }

  $wrapper_id = $variables['attributes_array']['id'];

  // 1 - Setup modal.
  $modal_id = $variables['modal_id'] = $wrapper_id . '-modal';
  drupal_add_js($theme_path . '/assets/lib/remodal/dist/remodal.js');

  // 2 - Setup slider.
  $slider_selector = '#' . $wrapper_id . ' > div > .field-items';
  drupal_add_js($theme_path . '/assets/lib/slick-carousel/slick/slick.js');
  drupal_add_js($theme_path . '/assets/js/slider.js');
  drupal_add_js(array('peceSlider' => array($slider_selector => array(
    'sameHeight' => TRUE,
    'arrows' => TRUE,
    'autoplay' => FALSE,
    'adaptiveHeight' => FALSE,
    'appendArrows' => '.remodal-wrapper.photo-essay-modal',
    'draggable' => FALSE,
    'fade' => TRUE,
    'prevArrow' => '<a href="#" class="slick-prev photo-essay-slider-arrow"><i class="fa fa-chevron-left" aria-hidden="true"></i> ' . t('Previous') . '</a>',
    'nextArrow' => '<a href="#" class="slick-next photo-essay-slider-arrow"><i class="fa fa-chevron-right" aria-hidden="true"></i> ' . t('Next') . '</a>',
  ))), 'setting');

  // 3 - Make sure slider works on modal.
  drupal_add_js($theme_path . '/assets/js/modal-slider.js');
}
