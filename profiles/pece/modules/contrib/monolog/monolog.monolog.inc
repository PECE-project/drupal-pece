<?php

/**
 * @file
 * Monolog hook implementations.
 */

/**
 * Implements hook_monolog_handler_path().
 */
function monolog_monolog_handler_path() {
  return 'handlers';
}

/**
 * Implements hook_monolog_handler_info().
 */
function monolog_monolog_handler_info() {
  $handlers = array();

  $handlers['stream'] = array(
    'label' => t('Stream Handler'),
    'description' => t('Logs records into any PHP stream, use this for log files.'),
    'group' => t('Files and syslog'),
    'default settings' => array(
      'filepath' => 'public://monolog/drupal.log',
    ),
  );

  $handlers['rotating_file'] = array(
    'label' => t('Rotating File Handler'),
    'description' => t('Logs records to a file and creates one logfile per day. It will also delete files older than the "Max Files" settings.'),
    'group' => t('Files and syslog'),
    'default settings' => array(
      'filepath' => 'public://monolog/drupal.log',
      'max_files' => 0,
    ),
  );

  $handlers['syslog'] = array(
    'label' => t('Syslog Handler'),
    'description' => t('Logs records to the syslog.'),
    'group' => t('Files and syslog'),
    'default settings' => array(
      'ident' => 'drupal',
    ),
  );

  $handlers['syslogudp'] = array(
    'label' => t('SyslogUdp Handler'),
    'description' => t('Logs records to syslogUdp.'),
    'group' => t('Files and syslog'),
    'default settings' => array(
      'host' => 'rsyslog',
      'port' => 514,
    ),
  );

  $handlers['native_mailer'] = array(
    'label' => t('Native Mail Handler'),
    'description' => t('Sends emails using PHP\'s <code>mail()</code> function.'),
    'group' => t('Alerts and emails'),
    'default settings' => array(
      'to' => '<site-mail>',
      'from' => '<site-mail>',
      'subject' => t('Log message sent by !site', array('!site' => variable_get('site_name', 'Drupal'))),
    ),
  );

  $handlers['socket'] = array(
    'label' => t('Sockets Handler'),
    'description' => t('Logs records to sockets, use this for UNIX and TCP sockets.'),
    'group' => t('Servers and networked logging'),
    'default settings' => array(
      'connection_string' => '',
      'persistent' => 0,
      'connection_timeout' => 5,
      'write_timeout' => 60,
    ),
  );

  $handlers['chromephp'] = array(
    'label' => t('ChromePHP Handler'),
    'description' => t('Handler for ChromePHP, providing inline console messages within Chrome.'),
    'group' => t('Development'),
    'settings callback' => FALSE,
  );

  $handlers['firephp'] = array(
    'label' => t('FirePHP Handler'),
    'description' => t('Handler for FirePHP, providing inline console messages within FireBug.'),
    'group' => t('Development'),
    'settings callback' => FALSE,
  );

  $handlers['null'] = array(
    'label' => t('Null Handler'),
    'description' => t('Any record it can handle will be thrown away. This can be used to put on top of an existing handler stack to disable it temporarily.'),
    'group' => t('Wrappers / special handlers'),
  );

  $handlers['hipchat'] = array(
    'label' => t('HipChat Handler'),
    'description' => t('Logs records to a HipChat chat room using its API.'),
    'group' => t('Alerts and emails'),
    'default settings' => array(
      'token' => '',
      'room' => '',
      'contact_name' => variable_get('site_name', 'Drupal'),
      'notify' => 0,
    ),
  );

  return $handlers;
}

/**
 * Implements hook_default_monolog_profiles().
 */
function monolog_default_monolog_profiles() {
  $profiles = array();

  $profile = new stdClass();
  $profile->disabled = FALSE;
  $profile->api_version = 1;
  $profile->name = 'production';
  $profile->options = array(
    'label' => 'Production',
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

  $profile = new stdClass();
  $profile->disabled = FALSE;
  $profile->api_version = 1;
  $profile->name = 'development';
  $profile->options = array(
    'label' => 'Development',
    'handlers' => array(
      'stream' => array(
        'handler' => 'stream',
        'label' => 'Log file',
        'filepath' => 'public://monolog/drupal.log',
        'level' => 200,
        'bubble' => 1,
        'weight' => -50,
      ),
    ),
  );
  $profiles[$profile->name] = $profile;

  return $profiles;
}
