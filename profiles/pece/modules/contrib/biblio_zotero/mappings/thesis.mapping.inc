<?php
function biblio_zotero_get_field_mappings__thesis() {
   return array(
      array(
         'source' => 'thesis:abstractNote',
         'target' => 'biblio_abst_e',
         'unique' => FALSE,
         ),
      array(
         'source' => 'thesis:accessDate',
         'target' => 'biblio_access_date',
         'unique' => FALSE,
         ),
      array(
         'source' => 'thesis:archive',
         'target' => 'biblio_publisher',
         'unique' => FALSE,
         ),
      array(
         'source' => 'thesis:archiveLocation',
         'target' => 'biblio_place_published',
         'unique' => FALSE,
         ),
      array(
         'source' => 'thesis:callNumber',
         'target' => 'biblio_call_number',
         'unique' => FALSE,
         ),
      array(
         'source' => 'thesis:date',
         'target' => 'biblio_year',
         'unique' => FALSE,
         ),
      array(
         'source' => 'thesis:extra',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'thesis:language',
         'target' => 'biblio_lang',
         'unique' => FALSE,
         ),
      array(
         'source' => 'thesis:libraryCatalog',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'thesis:numPages',
         'target' => 'biblio_pages',
         'unique' => FALSE,
         ),
      array(
         'source' => 'thesis:place',
         'target' => 'biblio_place_published',
         'unique' => FALSE,
         ),
      array(
         'source' => 'thesis:rights',
         'target' => 'biblio_custom7',
         'unique' => FALSE,
         ),
      array(
         'source' => 'thesis:shortTitle',
         'target' => 'biblio_short_title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'thesis:thesisType',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'thesis:title',
         'target' => 'title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'thesis:university',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'thesis:url',
         'target' => 'biblio_url',
         'unique' => FALSE,
         ),
      );
}