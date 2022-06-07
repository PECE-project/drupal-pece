<?php

/**
 * @file
 * Handler include for SyslogHandler.
 */

use Monolog\Handler\SyslogHandler;

/**
 * Monolog loader callback; Loads a SyslogHandler handler.
 *
 * @return HandlerInterface
 */
function monolog_syslog_handler_loader($options) {
  return new SyslogHandler($options['ident'], LOG_USER, $options['level'], $options['bubble']);
}

/**
 * Monolog settings form; Settings for the SyslogHandler handler.
 */
function monolog_syslog_handler_settings(&$form, &$form_state, $profile, array $handler) {
  $form['ident'] = array(
    '#title' => t('Identity string'),
    '#type' => 'textfield',
    '#default_value' => $handler['ident'],
    '#description' => t('The string ident is added to each message.'),
  );
}
