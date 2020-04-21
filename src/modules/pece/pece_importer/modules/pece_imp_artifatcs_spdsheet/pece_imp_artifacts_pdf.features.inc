<?php

/**
 * @file
 * pece_imp_artifacts_spdsheet.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function pece_imp_artifacts_spdsheet_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "feeds" && $api == "feeds_importer_default") {
    return array("version" => "1");
  }
  if ($module == "feeds_tamper" && $api == "feeds_tamper_default") {
    return array("version" => "2");
  }
}
