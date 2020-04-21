<?php

/**
 * @file
 * pece_imp_artifacts_spdsheet.feeds_tamper_default.inc
 */

/**
 * Implements hook_feeds_tamper_default().
 */
function pece_imp_artifacts_spdsheet_feeds_tamper_default() {
  $export = array();

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'pece_imp_artifacts_spdsheet-content_creators-explode';
  $feeds_tamper->importer = 'pece_imp_artifacts_spdsheet';
  $feeds_tamper->source = 'content_creators';
  $feeds_tamper->plugin_id = 'explode';
  $feeds_tamper->settings = array(
    'separator' => ';',
    'limit' => '',
    'real_separator' => ';',
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Explode on semicolon';
  $export['pece_imp_artifacts_spdsheet-content_creators-explode'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'pece_imp_artifacts_spdsheet-content_creators-trim';
  $feeds_tamper->importer = 'pece_imp_artifacts_spdsheet';
  $feeds_tamper->source = 'content_creators';
  $feeds_tamper->plugin_id = 'trim';
  $feeds_tamper->settings = array(
    'mask' => '',
    'side' => 'trim',
  );
  $feeds_tamper->weight = 1;
  $feeds_tamper->description = 'Trim - Whitespace will be removed from both sides.';
  $export['pece_imp_artifacts_spdsheet-content_creators-trim'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'pece_imp_artifacts_spdsheet-contributors-explode';
  $feeds_tamper->importer = 'pece_imp_artifacts_spdsheet';
  $feeds_tamper->source = 'contributors';
  $feeds_tamper->plugin_id = 'explode';
  $feeds_tamper->settings = array(
    'separator' => ';',
    'limit' => '',
    'real_separator' => ';',
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Explode on semicolon';
  $export['pece_imp_artifacts_spdsheet-contributors-explode'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'pece_imp_artifacts_spdsheet-contributors-trim';
  $feeds_tamper->importer = 'pece_imp_artifacts_spdsheet';
  $feeds_tamper->source = 'contributors';
  $feeds_tamper->plugin_id = 'trim';
  $feeds_tamper->settings = array(
    'mask' => '',
    'side' => 'trim',
  );
  $feeds_tamper->weight = 1;
  $feeds_tamper->description = 'Trim - Whitespace will be removed from both sides.';
  $export['pece_imp_artifacts_spdsheet-contributors-trim'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'pece_imp_artifacts_spdsheet-tags-explode';
  $feeds_tamper->importer = 'pece_imp_artifacts_spdsheet';
  $feeds_tamper->source = 'tags';
  $feeds_tamper->plugin_id = 'explode';
  $feeds_tamper->settings = array(
    'separator' => ';',
    'limit' => '',
    'real_separator' => ';',
  );
  $feeds_tamper->weight = 0;
  $feeds_tamper->description = 'Explode on semicolon';
  $export['pece_imp_artifacts_spdsheet-tags-explode'] = $feeds_tamper;

  $feeds_tamper = new stdClass();
  $feeds_tamper->disabled = FALSE; /* Edit this to true to make a default feeds_tamper disabled initially */
  $feeds_tamper->api_version = 2;
  $feeds_tamper->id = 'pece_imp_artifacts_spdsheet-tags-trim';
  $feeds_tamper->importer = 'pece_imp_artifacts_spdsheet';
  $feeds_tamper->source = 'tags';
  $feeds_tamper->plugin_id = 'trim';
  $feeds_tamper->settings = array(
    'mask' => '',
    'side' => 'trim',
  );
  $feeds_tamper->weight = 1;
  $feeds_tamper->description = 'Trim - Whitespace will be removed from both sides.';
  $export['pece_imp_artifacts_spdsheet-tags-trim'] = $feeds_tamper;

  return $export;
}
