<?php

/**
 * @file
 * Handler include for FirePHPHandler.
 */

use Monolog\Handler\GelfHandler;
use Gelf\Publisher;
use Gelf\Transport\UdpTransport;

/**
 * Monolog loader callback; Loads a GelfHandler handler.
 *
 * @return HandlerInterface
 */
function monolog_gelf_handler_loader($options) {
  $publisher = new Publisher();
  $publisher->addTransport(new UdpTransport($options['hostname'], $options['port'], $options['chunk_size']));
  return new GelfHandler($publisher, $options['level'], $options['bubble']);
}

/**
 * Monolog settings form; Settings for the GelfHandler handler.
 */
function monolog_gelf_handler_settings(&$form, &$form_state, $profile, array $handler) {

  $form['hostname'] = array(
    '#title' => t('Hostname'),
    '#type' => 'textfield',
    '#default_value' => $handler['hostname'],
    '#description' => t('The hostname of the Graylog2 server.'),
    '#required' => TRUE,
  );

  $form['port'] = array(
    '#title' => t('Port'),
    '#type' => 'textfield',
    '#default_value' => $handler['port'],
    '#description' => t('The port that the server is listening on.'),
    '#required' => TRUE,
    '#size' => 6,
  );

  $form['chunk_size'] = array(
    '#title' => t('Chunk size'),
    '#type' => 'textfield',
    '#default_value' => $handler['chunk_size'],
    '#description' => t('The size of chunked messages in bytes. This allows larger messages to be broken up into smaller pieces.'),
    '#required' => TRUE,
    '#size' => 6,
  );
}
