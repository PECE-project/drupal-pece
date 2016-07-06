<?php
function biblio_zotero_get_field_mappings__film() {
   return array(
      array(
         'source' => 'film:abstractNote',
         'target' => 'biblio_abst_e',
         'unique' => FALSE,
         ),
      array(
         'source' => 'film:accessDate',
         'target' => 'biblio_access_date',
         'unique' => FALSE,
         ),
      array(
         'source' => 'film:archive',
         'target' => 'biblio_publisher',
         'unique' => FALSE,
         ),
      array(
         'source' => 'film:archiveLocation',
         'target' => 'biblio_place_published',
         'unique' => FALSE,
         ),
      array(
         'source' => 'film:callNumber',
         'target' => 'biblio_call_number',
         'unique' => FALSE,
         ),
      array(
         'source' => 'film:date',
         'target' => 'biblio_year',
         'unique' => FALSE,
         ),
      array(
         'source' => 'film:distributor',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'film:extra',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'film:genre',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'film:language',
         'target' => 'biblio_lang',
         'unique' => FALSE,
         ),
      array(
         'source' => 'film:libraryCatalog',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'film:rights',
         'target' => 'biblio_custom7',
         'unique' => FALSE,
         ),
      array(
         'source' => 'film:runningTime',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'film:shortTitle',
         'target' => 'biblio_short_title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'film:title',
         'target' => 'title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'film:url',
         'target' => 'biblio_url',
         'unique' => FALSE,
         ),
      array(
         'source' => 'film:videoRecordingFormat',
         'target' => '',
         'unique' => FALSE,
         ),
      );
}