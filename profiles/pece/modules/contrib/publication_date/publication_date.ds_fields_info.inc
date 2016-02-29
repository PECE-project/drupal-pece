<?php

/**
 * @file
 * Display Suite Integration
 */

/**
 * Implements hook_ds_fields_info().
 */
function publication_date_ds_fields_info($entity_type) {
  $fields = array();

  if ($entity_type == 'node') {
    // Get the time format specified in date/time.
    $format_types = system_get_date_types();
    $date_formatters = array();
    foreach ($format_types as $formatter) {
      $date_formatters['publication_date_' . $formatter['type']] = t($formatter['title']);
    }

    $fields['node']['published_on'] = array(
      'title' => t('Published on'),
      'field_type' => DS_FIELD_TYPE_FUNCTION,
      'function' => 'publication_date_render_published_at_field',
      'file' => drupal_get_path('module', 'publication_date') . '/publication_date.ds_fields_info.inc',
      'properties' => array(
        'formatters' => $date_formatters,
      ),
    );

    if (isset($fields[$entity_type])) {
      return array($entity_type => $fields[$entity_type]);
    }
    return;
  }
}

/**
 * Render the publication date field.
 *
 * @see publication_date_ds_fields_info()
 */
function publication_date_render_published_at_field($field) {
  $date_format = str_replace('publication_date_', '', $field['formatter']);
  if (isset($field['entity']->published_at) && !empty($field['entity']->published_at)) {
    return format_date($field['entity']->published_at, $date_format);
  }
  else {
    // If the entity has never been published, then return the current time.
    return format_date(time(), $date_format);
  }
}

/**
 * Implements hook_ds_field_settings_form().
 */
function publication_date_ds_field_settings_form($field) {
  return ds_ds_field_settings_form($field);
}

/**
 * Implements hook_ds_field_format_summary().
 */
function publication_date_ds_field_format_summary($field) {
  return ds_ds_field_format_summary($field);
}
