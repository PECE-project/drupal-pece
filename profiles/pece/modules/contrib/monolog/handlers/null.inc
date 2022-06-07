<?php

/**
 * @file
 * Handler include for NullHandler.
 */

use Monolog\Handler\NullHandler;

/**
 * Monolog loader callback; Loads a NullHandler handler.
 *
 * @return HandlerInterface
 */
function monolog_null_handler_loader($options) {
  return new NullHandler($options['level']);
}

/**
 * Monolog settings form; Settings for the NullHandler handler.
 */
function monolog_null_handler_settings(&$form, &$form_state, $profile, array $handler) {
  $form['bubble']['#access'] = FALSE;
}
