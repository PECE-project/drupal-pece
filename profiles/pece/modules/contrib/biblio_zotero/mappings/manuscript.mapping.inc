<?php
function biblio_zotero_get_field_mappings__manuscript() {
   return array(
      array(
         'source' => 'manuscript:abstractNote',
         'target' => 'biblio_abst_e',
         'unique' => FALSE,
         ),
      array(
         'source' => 'manuscript:accessDate',
         'target' => 'biblio_access_date',
         'unique' => FALSE,
         ),
      array(
         'source' => 'manuscript:archive',
         'target' => 'biblio_publisher',
         'unique' => FALSE,
         ),
      array(
         'source' => 'manuscript:archiveLocation',
         'target' => 'biblio_place_published',
         'unique' => FALSE,
         ),
      array(
         'source' => 'manuscript:callNumber',
         'target' => 'biblio_call_number',
         'unique' => FALSE,
         ),
      array(
         'source' => 'manuscript:date',
         'target' => 'biblio_year',
         'unique' => FALSE,
         ),
      array(
         'source' => 'manuscript:extra',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'manuscript:language',
         'target' => 'biblio_lang',
         'unique' => FALSE,
         ),
      array(
         'source' => 'manuscript:libraryCatalog',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'manuscript:manuscriptType',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'manuscript:numPages',
         'target' => 'biblio_pages',
         'unique' => FALSE,
         ),
      array(
         'source' => 'manuscript:place',
         'target' => 'biblio_place_published',
         'unique' => FALSE,
         ),
      array(
         'source' => 'manuscript:rights',
         'target' => 'biblio_custom7',
         'unique' => FALSE,
         ),
      array(
         'source' => 'manuscript:shortTitle',
         'target' => 'biblio_short_title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'manuscript:title',
         'target' => 'title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'manuscript:url',
         'target' => 'biblio_url',
         'unique' => FALSE,
         ),
      );
}