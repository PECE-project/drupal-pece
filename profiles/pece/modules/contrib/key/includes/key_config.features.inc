<?php

/**
 * @file
 * Provides Features integration for managing keys.
 */

/**
 * Implements hook_features_export_options().
 */
function key_config_features_export_options() {
  return key_get_key_names_as_options(array(), TRUE);
}

/**
 * Implements hook_features_export().
 */
function key_config_features_export($data, &$export, $module_name) {
  $pipe = array();

  $export['dependencies']['key'] = 'key';
  foreach ($data as $component) {
    $export['features']['key_config'][$component] = $component;
  }

  return $pipe;
}

/**
 * Implements hook_features_export_render().
 */
function key_config_features_export_render($module_name, $data, $export = NULL) {
  $code = array();
  $code[] = '  $configs = array();';
  $code[] = '';

  foreach ($data as $id) {
    $config = key_get_key($id, TRUE);
    $config_identifier = features_var_export($id);
    $config_export = features_var_export($config, '  ');
    $code[] = "  // Exported key: {$id}.";
    $code[] = "  \$configs[{$config_identifier}] = {$config_export};";
    $code[] = "";
  }

  $code[] = '  return $configs;';
  $code = implode("\n", $code);

  return array('key_default_configs' => $code);
}

/**
 * Implements hook_features_revert().
 */
function key_config_features_revert($module) {
  key_config_features_rebuild($module);
}

/**
 * Implements hook_features_rebuild().
 */
function key_config_features_rebuild($module) {
  $configs = module_invoke($module, 'key_default_configs');

  foreach ($configs as $config) {
    key_save_key($config, array(), FALSE);
  }
}
