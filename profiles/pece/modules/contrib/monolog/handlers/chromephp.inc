<?php

/**
 * @file
 * Handler include for ChromePHPHandler.
 */

use Monolog\Handler\ChromePHPHandler;

/**
 * Monolog loader callback; Loads a ChromePHPHandler handler.
 *
 * @return HandlerInterface
 */
function monolog_chromephp_handler_loader($options) {
  return new ChromePHPHandler($options['level'], $options['bubble']);
}
