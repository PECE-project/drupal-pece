<?php
/**
 * @file
 * pece_about.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function pece_about_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "panelizer" && $api == "panelizer") {
    return array("version" => "1");
  }
}
