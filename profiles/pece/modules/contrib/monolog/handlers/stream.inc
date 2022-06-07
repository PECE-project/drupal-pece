<?php

/**
 * @file
 * Handler include for StreamHandler include.
 */

use Monolog\Handler\StreamHandler;

/**
 * Monolog loader callback; Loads a StreamHandler handler.
 *
 * @return HandlerInterface
 */
function monolog_stream_handler_loader($options) {
  $directory = dirname($options['filepath']);
  monolog_prepare_log_dir($directory);
  return new StreamHandler($options['filepath'], $options['level'], $options['bubble']);
}

/**
 * Monolog settings form; Settings for the StreamHandler handler.
 */
function monolog_stream_handler_settings(&$form, &$form_state, $profile, array $handler) {
  $form['filepath'] = array(
    '#title' => 'Log file path',
    '#type' => 'textfield',
    '#default_value' => $handler['filepath'],
    '#description' => t('The path or URI that the log file will be written to.'),
  );
}
