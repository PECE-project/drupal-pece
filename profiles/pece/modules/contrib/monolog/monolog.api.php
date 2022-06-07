<?php

/**
 * @file
 * Hooks provided by the Composer Manager module.
 */

use Monolog\Handler\StreamHandler;
use Monolog\Handler\HandlerInterface;

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Defines monolog channels.
 *
 * A channel identifies which part of the application a record is related to.
 *
 * @return array
 *   An associative array keyed by unique name of the channel. Each channel is
 *   an associative array containing:
 *   - label: The human readable name of the channel as displayed in
 *     administrative pages.
 *   - description: The description of the channel displayed in administrative
 *     pages.
 *   - default profile: The machine readable name of the channel's default
 *     logging profile.
 */
function hook_monolog_channel_info() {
  $channels = array();

  $channels['watchdog'] = array(
    'label' => t('Watchdog'),
    'description' => t('The default channel that watchdog messages are routed through.'),
    'default profile' => 'production',
  );

  return $channels;
}

/**
 * The path to the directory containing the handler includes.
 *
 * Each include file inside of the directory contains a handler's "loader
 * callback" and "settings callback" functions. The file will be autoloaded if
 * the filename is the machine name of the handler with a ".inc" suffix, for
 * example "stream.inc" for the "stream" handler.
 *
 * The directory is relative to the module's root.
 *
 * @return string
 */
function hook_monolog_handler_path() {
  return 'handlers';
}

/**
 * Defines monolog handlers.
 *
 * Handlers process the records and write them to various sources such as files
 * remote servers, sockets, etc.
 *
 * @return array
 *   An associative array keyed by unique name of the handler. Each handler is
 *   an associative array containing:
 *   - label: The human readable name of the handler displayed in admin pages.
 *   - description: The description of the handler displayed in admin pages.
 *   - default settings: An associative array of defaults for the settings
 *     defined in the "settings callback".
 *   - loader callback: The name of the function that loads the handler class.
 *     Defaults to `monolog_HANDLER_NAME_handler_loader`.
 *   - settings callback: The name of the function that adds additional settings
 *     to the handler's configuration form. Pass FALSE if no additional settings
 *     are required. Defaults to `monolog_HANDLER_NAME_handler_settings`.
 *   - handler file: The path to the include file containing the loader and
 *     settings callbacks. If the module implements hook_monolog_handler_path(),
 *     this option defaults to `MODULE_PATH/HANDLER_PATH/HANDLER_NAME.inc`.
 *
 * @see https://github.com/Seldaek/monolog#handlers
 */
function hook_monolog_handler_info() {
  $handlers = array();

  $handlers['stream'] = array(
    'label' => t('Stream Handler'),
    'description' => t('Logs records into any PHP stream, use this for log files.'),
    'default settings' => array(
      'filepath' => 'public://monolog/drupal.log',
    ),

    // "loader callback" defaults to `monolog_stream_handler_loader`.

    // "settings callback" defaults to `monolog_stream_handler_settings`.

    // "handler file" defaults to `MODULE_PATH/handlers/stream.inc` since the
    // hook_monolog_handler_path() returns "handlers".
  );

  return $handlers;
}

/**
 * Example loader callback.
 *
 * Loader callbacks instantiate the handler class.
 *
 * @param array $options
 *   The configuration options set for this handler.
 *
 * @return HandlerInterface
 *
 * @see hook_monolog_handler_info()
 */
function mymodule_stream_handler_loader($options) {
  return new StreamHandler($options['filepath'], $options['level']);
}

/**
 * Example Monolog settings callback.
 *
 * The forms add handler specific options to the handler settings pages.
 *
 * @param array $handler
 *   The handler options set for profile the handler is attached to.
 */
function monolog_stream_handler_settings(&$form, &$form_state, array $handler) {
  $form['filepath'] = array(
    '#title' => 'Log file path',
    '#type' => 'textfield',
    '#default_value' => $handler['filepath'],
    '#description' => t('The path or URI that the log file will be written to.'),
  );
}

/**
 * Contains default profile configurations.
 *
 * A profile is a collection of handlers that process the record.
 */
function hook_default_monolog_profiles() {
  $profiles = array();

  $profile = new stdClass();
  $profile->disabled = FALSE;
  $profile->api_version = 1;
  $profile->name = 'syslog';
  $profile->options = array(
    'label' => 'Syslog',
    'handlers' => array(
      'syslog' => array(
        'handler' => 'syslog',
        'label' => 'Syslog',
        'ident' => 'drupal',
        'level' => 200,
        'bubble' => 1,
        'weight' => -50,
      ),
    ),
  );
  $profiles[$profile->name] = $profile;

  return $profiles;
}

/**
 * @} End of "addtogroup hooks".
 */
