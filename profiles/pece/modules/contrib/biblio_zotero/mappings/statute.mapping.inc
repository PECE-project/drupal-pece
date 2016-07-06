<?php
function biblio_zotero_get_field_mappings__statute() {
   return array(
      array(
         'source' => 'statute:abstractNote',
         'target' => 'biblio_abst_e',
         'unique' => FALSE,
         ),
      array(
         'source' => 'statute:accessDate',
         'target' => 'biblio_access_date',
         'unique' => FALSE,
         ),
      array(
         'source' => 'statute:code',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'statute:codeNumber',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'statute:dateEnacted',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'statute:extra',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'statute:history',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'statute:language',
         'target' => 'biblio_lang',
         'unique' => FALSE,
         ),
      array(
         'source' => 'statute:nameOfAct',
         'target' => 'title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'statute:pages',
         'target' => 'biblio_pages',
         'unique' => FALSE,
         ),
      array(
         'source' => 'statute:publicLawNumber',
         'target' => 'biblio_number',
         'unique' => FALSE,
         ),
      array(
         'source' => 'statute:rights',
         'target' => 'biblio_custom7',
         'unique' => FALSE,
         ),
      array(
         'source' => 'statute:section',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'statute:session',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'statute:shortTitle',
         'target' => 'biblio_short_title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'statute:url',
         'target' => 'biblio_url',
         'unique' => FALSE,
         ),
      );
}