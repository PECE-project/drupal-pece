<?php
/**
 * @file
 * pece_photo_essay.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function pece_photo_essay_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance:
  // 'photo_essay_item-photo_essay_item-field_description'.
  $field_instances['photo_essay_item-photo_essay_item-field_description'] = array(
    'bundle' => 'photo_essay_item',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'photo_essay_item',
    'fences_wrapper' => 'div',
    'field_name' => 'field_description',
    'label' => 'Text',
    'required' => 0,
    'settings' => array(
      'linkit' => array(
        'button_text' => 'Search',
        'enable' => 0,
        'profile' => '',
      ),
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 1,
    ),
  );

  // Exported field_instance:
  // 'photo_essay_item-photo_essay_item-field_image_artifact'.
  $field_instances['photo_essay_item-photo_essay_item-field_image_artifact'] = array(
    'bundle' => 'photo_essay_item',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 1,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'photo_essay_item',
    'entityconnect_show_add_icon' => 0,
    'entityconnect_show_edit_icon' => 0,
    'entityconnect_unload_add' => 1,
    'entityconnect_unload_edit' => 1,
    'fences_wrapper' => 'div_div_div',
    'field_name' => 'field_image_artifact',
    'label' => 'Image artifact',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'entityreference',
      'settings' => array(
        'match_operator' => 'CONTAINS',
        'path' => '',
        'size' => 60,
      ),
      'type' => 'entityreference_autocomplete',
      'weight' => 0,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Image artifact');
  t('Text');

  return $field_instances;
}
