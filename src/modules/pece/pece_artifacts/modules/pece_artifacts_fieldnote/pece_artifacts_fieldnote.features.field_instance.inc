<?php

/**
 * @file
 * pece_artifacts_fieldnote.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function pece_artifacts_fieldnote_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-pece_artifact_fieldnote-body'.
  $field_instances['node-pece_artifact_fieldnote-body'] = array(
    'bundle' => 'pece_artifact_fieldnote',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'card' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
      'featured' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'free_panel' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'highlighted' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'meta_content' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'mini_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'most_recent' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'nodeorder' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'fences_wrapper' => 'div',
    'field_name' => 'body',
    'label' => 'Text',
    'locked' => TRUE,
    'required' => 1,
    'settings' => array(
      'display_summary' => 1,
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
        'rows' => 20,
        'summary_rows' => 5,
      ),
      'type' => 'text_textarea_with_summary',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'node-pece_artifact_fieldnote-field_ark_enabled'.
  $field_instances['node-pece_artifact_fieldnote-field_ark_enabled'] = array(
    'bundle' => 'pece_artifact_fieldnote',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'card' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 20,
      ),
      'featured' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'free_panel' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'highlighted' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'meta_content' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'mini_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'most_recent' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'nodeorder' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'fences_wrapper' => 'div_div_div',
    'field_name' => 'field_ark_enabled',
    'label' => 'ARK Enabled',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 19,
    ),
  );

  // Exported field_instance: 'node-pece_artifact_fieldnote-field_pece_authors'.
  $field_instances['node-pece_artifact_fieldnote-field_pece_authors'] = array(
    'bundle' => 'pece_artifact_fieldnote',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Who created this artifact?',
    'display' => array(
      'card' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 10,
      ),
      'featured' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'free_panel' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'highlighted' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'meta_content' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'mini_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'most_recent' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'nodeorder' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 8,
      ),
    ),
    'entity_type' => 'node',
    'fences_wrapper' => 'div',
    'field_name' => 'field_pece_authors',
    'label' => 'Creator(s)',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'taxonomy',
      'settings' => array(
        'autocomplete_path' => 'taxonomy/autocomplete',
        'size' => 60,
      ),
      'type' => 'taxonomy_autocomplete',
      'weight' => 6,
    ),
  );

  // Exported field_instance:
  // 'node-pece_artifact_fieldnote-field_pece_contributors'.
  $field_instances['node-pece_artifact_fieldnote-field_pece_contributors'] = array(
    'bundle' => 'pece_artifact_fieldnote',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Who is contributing this artifact to the platform?',
    'display' => array(
      'card' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'bypass_access' => FALSE,
          'link' => 1,
        ),
        'type' => 'entityreference_label',
        'weight' => 2,
      ),
      'featured' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'free_panel' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'highlighted' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'meta_content' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'mini_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'most_recent' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'nodeorder' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 6,
      ),
    ),
    'entity_type' => 'node',
    'entityconnect' => array(
      'button' => array(
        'unload_add_button' => 1,
        'unload_edit_button' => 1,
      ),
      'icon' => array(
        'show_add_icon' => 0,
        'show_edit_icon' => 0,
      ),
    ),
    'fences_wrapper' => 'div',
    'field_name' => 'field_pece_contributors',
    'label' => 'Contributors',
    'locked' => TRUE,
    'required' => 0,
    'settings' => array(
      'nodeaccess_userreference' => array(
        'all' => array(
          'view' => 'view',
        ),
        'all_published' => 0,
        'author' => array(
          'delete' => 'delete',
          'update' => 'update',
          'view' => 'view',
        ),
        'author_published' => 0,
        'create' => array(
          'biblio' => 0,
          'frontpage_image_slideshow' => 0,
          'panopoly_landing_page' => 0,
          'panopoly_page' => 0,
          'pece_about_page' => 0,
          'pece_analytic' => 0,
          'pece_annotation' => 0,
          'pece_artifact_audio' => 0,
          'pece_artifact_bundle' => 0,
          'pece_artifact_fieldnote' => 0,
          'pece_artifact_image' => 0,
          'pece_artifact_pdf' => 0,
          'pece_artifact_text' => 0,
          'pece_artifact_video' => 0,
          'pece_artifact_website' => 0,
          'pece_essay' => 0,
          'pece_fieldsite' => 0,
          'pece_group' => 0,
          'pece_memo' => 0,
          'pece_photo_essay' => 0,
          'pece_project' => 0,
          'pece_sub_logic' => 0,
          'pece_timeline_essay' => 0,
          'zotero_feed' => 0,
        ),
        'priority' => 0,
        'referenced' => array(
          'delete' => 0,
          'deny_delete' => 0,
          'deny_update' => 0,
          'deny_view' => 0,
          'update' => 'update',
          'view' => 'view',
        ),
        'referenced_published' => 0,
        'unused' => 0,
        'views' => array(
          'view' => '',
          'view_args' => '',
        ),
      ),
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
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'node-pece_artifact_fieldnote-field_pece_created'.
  $field_instances['node-pece_artifact_fieldnote-field_pece_created'] = array(
    'bundle' => 'pece_artifact_fieldnote',
    'deleted' => 0,
    'description' => 'When was this artifact created?',
    'display' => array(
      'card' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'date',
        'settings' => array(
          'format_type' => 'long',
          'fromto' => 'both',
          'multiple_from' => '',
          'multiple_number' => '',
          'multiple_to' => '',
          'show_remaining_days' => FALSE,
        ),
        'type' => 'date_default',
        'weight' => 18,
      ),
      'featured' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'free_panel' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'highlighted' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'meta_content' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'mini_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'most_recent' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'nodeorder' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'fences_wrapper' => 'div_div_div',
    'field_name' => 'field_pece_created',
    'label' => 'Created Date',
    'required' => 0,
    'settings' => array(
      'default_value' => 'blank',
      'default_value2' => 'same',
      'default_value_code' => '',
      'default_value_code2' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'date',
      'settings' => array(
        'increment' => 15,
        'input_format' => 'M j Y - g:i:sa',
        'input_format_custom' => '',
        'label_position' => 'above',
        'no_fieldset' => 0,
        'text_parts' => array(),
        'year_range' => '-3:+3',
      ),
      'type' => 'date_popup',
      'weight' => 7,
    ),
  );

  // Exported field_instance:
  // 'node-pece_artifact_fieldnote-field_pece_fieldsite'.
  $field_instances['node-pece_artifact_fieldnote-field_pece_fieldsite'] = array(
    'bundle' => 'pece_artifact_fieldnote',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'card' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'bypass_access' => FALSE,
          'link' => 1,
        ),
        'type' => 'entityreference_label',
        'weight' => 5,
      ),
      'featured' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'free_panel' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'highlighted' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'meta_content' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'mini_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'most_recent' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'nodeorder' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 7,
      ),
    ),
    'entity_type' => 'node',
    'fences_wrapper' => 'div',
    'field_name' => 'field_pece_fieldsite',
    'label' => 'Fieldsite',
    'locked' => TRUE,
    'required' => 0,
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
      'weight' => 9,
    ),
  );

  // Exported field_instance:
  // 'node-pece_artifact_fieldnote-field_pece_language'.
  $field_instances['node-pece_artifact_fieldnote-field_pece_language'] = array(
    'bundle' => 'pece_artifact_fieldnote',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'In what language is this artifact?',
    'display' => array(
      'card' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'languagefield',
        'settings' => array(
          'format' => array(
            'name' => 'name',
          ),
        ),
        'type' => 'language_default',
        'weight' => 17,
      ),
      'featured' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'free_panel' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'highlighted' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'meta_content' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'mini_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'most_recent' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'nodeorder' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'fences_wrapper' => 'div_div_div',
    'field_name' => 'field_pece_language',
    'label' => 'Language',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 8,
    ),
  );

  // Exported field_instance: 'node-pece_artifact_fieldnote-field_pece_license'.
  $field_instances['node-pece_artifact_fieldnote-field_pece_license'] = array(
    'bundle' => 'pece_artifact_fieldnote',
    'default_value' => array(
      0 => array(
        'licence' => 3,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'card' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'creative_commons',
        'settings' => array(),
        'type' => 'creative_commons_small_image',
        'weight' => 9,
      ),
      'featured' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'free_panel' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'highlighted' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'meta_content' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'mini_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'most_recent' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'nodeorder' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 5,
      ),
    ),
    'entity_type' => 'node',
    'fences_wrapper' => 'div',
    'field_name' => 'field_pece_license',
    'label' => 'License',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'creative_commons',
      'settings' => array(),
      'type' => 'select',
      'weight' => 12,
    ),
  );

  // Exported field_instance:
  // 'node-pece_artifact_fieldnote-field_pece_location'.
  $field_instances['node-pece_artifact_fieldnote-field_pece_location'] = array(
    'bundle' => 'pece_artifact_fieldnote',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'card' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'location_cck',
        'settings' => array(),
        'type' => 'location_default',
        'weight' => 13,
      ),
      'featured' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'free_panel' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'highlighted' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'meta_content' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'mini_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'most_recent' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'nodeorder' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'fences_wrapper' => 'div_div_div',
    'field_name' => 'field_pece_location',
    'label' => 'Location',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'location_cck',
      'settings' => array(),
      'type' => 'location',
      'weight' => 11,
    ),
  );

  // Exported field_instance:
  // 'node-pece_artifact_fieldnote-field_pece_project_ref'.
  $field_instances['node-pece_artifact_fieldnote-field_pece_project_ref'] = array(
    'bundle' => 'pece_artifact_fieldnote',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'card' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'bypass_access' => FALSE,
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 19,
      ),
      'featured' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'free_panel' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'highlighted' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'meta_content' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'mini_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'most_recent' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'nodeorder' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'entityconnect' => array(
      'button' => array(
        'unload_add_button' => 1,
        'unload_edit_button' => 1,
      ),
      'icon' => array(
        'show_add_icon' => 0,
        'show_edit_icon' => 0,
      ),
    ),
    'fences_wrapper' => 'div_div_div',
    'field_name' => 'field_pece_project_ref',
    'label' => 'Cite as part of...',
    'required' => 0,
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
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'node-pece_artifact_fieldnote-field_pece_source'.
  $field_instances['node-pece_artifact_fieldnote-field_pece_source'] = array(
    'bundle' => 'pece_artifact_fieldnote',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Where did you find this artifact?',
    'display' => array(
      'card' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 16,
      ),
      'featured' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'free_panel' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'highlighted' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'meta_content' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'mini_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'most_recent' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'nodeorder' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'fences_wrapper' => 'div_div_div',
    'field_name' => 'field_pece_source',
    'label' => 'Source',
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
        'rows' => 1,
      ),
      'type' => 'text_textarea',
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'node-pece_artifact_fieldnote-field_pece_tags'.
  $field_instances['node-pece_artifact_fieldnote-field_pece_tags'] = array(
    'bundle' => 'pece_artifact_fieldnote',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'card' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 8,
      ),
      'featured' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'free_panel' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'highlighted' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'meta_content' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'mini_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'most_recent' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'nodeorder' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 4,
      ),
    ),
    'entity_type' => 'node',
    'fences_wrapper' => 'div',
    'field_name' => 'field_pece_tags',
    'label' => 'Tags',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'taxonomy',
      'settings' => array(
        'autocomplete_path' => 'taxonomy/autocomplete',
        'size' => 60,
      ),
      'type' => 'taxonomy_autocomplete',
      'weight' => 15,
    ),
  );

  // Exported field_instance: 'node-pece_artifact_fieldnote-field_pece_uri'.
  $field_instances['node-pece_artifact_fieldnote-field_pece_uri'] = array(
    'bundle' => 'pece_artifact_fieldnote',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'card' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 7,
      ),
      'featured' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'free_panel' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'highlighted' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'meta_content' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'mini_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'most_recent' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'nodeorder' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'node',
    'fences_wrapper' => 'div',
    'field_name' => 'field_pece_uri',
    'label' => 'URI',
    'required' => 0,
    'settings' => array(
      'linkit' => array(
        'button_text' => 'Search',
        'enable' => 0,
        'profile' => '',
      ),
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 2,
    ),
  );

  // Exported field_instance:
  // 'node-pece_artifact_fieldnote-field_pece_use_fieldsite_local'.
  $field_instances['node-pece_artifact_fieldnote-field_pece_use_fieldsite_local'] = array(
    'bundle' => 'pece_artifact_fieldnote',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => 'Check this to copy the location from the referenced fieldsite, if any.',
    'display' => array(
      'card' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 14,
      ),
      'featured' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'free_panel' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'highlighted' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'meta_content' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'mini_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'most_recent' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'nodeorder' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'fences_wrapper' => 'div_div_div',
    'field_name' => 'field_pece_use_fieldsite_local',
    'label' => 'Use fieldsite\'s location',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 1,
      ),
      'type' => 'options_onoff',
      'weight' => 10,
    ),
  );

  // Exported field_instance: 'node-pece_artifact_fieldnote-field_permissions'.
  $field_instances['node-pece_artifact_fieldnote-field_permissions'] = array(
    'bundle' => 'pece_artifact_fieldnote',
    'default_value' => array(
      0 => array(
        'value' => 'open',
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'card' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 11,
      ),
      'featured' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'free_panel' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'highlighted' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'meta_content' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'mini_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'most_recent' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'nodeorder' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'node',
    'fences_wrapper' => 'div',
    'field_name' => 'field_permissions',
    'label' => 'Permissions',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_buttons',
      'weight' => 13,
    ),
  );

  // Exported field_instance:
  // 'node-pece_artifact_fieldnote-group_content_access'.
  $field_instances['node-pece_artifact_fieldnote-group_content_access'] = array(
    'bundle' => 'pece_artifact_fieldnote',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'card' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 15,
      ),
      'featured' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'free_panel' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'highlighted' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'meta_content' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'mini_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'most_recent' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'nodeorder' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'group_content_access',
    'label' => 'Group content visibility',
    'required' => TRUE,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'view modes' => array(
      'full' => array(
        'label' => 'above',
        'type' => 'list_default',
      ),
      'teaser' => array(
        'label' => 'above',
        'type' => 'list_default',
      ),
    ),
    'widget' => array(
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 14,
    ),
    'widget_type' => 'options_select',
  );

  // Exported field_instance: 'node-pece_artifact_fieldnote-og_group_ref'.
  $field_instances['node-pece_artifact_fieldnote-og_group_ref'] = array(
    'bundle' => 'pece_artifact_fieldnote',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'card' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'bypass_access' => FALSE,
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 12,
      ),
      'featured' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'free_panel' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'highlighted' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'meta_content' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'mini_teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'most_recent' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'nodeorder' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 3,
      ),
    ),
    'entity_type' => 'node',
    'entityconnect' => array(
      'button' => array(
        'unload_add_button' => 1,
        'unload_edit_button' => 1,
      ),
      'icon' => array(
        'show_add_icon' => 0,
        'show_edit_icon' => 0,
      ),
    ),
    'entityconnect_show_add_icon' => 0,
    'entityconnect_show_edit_icon' => 0,
    'entityconnect_unload_add' => 1,
    'entityconnect_unload_edit' => 1,
    'fences_wrapper' => 'div_div_div',
    'field_name' => 'og_group_ref',
    'label' => 'Group audience',
    'required' => 0,
    'settings' => array(
      'behaviors' => array(
        'og_widget' => array(
          'access_override' => 0,
          'admin' => array(
            'widget_type' => 'entityreference_autocomplete',
          ),
          'default' => array(
            'widget_type' => 'options_select',
          ),
          'status' => TRUE,
        ),
      ),
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'og',
      'settings' => array(),
      'type' => 'og_complex',
      'weight' => 13,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('ARK Enabled');
  t('Check this to copy the location from the referenced fieldsite, if any.');
  t('Cite as part of...');
  t('Contributors');
  t('Created Date');
  t('Creator(s)');
  t('Fieldsite');
  t('Group audience');
  t('Group content visibility');
  t('In what language is this artifact?');
  t('Language');
  t('License');
  t('Location');
  t('Permissions');
  t('Source');
  t('Tags');
  t('Text');
  t('URI');
  t('Use fieldsite\'s location');
  t('When was this artifact created?');
  t('Where did you find this artifact?');
  t('Who created this artifact?');
  t('Who is contributing this artifact to the platform?');

  return $field_instances;
}
