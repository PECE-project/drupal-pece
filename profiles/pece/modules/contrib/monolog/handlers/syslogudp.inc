<?php

/**
 * @file
 * Handler include for SyslogUdpHandler.
 */

use Monolog\Handler\SyslogUdpHandler;

/**
 * Monolog loader callback; Loads a SyslogUdpHandler handler.
 *
 * @return HandlerInterface
 */
function monolog_syslogudp_handler_loader($options) {
  if (!$options['port']) {
    $options['port'] = 514;
  }
  return new SyslogUdpHandler($options['host'], $options['port'], LOG_USER, $options['level'], $options['bubble']);
}

/**
 * Monolog settings form; Settings for the SyslogUdpHandler handler.
 */
function monolog_syslogudp_handler_settings(&$form, &$form_state, $profile, array $handler) {
  $form['host'] = array(
    '#title' => t('Host'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => $handler['host'],
  );
  $form['port'] = array(
    '#title' => t('Port'),
    '#type' => 'textfield',
    '#default_value' => $handler['port'],
    '#description' => t('Defaults to 514 if not set.'),
  );
}
