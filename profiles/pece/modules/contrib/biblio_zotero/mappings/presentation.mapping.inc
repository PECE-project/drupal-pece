<?php
function biblio_zotero_get_field_mappings__presentation() {
   return array(
      array(
         'source' => 'presentation:abstractNote',
         'target' => 'biblio_abst_e',
         'unique' => FALSE,
         ),
      array(
         'source' => 'presentation:accessDate',
         'target' => 'biblio_access_date',
         'unique' => FALSE,
         ),
      array(
         'source' => 'presentation:date',
         'target' => 'biblio_year',
         'unique' => FALSE,
         ),
      array(
         'source' => 'presentation:extra',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'presentation:language',
         'target' => 'biblio_lang',
         'unique' => FALSE,
         ),
      array(
         'source' => 'presentation:meetingName',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'presentation:place',
         'target' => 'biblio_place_published',
         'unique' => FALSE,
         ),
      array(
         'source' => 'presentation:presentationType',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'presentation:rights',
         'target' => 'biblio_custom7',
         'unique' => FALSE,
         ),
      array(
         'source' => 'presentation:shortTitle',
         'target' => 'biblio_short_title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'presentation:title',
         'target' => 'title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'presentation:url',
         'target' => 'biblio_url',
         'unique' => FALSE,
         ),
      );
}