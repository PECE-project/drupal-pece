<?php

/**
 * @file
 * Administrative settings for the Monolog Logging module.
 */

/**
 * Watchdog settings for the Monolog module.
 *
 * @see monolog_logging_watchdog_settings_form_submit()
 *
 * @ingroup forms
 */
function monolog_logging_watchdog_settings_form($form, &$form_state) {

  $form['monolog_logging_contexts'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Include contexts in record'),
    '#description' => t('Include the selected contexts in all log messages that are routed through Monolog from <code>watchdog()</code>.'),
    '#options' => array(
      'type' => t('The type of message for this entry.'),
      'uid' => t('The user ID for the user who was logged in when the event happened.'),
      'request_uri' => t('The request URI for the page the event happened in.'),
      'referer' => t('The page that referred the user to the page where the event occurred.'),
      'ip' => t('The IP address where the request for the page came from.'),
      'link' => t('An optional link provided by the module that called the watchdog() function.'),
      'request_id' => t('A unique identifier for the page request or PHP process to logically group log messages.'),
    ),
    '#default_value' => variable_get('monolog_logging_contexts', array(
      'uid' => 'uid',
      'request_uri' => 'request_uri',
      'referer' => 'referer',
      'ip' => 'ip',
      'link' => 'link',
    )),
  );

  $form['monolog_drupal_compatibility'] = array(
    '#type' => 'item',
    '#title' => t('Drupal compatibility'),
  );

  $form['monolog_type_as_channel'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use the watchdog type as the channel name'),
    '#description' => t('Enable this option to use the watchdog type as each record\'s channel name instead of "watchdog". This allows handlers such as the GELF handler to behave as the current Drupal watchdog implementations do.'),
    '#default_value' => variable_get('monolog_type_as_channel', 1),
  );

  return system_settings_form($form);
}

/**
 * Returns HTML for the type map table.
 *
 * @param array $variables
 *   An associative array containing:
 *   - element: The FAPI element being themed.
 *
 * @ingroup themeable
 */
function theme_monolog_logging_map_table(array $variables) {
  $output = '';

  $header = array(
    'type' => t('Watchdog Types'),
    'channel' => t('Monolog Channel'),
    'operations' => t('Operations'),
  );

  $rows = array();
  $types = array();
  foreach ($types as $type) {

    $rows[] = array(
      'type' => '',
      'channel' => drupal_render($variables['element']['type'][$type]['profile']),
      'operations' => '',
    );
  }

  $output .= drupal_render_children($variables['element']);
  $output .= theme('table', array(
    'caption' => t('Watchdog type mappings'),
    'header' => $header,
    'rows' => $rows,
    'empty' => t('There are no watchdog types mapped to Monolog channels.'),
    'attributes' => array('id' => 'monolog-logging-map-table'),
  ));

  return $output;
}
