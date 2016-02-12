<?php
/**
 * @file
 * pece_profile.features.inc
 */

/**
 * Implements hook_field_default_field_instances_alter().
 */
function pece_profile_field_default_field_instances_alter(&$data) {
  if (isset($data['user-user-field_user_picture'])) {
    $data['user-user-field_user_picture']['display']['mini_teaser'] = array(
      'label' => 'hidden',
      'module' => 'image',
      'settings' => array(
        'image_link' => '',
        'image_style' => 'panopoly_image_square',
      ),
      'type' => 'image',
      'weight' => 0,
    ); /* WAS: '' */
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
