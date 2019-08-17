<?php

/**
 * @file
 * pece_imp_artifacts_text.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function pece_imp_artifacts_text_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "feeds" && $api == "feeds_importer_default") {
    return array("version" => "1");
  }
}
