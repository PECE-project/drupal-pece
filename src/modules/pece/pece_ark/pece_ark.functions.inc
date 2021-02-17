<?php

/**
 * Set default values for PECE.
 */
function pece_ark_set_default_vars() {
//  variable_set('ark_naan'                                 , '99999');
//  variable_set('ark_ezid_user'                            , getenv('ARK_USER'));
//  variable_set('ark_ezid_password'                        , getenv('ARK_PASS'));
//  variable_set('ark_ezid_remote_export'                   , ARK_DEFAULT_REMOTE_EXPORT_ENTRY_VALUE );
//  variable_set('ark_ezid_remote_status'                   , ARK_DEFAULT_REMOTE_STATUS_ENTRY_VALUE);
//  variable_set('ark_ezid_update_if_exists'                , ARK_DEFAULT_REMOTE_UPDATE_IF_EXISTS);
//  variable_set('ark_composite_who_field'                  , implode(',', ARK_COMPOSITE_WHO_FIELD));
//  variable_set('ark_indexing_limit'                       , ARK_INDEXING_LIMIT);
//  variable_set('ark_authors_name_separator'               , ARK_DEFAULT_AUTHORS_NAME_SEPARATOR);
//  variable_set('ark_remote_server_address'                , ARK_DEFAULT_REMOTE_SERVER_ADDRESS);
//  variable_set('ark_remote_identifier_site_address'       , ARK_DEFAULT_REMOTE_IDENTIFIER_SITE_ADDRESS);
//  variable_set('ark_name_prefix'                          , ARK_DEFAULT_PRE_PREFIX . substr(str_shuffle('bcdfghjklmnpqrstvwxyz123456789'), 0, 4));
  $def_vars = array(
    'ark_naan' => '99999',
    'ark_ezid_user' => getenv('ARK_USER'),
    'ark_ezid_password' => getenv('ARK_PASS'),
    'ark_ezid_remote_export' => ARK_DEFAULT_REMOTE_EXPORT_ENTRY_VALUE,
    'ark_ezid_remote_status' => ARK_DEFAULT_REMOTE_STATUS_ENTRY_VALUE,
    'ark_ezid_update_if_exists' => ARK_DEFAULT_REMOTE_UPDATE_IF_EXISTS,
    'ark_composite_who_field' => implode(',', ARK_COMPOSITE_WHO_FIELD),
    'ark_indexing_limit' => ARK_INDEXING_LIMIT,
    'ark_authors_name_separator' => ARK_DEFAULT_AUTHORS_NAME_SEPARATOR,
    'ark_remote_server_address' => ARK_DEFAULT_REMOTE_SERVER_ADDRESS,
    'ark_remote_identifier_site_address' => ARK_DEFAULT_REMOTE_IDENTIFIER_SITE_ADDRESS,
    'ark_name_prefix' => ARK_DEFAULT_PRE_PREFIX . substr(str_shuffle('bcdfghjklmnpqrstvwxyz123456789'), 0, 4),
  );
  foreach ($def_vars as $var_name => $value) {
    variable_set($var_name, $value);
  }
}

/**
 * Set default content to use ARK.
 */
function pece_ark_set_default_content() {
  $def_vars = array(
    'ark_node_types' => array(
      'pece_annotation' => 'pece_annotation',
      'pece_artifact_audio' => 'pece_artifact_audio',
      'pece_artifact_bundle' => 'pece_artifact_bundle',
      'pece_artifact_fieldnote' => 'pece_artifact_fieldnote',
      'pece_artifact_image' => 'pece_artifact_image',
      'pece_artifact_pdf' => 'pece_artifact_pdf',
      'pece_artifact_tabular' => 'pece_artifact_tabular',
      'pece_artifact_text' => 'pece_artifact_text',
      'pece_artifact_video' => 'pece_artifact_video',
      'pece_artifact_website' => 'pece_artifact_website',
      'pece_essay' => 'pece_essay',
      'pece_photo_essay' => 'pece_photo_essay',
      'pece_sub_logic' => 'pece_sub_logic',
      'pece_timeline_essay' => 'pece_timeline_essay',
      'pece_about_page' => 0,
      'pece_analytic' => 0,
      'biblio' => 0,
      'panopoly_page' => 0,
      'pece_fieldsite' => 0,
      'pece_group' => 0,
      'panopoly_landing_page' => 0,
      'pece_memo' => 0,
      'pece_project' => 0,
      'frontpage_image_slideshow' => 0,
      'zotero_feed' => 0,
    ),
    'ark_pece_timeline_essay_composite_who' => array(
      'ield_pece_contributors' => 'field_pece_contributors',
    ),
    'ark_pece_timeline_essay_when' => 'use_default_when',
    'ark_pece_timeline_essay_who' => 'use_composite_who',
    'ark_pece_sub_logic_composite_who' => array(
      'field_pece_contributors' => 'field_pece_contributors',
    ),
    'ark_pece_sub_logic_when' => 'use_default_when',
    'ark_pece_sub_logic_who' => 'use_composite_who',
    'ark_pece_project_composite_who' => array(
      'field_pece_contributors' => 'field_pece_contributors',
    ),
    'ark_pece_project_when' => 'use_default_when',
    'ark_pece_project_who' => 'use_composite_who',
    'ark_pece_photo_essay_composite_who' => array(
      'field_pece_contributors' => 'field_pece_contributors',
    ),
    'ark_pece_photo_essay_when' => 'use_default_when',
    'ark_pece_photo_essay_who' => 'use_composite_who',
    'ark_pece_memo_composite_who' => array(
      'field_pece_contributors' => 'field_pece_contributors',
    ),
    'ark_pece_memo_when' => 'use_default_when',
    'ark_pece_memo_who' => 'use_composite_who',

    'ark_pece_essay_composite_who' => array(
      'field_pece_contributors' => 'field_pece_contributors',
    ),
    'ark_pece_essay_when' => 'use_default_when',
    'ark_pece_essay_who' => 'use_composite_who',
    'ark_pece_artifact_website_composite_who' => array(
      'field_pece_authors' => 'field_pece_authors',
      'field_pece_contributors' => 'field_pece_contributors',
    ),
    'ark_pece_artifact_website_when' => 'field_pece_created',
    'ark_pece_artifact_website_who' => 'use_composite_who',
    'ark_pece_artifact_video_composite_who' => array(
      'field_pece_authors' => 'field_pece_authors',
      'field_pece_contributors' => 'field_pece_contributors',
    ),
    'ark_pece_artifact_video_when' => 'field_pece_created',
    'ark_pece_artifact_video_who' => 'use_composite_who',
    'ark_pece_artifact_text_composite_who' => array(
      'field_pece_authors' => 'field_pece_authors',
      'field_pece_contributors' => 'field_pece_contributors',
    ),
    'ark_pece_artifact_text_when' => 'field_pece_created',
    'ark_pece_artifact_text_who' => 'use_composite_who',
    'ark_pece_artifact_tabular_composite_who' => array(
      'field_pece_authors' => 'field_pece_authors',
      'field_pece_contributors' => 'field_pece_contributors',
    ),
    'ark_pece_artifact_tabular_when' => 'field_pece_created',
    'ark_pece_artifact_tabular_who' => 'use_composite_who',
    'ark_pece_artifact_pdf_composite_who' => array(
      'field_pece_authors' => 'field_pece_authors',
      'ield_pece_contributors' => 'field_pece_contributors',
    ),
    'ark_pece_artifact_pdf_when' => 'field_pece_created',
    'ark_pece_artifact_pdf_who' => 'use_composite_who',
    'ark_pece_artifact_image_composite_who' => array(
      'field_pece_authors' => 'field_pece_authors',
      'field_pece_contributors' => 'field_pece_contributors',
    ),
    'ark_pece_artifact_image_when' => 'field_pece_created',
    'ark_pece_artifact_image_who' => 'use_composite_who',
    'ark_pece_artifact_fieldnote_composite_who' => array(
      'field_pece_authors' => 'field_pece_authors',
      'field_pece_contributors' => 'field_pece_contributors',
    ),
    'ark_pece_artifact_fieldnote_when' => 'field_pece_created',
    'ark_pece_artifact_fieldnote_who' => 'use_composite_who',
    'ark_pece_artifact_bundle_composite_who' => array(
      'field_pece_authors' => 'field_pece_authors',
      'field_pece_contributors' => 'field_pece_contributors',
    ),
    'ark_pece_artifact_bundle_when' => 'field_pece_created',
    'ark_pece_artifact_bundle_who' => 'use_composite_who',
    'ark_pece_artifact_audio_composite_who' => array(
      'field_pece_authors' => 'field_pece_authors',
      'field_pece_contributors' => 'field_pece_contributors',
    ),
    'ark_pece_artifact_audio_when' => 'field_pece_created',
    'ark_pece_artifact_audio_who' => 'use_composite_who',
    'ark_pece_annotation_when' => 'use_default_when',
    'ark_pece_annotation_who' => 'use_default_who',
  );

  foreach ($def_vars as $var_name => $value) {
    variable_set($var_name, $value);
  }
}

/**
 * Rise a warning message when the user hasn't full name.
 * @param string $name
 * @param Object $user
 */
function _pece_ark_missing_fullname_warning_msg($name, $user) {
  if (isset($user->tid)) {
    return;
  }
  if (isset($user->uid) && _user_has_fullname($user)) {
    return;
  }
  drupal_set_message(
    t("User @username hasn't full name. Please contact @username to insert valid full name.", ['@username' => $user->name]),
    'warning'
  );
}
