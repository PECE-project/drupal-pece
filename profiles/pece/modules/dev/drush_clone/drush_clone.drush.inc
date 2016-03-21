<?php
/**
 * @file
 * Drush extension allows developers to quickly clone modules or features
 * to speed up writing code reusing custom templates
 */

/**
 * Implements hook_drush_command().
 */
function drush_clone_drush_command() {
  $items['module-clone'] = array(
    'description' => dt('Clone a module.'),
    'arguments' => array(
      'source' => dt('Name of module that will be cloned'),
      'target' => dt('Name of new, cloned module.'),
    ),
    'examples' => array(
      'module-clone model my_entity' => dt('Clone "model" module in to "my_entity" module.'),
    ),
  );

  $items['feature-clone'] = array(
    'description' => dt('Clone a feature.'),
    'arguments' => array(
      'source' => dt('Name of feature that will be cloned'),
      'target' => dt('Name of new, cloned feature.'),
    ),
    'examples' => array(
      'feature-clone feature_source feature_target' =>
      dt('Clone "feature_source" module in to "feature_target" feature.'),
    ),
  );

  $items['model-clone'] = array(
    'description' => dt('Clone an entity model.'),
    'arguments' => array(
      'target' => dt('Name of new, cloned entity.'),
    ),
    'examples' => array(
      'model-clone entity_name' => dt('Clone an entity model.'),
    ),
  );

  return $items;
}

/**
 * Drush callback for model clone.
 */
function drush_drush_clone_model_clone($target = NULL) {
  // TODO: implements handling for model if required.
  drush_clone_validate('model-clone', 'model', $target);
  drush_drush_clone_module_clone('model', $target);
}

/**
 * Drush callback for feature clone.
 */
function drush_drush_clone_feature_clone($source, $target = NULL) {
  // TODO: implements handling for feautures if required.
  drush_clone_validate('feature-clone', $source, $target);
  drush_drush_clone_module_clone($source, $target);
}

/**
 * Drush callback for module clone.
 */
function drush_drush_clone_module_clone($source = NULL, $target = NULL) {

  $source = drupal_strtolower($source);
  $target = drupal_strtolower($target);

  drush_clone_validate('module-clone', $source, $target);

  $source_path = drupal_get_path('module', $source);
  $files = file_scan_directory($source_path, '/.*/');

  foreach ($files as $file) {
    $target_uri = str_replace($source, $target, $file->uri);

    // Create target_dir if not exists.
    file_prepare_directory(dirname($target_uri), FILE_CREATE_DIRECTORY);

    if (drush_clone_is_file_to_clone($file)) {
      $data = file_get_contents($file->uri);

      if (drush_clone_is_file_info($file)) {
        drush_clone_info_handling($data, $target);
      }

      // Replace occurrences of $source.
      $data = str_replace($source, $target, $data);

      // Replace occurrences of first character of $source capitalized
      // needed for Classes.
      // TODO: Improve Class name handling.
      $data = str_replace(drupal_ucfirst($source), drupal_ucfirst($target), $data);

      file_unmanaged_save_data($data, $target_uri);

      drush_log(dt('Cloned !source in !target',
        array('!source' => $file->uri, '!target' => $target_uri)), 'ok');
    }
    else {
      // No need further modifications; copy file.
      file_unmanaged_copy($file->uri, $target_uri);
      drush_log(dt('Copied !source in !target',
        array('!source' => $file->uri, '!target' => $target_uri)), 'ok');
    }
  }
}

/**
 * Check for files need handling.
 *
 * @param stdClass $file
 *   A Drupal file object.
 *
 * @return bool
 *   True if $file is a file needs handling
 */
function drush_clone_is_file_to_clone($file) {
  // File extensions we need to handle.
  $ext_to_handle = 'info inc install module php';
  return (count(file_validate_extensions($file, $ext_to_handle)) == 0);
}

/**
 * Check if file is an info.
 *
 * @param stdClass $file
 *   A Drupal file object.
 *
 * @return bool
 *   True if $file is a .info file
 */
function drush_clone_is_file_info($file) {
  // File extensions we need to handle.
  $ext_to_handle = 'info';
  return (count(file_validate_extensions($file, $ext_to_handle)) == 0);
}

/**
 * Add human readable name in info file.
 *
 * @param string $data
 *   File content
 * @param string $target
 *   Machine name
 *
 * @return string
 *   Modified content
 */
function drush_clone_info_handling($data, $target) {
  $human_readable_name = ucwords(str_replace('_', ' ', $target));
  $data = preg_replace('/name\s*=\s*.+/i',
    "name = \"$human_readable_name\"",
    $data);
  $data = preg_replace('/description\s*=\s*.+/i',
    "description = \"$human_readable_name\"",
    $data);
  return $data;
}


/**
 * Implements validation for the specified command.
 *
 * @param string $command
 *   The command to execute
 * @param string $source
 *   The module or feature to clone
 * @param string $target
 *   The name of new, cloned module or feature
 */
function drush_clone_validate($command, $source = NULL, $target = NULL) {
  $module_list = array_keys(system_rebuild_module_data());
  if (empty($source)) {
    drush_die(dt('Missing arguments. See drush help !command for usage.',
      array('!command' => $command)));
  }
  if (is_null($target)) {
    drush_die(dt('The name of new, cloned module/feature is required.'));
  }
  if ($source == $target) {
    drush_die(dt('Source and target name are equal. Change the target name.'));
  }
  if (!in_array($source, $module_list)) {
    drush_die(dt('The module or feature "!module" could not be found.',
      array('!module' => $source)));
  }
  if (in_array($target, $module_list)) {
    drush_die(dt('A module/feature with target name "!module" already exists.',
      array('!module' => $target)));
  }
}
