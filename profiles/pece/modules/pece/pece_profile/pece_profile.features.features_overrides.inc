<?php
/**
 * @file
 * pece_profile.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function pece_profile_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: field_instance
  $overrides["field_instance.user-user-field_user_picture.display|mini_teaser"] = array(
    'label' => 'hidden',
    'module' => 'image',
    'settings' => array(
      'image_link' => '',
      'image_style' => 'panopoly_image_square',
    ),
    'type' => 'image',
    'weight' => 0,
  );

 return $overrides;
}
