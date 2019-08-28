<?php

/**
 * @file
 * pece_imp_artifacts_image.feeds_importer_default.inc
 */

/**
 * Implements hook_feeds_importer_default().
 */
function pece_imp_artifacts_image_feeds_importer_default() {
  $export = array();

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'pece_imp_artifacts_image';
  $feeds_importer->config = array(
    'name' => 'PECE - Image Artifacts Importer',
    'description' => 'Batch import Image Artifacts',
    'fetcher' => array(
      'plugin_key' => 'FeedsFileFetcher',
      'config' => array(
        'allowed_extensions' => 'txt csv tsv xml opml',
        'delete_uploaded_file' => 1,
        'direct' => 0,
        'directory' => 'private://content-import',
        'allowed_schemes' => array(
          'public' => 'public',
          'private' => 'private',
        ),
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsCSVParser',
      'config' => array(
        'delimiter' => ',',
        'encoding' => 'UTF-8',
        'no_headers' => 0,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'expire' => '-1',
        'author' => '0',
        'authorize' => 1,
        'mappings' => array(
          0 => array(
            'source' => 'title',
            'target' => 'title',
            'unique' => 0,
            'language' => 'und',
          ),
          1 => array(
            'source' => 'content_permission',
            'target' => 'field_permissions',
            'unique' => FALSE,
            'language' => 'und',
          ),
          2 => array(
            'source' => 'license',
            'target' => 'field_pece_license',
            'unique' => FALSE,
            'language' => 'und',
          ),
          3 => array(
            'source' => 'language',
            'target' => 'field_pece_language',
            'unique' => FALSE,
            'language' => 'und',
          ),
          4 => array(
            'source' => 'source',
            'target' => 'field_pece_source',
            'format' => 'plain_text',
            'language' => 'und',
          ),
          5 => array(
            'source' => 'file',
            'target' => 'field_pece_media_image:uri',
            'file_exists' => '3',
            'language' => 'und',
          ),
          6 => array(
            'source' => 'tags',
            'target' => 'field_pece_tags',
            'term_search' => '0',
            'autocreate' => 1,
            'language' => 'und',
          ),
          7 => array(
            'source' => 'group_content_access',
            'target' => 'group_content_access',
            'unique' => FALSE,
            'language' => 'und',
          ),
          8 => array(
            'source' => 'content_creators',
            'target' => 'field_pece_authors',
            'term_search' => '0',
            'autocreate' => 1,
            'language' => 'und',
          ),
          9 => array(
            'source' => 'critical_commentary',
            'target' => 'field_pece_crit_commentary',
            'unique' => FALSE,
            'language' => 'und',
          ),
          10 => array(
            'source' => 'contributors',
            'target' => 'field_pece_contributors:etid',
            'unique' => FALSE,
            'language' => 'und',
          ),
          11 => array(
            'source' => 'author',
            'target' => 'uid',
            'unique' => FALSE,
          ),
        ),
        'insert_new' => '1',
        'update_existing' => '2',
        'update_non_existent' => 'skip',
        'input_format' => 'plain_text',
        'skip_hash_check' => 0,
        'bundle' => 'pece_artifact_image',
        'language' => 'und',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['pece_imp_artifacts_image'] = $feeds_importer;

  return $export;
}
