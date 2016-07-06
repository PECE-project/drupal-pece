<?php
function biblio_zotero_get_field_mappings__hearing() {
   return array(
      array(
         'source' => 'hearing:abstractNote',
         'target' => 'biblio_abst_e',
         'unique' => FALSE,
         ),
      array(
         'source' => 'hearing:accessDate',
         'target' => 'biblio_access_date',
         'unique' => FALSE,
         ),
      array(
         'source' => 'hearing:committee',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'hearing:date',
         'target' => 'biblio_year',
         'unique' => FALSE,
         ),
      array(
         'source' => 'hearing:documentNumber',
         'target' => 'biblio_number',
         'unique' => FALSE,
         ),
      array(
         'source' => 'hearing:extra',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'hearing:history',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'hearing:language',
         'target' => 'biblio_lang',
         'unique' => FALSE,
         ),
      array(
         'source' => 'hearing:legislativeBody',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'hearing:numberOfVolumes',
         'target' => 'biblio_number_of_volumes',
         'unique' => FALSE,
         ),
      array(
         'source' => 'hearing:pages',
         'target' => 'biblio_pages',
         'unique' => FALSE,
         ),
      array(
         'source' => 'hearing:place',
         'target' => 'biblio_place_published',
         'unique' => FALSE,
         ),
      array(
         'source' => 'hearing:publisher',
         'target' => 'biblio_publisher',
         'unique' => FALSE,
         ),
      array(
         'source' => 'hearing:rights',
         'target' => 'biblio_custom7',
         'unique' => FALSE,
         ),
      array(
         'source' => 'hearing:session',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'hearing:shortTitle',
         'target' => 'biblio_short_title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'hearing:title',
         'target' => 'title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'hearing:url',
         'target' => 'biblio_url',
         'unique' => FALSE,
         ),
      );
}