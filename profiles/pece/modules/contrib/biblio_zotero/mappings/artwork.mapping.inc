<?php
function biblio_zotero_get_field_mappings__artwork() {
   return array(
      array(
         'source' => 'artwork:abstractNote',
         'target' => 'biblio_abst_e',
         'unique' => FALSE,
         ),
      array(
         'source' => 'artwork:accessDate',
         'target' => 'biblio_access_date',
         'unique' => FALSE,
         ),
      array(
         'source' => 'artwork:archive',
         'target' => 'biblio_publisher',
         'unique' => FALSE,
         ),
      array(
         'source' => 'artwork:archiveLocation',
         'target' => 'biblio_place_published',
         'unique' => FALSE,
         ),
      array(
         'source' => 'artwork:artworkMedium',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'artwork:artworkSize',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'artwork:callNumber',
         'target' => 'biblio_call_number',
         'unique' => FALSE,
         ),
      array(
         'source' => 'artwork:date',
         'target' => 'biblio_year',
         'unique' => FALSE,
         ),
      array(
         'source' => 'artwork:extra',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'artwork:language',
         'target' => 'biblio_lang',
         'unique' => FALSE,
         ),
      array(
         'source' => 'artwork:libraryCatalog',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'artwork:rights',
         'target' => 'biblio_custom7',
         'unique' => FALSE,
         ),
      array(
         'source' => 'artwork:shortTitle',
         'target' => 'biblio_short_title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'artwork:title',
         'target' => 'title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'artwork:url',
         'target' => 'biblio_url',
         'unique' => FALSE,
         ),
      );
}