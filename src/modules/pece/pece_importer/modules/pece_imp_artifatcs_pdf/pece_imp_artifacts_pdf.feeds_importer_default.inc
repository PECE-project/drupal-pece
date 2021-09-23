<?php

/**
 * @file
 * pece_imp_artifacts_pdf.feeds_importer_default.inc
 */

/**
 * Implements hook_feeds_importer_default().
 */
function pece_imp_artifacts_pdf_feeds_importer_default() {
  $export = array();

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'pece_imp_artifacts_pdf';
  $feeds_importer->config = array(
    'content_type' => '',
    'description' => 'Batch import PDF Artifacts',
    'expire_period' => 3600,
    'fetcher' => array(
      'config' => array(
        'allowed_extensions' => 'txt csv tsv xml opml',
        'allowed_schemes' => array(
          'private' => 'private',
          'public' => 'public',
        ),
        'delete_uploaded_file' => 1,
        'direct' => 0,
        'directory' => 'private://content-import',
      ),
      'plugin_key' => 'FeedsFileFetcher',
    ),
    'import_on_create' => 1,
    'import_period' => '-1',
    'name' => 'PECE - PDF Artifacts Importer',
    'parser' => array(
      'config' => array(
        'delimiter' => ',',
        'encoding' => 'UTF-8',
        'no_headers' => 0,
      ),
      'plugin_key' => 'FeedsCSVParser',
    ),
    'process_in_background' => 0,
    'processor' => array(
      'config' => array(
        'author' => '0',
        'authorize' => 1,
        'bundle' => 'pece_artifact_pdf',
        'expire' => '-1',
        'input_format' => 'plain_text',
        'insert_new' => '1',
        'language' => 'und',
        'mappings' => array(
          0 => array(
            'language' => 'und',
            'source' => 'title',
            'target' => 'title',
            'unique' => 0,
          ),
          1 => array(
            'language' => 'und',
            'source' => 'content_permission',
            'target' => 'field_permissions',
            'unique' => FALSE,
          ),
          2 => array(
            'language' => 'und',
            'source' => 'license',
            'target' => 'field_pece_license',
            'unique' => FALSE,
          ),
          3 => array(
            'language' => 'und',
            'source' => 'language',
            'target' => 'field_pece_language',
            'unique' => FALSE,
          ),
          4 => array(
            'format' => 'plain_text',
            'language' => 'und',
            'source' => 'source',
            'target' => 'field_pece_source',
          ),
          5 => array(
            'file_exists' => '3',
            'language' => 'und',
            'source' => 'file',
            'target' => 'field_pece_media_pdf:uri',
          ),
          6 => array(
            'autocreate' => 1,
            'source' => 'tags',
            'target' => 'field_pece_tags',
            'term_search' => '0',
          ),
          7 => array(
            'language' => 'und',
            'source' => 'group_content_access',
            'target' => 'group_content_access',
            'unique' => FALSE,
          ),
          8 => array(
            'autocreate' => 1,
            'language' => 'und',
            'source' => 'content_creators',
            'target' => 'field_pece_authors',
            'term_search' => '0',
          ),
          9 => array(
            'language' => 'und',
            'source' => 'critical_commentary',
            'target' => 'field_pece_crit_commentary',
            'unique' => FALSE,
          ),
          10 => array(
            'language' => 'und',
            'source' => 'contributors',
            'target' => 'field_pece_contributors:etid',
            'unique' => FALSE,
          ),
          11 => array(
            'language' => 'und',
            'source' => 'author',
            'target' => 'uid',
            'unique' => FALSE,
          ),
        ),
        'skip_hash_check' => 0,
        'update_existing' => '2',
        'update_non_existent' => 'skip',
      ),
      'plugin_key' => 'FeedsNodeProcessor',
    ),
    'update' => 0,
  );
  $export['pece_imp_artifacts_pdf'] = $feeds_importer;

  return $export;
}
