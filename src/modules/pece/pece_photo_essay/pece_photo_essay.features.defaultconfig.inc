<?php
/**
 * @file
 * pece_photo_essay.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function pece_photo_essay_defaultconfig_features() {
  return array(
    'pece_photo_essay' => array(
      'strongarm' => 'strongarm',
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_strongarm().
 */
function pece_photo_essay_defaultconfig_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_pece_photo_essay';
  $strongarm->value = 0;
  $export['comment_anonymous_pece_photo_essay'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_pece_photo_essay';
  $strongarm->value = 1;
  $export['comment_default_mode_pece_photo_essay'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_pece_photo_essay';
  $strongarm->value = '50';
  $export['comment_default_per_page_pece_photo_essay'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_pece_photo_essay';
  $strongarm->value = 1;
  $export['comment_form_location_pece_photo_essay'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_pece_photo_essay';
  $strongarm->value = '2';
  $export['comment_pece_photo_essay'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_pece_photo_essay';
  $strongarm->value = '1';
  $export['comment_preview_pece_photo_essay'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_pece_photo_essay';
  $strongarm->value = 1;
  $export['comment_subject_field_pece_photo_essay'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__pece_photo_essay';
  $strongarm->value = array(
    'view_modes' => array(),
    'extra_fields' => array(
      'form' => array(
        'locations' => array(
          'weight' => '12',
        ),
        'title' => array(
          'weight' => '1',
        ),
        'path' => array(
          'weight' => '11',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__pece_photo_essay'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_pece_photo_essay';
  $strongarm->value = '0';
  $export['language_content_type_pece_photo_essay'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_pece_photo_essay';
  $strongarm->value = array();
  $export['menu_options_pece_photo_essay'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_pece_photo_essay';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_pece_photo_essay'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_pece_photo_essay';
  $strongarm->value = array(
    0 => 'status',
    1 => 'revision',
  );
  $export['node_options_pece_photo_essay'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_pece_photo_essay';
  $strongarm->value = '1';
  $export['node_preview_pece_photo_essay'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_pece_photo_essay';
  $strongarm->value = 1;
  $export['node_submitted_pece_photo_essay'] = $strongarm;

  return $export;
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function pece_photo_essay_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create pece_photo_essay content'.
  $permissions['create pece_photo_essay content'] = array(
    'name' => 'create pece_photo_essay content',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any pece_photo_essay content'.
  $permissions['delete any pece_photo_essay content'] = array(
    'name' => 'delete any pece_photo_essay content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own pece_photo_essay content'.
  $permissions['delete own pece_photo_essay content'] = array(
    'name' => 'delete own pece_photo_essay content',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'eck add pece_photo_essay_item pece_photo_essay_item entities'.
  $permissions['eck add pece_photo_essay_item pece_photo_essay_item entities'] = array(
    'name' => 'eck add pece_photo_essay_item pece_photo_essay_item entities',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'eck',
  );

  // Exported permission: 'eck delete pece_photo_essay_item pece_photo_essay_item entities'.
  $permissions['eck delete pece_photo_essay_item pece_photo_essay_item entities'] = array(
    'name' => 'eck delete pece_photo_essay_item pece_photo_essay_item entities',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'eck',
  );

  // Exported permission: 'eck edit pece_photo_essay_item pece_photo_essay_item entities'.
  $permissions['eck edit pece_photo_essay_item pece_photo_essay_item entities'] = array(
    'name' => 'eck edit pece_photo_essay_item pece_photo_essay_item entities',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'eck',
  );

  // Exported permission: 'eck view pece_photo_essay_item pece_photo_essay_item entities'.
  $permissions['eck view pece_photo_essay_item pece_photo_essay_item entities'] = array(
    'name' => 'eck view pece_photo_essay_item pece_photo_essay_item entities',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'eck',
  );

  // Exported permission: 'edit any pece_photo_essay content'.
  $permissions['edit any pece_photo_essay content'] = array(
    'name' => 'edit any pece_photo_essay content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own pece_photo_essay content'.
  $permissions['edit own pece_photo_essay content'] = array(
    'name' => 'edit own pece_photo_essay content',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
      'editor' => 'editor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'set pece_photo_essay published on date'.
  $permissions['set pece_photo_essay published on date'] = array(
    'name' => 'set pece_photo_essay published on date',
    'roles' => array(),
    'module' => 'publication_date',
  );

  return $permissions;
}
