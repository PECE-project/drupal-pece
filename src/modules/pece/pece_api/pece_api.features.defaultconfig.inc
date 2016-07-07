<?php
/**
 * @file
 * pece_api.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function pece_api_defaultconfig_features() {
  return array(
    'pece_api' => array(
      'default_services_endpoint' => 'default_services_endpoint',
      'strongarm' => 'strongarm',
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_default_services_endpoint().
 */
function pece_api_defaultconfig_default_services_endpoint() {
  $export = array();

  $endpoint = new stdClass();
  $endpoint->disabled = FALSE; /* Edit this to true to make a default endpoint disabled initially */
  $endpoint->api_version = 3;
  $endpoint->name = 'auth';
  $endpoint->server = 'rest_server';
  $endpoint->path = 'api/auth';
  $endpoint->authentication = array(
    'services' => 'services',
  );
  $endpoint->server_settings = array(
    'formatters' => array(
      'json' => TRUE,
      'xml' => TRUE,
      'bencode' => FALSE,
      'jsonp' => FALSE,
      'php' => FALSE,
      'yaml' => FALSE,
    ),
    'parsers' => array(
      'application/json' => TRUE,
      'application/x-www-form-urlencoded' => TRUE,
      'application/xml' => TRUE,
      'multipart/form-data' => TRUE,
      'application/vnd.php.serialized' => FALSE,
      'application/x-yaml' => FALSE,
      'text/xml' => FALSE,
    ),
  );
  $endpoint->resources = array(
    'file' => array(
      'alias' => 'files',
      'operations' => array(
        'create' => array(
          'enabled' => '1',
        ),
        'retrieve' => array(
          'enabled' => '1',
        ),
        'delete' => array(
          'enabled' => '1',
        ),
        'index' => array(
          'enabled' => '1',
        ),
      ),
      'actions' => array(
        'create_raw' => array(
          'enabled' => '1',
        ),
      ),
    ),
    'node' => array(
      'alias' => 'nodes',
      'operations' => array(
        'retrieve' => array(
          'enabled' => '1',
        ),
        'create' => array(
          'enabled' => '1',
        ),
        'update' => array(
          'enabled' => '1',
        ),
        'delete' => array(
          'enabled' => '1',
        ),
        'index' => array(
          'enabled' => '1',
        ),
      ),
      'relationships' => array(
        'files' => array(
          'enabled' => '1',
        ),
        'comments' => array(
          'enabled' => '1',
        ),
      ),
      'targeted_actions' => array(
        'attach_file' => array(
          'enabled' => '1',
        ),
      ),
    ),
    'taxonomy_term' => array(
      'alias' => 'tags',
      'operations' => array(
        'retrieve' => array(
          'enabled' => '1',
        ),
        'create' => array(
          'enabled' => '1',
        ),
        'update' => array(
          'enabled' => '1',
        ),
        'delete' => array(
          'enabled' => '1',
        ),
        'index' => array(
          'enabled' => '1',
        ),
      ),
      'actions' => array(
        'selectNodes' => array(
          'enabled' => '1',
        ),
      ),
    ),
    'taxonomy_vocabulary' => array(
      'alias' => 'vocab',
      'operations' => array(
        'retrieve' => array(
          'enabled' => '1',
        ),
        'create' => array(
          'enabled' => '1',
        ),
        'update' => array(
          'enabled' => '1',
        ),
        'delete' => array(
          'enabled' => '1',
        ),
        'index' => array(
          'enabled' => '1',
        ),
      ),
      'actions' => array(
        'getTree' => array(
          'enabled' => '1',
        ),
      ),
    ),
    'user' => array(
      'alias' => 'users',
      'operations' => array(
        'retrieve' => array(
          'enabled' => '1',
        ),
        'create' => array(
          'enabled' => '1',
        ),
        'update' => array(
          'enabled' => '1',
        ),
        'delete' => array(
          'enabled' => '1',
        ),
        'index' => array(
          'enabled' => '1',
        ),
      ),
      'actions' => array(
        'login' => array(
          'enabled' => '1',
          'settings' => array(
            'services' => array(
              'resource_api_version' => '1.0',
            ),
          ),
        ),
        'logout' => array(
          'enabled' => '1',
          'settings' => array(
            'services' => array(
              'resource_api_version' => '1.0',
            ),
          ),
        ),
        'token' => array(
          'enabled' => '1',
        ),
        'request_new_password' => array(
          'enabled' => '1',
        ),
        'register' => array(
          'enabled' => '1',
        ),
      ),
      'targeted_actions' => array(
        'cancel' => array(
          'enabled' => '1',
        ),
        'password_reset' => array(
          'enabled' => '1',
        ),
        'resend_welcome_email' => array(
          'enabled' => '1',
        ),
      ),
    ),
  );
  $endpoint->debug = 0;
  $export['auth'] = $endpoint;

  return $export;
}

/**
 * Implements hook_defaultconfig_strongarm().
 */
function pece_api_defaultconfig_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'services_security_update_1';
  $strongarm->value = TRUE;
  $export['services_security_update_1'] = $strongarm;

  return $export;
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function pece_api_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer services'.
  $permissions['administer services'] = array(
    'name' => 'administer services',
    'roles' => array(),
    'module' => 'services',
  );

  return $permissions;
}
