<?php

/**
 * Helper functions for PECE Core module.
 */

/**
 * Custom function to add modal
 */
function pece_core_modal_presets($modal_name, $width, $height) {
  // Include the CTools tools that we need.
  ctools_include('ajax');
  ctools_include('modal');

  $theme_default = variable_get('theme_default');

  $settings = array(
    $modal_name => array(
      'modalSize' => array(
        'type' => 'fixed',
        'width' => $width,
        'height' => $height,
      ),
      'modalOptions' => array(
        'backdropClose' => TRUE,
      ),
      'loadingText' => t('Loading...'),
      'closeText' => t('close'),
      'closeImage' => '',
      'throbber' => theme('image', array(
        'path' => drupal_get_path('theme', $theme_default) . '/img/throbber.gif',
        'title' => t('Loading.'),
        'alt' => t('Loading'),
      )),
    ),
  );
  drupal_add_js($settings, 'setting');

  // Add CTools' javascript to the page.
  ctools_modal_add_js();
}

/**
 * Helper method to perform jQuery.extend like default settings.
 */
function pece_array_extend() {
  $arrays = func_get_args();
  $base = array_shift($arrays);
  foreach ($arrays as $array) {
    reset($base);
    while (list($key, $value) = @each($array)) {
      if (is_array($value) && @is_array($base[$key])) {
        $base[$key] = pece_array_extend($base[$key], $value);
      } else {
        $base[$key] = $value;
      }
    }
  }
  return $base;
}


/**
 * Helper Access callback generator for entity reference fields.
 *
 * @param $entity_info array
 * @param $entity_type_name string
 *    Entity machine name
 */
function pece_entity_access_info_alter_prepare(&$entity_info, $entity_type_name = '') {
  if (!empty($entity_info[$entity_type_name])) {
    if (empty($callback = variable_get($entity_type_name . '__access_callback', NULL))) {
      $callback = $entity_info[$entity_type_name]['access callback'];
      variable_set($entity_type_name. '__access_callback', $callback);
    }

    $entity_info[$entity_type_name]['access callback'] = $entity_type_name . '__entity_callback';
  }
}

/**
 * Dynamic entity access for Eck entities.
 */
function pece_entity_access_callback_prepare($op, $entity, $account, $entity_type_name, $field_name) {
  switch ($op) {
    case 'view':
      if (is_object($entity) && isset($entity->id)) {
        $$entity_type_name = entity_metadata_wrapper($entity_type_name, $entity);
        $referenced_entity = $$entity_type_name->$field_name->value();

        if (!empty($referenced_entity) && !node_access('view', $referenced_entity, $account)) {
          return FALSE;
        }
      }
      break;
  }

  $default_access_callback = variable_get($entity_type_name . '__access_callback', 'eck__entity_access');
  return $default_access_callback($op, $entity, $account, $entity_type_name);
}
