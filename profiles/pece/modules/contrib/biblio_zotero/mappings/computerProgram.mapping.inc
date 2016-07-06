<?php
function biblio_zotero_get_field_mappings__computerProgram() {
   return array(
      array(
         'source' => 'computerProgram:abstractNote',
         'target' => 'biblio_abst_e',
         'unique' => FALSE,
         ),
      array(
         'source' => 'computerProgram:accessDate',
         'target' => 'biblio_access_date',
         'unique' => FALSE,
         ),
      array(
         'source' => 'computerProgram:archive',
         'target' => 'biblio_publisher',
         'unique' => FALSE,
         ),
      array(
         'source' => 'computerProgram:archiveLocation',
         'target' => 'biblio_place_published',
         'unique' => FALSE,
         ),
      array(
         'source' => 'computerProgram:callNumber',
         'target' => 'biblio_call_number',
         'unique' => FALSE,
         ),
      array(
         'source' => 'computerProgram:company',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'computerProgram:date',
         'target' => 'biblio_year',
         'unique' => FALSE,
         ),
      array(
         'source' => 'computerProgram:extra',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'computerProgram:ISBN',
         'target' => 'biblio_isbn',
         'unique' => FALSE,
         ),
      array(
         'source' => 'computerProgram:libraryCatalog',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'computerProgram:place',
         'target' => 'biblio_place_published',
         'unique' => FALSE,
         ),
      array(
         'source' => 'computerProgram:programmingLanguage',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'computerProgram:rights',
         'target' => 'biblio_custom7',
         'unique' => FALSE,
         ),
      array(
         'source' => 'computerProgram:series',
         'target' => 'biblio_secondary_title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'computerProgram:shortTitle',
         'target' => 'biblio_short_title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'computerProgram:system',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'computerProgram:title',
         'target' => 'title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'computerProgram:url',
         'target' => 'biblio_url',
         'unique' => FALSE,
         ),
      array(
         'source' => 'computerProgram:version',
         'target' => '',
         'unique' => FALSE,
         ),
      );
}