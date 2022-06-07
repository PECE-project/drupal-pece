<?php

/**
 * @file
 * Handler include for HipChatHandler.
 */

use Monolog\Handler\HipChatHandler;

/**
 * Monolog loader callback; Loads a HipChatHandler handler.
 *
 * @return HandlerInterface
 */
function monolog_hipchat_handler_loader($options) {
  return new HipChatHandler($options['token'], $options['room'], $options['contact_name'], $options['notify'], $options['level'], $options['bubble']);
}

/**
 * Monolog settings form; Settings for the HipChat handler.
 */
function monolog_hipchat_handler_settings(&$form, &$form_state, $profile, array $handler) {

  $form['token'] = array(
    '#title' => t('HipChat API Token'),
    '#type' => 'textfield',
    '#default_value' => $handler['token'],
    '#description' => t('HipChat API Token.'),
    '#required' => TRUE,
  );

  $form['room'] = array(
    '#title' => t('Room'),
    '#type' => 'textfield',
    '#default_value' => $handler['room'],
    '#description' => t('The room that should be alerted of the message (Id or Name).'),
    '#required' => TRUE,
  );

  $form['contact_name'] = array(
    '#title' => t('Contact Name'),
    '#type' => 'textfield',
    '#default_value' => $handler['contact_name'],
    '#description' => t('Name used in the "from" field.'),
  );

  $form['notify'] = array(
    '#title' => t('Trigger a notification in clients.'),
    '#type' => 'checkbox',
    '#default_value' => $handler['notify'],
    '#description' => t('Check this box to notify HipChat clients connected to the room.'),
  );
}
