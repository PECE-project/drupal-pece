<?php

/**
 * @file
 * Handler include for SocketHandler include.
 */

use Monolog\Handler\SocketHandler;

/**
 * Monolog loader callback; Loads a StreamHandler handler.
 *
 * @return HandlerInterface
 */
function monolog_socket_handler_loader($options) {
  $handler = new SocketHandler($options['connection_string'], $options['level'], $options['bubble']);
  $handler->setPersistent((bool) $options['persistent']);
  if ($options['connection_timeout']) {
    $handler->setConnectionTimeout($options['connection_timeout']);
  }
  if ($options['write_timeout']) {
    $handler->setTimeout($options['write_timeout']);
  }
  return $handler;
}

/**
 * Monolog settings form; Settings for the StreamHandler handler.
 */
function monolog_socket_handler_settings(&$form, &$form_state, $profile, array $handler) {

  $form['connection_string'] = array(
    '#title' => t('Socket connection string'),
    '#type' => 'textfield',
    '#default_value' => $handler['connection_string'],
    '#description' => t('The socket connection string, for example <code>unix:///var/log/httpd_app_log.socket</code>.'),
    '#required' => TRUE,
  );

  $form['persistent'] = array(
    '#title' => t('Set socket connection to be persistent'),
    '#type' => 'checkbox',
    '#default_value' => $handler['persistent'],
  );

  $form['connection_timeout'] = array(
    '#title' => t('Connection timeout'),
    '#type' => 'textfield',
    '#description' => t('The socket connection timeout in seconds.'),
    '#default_value' => $handler['connection_timeout'],
    '#size' => 5,
  );

  $form['write_timeout'] = array(
    '#title' => t('Write timeout'),
    '#type' => 'textfield',
    '#description' => t('The socket write timeout in seconds.'),
    '#default_value' => $handler['write_timeout'],
    '#size' => 5,
  );
}
