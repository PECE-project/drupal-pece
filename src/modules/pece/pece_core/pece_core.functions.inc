<?php

/**
 * Helper functions for PECE Core module.
 */

/**
 * Custom function to add modal
 */
function pece_core_modal_presets($modal_name, $width, $height) {
  // Include the CTools tools that we need.
  ctools_include('ajax');
  ctools_include('modal');

  $theme_default = variable_get('theme_default');

  $settings = array(
    $modal_name => array(
      'modalSize' => array(
        'type' => 'fixed',
        'width' => $width,
        'height' => $height,
      ),
      'modalOptions' => array(
        'backdropClose' => TRUE,
      ),
      'loadingText' => t('Loading...'),
      'closeText' => t('close'),
      'closeImage' => '',
      'throbber' => theme('image', array(
        'path' => drupal_get_path('theme', $theme_default) . '/img/throbber.gif',
        'title' => t('Loading.'),
        'alt' => t('Loading'),
      )),
    ),
  );
  drupal_add_js($settings, 'setting');

  // Add CTools' javascript to the page.
  ctools_modal_add_js();
}

/**
 * Helper method to perform jQuery.extend like default settings.
 */
function pece_array_extend() {
  $arrays = func_get_args();
  $base = array_shift($arrays);
  foreach ($arrays as $array) {
    reset($base);
    while (list($key, $value) = @each($array)) {
      if (is_array($value) && @is_array($base[$key])) {
        $base[$key] = pece_array_extend($base[$key], $value);
      } else {
        $base[$key] = $value;
      }
    }
  }
  return $base;
}


/**
 * Helper Access callback generator for entity reference fields.
 *
 * @param $entity_info array
 * @param $entity_type_name string
 *    Entity machine name
 */
function pece_entity_access_info_alter_prepare(&$entity_info, $entity_type_name = '') {
  if (!empty($entity_info[$entity_type_name])) {
    if (empty($callback = variable_get($entity_type_name . '__access_callback', NULL))) {
      $callback = $entity_info[$entity_type_name]['access callback'];
      variable_set($entity_type_name. '__access_callback', $callback);
    }

    $entity_info[$entity_type_name]['access callback'] = $entity_type_name . '__entity_callback';
  }
}

/**
 * Dynamic entity access for Eck entities.
 */
function pece_entity_access_callback_prepare($op, $entity, $account, $entity_type_name, $field_name) {
  switch ($op) {
    case 'view':
      if (is_object($entity) && isset($entity->id)) {
        $$entity_type_name = entity_metadata_wrapper($entity_type_name, $entity);
        $referenced_entity = $$entity_type_name->$field_name->value();

        if (!empty($referenced_entity) && !node_access('view', $referenced_entity, $account)) {
          return FALSE;
        }
      }
      break;
  }

  $default_access_callback = variable_get($entity_type_name . '__access_callback', 'eck__entity_access');
  return $default_access_callback($op, $entity, $account, $entity_type_name);
}

/**
 * Helper to build complex permission list blocks.
 */
function pece_core_compose_typed_perms($types = array(), $perm_list = array(), $permissions = array(), $role_name = '') {
  foreach ($types as $type) {
    // Replace the placeholder with given type.
    $perms = json_decode(str_replace('<type>', $type, json_encode($perm_list)), true);
    $permissions[$role_name] =
      array_merge($permissions[$role_name], $perms);
  }
  return $permissions;
}

/**
 * Set default permissions of Data Importer role.
 */
function pece_core_set_data_importer_role_perms() {
  pece_set_permissions(pece_core_get_data_importer_role_perms());
}

/**
 * Returns complete list of permissions of Data Importer role.
 */
function pece_core_get_data_importer_role_perms() {
  $perms = pece_core_get_data_importer_init_perms();
  $perms = pece_core_get_data_importer_files_perms($perms);
  return pece_core_get_data_importer_feeds_perms($perms);
}

/**
 * Returns initial list of permissions of Data Importer role.
 */
function pece_core_get_data_importer_init_perms() {
  return array(
    'Data Importer' => array(
      'access administration menu' => TRUE,
      'access administration pages' => TRUE,
      'access content' => TRUE,
      'access content overview' => TRUE,
      'administer files' => TRUE,
      'create files' => TRUE,
      'view own private files' => TRUE,
      'view files' => TRUE,
      'view own files' => TRUE,
      'access media browser' => TRUE,
      'add media from remote sources' => TRUE,
      'view the administration theme' => TRUE,
    )
  );
}

/**
 * Build permissions array with files permission list block.
 */
function pece_core_get_data_importer_files_perms($permissions = array()) {
  // Insert multiple file types permissions into Data Importer permissions.
  return pece_core_compose_typed_perms(
    array('image', 'audio', 'document'),
    array(
      'edit own <type> files' => TRUE,
      'edit any <type> files' => TRUE,
      'delete own <type> files' => TRUE,
      'delete any <type> files' => TRUE,
      'download own <type> files' => TRUE,
      'download any <type> files' => TRUE,
    ),
    $permissions,
    'Data Importer');
}

/**
 * Build permissions array with feeds permission list block.
 */
function pece_core_get_data_importer_feeds_perms($permissions = array()) {
  // Feeds module specific permissions for custom feeds.
  return pece_core_compose_typed_perms(
    array(
      'pece_imp_artifacts_audio',
      'pece_imp_artifacts_image',
      'pece_imp_artifacts_pdf',
      'pece_imp_artifacts_tabular',
      'pece_imp_artifacts_text',
      'pece_imp_artifacts_video',
      'pece_imp_artifacts_website'
    ),
    array(
      'import <type> feeds' => TRUE,
      'clear <type> feeds' => TRUE,
      'unlock <type> feeds' => TRUE,
    ),
    $permissions,
    'Data Importer'
  );
}
