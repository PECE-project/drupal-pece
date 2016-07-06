<?php
function biblio_zotero_get_field_mappings__tvBroadcast() {
   return array(
      array(
         'source' => 'tvBroadcast:abstractNote',
         'target' => 'biblio_abst_e',
         'unique' => FALSE,
         ),
      array(
         'source' => 'tvBroadcast:accessDate',
         'target' => 'biblio_access_date',
         'unique' => FALSE,
         ),
      array(
         'source' => 'tvBroadcast:archive',
         'target' => 'biblio_publisher',
         'unique' => FALSE,
         ),
      array(
         'source' => 'tvBroadcast:archiveLocation',
         'target' => 'biblio_place_published',
         'unique' => FALSE,
         ),
      array(
         'source' => 'tvBroadcast:callNumber',
         'target' => 'biblio_call_number',
         'unique' => FALSE,
         ),
      array(
         'source' => 'tvBroadcast:date',
         'target' => 'biblio_year',
         'unique' => FALSE,
         ),
      array(
         'source' => 'tvBroadcast:episodeNumber',
         'target' => 'biblio_number',
         'unique' => FALSE,
         ),
      array(
         'source' => 'tvBroadcast:extra',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'tvBroadcast:language',
         'target' => 'biblio_lang',
         'unique' => FALSE,
         ),
      array(
         'source' => 'tvBroadcast:libraryCatalog',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'tvBroadcast:network',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'tvBroadcast:place',
         'target' => 'biblio_place_published',
         'unique' => FALSE,
         ),
      array(
         'source' => 'tvBroadcast:programTitle',
         'target' => 'biblio_secondary_title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'tvBroadcast:rights',
         'target' => 'biblio_custom7',
         'unique' => FALSE,
         ),
      array(
         'source' => 'tvBroadcast:runningTime',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'tvBroadcast:shortTitle',
         'target' => 'biblio_short_title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'tvBroadcast:title',
         'target' => 'title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'tvBroadcast:url',
         'target' => 'biblio_url',
         'unique' => FALSE,
         ),
      array(
         'source' => 'tvBroadcast:videoRecordingFormat',
         'target' => '',
         'unique' => FALSE,
         ),
      );
}