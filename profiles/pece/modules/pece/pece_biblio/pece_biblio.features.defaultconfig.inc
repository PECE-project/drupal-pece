<?php
/**
 * @file
 * pece_biblio.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function pece_biblio_defaultconfig_features() {
  return array(
    'pece_biblio' => array(
      'feeds_importer_default' => 'feeds_importer_default',
      'strongarm' => 'strongarm',
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_feeds_importer_default().
 */
function pece_biblio_defaultconfig_feeds_importer_default() {
  $export = array();

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'zotero_feed';
  $feeds_importer->config = array(
    'name' => 'Zotero Feed',
    'description' => 'Import Zotero items.',
    'fetcher' => array(
      'plugin_key' => 'FeedsZoteroFetcher',
      'config' => array(
        'auto_detect_feeds' => FALSE,
        'use_pubsubhubbub' => FALSE,
        'designated_hub' => '',
        'request_timeout' => NULL,
        'auto_scheme' => 'http',
        'accept_invalid_cert' => FALSE,
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsZoteroParser',
      'config' => array(
        'refresh_zotero_item_type_fields' => FALSE,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsZoteroProcessor',
      'config' => array(
        'bundle' => 'biblio',
        'update_existing' => '0',
        'expire' => '-1',
        'mappings' => array(
          0 => array(
            'source' => 'guid',
            'target' => 'guid',
            'unique' => TRUE,
          ),
          1 => array(
            'source' => 'url',
            'target' => 'url',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'timestamp',
            'target' => 'created',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'note',
            'target' => 'biblio_notes',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'creators',
            'target' => 'biblio_contributors',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'links',
            'target' => 'field_zotero_attachment_links',
            'unique' => FALSE,
          ),
          7 => array(
            'source' => 'files',
            'target' => 'field_zotero_attachment_links',
            'unique' => FALSE,
          ),
          8 => array(
            'source' => 'url',
            'target' => 'field_zotero_canonical_url',
            'unique' => TRUE,
          ),
          9 => array(
            'source' => 'zotero_fetch_url',
            'target' => 'field_zotero_fetch_url',
            'unique' => TRUE,
          ),
          10 => array(
            'source' => 'artwork:abstractNote',
            'target' => 'biblio_abst_e',
            'unique' => FALSE,
          ),
          11 => array(
            'source' => 'artwork:accessDate',
            'target' => 'biblio_access_date',
            'unique' => FALSE,
          ),
          12 => array(
            'source' => 'artwork:archive',
            'target' => 'biblio_publisher',
            'unique' => FALSE,
          ),
          13 => array(
            'source' => 'artwork:archiveLocation',
            'target' => 'biblio_place_published',
            'unique' => FALSE,
          ),
          14 => array(
            'source' => 'artwork:callNumber',
            'target' => 'biblio_call_number',
            'unique' => FALSE,
          ),
          15 => array(
            'source' => 'artwork:date',
            'target' => 'biblio_year',
            'unique' => FALSE,
          ),
          16 => array(
            'source' => 'artwork:language',
            'target' => 'biblio_lang',
            'unique' => FALSE,
          ),
          17 => array(
            'source' => 'artwork:rights',
            'target' => 'biblio_custom7',
            'unique' => FALSE,
          ),
          18 => array(
            'source' => 'artwork:shortTitle',
            'target' => 'biblio_short_title',
            'unique' => FALSE,
          ),
          19 => array(
            'source' => 'artwork:title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          20 => array(
            'source' => 'artwork:url',
            'target' => 'biblio_url',
            'unique' => FALSE,
          ),
          21 => array(
            'source' => 'audioRecording:abstractNote',
            'target' => 'biblio_abst_e',
            'unique' => FALSE,
          ),
          22 => array(
            'source' => 'audioRecording:accessDate',
            'target' => 'biblio_access_date',
            'unique' => FALSE,
          ),
          23 => array(
            'source' => 'audioRecording:archive',
            'target' => 'biblio_publisher',
            'unique' => FALSE,
          ),
          24 => array(
            'source' => 'audioRecording:archiveLocation',
            'target' => 'biblio_place_published',
            'unique' => FALSE,
          ),
          25 => array(
            'source' => 'audioRecording:callNumber',
            'target' => 'biblio_call_number',
            'unique' => FALSE,
          ),
          26 => array(
            'source' => 'audioRecording:date',
            'target' => 'biblio_year',
            'unique' => FALSE,
          ),
          27 => array(
            'source' => 'audioRecording:ISBN',
            'target' => 'biblio_isbn',
            'unique' => FALSE,
          ),
          28 => array(
            'source' => 'audioRecording:label',
            'target' => 'biblio_label',
            'unique' => FALSE,
          ),
          29 => array(
            'source' => 'audioRecording:language',
            'target' => 'biblio_lang',
            'unique' => FALSE,
          ),
          30 => array(
            'source' => 'audioRecording:numberOfVolumes',
            'target' => 'biblio_number_of_volumes',
            'unique' => FALSE,
          ),
          31 => array(
            'source' => 'audioRecording:place',
            'target' => 'biblio_place_published',
            'unique' => FALSE,
          ),
          32 => array(
            'source' => 'audioRecording:rights',
            'target' => 'biblio_custom7',
            'unique' => FALSE,
          ),
          33 => array(
            'source' => 'audioRecording:series',
            'target' => 'biblio_secondary_title',
            'unique' => FALSE,
          ),
          34 => array(
            'source' => 'audioRecording:shortTitle',
            'target' => 'biblio_short_title',
            'unique' => FALSE,
          ),
          35 => array(
            'source' => 'audioRecording:title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          36 => array(
            'source' => 'audioRecording:url',
            'target' => 'biblio_url',
            'unique' => FALSE,
          ),
          37 => array(
            'source' => 'audioRecording:volume',
            'target' => 'biblio_volume',
            'unique' => FALSE,
          ),
          38 => array(
            'source' => 'bill:abstractNote',
            'target' => 'biblio_abst_e',
            'unique' => FALSE,
          ),
          39 => array(
            'source' => 'bill:accessDate',
            'target' => 'biblio_access_date',
            'unique' => FALSE,
          ),
          40 => array(
            'source' => 'bill:billNumber',
            'target' => 'biblio_number',
            'unique' => FALSE,
          ),
          41 => array(
            'source' => 'bill:date',
            'target' => 'biblio_year',
            'unique' => FALSE,
          ),
          42 => array(
            'source' => 'bill:language',
            'target' => 'biblio_lang',
            'unique' => FALSE,
          ),
          43 => array(
            'source' => 'bill:rights',
            'target' => 'biblio_custom7',
            'unique' => FALSE,
          ),
          44 => array(
            'source' => 'bill:shortTitle',
            'target' => 'biblio_short_title',
            'unique' => FALSE,
          ),
          45 => array(
            'source' => 'bill:title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          46 => array(
            'source' => 'bill:url',
            'target' => 'biblio_url',
            'unique' => FALSE,
          ),
          47 => array(
            'source' => 'blogPost:abstractNote',
            'target' => 'biblio_abst_e',
            'unique' => FALSE,
          ),
          48 => array(
            'source' => 'blogPost:accessDate',
            'target' => 'biblio_access_date',
            'unique' => FALSE,
          ),
          49 => array(
            'source' => 'blogPost:date',
            'target' => 'biblio_year',
            'unique' => FALSE,
          ),
          50 => array(
            'source' => 'blogPost:language',
            'target' => 'biblio_lang',
            'unique' => FALSE,
          ),
          51 => array(
            'source' => 'blogPost:rights',
            'target' => 'biblio_custom7',
            'unique' => FALSE,
          ),
          52 => array(
            'source' => 'blogPost:shortTitle',
            'target' => 'biblio_short_title',
            'unique' => FALSE,
          ),
          53 => array(
            'source' => 'blogPost:title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          54 => array(
            'source' => 'blogPost:url',
            'target' => 'biblio_url',
            'unique' => FALSE,
          ),
          55 => array(
            'source' => 'book:abstractNote',
            'target' => 'biblio_abst_e',
            'unique' => FALSE,
          ),
          56 => array(
            'source' => 'book:accessDate',
            'target' => 'biblio_access_date',
            'unique' => FALSE,
          ),
          57 => array(
            'source' => 'book:archive',
            'target' => 'biblio_publisher',
            'unique' => FALSE,
          ),
          58 => array(
            'source' => 'book:archiveLocation',
            'target' => 'biblio_place_published',
            'unique' => FALSE,
          ),
          59 => array(
            'source' => 'book:callNumber',
            'target' => 'biblio_call_number',
            'unique' => FALSE,
          ),
          60 => array(
            'source' => 'book:date',
            'target' => 'biblio_year',
            'unique' => FALSE,
          ),
          61 => array(
            'source' => 'book:edition',
            'target' => 'biblio_edition',
            'unique' => FALSE,
          ),
          62 => array(
            'source' => 'book:ISBN',
            'target' => 'biblio_isbn',
            'unique' => FALSE,
          ),
          63 => array(
            'source' => 'book:language',
            'target' => 'biblio_lang',
            'unique' => FALSE,
          ),
          64 => array(
            'source' => 'book:numberOfVolumes',
            'target' => 'biblio_number_of_volumes',
            'unique' => FALSE,
          ),
          65 => array(
            'source' => 'book:numPages',
            'target' => 'biblio_pages',
            'unique' => FALSE,
          ),
          66 => array(
            'source' => 'book:place',
            'target' => 'biblio_place_published',
            'unique' => FALSE,
          ),
          67 => array(
            'source' => 'book:publisher',
            'target' => 'biblio_publisher',
            'unique' => FALSE,
          ),
          68 => array(
            'source' => 'book:rights',
            'target' => 'biblio_custom7',
            'unique' => FALSE,
          ),
          69 => array(
            'source' => 'book:series',
            'target' => 'biblio_secondary_title',
            'unique' => FALSE,
          ),
          70 => array(
            'source' => 'book:seriesNumber',
            'target' => 'biblio_number',
            'unique' => FALSE,
          ),
          71 => array(
            'source' => 'book:shortTitle',
            'target' => 'biblio_short_title',
            'unique' => FALSE,
          ),
          72 => array(
            'source' => 'book:title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          73 => array(
            'source' => 'book:url',
            'target' => 'biblio_url',
            'unique' => FALSE,
          ),
          74 => array(
            'source' => 'book:volume',
            'target' => 'biblio_volume',
            'unique' => FALSE,
          ),
          75 => array(
            'source' => 'bookSection:abstractNote',
            'target' => 'biblio_abst_e',
            'unique' => FALSE,
          ),
          76 => array(
            'source' => 'bookSection:accessDate',
            'target' => 'biblio_access_date',
            'unique' => FALSE,
          ),
          77 => array(
            'source' => 'bookSection:archive',
            'target' => 'biblio_publisher',
            'unique' => FALSE,
          ),
          78 => array(
            'source' => 'bookSection:archiveLocation',
            'target' => 'biblio_place_published',
            'unique' => FALSE,
          ),
          79 => array(
            'source' => 'bookSection:callNumber',
            'target' => 'biblio_call_number',
            'unique' => FALSE,
          ),
          80 => array(
            'source' => 'bookSection:date',
            'target' => 'biblio_year',
            'unique' => FALSE,
          ),
          81 => array(
            'source' => 'bookSection:edition',
            'target' => 'biblio_edition',
            'unique' => FALSE,
          ),
          82 => array(
            'source' => 'bookSection:ISBN',
            'target' => 'biblio_isbn',
            'unique' => FALSE,
          ),
          83 => array(
            'source' => 'bookSection:language',
            'target' => 'biblio_lang',
            'unique' => FALSE,
          ),
          84 => array(
            'source' => 'bookSection:numberOfVolumes',
            'target' => 'biblio_number_of_volumes',
            'unique' => FALSE,
          ),
          85 => array(
            'source' => 'bookSection:pages',
            'target' => 'biblio_pages',
            'unique' => FALSE,
          ),
          86 => array(
            'source' => 'bookSection:place',
            'target' => 'biblio_place_published',
            'unique' => FALSE,
          ),
          87 => array(
            'source' => 'bookSection:publisher',
            'target' => 'biblio_publisher',
            'unique' => FALSE,
          ),
          88 => array(
            'source' => 'bookSection:rights',
            'target' => 'biblio_custom7',
            'unique' => FALSE,
          ),
          89 => array(
            'source' => 'bookSection:series',
            'target' => 'biblio_secondary_title',
            'unique' => FALSE,
          ),
          90 => array(
            'source' => 'bookSection:seriesNumber',
            'target' => 'biblio_number',
            'unique' => FALSE,
          ),
          91 => array(
            'source' => 'bookSection:shortTitle',
            'target' => 'biblio_short_title',
            'unique' => FALSE,
          ),
          92 => array(
            'source' => 'bookSection:title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          93 => array(
            'source' => 'bookSection:url',
            'target' => 'biblio_url',
            'unique' => FALSE,
          ),
          94 => array(
            'source' => 'bookSection:volume',
            'target' => 'biblio_volume',
            'unique' => FALSE,
          ),
          95 => array(
            'source' => 'case:abstractNote',
            'target' => 'biblio_abst_e',
            'unique' => FALSE,
          ),
          96 => array(
            'source' => 'case:accessDate',
            'target' => 'biblio_access_date',
            'unique' => FALSE,
          ),
          97 => array(
            'source' => 'case:caseName',
            'target' => 'title',
            'unique' => FALSE,
          ),
          98 => array(
            'source' => 'case:docketNumber',
            'target' => 'biblio_number',
            'unique' => FALSE,
          ),
          99 => array(
            'source' => 'case:language',
            'target' => 'biblio_lang',
            'unique' => FALSE,
          ),
          100 => array(
            'source' => 'case:rights',
            'target' => 'biblio_custom7',
            'unique' => FALSE,
          ),
          101 => array(
            'source' => 'case:shortTitle',
            'target' => 'biblio_short_title',
            'unique' => FALSE,
          ),
          102 => array(
            'source' => 'case:url',
            'target' => 'biblio_url',
            'unique' => FALSE,
          ),
          103 => array(
            'source' => 'computerProgram:abstractNote',
            'target' => 'biblio_abst_e',
            'unique' => FALSE,
          ),
          104 => array(
            'source' => 'computerProgram:accessDate',
            'target' => 'biblio_access_date',
            'unique' => FALSE,
          ),
          105 => array(
            'source' => 'computerProgram:archive',
            'target' => 'biblio_publisher',
            'unique' => FALSE,
          ),
          106 => array(
            'source' => 'computerProgram:archiveLocation',
            'target' => 'biblio_place_published',
            'unique' => FALSE,
          ),
          107 => array(
            'source' => 'computerProgram:callNumber',
            'target' => 'biblio_call_number',
            'unique' => FALSE,
          ),
          108 => array(
            'source' => 'computerProgram:date',
            'target' => 'biblio_year',
            'unique' => FALSE,
          ),
          109 => array(
            'source' => 'computerProgram:ISBN',
            'target' => 'biblio_isbn',
            'unique' => FALSE,
          ),
          110 => array(
            'source' => 'computerProgram:place',
            'target' => 'biblio_place_published',
            'unique' => FALSE,
          ),
          111 => array(
            'source' => 'computerProgram:rights',
            'target' => 'biblio_custom7',
            'unique' => FALSE,
          ),
          112 => array(
            'source' => 'computerProgram:series',
            'target' => 'biblio_secondary_title',
            'unique' => FALSE,
          ),
          113 => array(
            'source' => 'computerProgram:shortTitle',
            'target' => 'biblio_short_title',
            'unique' => FALSE,
          ),
          114 => array(
            'source' => 'computerProgram:title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          115 => array(
            'source' => 'computerProgram:url',
            'target' => 'biblio_url',
            'unique' => FALSE,
          ),
          116 => array(
            'source' => 'conferencePaper:abstractNote',
            'target' => 'biblio_abst_e',
            'unique' => FALSE,
          ),
          117 => array(
            'source' => 'conferencePaper:accessDate',
            'target' => 'biblio_access_date',
            'unique' => FALSE,
          ),
          118 => array(
            'source' => 'conferencePaper:archive',
            'target' => 'biblio_publisher',
            'unique' => FALSE,
          ),
          119 => array(
            'source' => 'conferencePaper:archiveLocation',
            'target' => 'biblio_place_published',
            'unique' => FALSE,
          ),
          120 => array(
            'source' => 'conferencePaper:callNumber',
            'target' => 'biblio_call_number',
            'unique' => FALSE,
          ),
          121 => array(
            'source' => 'conferencePaper:date',
            'target' => 'biblio_year',
            'unique' => FALSE,
          ),
          122 => array(
            'source' => 'conferencePaper:DOI',
            'target' => 'biblio_doi',
            'unique' => FALSE,
          ),
          123 => array(
            'source' => 'conferencePaper:ISBN',
            'target' => 'biblio_isbn',
            'unique' => FALSE,
          ),
          124 => array(
            'source' => 'conferencePaper:language',
            'target' => 'biblio_lang',
            'unique' => FALSE,
          ),
          125 => array(
            'source' => 'conferencePaper:pages',
            'target' => 'biblio_pages',
            'unique' => FALSE,
          ),
          126 => array(
            'source' => 'conferencePaper:place',
            'target' => 'biblio_place_published',
            'unique' => FALSE,
          ),
          127 => array(
            'source' => 'conferencePaper:publisher',
            'target' => 'biblio_publisher',
            'unique' => FALSE,
          ),
          128 => array(
            'source' => 'conferencePaper:rights',
            'target' => 'biblio_custom7',
            'unique' => FALSE,
          ),
          129 => array(
            'source' => 'conferencePaper:series',
            'target' => 'biblio_secondary_title',
            'unique' => FALSE,
          ),
          130 => array(
            'source' => 'conferencePaper:shortTitle',
            'target' => 'biblio_short_title',
            'unique' => FALSE,
          ),
          131 => array(
            'source' => 'conferencePaper:title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          132 => array(
            'source' => 'conferencePaper:url',
            'target' => 'biblio_url',
            'unique' => FALSE,
          ),
          133 => array(
            'source' => 'conferencePaper:volume',
            'target' => 'biblio_volume',
            'unique' => FALSE,
          ),
          134 => array(
            'source' => 'dictionaryEntry:abstractNote',
            'target' => 'biblio_abst_e',
            'unique' => FALSE,
          ),
          135 => array(
            'source' => 'dictionaryEntry:accessDate',
            'target' => 'biblio_access_date',
            'unique' => FALSE,
          ),
          136 => array(
            'source' => 'dictionaryEntry:archive',
            'target' => 'biblio_publisher',
            'unique' => FALSE,
          ),
          137 => array(
            'source' => 'dictionaryEntry:archiveLocation',
            'target' => 'biblio_place_published',
            'unique' => FALSE,
          ),
          138 => array(
            'source' => 'dictionaryEntry:callNumber',
            'target' => 'biblio_call_number',
            'unique' => FALSE,
          ),
          139 => array(
            'source' => 'dictionaryEntry:date',
            'target' => 'biblio_year',
            'unique' => FALSE,
          ),
          140 => array(
            'source' => 'dictionaryEntry:edition',
            'target' => 'biblio_edition',
            'unique' => FALSE,
          ),
          141 => array(
            'source' => 'dictionaryEntry:ISBN',
            'target' => 'biblio_isbn',
            'unique' => FALSE,
          ),
          142 => array(
            'source' => 'dictionaryEntry:language',
            'target' => 'biblio_lang',
            'unique' => FALSE,
          ),
          143 => array(
            'source' => 'dictionaryEntry:numberOfVolumes',
            'target' => 'biblio_number_of_volumes',
            'unique' => FALSE,
          ),
          144 => array(
            'source' => 'dictionaryEntry:pages',
            'target' => 'biblio_pages',
            'unique' => FALSE,
          ),
          145 => array(
            'source' => 'dictionaryEntry:place',
            'target' => 'biblio_place_published',
            'unique' => FALSE,
          ),
          146 => array(
            'source' => 'dictionaryEntry:publisher',
            'target' => 'biblio_publisher',
            'unique' => FALSE,
          ),
          147 => array(
            'source' => 'dictionaryEntry:rights',
            'target' => 'biblio_custom7',
            'unique' => FALSE,
          ),
          148 => array(
            'source' => 'dictionaryEntry:series',
            'target' => 'biblio_secondary_title',
            'unique' => FALSE,
          ),
          149 => array(
            'source' => 'dictionaryEntry:seriesNumber',
            'target' => 'biblio_number',
            'unique' => FALSE,
          ),
          150 => array(
            'source' => 'dictionaryEntry:shortTitle',
            'target' => 'biblio_short_title',
            'unique' => FALSE,
          ),
          151 => array(
            'source' => 'dictionaryEntry:title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          152 => array(
            'source' => 'dictionaryEntry:url',
            'target' => 'biblio_url',
            'unique' => FALSE,
          ),
          153 => array(
            'source' => 'dictionaryEntry:volume',
            'target' => 'biblio_volume',
            'unique' => FALSE,
          ),
          154 => array(
            'source' => 'document:abstractNote',
            'target' => 'biblio_abst_e',
            'unique' => FALSE,
          ),
          155 => array(
            'source' => 'document:accessDate',
            'target' => 'biblio_access_date',
            'unique' => FALSE,
          ),
          156 => array(
            'source' => 'document:archive',
            'target' => 'biblio_publisher',
            'unique' => FALSE,
          ),
          157 => array(
            'source' => 'document:archiveLocation',
            'target' => 'biblio_place_published',
            'unique' => FALSE,
          ),
          158 => array(
            'source' => 'document:callNumber',
            'target' => 'biblio_call_number',
            'unique' => FALSE,
          ),
          159 => array(
            'source' => 'document:date',
            'target' => 'biblio_year',
            'unique' => FALSE,
          ),
          160 => array(
            'source' => 'document:language',
            'target' => 'biblio_lang',
            'unique' => FALSE,
          ),
          161 => array(
            'source' => 'document:publisher',
            'target' => 'biblio_publisher',
            'unique' => FALSE,
          ),
          162 => array(
            'source' => 'document:rights',
            'target' => 'biblio_custom7',
            'unique' => FALSE,
          ),
          163 => array(
            'source' => 'document:shortTitle',
            'target' => 'biblio_short_title',
            'unique' => FALSE,
          ),
          164 => array(
            'source' => 'document:title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          165 => array(
            'source' => 'document:url',
            'target' => 'biblio_url',
            'unique' => FALSE,
          ),
          166 => array(
            'source' => 'email:abstractNote',
            'target' => 'biblio_abst_e',
            'unique' => FALSE,
          ),
          167 => array(
            'source' => 'email:accessDate',
            'target' => 'biblio_access_date',
            'unique' => FALSE,
          ),
          168 => array(
            'source' => 'email:date',
            'target' => 'biblio_year',
            'unique' => FALSE,
          ),
          169 => array(
            'source' => 'email:language',
            'target' => 'biblio_lang',
            'unique' => FALSE,
          ),
          170 => array(
            'source' => 'email:rights',
            'target' => 'biblio_custom7',
            'unique' => FALSE,
          ),
          171 => array(
            'source' => 'email:shortTitle',
            'target' => 'biblio_short_title',
            'unique' => FALSE,
          ),
          172 => array(
            'source' => 'email:subject',
            'target' => 'title',
            'unique' => FALSE,
          ),
          173 => array(
            'source' => 'email:url',
            'target' => 'biblio_url',
            'unique' => FALSE,
          ),
          174 => array(
            'source' => 'encyclopediaArticle:abstractNote',
            'target' => 'biblio_abst_e',
            'unique' => FALSE,
          ),
          175 => array(
            'source' => 'encyclopediaArticle:accessDate',
            'target' => 'biblio_access_date',
            'unique' => FALSE,
          ),
          176 => array(
            'source' => 'encyclopediaArticle:archive',
            'target' => 'biblio_publisher',
            'unique' => FALSE,
          ),
          177 => array(
            'source' => 'encyclopediaArticle:archiveLocation',
            'target' => 'biblio_place_published',
            'unique' => FALSE,
          ),
          178 => array(
            'source' => 'encyclopediaArticle:callNumber',
            'target' => 'biblio_call_number',
            'unique' => FALSE,
          ),
          179 => array(
            'source' => 'encyclopediaArticle:date',
            'target' => 'biblio_year',
            'unique' => FALSE,
          ),
          180 => array(
            'source' => 'encyclopediaArticle:edition',
            'target' => 'biblio_edition',
            'unique' => FALSE,
          ),
          181 => array(
            'source' => 'encyclopediaArticle:ISBN',
            'target' => 'biblio_isbn',
            'unique' => FALSE,
          ),
          182 => array(
            'source' => 'encyclopediaArticle:language',
            'target' => 'biblio_lang',
            'unique' => FALSE,
          ),
          183 => array(
            'source' => 'encyclopediaArticle:numberOfVolumes',
            'target' => 'biblio_number_of_volumes',
            'unique' => FALSE,
          ),
          184 => array(
            'source' => 'encyclopediaArticle:pages',
            'target' => 'biblio_pages',
            'unique' => FALSE,
          ),
          185 => array(
            'source' => 'encyclopediaArticle:place',
            'target' => 'biblio_place_published',
            'unique' => FALSE,
          ),
          186 => array(
            'source' => 'encyclopediaArticle:publisher',
            'target' => 'biblio_publisher',
            'unique' => FALSE,
          ),
          187 => array(
            'source' => 'encyclopediaArticle:rights',
            'target' => 'biblio_custom7',
            'unique' => FALSE,
          ),
          188 => array(
            'source' => 'encyclopediaArticle:series',
            'target' => 'biblio_secondary_title',
            'unique' => FALSE,
          ),
          189 => array(
            'source' => 'encyclopediaArticle:seriesNumber',
            'target' => 'biblio_number',
            'unique' => FALSE,
          ),
          190 => array(
            'source' => 'encyclopediaArticle:shortTitle',
            'target' => 'biblio_short_title',
            'unique' => FALSE,
          ),
          191 => array(
            'source' => 'encyclopediaArticle:title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          192 => array(
            'source' => 'encyclopediaArticle:url',
            'target' => 'biblio_url',
            'unique' => FALSE,
          ),
          193 => array(
            'source' => 'encyclopediaArticle:volume',
            'target' => 'biblio_volume',
            'unique' => FALSE,
          ),
          194 => array(
            'source' => 'film:abstractNote',
            'target' => 'biblio_abst_e',
            'unique' => FALSE,
          ),
          195 => array(
            'source' => 'film:accessDate',
            'target' => 'biblio_access_date',
            'unique' => FALSE,
          ),
          196 => array(
            'source' => 'film:archive',
            'target' => 'biblio_publisher',
            'unique' => FALSE,
          ),
          197 => array(
            'source' => 'film:archiveLocation',
            'target' => 'biblio_place_published',
            'unique' => FALSE,
          ),
          198 => array(
            'source' => 'film:callNumber',
            'target' => 'biblio_call_number',
            'unique' => FALSE,
          ),
          199 => array(
            'source' => 'film:date',
            'target' => 'biblio_year',
            'unique' => FALSE,
          ),
          200 => array(
            'source' => 'film:language',
            'target' => 'biblio_lang',
            'unique' => FALSE,
          ),
          201 => array(
            'source' => 'film:rights',
            'target' => 'biblio_custom7',
            'unique' => FALSE,
          ),
          202 => array(
            'source' => 'film:shortTitle',
            'target' => 'biblio_short_title',
            'unique' => FALSE,
          ),
          203 => array(
            'source' => 'film:title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          204 => array(
            'source' => 'film:url',
            'target' => 'biblio_url',
            'unique' => FALSE,
          ),
          205 => array(
            'source' => 'forumPost:abstractNote',
            'target' => 'biblio_abst_e',
            'unique' => FALSE,
          ),
          206 => array(
            'source' => 'forumPost:accessDate',
            'target' => 'biblio_access_date',
            'unique' => FALSE,
          ),
          207 => array(
            'source' => 'forumPost:date',
            'target' => 'biblio_year',
            'unique' => FALSE,
          ),
          208 => array(
            'source' => 'forumPost:language',
            'target' => 'biblio_lang',
            'unique' => FALSE,
          ),
          209 => array(
            'source' => 'forumPost:rights',
            'target' => 'biblio_custom7',
            'unique' => FALSE,
          ),
          210 => array(
            'source' => 'forumPost:shortTitle',
            'target' => 'biblio_short_title',
            'unique' => FALSE,
          ),
          211 => array(
            'source' => 'forumPost:title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          212 => array(
            'source' => 'forumPost:url',
            'target' => 'biblio_url',
            'unique' => FALSE,
          ),
          213 => array(
            'source' => 'hearing:abstractNote',
            'target' => 'biblio_abst_e',
            'unique' => FALSE,
          ),
          214 => array(
            'source' => 'hearing:accessDate',
            'target' => 'biblio_access_date',
            'unique' => FALSE,
          ),
          215 => array(
            'source' => 'hearing:date',
            'target' => 'biblio_year',
            'unique' => FALSE,
          ),
          216 => array(
            'source' => 'hearing:documentNumber',
            'target' => 'biblio_number',
            'unique' => FALSE,
          ),
          217 => array(
            'source' => 'hearing:language',
            'target' => 'biblio_lang',
            'unique' => FALSE,
          ),
          218 => array(
            'source' => 'hearing:numberOfVolumes',
            'target' => 'biblio_number_of_volumes',
            'unique' => FALSE,
          ),
          219 => array(
            'source' => 'hearing:pages',
            'target' => 'biblio_pages',
            'unique' => FALSE,
          ),
          220 => array(
            'source' => 'hearing:place',
            'target' => 'biblio_place_published',
            'unique' => FALSE,
          ),
          221 => array(
            'source' => 'hearing:publisher',
            'target' => 'biblio_publisher',
            'unique' => FALSE,
          ),
          222 => array(
            'source' => 'hearing:rights',
            'target' => 'biblio_custom7',
            'unique' => FALSE,
          ),
          223 => array(
            'source' => 'hearing:shortTitle',
            'target' => 'biblio_short_title',
            'unique' => FALSE,
          ),
          224 => array(
            'source' => 'hearing:title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          225 => array(
            'source' => 'hearing:url',
            'target' => 'biblio_url',
            'unique' => FALSE,
          ),
          226 => array(
            'source' => 'instantMessage:abstractNote',
            'target' => 'biblio_abst_e',
            'unique' => FALSE,
          ),
          227 => array(
            'source' => 'instantMessage:accessDate',
            'target' => 'biblio_access_date',
            'unique' => FALSE,
          ),
          228 => array(
            'source' => 'instantMessage:date',
            'target' => 'biblio_year',
            'unique' => FALSE,
          ),
          229 => array(
            'source' => 'instantMessage:language',
            'target' => 'biblio_lang',
            'unique' => FALSE,
          ),
          230 => array(
            'source' => 'instantMessage:rights',
            'target' => 'biblio_custom7',
            'unique' => FALSE,
          ),
          231 => array(
            'source' => 'instantMessage:shortTitle',
            'target' => 'biblio_short_title',
            'unique' => FALSE,
          ),
          232 => array(
            'source' => 'instantMessage:title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          233 => array(
            'source' => 'instantMessage:url',
            'target' => 'biblio_url',
            'unique' => FALSE,
          ),
          234 => array(
            'source' => 'interview:abstractNote',
            'target' => 'biblio_abst_e',
            'unique' => FALSE,
          ),
          235 => array(
            'source' => 'interview:accessDate',
            'target' => 'biblio_access_date',
            'unique' => FALSE,
          ),
          236 => array(
            'source' => 'interview:archive',
            'target' => 'biblio_publisher',
            'unique' => FALSE,
          ),
          237 => array(
            'source' => 'interview:archiveLocation',
            'target' => 'biblio_place_published',
            'unique' => FALSE,
          ),
          238 => array(
            'source' => 'interview:callNumber',
            'target' => 'biblio_call_number',
            'unique' => FALSE,
          ),
          239 => array(
            'source' => 'interview:date',
            'target' => 'biblio_year',
            'unique' => FALSE,
          ),
          240 => array(
            'source' => 'interview:language',
            'target' => 'biblio_lang',
            'unique' => FALSE,
          ),
          241 => array(
            'source' => 'interview:rights',
            'target' => 'biblio_custom7',
            'unique' => FALSE,
          ),
          242 => array(
            'source' => 'interview:shortTitle',
            'target' => 'biblio_short_title',
            'unique' => FALSE,
          ),
          243 => array(
            'source' => 'interview:title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          244 => array(
            'source' => 'interview:url',
            'target' => 'biblio_url',
            'unique' => FALSE,
          ),
          245 => array(
            'source' => 'journalArticle:abstractNote',
            'target' => 'biblio_abst_e',
            'unique' => FALSE,
          ),
          246 => array(
            'source' => 'journalArticle:accessDate',
            'target' => 'biblio_access_date',
            'unique' => FALSE,
          ),
          247 => array(
            'source' => 'journalArticle:archive',
            'target' => 'biblio_publisher',
            'unique' => FALSE,
          ),
          248 => array(
            'source' => 'journalArticle:archiveLocation',
            'target' => 'biblio_place_published',
            'unique' => FALSE,
          ),
          249 => array(
            'source' => 'journalArticle:callNumber',
            'target' => 'biblio_call_number',
            'unique' => FALSE,
          ),
          250 => array(
            'source' => 'journalArticle:date',
            'target' => 'biblio_year',
            'unique' => FALSE,
          ),
          251 => array(
            'source' => 'journalArticle:DOI',
            'target' => 'biblio_doi',
            'unique' => FALSE,
          ),
          252 => array(
            'source' => 'journalArticle:ISSN',
            'target' => 'biblio_issn',
            'unique' => FALSE,
          ),
          253 => array(
            'source' => 'journalArticle:issue',
            'target' => 'biblio_issue',
            'unique' => FALSE,
          ),
          254 => array(
            'source' => 'journalArticle:language',
            'target' => 'biblio_lang',
            'unique' => FALSE,
          ),
          255 => array(
            'source' => 'journalArticle:pages',
            'target' => 'biblio_pages',
            'unique' => FALSE,
          ),
          256 => array(
            'source' => 'journalArticle:publicationTitle',
            'target' => 'biblio_secondary_title',
            'unique' => FALSE,
          ),
          257 => array(
            'source' => 'journalArticle:rights',
            'target' => 'biblio_custom7',
            'unique' => FALSE,
          ),
          258 => array(
            'source' => 'journalArticle:series',
            'target' => 'biblio_alternate_title',
            'unique' => FALSE,
          ),
          259 => array(
            'source' => 'journalArticle:shortTitle',
            'target' => 'biblio_short_title',
            'unique' => FALSE,
          ),
          260 => array(
            'source' => 'journalArticle:title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          261 => array(
            'source' => 'journalArticle:url',
            'target' => 'biblio_url',
            'unique' => FALSE,
          ),
          262 => array(
            'source' => 'journalArticle:volume',
            'target' => 'biblio_volume',
            'unique' => FALSE,
          ),
          263 => array(
            'source' => 'letter:abstractNote',
            'target' => 'biblio_abst_e',
            'unique' => FALSE,
          ),
          264 => array(
            'source' => 'letter:accessDate',
            'target' => 'biblio_access_date',
            'unique' => FALSE,
          ),
          265 => array(
            'source' => 'letter:archive',
            'target' => 'biblio_publisher',
            'unique' => FALSE,
          ),
          266 => array(
            'source' => 'letter:archiveLocation',
            'target' => 'biblio_place_published',
            'unique' => FALSE,
          ),
          267 => array(
            'source' => 'letter:callNumber',
            'target' => 'biblio_call_number',
            'unique' => FALSE,
          ),
          268 => array(
            'source' => 'letter:date',
            'target' => 'biblio_year',
            'unique' => FALSE,
          ),
          269 => array(
            'source' => 'letter:language',
            'target' => 'biblio_lang',
            'unique' => FALSE,
          ),
          270 => array(
            'source' => 'letter:rights',
            'target' => 'biblio_custom7',
            'unique' => FALSE,
          ),
          271 => array(
            'source' => 'letter:shortTitle',
            'target' => 'biblio_short_title',
            'unique' => FALSE,
          ),
          272 => array(
            'source' => 'letter:title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          273 => array(
            'source' => 'letter:url',
            'target' => 'biblio_url',
            'unique' => FALSE,
          ),
          274 => array(
            'source' => 'magazineArticle:abstractNote',
            'target' => 'biblio_abst_e',
            'unique' => FALSE,
          ),
          275 => array(
            'source' => 'magazineArticle:accessDate',
            'target' => 'biblio_access_date',
            'unique' => FALSE,
          ),
          276 => array(
            'source' => 'magazineArticle:archive',
            'target' => 'biblio_publisher',
            'unique' => FALSE,
          ),
          277 => array(
            'source' => 'magazineArticle:archiveLocation',
            'target' => 'biblio_place_published',
            'unique' => FALSE,
          ),
          278 => array(
            'source' => 'magazineArticle:callNumber',
            'target' => 'biblio_call_number',
            'unique' => FALSE,
          ),
          279 => array(
            'source' => 'magazineArticle:date',
            'target' => 'biblio_year',
            'unique' => FALSE,
          ),
          280 => array(
            'source' => 'magazineArticle:ISSN',
            'target' => 'biblio_issn',
            'unique' => FALSE,
          ),
          281 => array(
            'source' => 'magazineArticle:issue',
            'target' => 'biblio_issue',
            'unique' => FALSE,
          ),
          282 => array(
            'source' => 'magazineArticle:language',
            'target' => 'biblio_lang',
            'unique' => FALSE,
          ),
          283 => array(
            'source' => 'magazineArticle:pages',
            'target' => 'biblio_pages',
            'unique' => FALSE,
          ),
          284 => array(
            'source' => 'magazineArticle:rights',
            'target' => 'biblio_custom7',
            'unique' => FALSE,
          ),
          285 => array(
            'source' => 'magazineArticle:shortTitle',
            'target' => 'biblio_short_title',
            'unique' => FALSE,
          ),
          286 => array(
            'source' => 'magazineArticle:title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          287 => array(
            'source' => 'magazineArticle:url',
            'target' => 'biblio_url',
            'unique' => FALSE,
          ),
          288 => array(
            'source' => 'magazineArticle:volume',
            'target' => 'biblio_volume',
            'unique' => FALSE,
          ),
          289 => array(
            'source' => 'manuscript:abstractNote',
            'target' => 'biblio_abst_e',
            'unique' => FALSE,
          ),
          290 => array(
            'source' => 'manuscript:accessDate',
            'target' => 'biblio_access_date',
            'unique' => FALSE,
          ),
          291 => array(
            'source' => 'manuscript:archive',
            'target' => 'biblio_publisher',
            'unique' => FALSE,
          ),
          292 => array(
            'source' => 'manuscript:archiveLocation',
            'target' => 'biblio_place_published',
            'unique' => FALSE,
          ),
          293 => array(
            'source' => 'manuscript:callNumber',
            'target' => 'biblio_call_number',
            'unique' => FALSE,
          ),
          294 => array(
            'source' => 'manuscript:date',
            'target' => 'biblio_year',
            'unique' => FALSE,
          ),
          295 => array(
            'source' => 'manuscript:language',
            'target' => 'biblio_lang',
            'unique' => FALSE,
          ),
          296 => array(
            'source' => 'manuscript:numPages',
            'target' => 'biblio_pages',
            'unique' => FALSE,
          ),
          297 => array(
            'source' => 'manuscript:place',
            'target' => 'biblio_place_published',
            'unique' => FALSE,
          ),
          298 => array(
            'source' => 'manuscript:rights',
            'target' => 'biblio_custom7',
            'unique' => FALSE,
          ),
          299 => array(
            'source' => 'manuscript:shortTitle',
            'target' => 'biblio_short_title',
            'unique' => FALSE,
          ),
          300 => array(
            'source' => 'manuscript:title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          301 => array(
            'source' => 'manuscript:url',
            'target' => 'biblio_url',
            'unique' => FALSE,
          ),
          302 => array(
            'source' => 'map:abstractNote',
            'target' => 'biblio_abst_e',
            'unique' => FALSE,
          ),
          303 => array(
            'source' => 'map:accessDate',
            'target' => 'biblio_access_date',
            'unique' => FALSE,
          ),
          304 => array(
            'source' => 'map:archive',
            'target' => 'biblio_publisher',
            'unique' => FALSE,
          ),
          305 => array(
            'source' => 'map:archiveLocation',
            'target' => 'biblio_place_published',
            'unique' => FALSE,
          ),
          306 => array(
            'source' => 'map:callNumber',
            'target' => 'biblio_call_number',
            'unique' => FALSE,
          ),
          307 => array(
            'source' => 'map:date',
            'target' => 'biblio_year',
            'unique' => FALSE,
          ),
          308 => array(
            'source' => 'map:edition',
            'target' => 'biblio_edition',
            'unique' => FALSE,
          ),
          309 => array(
            'source' => 'map:ISBN',
            'target' => 'biblio_isbn',
            'unique' => FALSE,
          ),
          310 => array(
            'source' => 'map:language',
            'target' => 'biblio_lang',
            'unique' => FALSE,
          ),
          311 => array(
            'source' => 'map:place',
            'target' => 'biblio_place_published',
            'unique' => FALSE,
          ),
          312 => array(
            'source' => 'map:publisher',
            'target' => 'biblio_publisher',
            'unique' => FALSE,
          ),
          313 => array(
            'source' => 'map:rights',
            'target' => 'biblio_custom7',
            'unique' => FALSE,
          ),
          314 => array(
            'source' => 'map:series',
            'target' => 'biblio_secondary_title',
            'unique' => FALSE,
          ),
          315 => array(
            'source' => 'map:shortTitle',
            'target' => 'biblio_short_title',
            'unique' => FALSE,
          ),
          316 => array(
            'source' => 'map:title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          317 => array(
            'source' => 'map:url',
            'target' => 'biblio_url',
            'unique' => FALSE,
          ),
          318 => array(
            'source' => 'newspaperArticle:abstractNote',
            'target' => 'biblio_abst_e',
            'unique' => FALSE,
          ),
          319 => array(
            'source' => 'newspaperArticle:accessDate',
            'target' => 'biblio_access_date',
            'unique' => FALSE,
          ),
          320 => array(
            'source' => 'newspaperArticle:archive',
            'target' => 'biblio_publisher',
            'unique' => FALSE,
          ),
          321 => array(
            'source' => 'newspaperArticle:archiveLocation',
            'target' => 'biblio_place_published',
            'unique' => FALSE,
          ),
          322 => array(
            'source' => 'newspaperArticle:callNumber',
            'target' => 'biblio_call_number',
            'unique' => FALSE,
          ),
          323 => array(
            'source' => 'newspaperArticle:date',
            'target' => 'biblio_year',
            'unique' => FALSE,
          ),
          324 => array(
            'source' => 'newspaperArticle:edition',
            'target' => 'biblio_edition',
            'unique' => FALSE,
          ),
          325 => array(
            'source' => 'newspaperArticle:ISSN',
            'target' => 'biblio_issn',
            'unique' => FALSE,
          ),
          326 => array(
            'source' => 'newspaperArticle:language',
            'target' => 'biblio_lang',
            'unique' => FALSE,
          ),
          327 => array(
            'source' => 'newspaperArticle:pages',
            'target' => 'biblio_pages',
            'unique' => FALSE,
          ),
          328 => array(
            'source' => 'newspaperArticle:place',
            'target' => 'biblio_place_published',
            'unique' => FALSE,
          ),
          329 => array(
            'source' => 'newspaperArticle:rights',
            'target' => 'biblio_custom7',
            'unique' => FALSE,
          ),
          330 => array(
            'source' => 'newspaperArticle:shortTitle',
            'target' => 'biblio_short_title',
            'unique' => FALSE,
          ),
          331 => array(
            'source' => 'newspaperArticle:title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          332 => array(
            'source' => 'newspaperArticle:url',
            'target' => 'biblio_url',
            'unique' => FALSE,
          ),
          333 => array(
            'source' => 'patent:abstractNote',
            'target' => 'biblio_abst_e',
            'unique' => FALSE,
          ),
          334 => array(
            'source' => 'patent:accessDate',
            'target' => 'biblio_access_date',
            'unique' => FALSE,
          ),
          335 => array(
            'source' => 'patent:language',
            'target' => 'biblio_lang',
            'unique' => FALSE,
          ),
          336 => array(
            'source' => 'patent:pages',
            'target' => 'biblio_pages',
            'unique' => FALSE,
          ),
          337 => array(
            'source' => 'patent:patentNumber',
            'target' => 'biblio_number',
            'unique' => FALSE,
          ),
          338 => array(
            'source' => 'patent:place',
            'target' => 'biblio_place_published',
            'unique' => FALSE,
          ),
          339 => array(
            'source' => 'patent:rights',
            'target' => 'biblio_custom7',
            'unique' => FALSE,
          ),
          340 => array(
            'source' => 'patent:shortTitle',
            'target' => 'biblio_short_title',
            'unique' => FALSE,
          ),
          341 => array(
            'source' => 'patent:title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          342 => array(
            'source' => 'patent:url',
            'target' => 'biblio_url',
            'unique' => FALSE,
          ),
          343 => array(
            'source' => 'podcast:abstractNote',
            'target' => 'biblio_abst_e',
            'unique' => FALSE,
          ),
          344 => array(
            'source' => 'podcast:accessDate',
            'target' => 'biblio_access_date',
            'unique' => FALSE,
          ),
          345 => array(
            'source' => 'podcast:episodeNumber',
            'target' => 'biblio_number',
            'unique' => FALSE,
          ),
          346 => array(
            'source' => 'podcast:language',
            'target' => 'biblio_lang',
            'unique' => FALSE,
          ),
          347 => array(
            'source' => 'podcast:rights',
            'target' => 'biblio_custom7',
            'unique' => FALSE,
          ),
          348 => array(
            'source' => 'podcast:series',
            'target' => 'biblio_secondary_title',
            'unique' => FALSE,
          ),
          349 => array(
            'source' => 'podcast:shortTitle',
            'target' => 'biblio_short_title',
            'unique' => FALSE,
          ),
          350 => array(
            'source' => 'podcast:title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          351 => array(
            'source' => 'podcast:url',
            'target' => 'biblio_url',
            'unique' => FALSE,
          ),
          352 => array(
            'source' => 'presentation:abstractNote',
            'target' => 'biblio_abst_e',
            'unique' => FALSE,
          ),
          353 => array(
            'source' => 'presentation:accessDate',
            'target' => 'biblio_access_date',
            'unique' => FALSE,
          ),
          354 => array(
            'source' => 'presentation:date',
            'target' => 'biblio_year',
            'unique' => FALSE,
          ),
          355 => array(
            'source' => 'presentation:language',
            'target' => 'biblio_lang',
            'unique' => FALSE,
          ),
          356 => array(
            'source' => 'presentation:place',
            'target' => 'biblio_place_published',
            'unique' => FALSE,
          ),
          357 => array(
            'source' => 'presentation:rights',
            'target' => 'biblio_custom7',
            'unique' => FALSE,
          ),
          358 => array(
            'source' => 'presentation:shortTitle',
            'target' => 'biblio_short_title',
            'unique' => FALSE,
          ),
          359 => array(
            'source' => 'presentation:title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          360 => array(
            'source' => 'presentation:url',
            'target' => 'biblio_url',
            'unique' => FALSE,
          ),
          361 => array(
            'source' => 'radioBroadcast:abstractNote',
            'target' => 'biblio_abst_e',
            'unique' => FALSE,
          ),
          362 => array(
            'source' => 'radioBroadcast:accessDate',
            'target' => 'biblio_access_date',
            'unique' => FALSE,
          ),
          363 => array(
            'source' => 'radioBroadcast:archive',
            'target' => 'biblio_publisher',
            'unique' => FALSE,
          ),
          364 => array(
            'source' => 'radioBroadcast:archiveLocation',
            'target' => 'biblio_place_published',
            'unique' => FALSE,
          ),
          365 => array(
            'source' => 'radioBroadcast:callNumber',
            'target' => 'biblio_call_number',
            'unique' => FALSE,
          ),
          366 => array(
            'source' => 'radioBroadcast:date',
            'target' => 'biblio_year',
            'unique' => FALSE,
          ),
          367 => array(
            'source' => 'radioBroadcast:episodeNumber',
            'target' => 'biblio_number',
            'unique' => FALSE,
          ),
          368 => array(
            'source' => 'radioBroadcast:language',
            'target' => 'biblio_lang',
            'unique' => FALSE,
          ),
          369 => array(
            'source' => 'radioBroadcast:place',
            'target' => 'biblio_place_published',
            'unique' => FALSE,
          ),
          370 => array(
            'source' => 'radioBroadcast:programTitle',
            'target' => 'biblio_secondary_title',
            'unique' => FALSE,
          ),
          371 => array(
            'source' => 'radioBroadcast:rights',
            'target' => 'biblio_custom7',
            'unique' => FALSE,
          ),
          372 => array(
            'source' => 'radioBroadcast:shortTitle',
            'target' => 'biblio_short_title',
            'unique' => FALSE,
          ),
          373 => array(
            'source' => 'radioBroadcast:title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          374 => array(
            'source' => 'radioBroadcast:url',
            'target' => 'biblio_url',
            'unique' => FALSE,
          ),
          375 => array(
            'source' => 'report:abstractNote',
            'target' => 'biblio_abst_e',
            'unique' => FALSE,
          ),
          376 => array(
            'source' => 'report:accessDate',
            'target' => 'biblio_access_date',
            'unique' => FALSE,
          ),
          377 => array(
            'source' => 'report:archive',
            'target' => 'biblio_publisher',
            'unique' => FALSE,
          ),
          378 => array(
            'source' => 'report:archiveLocation',
            'target' => 'biblio_place_published',
            'unique' => FALSE,
          ),
          379 => array(
            'source' => 'report:callNumber',
            'target' => 'biblio_call_number',
            'unique' => FALSE,
          ),
          380 => array(
            'source' => 'report:date',
            'target' => 'biblio_year',
            'unique' => FALSE,
          ),
          381 => array(
            'source' => 'report:language',
            'target' => 'biblio_lang',
            'unique' => FALSE,
          ),
          382 => array(
            'source' => 'report:pages',
            'target' => 'biblio_pages',
            'unique' => FALSE,
          ),
          383 => array(
            'source' => 'report:place',
            'target' => 'biblio_place_published',
            'unique' => FALSE,
          ),
          384 => array(
            'source' => 'report:reportNumber',
            'target' => 'biblio_number',
            'unique' => FALSE,
          ),
          385 => array(
            'source' => 'report:rights',
            'target' => 'biblio_custom7',
            'unique' => FALSE,
          ),
          386 => array(
            'source' => 'report:series',
            'target' => 'biblio_secondary_title',
            'unique' => FALSE,
          ),
          387 => array(
            'source' => 'report:shortTitle',
            'target' => 'biblio_short_title',
            'unique' => FALSE,
          ),
          388 => array(
            'source' => 'report:title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          389 => array(
            'source' => 'report:url',
            'target' => 'biblio_url',
            'unique' => FALSE,
          ),
          390 => array(
            'source' => 'statute:abstractNote',
            'target' => 'biblio_abst_e',
            'unique' => FALSE,
          ),
          391 => array(
            'source' => 'statute:accessDate',
            'target' => 'biblio_access_date',
            'unique' => FALSE,
          ),
          392 => array(
            'source' => 'statute:language',
            'target' => 'biblio_lang',
            'unique' => FALSE,
          ),
          393 => array(
            'source' => 'statute:nameOfAct',
            'target' => 'title',
            'unique' => FALSE,
          ),
          394 => array(
            'source' => 'statute:pages',
            'target' => 'biblio_pages',
            'unique' => FALSE,
          ),
          395 => array(
            'source' => 'statute:publicLawNumber',
            'target' => 'biblio_number',
            'unique' => FALSE,
          ),
          396 => array(
            'source' => 'statute:rights',
            'target' => 'biblio_custom7',
            'unique' => FALSE,
          ),
          397 => array(
            'source' => 'statute:shortTitle',
            'target' => 'biblio_short_title',
            'unique' => FALSE,
          ),
          398 => array(
            'source' => 'statute:url',
            'target' => 'biblio_url',
            'unique' => FALSE,
          ),
          399 => array(
            'source' => 'tvBroadcast:abstractNote',
            'target' => 'biblio_abst_e',
            'unique' => FALSE,
          ),
          400 => array(
            'source' => 'tvBroadcast:accessDate',
            'target' => 'biblio_access_date',
            'unique' => FALSE,
          ),
          401 => array(
            'source' => 'tvBroadcast:archive',
            'target' => 'biblio_publisher',
            'unique' => FALSE,
          ),
          402 => array(
            'source' => 'tvBroadcast:archiveLocation',
            'target' => 'biblio_place_published',
            'unique' => FALSE,
          ),
          403 => array(
            'source' => 'tvBroadcast:callNumber',
            'target' => 'biblio_call_number',
            'unique' => FALSE,
          ),
          404 => array(
            'source' => 'tvBroadcast:date',
            'target' => 'biblio_year',
            'unique' => FALSE,
          ),
          405 => array(
            'source' => 'tvBroadcast:episodeNumber',
            'target' => 'biblio_number',
            'unique' => FALSE,
          ),
          406 => array(
            'source' => 'tvBroadcast:language',
            'target' => 'biblio_lang',
            'unique' => FALSE,
          ),
          407 => array(
            'source' => 'tvBroadcast:place',
            'target' => 'biblio_place_published',
            'unique' => FALSE,
          ),
          408 => array(
            'source' => 'tvBroadcast:programTitle',
            'target' => 'biblio_secondary_title',
            'unique' => FALSE,
          ),
          409 => array(
            'source' => 'tvBroadcast:rights',
            'target' => 'biblio_custom7',
            'unique' => FALSE,
          ),
          410 => array(
            'source' => 'tvBroadcast:shortTitle',
            'target' => 'biblio_short_title',
            'unique' => FALSE,
          ),
          411 => array(
            'source' => 'tvBroadcast:title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          412 => array(
            'source' => 'tvBroadcast:url',
            'target' => 'biblio_url',
            'unique' => FALSE,
          ),
          413 => array(
            'source' => 'thesis:abstractNote',
            'target' => 'biblio_abst_e',
            'unique' => FALSE,
          ),
          414 => array(
            'source' => 'thesis:accessDate',
            'target' => 'biblio_access_date',
            'unique' => FALSE,
          ),
          415 => array(
            'source' => 'thesis:archive',
            'target' => 'biblio_publisher',
            'unique' => FALSE,
          ),
          416 => array(
            'source' => 'thesis:archiveLocation',
            'target' => 'biblio_place_published',
            'unique' => FALSE,
          ),
          417 => array(
            'source' => 'thesis:callNumber',
            'target' => 'biblio_call_number',
            'unique' => FALSE,
          ),
          418 => array(
            'source' => 'thesis:date',
            'target' => 'biblio_year',
            'unique' => FALSE,
          ),
          419 => array(
            'source' => 'thesis:language',
            'target' => 'biblio_lang',
            'unique' => FALSE,
          ),
          420 => array(
            'source' => 'thesis:numPages',
            'target' => 'biblio_pages',
            'unique' => FALSE,
          ),
          421 => array(
            'source' => 'thesis:place',
            'target' => 'biblio_place_published',
            'unique' => FALSE,
          ),
          422 => array(
            'source' => 'thesis:rights',
            'target' => 'biblio_custom7',
            'unique' => FALSE,
          ),
          423 => array(
            'source' => 'thesis:shortTitle',
            'target' => 'biblio_short_title',
            'unique' => FALSE,
          ),
          424 => array(
            'source' => 'thesis:title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          425 => array(
            'source' => 'thesis:url',
            'target' => 'biblio_url',
            'unique' => FALSE,
          ),
          426 => array(
            'source' => 'videoRecording:abstractNote',
            'target' => 'biblio_abst_e',
            'unique' => FALSE,
          ),
          427 => array(
            'source' => 'videoRecording:accessDate',
            'target' => 'biblio_access_date',
            'unique' => FALSE,
          ),
          428 => array(
            'source' => 'videoRecording:archive',
            'target' => 'biblio_publisher',
            'unique' => FALSE,
          ),
          429 => array(
            'source' => 'videoRecording:archiveLocation',
            'target' => 'biblio_place_published',
            'unique' => FALSE,
          ),
          430 => array(
            'source' => 'videoRecording:callNumber',
            'target' => 'biblio_call_number',
            'unique' => FALSE,
          ),
          431 => array(
            'source' => 'videoRecording:date',
            'target' => 'biblio_year',
            'unique' => FALSE,
          ),
          432 => array(
            'source' => 'videoRecording:ISBN',
            'target' => 'biblio_isbn',
            'unique' => FALSE,
          ),
          433 => array(
            'source' => 'videoRecording:language',
            'target' => 'biblio_lang',
            'unique' => FALSE,
          ),
          434 => array(
            'source' => 'videoRecording:numberOfVolumes',
            'target' => 'biblio_number_of_volumes',
            'unique' => FALSE,
          ),
          435 => array(
            'source' => 'videoRecording:place',
            'target' => 'biblio_place_published',
            'unique' => FALSE,
          ),
          436 => array(
            'source' => 'videoRecording:rights',
            'target' => 'biblio_custom7',
            'unique' => FALSE,
          ),
          437 => array(
            'source' => 'videoRecording:series',
            'target' => 'biblio_secondary_title',
            'unique' => FALSE,
          ),
          438 => array(
            'source' => 'videoRecording:shortTitle',
            'target' => 'biblio_short_title',
            'unique' => FALSE,
          ),
          439 => array(
            'source' => 'videoRecording:title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          440 => array(
            'source' => 'videoRecording:url',
            'target' => 'biblio_url',
            'unique' => FALSE,
          ),
          441 => array(
            'source' => 'videoRecording:volume',
            'target' => 'biblio_volume',
            'unique' => FALSE,
          ),
          442 => array(
            'source' => 'webpage:abstractNote',
            'target' => 'biblio_abst_e',
            'unique' => FALSE,
          ),
          443 => array(
            'source' => 'webpage:accessDate',
            'target' => 'biblio_access_date',
            'unique' => FALSE,
          ),
          444 => array(
            'source' => 'webpage:date',
            'target' => 'biblio_year',
            'unique' => FALSE,
          ),
          445 => array(
            'source' => 'webpage:language',
            'target' => 'biblio_lang',
            'unique' => FALSE,
          ),
          446 => array(
            'source' => 'webpage:rights',
            'target' => 'biblio_custom7',
            'unique' => FALSE,
          ),
          447 => array(
            'source' => 'webpage:shortTitle',
            'target' => 'biblio_short_title',
            'unique' => FALSE,
          ),
          448 => array(
            'source' => 'webpage:title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          449 => array(
            'source' => 'webpage:url',
            'target' => 'biblio_url',
            'unique' => FALSE,
          ),
          450 => array(
            'source' => 'webpage:websiteType',
            'target' => 'biblio_type_of_work',
            'unique' => FALSE,
          ),
        ),
        'input_format' => 'panopoly_wysiwyg_text',
        'author' => 0,
        'sync_tags' => '1',
        'authorize' => 0,
        'insert_new' => '1',
        'update_non_existent' => 'skip',
        'skip_hash_check' => 0,
        'language' => 'und',
        'tags_field' => 'field_pece_tags',
        'tags_vocab' => 'pece_tags',
        'collections_field' => 'field_pece_biblio_collection',
        'collections_vocab' => 'pece_biblio_collections',
        'notes_field' => 'biblio_notes',
        'use_feed_owner_as_author' => '1',
        'zotero_username_field_name' => 'field_zotero_username',
        'url_field' => NULL,
      ),
    ),
    'content_type' => 'zotero_feed',
    'update' => 0,
    'import_period' => '1800',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => FALSE,
  );
  $export['zotero_feed'] = $feeds_importer;

  return $export;
}

/**
 * Implements hook_defaultconfig_strongarm().
 */
function pece_biblio_defaultconfig_strongarm() {
  $export = array();

    $strongarm = new stdClass();
    $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
    $strongarm->api_version = 1;
    $strongarm->name = 'biblio_index';
    $strongarm->value = 1;
    $export['biblio_index'] = $strongarm;

    $strongarm = new stdClass();
    $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
    $strongarm->api_version = 1;
    $strongarm->name = 'biblio_search';
    $strongarm->value = 1;
    $export['biblio_search'] = $strongarm;

    $strongarm = new stdClass();
    $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
    $strongarm->api_version = 1;
    $strongarm->name = 'biblio_search_button_text';
    $strongarm->value = 'Search';
    $export['biblio_search_button_text'] = $strongarm;

    $strongarm = new stdClass();
    $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
    $strongarm->api_version = 1;
    $strongarm->name = 'biblio_node_layout';
    $strongarm->value = 'tabular';
    $export['biblio_node_layout'] = $strongarm;

    $strongarm = new stdClass();
    $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
    $strongarm->api_version = 1;
    $strongarm->name = 'biblio_show_openurl_profile_form';
    $strongarm->value = 0;
    $export['biblio_show_openurl_profile_form'] = $strongarm;

    $strongarm = new stdClass();
    $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
    $strongarm->api_version = 1;
    $strongarm->name = 'biblio_show_user_profile_form';
    $strongarm->value = 0;
    $export['biblio_show_user_profile_form'] = $strongarm;

    $strongarm = new stdClass();
    $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
    $strongarm->api_version = 1;
    $strongarm->name = 'biblio_style';
    $strongarm->value = 'chicago';
    $export['biblio_style'] = $strongarm;

    $strongarm = new stdClass();
    $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
    $strongarm->api_version = 1;
    $strongarm->name = 'biblio_sort';
    $strongarm->value = 'year';
    $export['biblio_sort'] = $strongarm;

    $strongarm = new stdClass();
    $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
    $strongarm->api_version = 1;
    $strongarm->name = 'biblio_sort_tabs';
    $strongarm->value = array(
      'author' => 'author',
      'title' => 'title',
      'type' => 'type',
      'year' => 'year',
      'keyword' => 0,
    );
    $export['biblio_sort_tabs'] = $strongarm;

    $strongarm = new stdClass();
    $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
    $strongarm->api_version = 1;
    $strongarm->name = 'biblio_sort_tabs_style';
    $strongarm->value = 1;
    $export['biblio_sort_tabs_style'] = $strongarm;

  return $export;
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function pece_biblio_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer biblio'.
  $permissions['administer biblio'] = array(
    'name' => 'administer biblio',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'biblio',
  );

  // Exported permission: 'create zotero_feed content'.
  $permissions['create zotero_feed content'] = array(
    'name' => 'create zotero_feed content',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own zotero_feed content'.
  $permissions['delete own zotero_feed content'] = array(
    'name' => 'delete own zotero_feed content',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own zotero_feed content'.
  $permissions['edit own zotero_feed content'] = array(
    'name' => 'edit own zotero_feed content',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'import zotero_feed feeds'.
  $permissions['import zotero_feed feeds'] = array(
    'name' => 'import zotero_feed feeds',
    'roles' => array(
      'Contributor' => 'Contributor',
      'Researcher' => 'Researcher',
      'administrator' => 'administrator',
    ),
    'module' => 'feeds',
  );

  // Exported permission: 'show filter tab'.
  $permissions['show filter tab'] = array(
    'name' => 'show filter tab',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'biblio',
  );

  // Exported permission: 'show sort links'.
  $permissions['show sort links'] = array(
    'name' => 'show sort links',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'biblio',
  );

  // Exported permission: 'show sort links'.
  $permissions['view full text'] = array(
    'name' => 'view full text',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'biblio',
  );

  return $permissions;
}
