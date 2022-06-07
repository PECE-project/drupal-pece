<?php

/**
 * @file
 * Handler include for MailHandler.
 */

use Monolog\Handler\NativeMailerHandler;

/**
 * Monolog loader callback; Loads a NativeMailerHandler class.
 *
 * @return HandlerInterface
 */
function monolog_native_mailer_handler_loader($options) {
  if ('<site-mail>' == $options['to']) {
    $options['to'] = variable_get('site_mail', ini_get('sendmail_from'));
  }
  if ('<site-mail>' == $options['from']) {
    $options['from'] = variable_get('site_mail', ini_get('sendmail_from'));
  }
  return new NativeMailerHandler($options['to'], $options['subject'], $options['from'], $options['level'], $options['bubble']);
}

/**
 * Monolog settings callback; Settings for the native_mailer handler.
 */
function monolog_native_mailer_handler_settings(&$form, &$form_state, $profile, array $handler) {

  $form['to'] = array(
    '#title' => t('Receiver'),
    '#type' => 'textfield',
    '#default_value' => $handler['to'],
    '#description' => t('The email address that messages will be sent to.<br/><code>&lt;site-mail&gt;</code> will use address that this site uses to send automated emails.'),
    '#required' => TRUE,
  );

  $form['subject'] = array(
    '#title' => t('Subject'),
    '#type' => 'textfield',
    '#default_value' => $handler['subject'],
    '#description' => t('The subject of the email address.'),
    '#required' => TRUE,
  );

  $form['from'] = array(
    '#title' => t('Sender'),
    '#type' => 'textfield',
    '#default_value' => $handler['from'],
    '#description' => t('The email address of the sender.<br/><code>&lt;site-mail&gt;</code> will use address that this site uses to send automated emails.'),
    '#required' => TRUE,
  );
}
