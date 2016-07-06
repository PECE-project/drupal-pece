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

  // Exported overrides for: page_manager_handlers
  $overrides["page_manager_handlers.user_view_panelizer.conf|contexts"] = array();
  $overrides["page_manager_handlers.user_view_panelizer.conf|relationships"] = array(
    0 => array(
      'identifier' => 'Profile from User (on profile.uid)',
      'keyword' => 'profile',
      'name' => 'entity_from_schema:uid-user-profile2',
      'context' => 'argument_entity_id:user_1',
      'id' => 1,
    ),
  );
  $overrides["page_manager_handlers.user_view_panelizer.weight"] = -29;

  // Exported overrides for: panelizer_defaults
  $overrides["panelizer_defaults.user:user:default.display|content|new-067392e5-fa99-4463-ae00-6d0af59f7aef"] = (object) array(
      'pid' => 'new-067392e5-fa99-4463-ae00-6d0af59f7aef',
      'panel' => 'content',
      'type' => 'entity_field',
      'subtype' => 'profile2:field_pece_biography',
      'shown' => TRUE,
      'access' => array(),
      'configuration' => array(
        'label' => 'title',
        'formatter' => 'text_default',
        'delta_limit' => 0,
        'delta_offset' => 0,
        'delta_reversed' => FALSE,
        'formatter_settings' => array(),
        'context' => array(),
        'override_title' => 0,
        'override_title_text' => '',
        'override_title_heading' => 'h2',
      ),
      'cache' => array(),
      'style' => array(),
      'css' => array(),
      'extras' => array(),
      'position' => 3,
      'locks' => array(),
      'uuid' => '067392e5-fa99-4463-ae00-6d0af59f7aef',
    );
  $overrides["panelizer_defaults.user:user:default.display|content|new-0b86ef08-4f95-4d30-9abb-dcf401f76a0b"] = (object) array(
      'pid' => 'new-0b86ef08-4f95-4d30-9abb-dcf401f76a0b',
      'panel' => 'content',
      'type' => 'entity_field',
      'subtype' => 'profile2:field_pece_position',
      'shown' => TRUE,
      'access' => array(),
      'configuration' => array(
        'label' => 'title',
        'formatter' => 'text_plain',
        'delta_limit' => 0,
        'delta_offset' => 0,
        'delta_reversed' => FALSE,
        'formatter_settings' => array(),
        'context' => array(),
        'override_title' => 0,
        'override_title_text' => 'Position',
        'override_title_heading' => 'h3',
      ),
      'cache' => array(),
      'style' => array(),
      'css' => array(),
      'extras' => array(),
      'position' => 2,
      'locks' => array(),
      'uuid' => '0b86ef08-4f95-4d30-9abb-dcf401f76a0b',
    );
  $overrides["panelizer_defaults.user:user:default.display|content|new-23b1f4f1-cda8-42ca-880a-afc2ae92f3e9|panel"] = 'sidebar';
  $overrides["panelizer_defaults.user:user:default.display|content|new-336bb02d-bd44-44ae-bc61-8a88b2526dcd"] = (object) array(
      'pid' => 'new-336bb02d-bd44-44ae-bc61-8a88b2526dcd',
      'panel' => 'sidebar',
      'type' => 'entity_field',
      'subtype' => 'profile2:field_pece_tags',
      'shown' => TRUE,
      'access' => array(),
      'configuration' => array(
        'label' => 'title',
        'formatter' => 'taxonomy_term_reference_link',
        'delta_limit' => 0,
        'delta_offset' => 0,
        'delta_reversed' => 0,
        'formatter_settings' => array(),
        'context' => array(),
        'override_title' => 0,
        'override_title_text' => '',
        'override_title_heading' => 'h2',
      ),
      'cache' => array(),
      'style' => array(),
      'css' => array(),
      'extras' => array(),
      'position' => 1,
      'locks' => array(),
      'uuid' => '336bb02d-bd44-44ae-bc61-8a88b2526dcd',
    );
  $overrides["panelizer_defaults.user:user:default.display|content|new-d76e85cd-4625-4a52-a17b-e5c65e1a0247"]["DELETED"] = TRUE;
  $overrides["panelizer_defaults.user:user:default.display|content|new-fb31bbec-c7f7-4076-94b9-ef518518a4a0"] = (object) array(
      'pid' => 'new-fb31bbec-c7f7-4076-94b9-ef518518a4a0',
      'panel' => 'content',
      'type' => 'entity_field',
      'subtype' => 'profile2:field_pece_location',
      'shown' => TRUE,
      'access' => array(),
      'configuration' => array(
        'label' => 'title',
        'formatter' => 'location_all',
        'delta_limit' => 0,
        'delta_offset' => 0,
        'delta_reversed' => FALSE,
        'formatter_settings' => array(),
        'context' => array(),
        'override_title' => 0,
        'override_title_text' => '%profile2:field-pece-institution',
        'override_title_heading' => 'h3',
      ),
      'cache' => array(),
      'style' => array(),
      'css' => array(),
      'extras' => array(),
      'position' => 1,
      'locks' => array(),
      'uuid' => 'fb31bbec-c7f7-4076-94b9-ef518518a4a0',
    );
  $overrides["panelizer_defaults.user:user:default.display|content|new-fe105be4-3a50-449d-9200-2c518c310e7a"] = (object) array(
      'pid' => 'new-fe105be4-3a50-449d-9200-2c518c310e7a',
      'panel' => 'content',
      'type' => 'entity_field',
      'subtype' => 'profile2:field_pece_institution',
      'shown' => TRUE,
      'access' => array(),
      'configuration' => array(
        'label' => 'title',
        'formatter' => 'text_plain',
        'delta_limit' => 0,
        'delta_offset' => 0,
        'delta_reversed' => FALSE,
        'formatter_settings' => array(),
        'context' => array(),
        'override_title' => 0,
        'override_title_text' => '',
        'override_title_heading' => 'h2',
      ),
      'cache' => array(),
      'style' => array(),
      'css' => array(),
      'extras' => array(),
      'position' => 0,
      'locks' => array(),
      'uuid' => 'fe105be4-3a50-449d-9200-2c518c310e7a',
    );
  $overrides["panelizer_defaults.user:user:default.display|layout"] = 'pece_sidebar_right';
  $overrides["panelizer_defaults.user:user:default.display|panels|column1"]["DELETED"] = TRUE;
  $overrides["panelizer_defaults.user:user:default.display|panels|column2"]["DELETED"] = TRUE;
  $overrides["panelizer_defaults.user:user:default.display|panels|content"] = array(
    0 => 'new-067392e5-fa99-4463-ae00-6d0af59f7aef',
    1 => 'new-0b86ef08-4f95-4d30-9abb-dcf401f76a0b',
    2 => 'new-fb31bbec-c7f7-4076-94b9-ef518518a4a0',
    3 => 'new-fe105be4-3a50-449d-9200-2c518c310e7a',
  );
  $overrides["panelizer_defaults.user:user:default.display|panels|sidebar"] = array(
    0 => 'new-23b1f4f1-cda8-42ca-880a-afc2ae92f3e9',
    1 => 'new-336bb02d-bd44-44ae-bc61-8a88b2526dcd',
  );
  $overrides["panelizer_defaults.user:user:default.relationships|0"] = array(
    'identifier' => 'Profile2 from user',
    'keyword' => 'profile2',
    'name' => 'profile2_from_user',
    'type' => 'pece_profile_main',
    'context' => 'panelizer',
    'id' => 1,
  );

 return $overrides;
}
