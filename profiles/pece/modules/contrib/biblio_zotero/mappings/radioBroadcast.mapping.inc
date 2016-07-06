<?php
function biblio_zotero_get_field_mappings__radioBroadcast() {
   return array(
      array(
         'source' => 'radioBroadcast:abstractNote',
         'target' => 'biblio_abst_e',
         'unique' => FALSE,
         ),
      array(
         'source' => 'radioBroadcast:accessDate',
         'target' => 'biblio_access_date',
         'unique' => FALSE,
         ),
      array(
         'source' => 'radioBroadcast:archive',
         'target' => 'biblio_publisher',
         'unique' => FALSE,
         ),
      array(
         'source' => 'radioBroadcast:archiveLocation',
         'target' => 'biblio_place_published',
         'unique' => FALSE,
         ),
      array(
         'source' => 'radioBroadcast:audioRecordingFormat',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'radioBroadcast:callNumber',
         'target' => 'biblio_call_number',
         'unique' => FALSE,
         ),
      array(
         'source' => 'radioBroadcast:date',
         'target' => 'biblio_year',
         'unique' => FALSE,
         ),
      array(
         'source' => 'radioBroadcast:episodeNumber',
         'target' => 'biblio_number',
         'unique' => FALSE,
         ),
      array(
         'source' => 'radioBroadcast:extra',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'radioBroadcast:language',
         'target' => 'biblio_lang',
         'unique' => FALSE,
         ),
      array(
         'source' => 'radioBroadcast:libraryCatalog',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'radioBroadcast:network',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'radioBroadcast:place',
         'target' => 'biblio_place_published',
         'unique' => FALSE,
         ),
      array(
         'source' => 'radioBroadcast:programTitle',
         'target' => 'biblio_secondary_title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'radioBroadcast:rights',
         'target' => 'biblio_custom7',
         'unique' => FALSE,
         ),
      array(
         'source' => 'radioBroadcast:runningTime',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'radioBroadcast:shortTitle',
         'target' => 'biblio_short_title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'radioBroadcast:title',
         'target' => 'title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'radioBroadcast:url',
         'target' => 'biblio_url',
         'unique' => FALSE,
         ),
      );
}