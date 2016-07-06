<?php
function biblio_zotero_get_field_mappings__instantMessage() {
   return array(
      array(
         'source' => 'instantMessage:abstractNote',
         'target' => 'biblio_abst_e',
         'unique' => FALSE,
         ),
      array(
         'source' => 'instantMessage:accessDate',
         'target' => 'biblio_access_date',
         'unique' => FALSE,
         ),
      array(
         'source' => 'instantMessage:date',
         'target' => 'biblio_year',
         'unique' => FALSE,
         ),
      array(
         'source' => 'instantMessage:extra',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'instantMessage:language',
         'target' => 'biblio_lang',
         'unique' => FALSE,
         ),
      array(
         'source' => 'instantMessage:rights',
         'target' => 'biblio_custom7',
         'unique' => FALSE,
         ),
      array(
         'source' => 'instantMessage:shortTitle',
         'target' => 'biblio_short_title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'instantMessage:title',
         'target' => 'title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'instantMessage:url',
         'target' => 'biblio_url',
         'unique' => FALSE,
         ),
      );
}