<?php
function biblio_zotero_get_field_mappings__interview() {
   return array(
      array(
         'source' => 'interview:abstractNote',
         'target' => 'biblio_abst_e',
         'unique' => FALSE,
         ),
      array(
         'source' => 'interview:accessDate',
         'target' => 'biblio_access_date',
         'unique' => FALSE,
         ),
      array(
         'source' => 'interview:archive',
         'target' => 'biblio_publisher',
         'unique' => FALSE,
         ),
      array(
         'source' => 'interview:archiveLocation',
         'target' => 'biblio_place_published',
         'unique' => FALSE,
         ),
      array(
         'source' => 'interview:callNumber',
         'target' => 'biblio_call_number',
         'unique' => FALSE,
         ),
      array(
         'source' => 'interview:date',
         'target' => 'biblio_year',
         'unique' => FALSE,
         ),
      array(
         'source' => 'interview:extra',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'interview:interviewMedium',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'interview:language',
         'target' => 'biblio_lang',
         'unique' => FALSE,
         ),
      array(
         'source' => 'interview:libraryCatalog',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'interview:rights',
         'target' => 'biblio_custom7',
         'unique' => FALSE,
         ),
      array(
         'source' => 'interview:shortTitle',
         'target' => 'biblio_short_title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'interview:title',
         'target' => 'title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'interview:url',
         'target' => 'biblio_url',
         'unique' => FALSE,
         ),
      );
}