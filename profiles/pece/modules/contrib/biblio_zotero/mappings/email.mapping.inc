<?php
function biblio_zotero_get_field_mappings__email() {
   return array(
      array(
         'source' => 'email:abstractNote',
         'target' => 'biblio_abst_e',
         'unique' => FALSE,
         ),
      array(
         'source' => 'email:accessDate',
         'target' => 'biblio_access_date',
         'unique' => FALSE,
         ),
      array(
         'source' => 'email:date',
         'target' => 'biblio_year',
         'unique' => FALSE,
         ),
      array(
         'source' => 'email:extra',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'email:language',
         'target' => 'biblio_lang',
         'unique' => FALSE,
         ),
      array(
         'source' => 'email:rights',
         'target' => 'biblio_custom7',
         'unique' => FALSE,
         ),
      array(
         'source' => 'email:shortTitle',
         'target' => 'biblio_short_title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'email:subject',
         'target' => 'title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'email:url',
         'target' => 'biblio_url',
         'unique' => FALSE,
         ),
      );
}