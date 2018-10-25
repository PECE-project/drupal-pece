<?php
/**
 * @file
 * Database interface for the tvi module.
 */

/**
 * Return a default setting object.
 *
 * @param string $type
 *   The type of default settings that we are generating. It can be
 *   TVI_TYPE_TERM or TVI_TYPE_VOCAB.
 * @param string|int $xid
 *   The identifier of the object for which we are generating these default
 *   settings. It can be an integer or and UUID.
 *
 * @return object
 *   The TVI default settings.
 */
function tvi_default_settings($type = TVI_TYPE_TERM, $xid = 0) {
  $settings = new stdClass();

  $settings->type = $type;
  $settings->xid  = $xid;

  $settings->view_name = NULL;
  $settings->display = NULL;
  $settings->status  = 0;
  $settings->inherit = 0;
  $settings->pass_arguments = 0;

  $settings->is_default = TRUE;

  return $settings;
}

/**
 * Load a setting from the database or return a default.
 *
 * @param string|int $xid
 *   The identifier of the object for which we are loading these settings. It
 *   can be an integer or and UUID.
 * @param string $type
 *   The type of the object for which we are loading these settings. It can be
 *   TVI_TYPE_TERM or TVI_TYPE_VOCAB.
 * @param bool $return_default
 *   A boolean to decide if we want to return default settings if no settings
 *   are set for this object.
 *
 * @return bool|object
 *   FALSE if no settings are set for this object and $return_default is TRUE.
 *   Otherwise, the settings object corresponding to the given term/vocabulary.
 */
function tvi_load_settings($xid, $type = TVI_TYPE_TERM, $return_default = TRUE) {
  $xid = _tvi_get_xid($xid, $type);

  $settings = variable_get('tvi_' . $type . '_' . $xid, FALSE);
  $settings = is_array($settings) ? (object) $settings : $settings;

  $settings = tvi_validate_settings($settings);
  if ($settings === FALSE && $return_default) {
    return tvi_default_settings($type, $xid);
  }

  // Avoid loss during tid/uuid conversion.
  if (!empty($settings)) {
    $settings->xid = $xid;
    $settings->type = $type;
  }

  return $settings;
}

/**
 * Check if the views and views' displays referenced by the settings are valid.
 *
 * They are valid if they stillexists and are still enabled.
 *
 * @param object $settings
 *   A TVI settings object.
 *
 * @return bool
 *   TRUE if the settings are still valid, else FALSE.
 */
function tvi_validate_settings($settings) {
  if (empty($settings) || empty($settings->view_name)) {
    return FALSE;
  }

  // Load the view.
  $view = views_get_view($settings->view_name);

  // If the view does not exist or if it is disabled.
  if (empty($view) || !empty($view->disabled)) {
    return FALSE;
  }
  // If the view's display does not exist.
  if (!array_key_exists($settings->display, $view->display)) {
    return FALSE;
  }
  // If the view's display is disabled.
  if (array_key_exists('enabled', $view->display[$settings->display]->display_options) && $view->display[$settings->display]->display_options['enabled'] === FALSE) {
    return FALSE;
  }

  $settings->view = $view;
  $settings->is_default = FALSE;
  return $settings;
}

/**
 * Save settings information for a taxonomy vocabulary or term to the database.
 *
 * @param object $settings
 *   A TVI settings object.
 */
function tvi_update_settings($settings) {
  if (is_object($settings)) {
    $settings = (array) $settings;
  }

  // Do not store the view object.
  unset($settings['view']);

  variable_set('tvi_' . $settings['type'] . '_' . $settings['xid'], $settings);
}

/**
 * Delete settings information for a taxonomy term/vocabulary in the database.
 *
 * @param string|int $xid
 *   The identifier of the object for which we are loading these settings. It
 *   can be an integer or and UUID.
 * @param string $type
 *   The type of the object for which we are loading these settings. It can be
 *   TVI_TYPE_TERM or TVI_TYPE_VOCAB.
 */
function tvi_remove_settings($xid, $type = TVI_TYPE_TERM) {
  $xid = _tvi_get_xid($xid, $type);

  variable_del('tvi_' . $type . '_' . $xid);
}

/**
 * Convert the entity id into its best parameter.
 *
 * Vocabulary's vid converts to machine_name.
 * Term's tid converts to uuid if set.
 *
 * @param string|int $xid
 *   The identifier of the object for which we are loading these settings. It
 *   can be an integer and/or a UUID.
 * @param string $type
 *   The type of the object for which we are loading these settings. It can be
 *   TVI_TYPE_TERM or TVI_TYPE_VOCAB.
 *
 * @return string
 *   Vocabulary machine_name or term uuid.
 */
function _tvi_get_xid($xid, $type = TVI_TYPE_TERM) {
  if ($type == TVI_TYPE_VOCAB) {
    $vocabulary = taxonomy_vocabulary_load($xid);
    if (!empty($vocabulary->machine_name)) {
      $xid = $vocabulary->machine_name;
    }
  }
  elseif ($type == TVI_TYPE_TERM && module_exists('uuid') && $xid != '_autocreate') {
    $uuids = entity_get_uuid_by_id('taxonomy_term', array($xid));
    $uuid = reset($uuids);
    if (!empty($uuid)) {
      $xid = $uuid;
    }
  }
  return $xid;
}

/**
 * Massively convert all settings based on the tid to uuids.
 */
function _tvi_convert_tids_to_uuids() {
  module_load_include('module', 'uuid');
  uuid_sync_all();

  $variables = db_select('variable', 'v')
    ->fields('v')
    ->condition('v.name', 'tvi_' . TVI_TYPE_TERM . '_%', 'LIKE')
    ->execute()
    ->fetchAll();

  foreach ($variables as $variable) {
    $tid = drupal_substr($variable->name, drupal_strlen('tvi_' . TVI_TYPE_TERM . '_'));
    $uuid = reset(entity_get_uuid_by_id('taxonomy_term', array($tid)));
    if (!empty($uuid) && $tid != $uuid) {
      db_update('variable')
        ->fields(array('name' => 'tvi_' . TVI_TYPE_TERM . '_' . $uuid))
        ->condition('name', $variable->name)
        ->execute();
    }
  }
}

/**
 * Massively convert all settings based on the uuids to tids.
 *
 * As UUID is disabled we cannot use its functions to retreive the related tid
 * so we have to get the value from the database.
 */
function _tvi_convert_uuids_to_tids() {
  $variables = db_select('variable', 'v')
    ->fields('v')
    ->condition('v.name', 'tvi_' . TVI_TYPE_TERM . '_%', 'LIKE')
    ->execute()
    ->fetchAll();

  foreach ($variables as $variable) {
    $uuid = drupal_substr($variable->name, drupal_strlen('tvi_' . TVI_TYPE_TERM . '_'));
    $tid = db_select('taxonomy_term_data', 'ttd')
      ->fields('ttd', array('tid'))
      ->condition('ttd.uuid', $uuid)
      ->execute()
      ->fetchColumn();
    if (!empty($tid) && $tid != $uuid) {
      db_update('variable')
        ->fields(array('name' => 'tvi_' . TVI_TYPE_TERM . '_' . $tid))
        ->condition('name', $variable->name)
        ->execute();
    }
  }
}
