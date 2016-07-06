<?php
function biblio_zotero_get_field_mappings__podcast() {
   return array(
      array(
         'source' => 'podcast:abstractNote',
         'target' => 'biblio_abst_e',
         'unique' => FALSE,
         ),
      array(
         'source' => 'podcast:accessDate',
         'target' => 'biblio_access_date',
         'unique' => FALSE,
         ),
      array(
         'source' => 'podcast:audioFileType',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'podcast:episodeNumber',
         'target' => 'biblio_number',
         'unique' => FALSE,
         ),
      array(
         'source' => 'podcast:extra',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'podcast:language',
         'target' => 'biblio_lang',
         'unique' => FALSE,
         ),
      array(
         'source' => 'podcast:rights',
         'target' => 'biblio_custom7',
         'unique' => FALSE,
         ),
      array(
         'source' => 'podcast:runningTime',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'podcast:series',
         'target' => 'biblio_secondary_title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'podcast:shortTitle',
         'target' => 'biblio_short_title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'podcast:title',
         'target' => 'title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'podcast:url',
         'target' => 'biblio_url',
         'unique' => FALSE,
         ),
      );
}