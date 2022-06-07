<?php

/**
 * @file
 * Handler include for FirePHPHandler.
 */

use Monolog\Handler\FirePHPHandler;

/**
 * Monolog loader callback; Loads a FirePHPHandler handler.
 *
 * @return HandlerInterface
 */
function monolog_firephp_handler_loader($options) {
  return new FirePHPHandler($options['level'], $options['bubble']);
}
