<?php
function biblio_zotero_get_field_mappings__case() {
   return array(
      array(
         'source' => 'case:abstractNote',
         'target' => 'biblio_abst_e',
         'unique' => FALSE,
         ),
      array(
         'source' => 'case:accessDate',
         'target' => 'biblio_access_date',
         'unique' => FALSE,
         ),
      array(
         'source' => 'case:caseName',
         'target' => 'title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'case:court',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'case:dateDecided',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'case:docketNumber',
         'target' => 'biblio_number',
         'unique' => FALSE,
         ),
      array(
         'source' => 'case:extra',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'case:firstPage',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'case:history',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'case:language',
         'target' => 'biblio_lang',
         'unique' => FALSE,
         ),
      array(
         'source' => 'case:reporter',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'case:reporterVolume',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'case:rights',
         'target' => 'biblio_custom7',
         'unique' => FALSE,
         ),
      array(
         'source' => 'case:shortTitle',
         'target' => 'biblio_short_title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'case:url',
         'target' => 'biblio_url',
         'unique' => FALSE,
         ),
      );
}