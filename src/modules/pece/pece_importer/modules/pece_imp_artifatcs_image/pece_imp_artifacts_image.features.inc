<?php

/**
 * @file
 * pece_imp_artifacts_image.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function pece_imp_artifacts_image_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "feeds" && $api == "feeds_importer_default") {
    return array("version" => "1");
  }
}
