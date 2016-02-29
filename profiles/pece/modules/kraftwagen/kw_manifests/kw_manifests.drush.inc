<?php

/**
 * Implements hook_drush_command().
 */
function kw_manifests_drush_command() {
  $items = array();

  $items['kw-manifests'] = array(
    'description' => 'Run all the manifests that are defined in this installation.',
    'aliases' => array('kw-m'),
    'drupal dependencies' => array('kw_manifests'),
  );

  return $items;
}

/**
 * Implements drush_COMMAND() for kw-manifests.
 */
function drush_kw_manifests($environment = null) {
  // if no explicit enviroment is given, default to production but let the 
  // kw_environment module override this.
  if (!isset($environment)) {
    $environment = 'production';
    if (function_exists('kw_environment')) {
      $environment = kw_environment();
    }
  }

  // load all defined manifests in executable order
  $manifests = kw_manifests_info();
  if (empty($manifests)) {
    drush_log(dt('No Kraftwagen manifests found.'), 'ok');
    return;
  }

  // execute all manifests
  foreach ($manifests as $id => $manifest) {
    // do not execute manifests that require an environment that is not the 
    // current
    if (!empty($manifest['require environment'])) {
      if (!is_array($manifest['require environment'])) {
        $manifest['require environment'] = array($manifest['require environment']);
      }
      if (!in_array($environment, $manifest['require environment'])) {
        continue;
      }
    }

    // do not execute manifests that exclude the current environment
    if (!empty($manifest['exclude environment'])) {
      if (!is_array($manifest['exclude environment'])) {
        $manifest['exclude environment'] = array($manifest['exclude environment']);
      }
      if (in_array($environment, $manifest['exclude environment'])) {
        continue;
      }
    }

    drush_log(dt('Applying manifest !name for !module', array('!name' => $manifest['name'], '!module' => $manifest['module'])));

    // run manifest
    $result = kw_manifests_run($manifest);

    // fail when a manifest could not be applied
    if (!$result) {
      return drush_set_error(dt('Could not apply manifest !name for !module.', array('!name' => $manifest['name'], '!module' => $manifest['module'])));
    }

    drush_log(dt('Manifest !name for !module ran successfully.', array('!name' => $manifest['name'], '!module' => $manifest['module'])), 'ok');
  }

  drush_log(dt('Finished running manifests.'), 'ok');
}
