<?php
/**
 * @file
 * pece_profile.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function pece_profile_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "panelizer" && $api == "panelizer") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_default_profile2_type().
 */
function pece_profile_default_profile2_type() {
  $items = array();
  $items['pece_profile_main'] = entity_import('profile2_type', '{
    "userCategory" : true,
    "userView" : true,
    "type" : "pece_profile_main",
    "label" : "Profile",
    "weight" : "0",
    "data" : { "registration" : 1, "use_page" : 1 }
  }');
  return $items;
}
