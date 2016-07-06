<?php
function biblio_zotero_get_field_mappings__letter() {
   return array(
      array(
         'source' => 'letter:abstractNote',
         'target' => 'biblio_abst_e',
         'unique' => FALSE,
         ),
      array(
         'source' => 'letter:accessDate',
         'target' => 'biblio_access_date',
         'unique' => FALSE,
         ),
      array(
         'source' => 'letter:archive',
         'target' => 'biblio_publisher',
         'unique' => FALSE,
         ),
      array(
         'source' => 'letter:archiveLocation',
         'target' => 'biblio_place_published',
         'unique' => FALSE,
         ),
      array(
         'source' => 'letter:callNumber',
         'target' => 'biblio_call_number',
         'unique' => FALSE,
         ),
      array(
         'source' => 'letter:date',
         'target' => 'biblio_year',
         'unique' => FALSE,
         ),
      array(
         'source' => 'letter:extra',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'letter:language',
         'target' => 'biblio_lang',
         'unique' => FALSE,
         ),
      array(
         'source' => 'letter:letterType',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'letter:libraryCatalog',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'letter:rights',
         'target' => 'biblio_custom7',
         'unique' => FALSE,
         ),
      array(
         'source' => 'letter:shortTitle',
         'target' => 'biblio_short_title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'letter:title',
         'target' => 'title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'letter:url',
         'target' => 'biblio_url',
         'unique' => FALSE,
         ),
      );
}