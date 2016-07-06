<?php
function biblio_zotero_get_field_mappings__bill() {
   return array(
      array(
         'source' => 'bill:abstractNote',
         'target' => 'biblio_abst_e',
         'unique' => FALSE,
         ),
      array(
         'source' => 'bill:accessDate',
         'target' => 'biblio_access_date',
         'unique' => FALSE,
         ),
      array(
         'source' => 'bill:billNumber',
         'target' => 'biblio_number',
         'unique' => FALSE,
         ),
      array(
         'source' => 'bill:code',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'bill:codePages',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'bill:codeVolume',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'bill:date',
         'target' => 'biblio_year',
         'unique' => FALSE,
         ),
      array(
         'source' => 'bill:extra',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'bill:history',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'bill:language',
         'target' => 'biblio_lang',
         'unique' => FALSE,
         ),
      array(
         'source' => 'bill:legislativeBody',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'bill:rights',
         'target' => 'biblio_custom7',
         'unique' => FALSE,
         ),
      array(
         'source' => 'bill:section',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'bill:session',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'bill:shortTitle',
         'target' => 'biblio_short_title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'bill:title',
         'target' => 'title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'bill:url',
         'target' => 'biblio_url',
         'unique' => FALSE,
         ),
      );
}