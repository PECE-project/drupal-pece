<?php

/**
 * @file
 * Provides Features integration for managing configurations.
 */

/**
 * Implements hook_features_export_options().
 */
function encrypt_config_features_export_options() {
  return encrypt_get_configs_as_options(TRUE);
}

/**
 * Implements hook_features_export().
 */
function encrypt_config_features_export($data, &$export, $module_name) {
  $pipe = array();

  $export['dependencies']['encrypt'] = 'encrypt';
  foreach ($data as $component) {
    $export['features']['encrypt_config'][$component] = $component;
  }

  return $pipe;
}

/**
 * Implements hook_features_export_render().
 */
function encrypt_config_features_export_render($module_name, $data, $export = NULL) {
  $code = array();
  $code[] = '  $configs = array();';
  $code[] = '';

  foreach ($data as $name) {
    $config = encrypt_config_load($name);
    $config_identifier = features_var_export($name);
    $config_export = features_var_export($config , '  ');
    $code[] = "  // Exported configuration: {$name}.";
    $code[] = "  \$configs[{$config_identifier}] = {$config_export};";
    $code[] = "";
  }

  $code[] = '  return $configs;';
  $code = implode("\n", $code);

  return array('encrypt_default_configs' => $code);
}

/**
 * Implements hook_features_revert().
 */
function encrypt_config_features_revert($module) {
  encrypt_config_features_rebuild($module);
}

/**
 * Implements hook_features_rebuild().
 */
function encrypt_config_features_rebuild($module) {
  $configs = module_invoke($module, 'encrypt_default_configs');

  foreach ($configs as $key => $config) {
    encrypt_save_config($config, FALSE);
  }
}
