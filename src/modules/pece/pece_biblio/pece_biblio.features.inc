<?php
/**
 * @file
 * pece_biblio.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function pece_biblio_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
