<?php
function biblio_zotero_get_field_mappings__webpage() {
   return array(
      array(
         'source' => 'webpage:abstractNote',
         'target' => 'biblio_abst_e',
         'unique' => FALSE,
         ),
      array(
         'source' => 'webpage:accessDate',
         'target' => 'biblio_access_date',
         'unique' => FALSE,
         ),
      array(
         'source' => 'webpage:date',
         'target' => 'biblio_year',
         'unique' => FALSE,
         ),
      array(
         'source' => 'webpage:extra',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'webpage:language',
         'target' => 'biblio_lang',
         'unique' => FALSE,
         ),
      array(
         'source' => 'webpage:rights',
         'target' => 'biblio_custom7',
         'unique' => FALSE,
         ),
      array(
         'source' => 'webpage:shortTitle',
         'target' => 'biblio_short_title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'webpage:title',
         'target' => 'title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'webpage:url',
         'target' => 'biblio_url',
         'unique' => FALSE,
         ),
      array(
         'source' => 'webpage:websiteTitle',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'webpage:websiteType',
         'target' => 'biblio_type_of_work',
         'unique' => FALSE,
         ),
      );
}