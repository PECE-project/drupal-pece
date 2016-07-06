<?php
function biblio_zotero_get_field_mappings__blogPost() {
   return array(
      array(
         'source' => 'blogPost:abstractNote',
         'target' => 'biblio_abst_e',
         'unique' => FALSE,
         ),
      array(
         'source' => 'blogPost:accessDate',
         'target' => 'biblio_access_date',
         'unique' => FALSE,
         ),
      array(
         'source' => 'blogPost:blogTitle',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'blogPost:date',
         'target' => 'biblio_year',
         'unique' => FALSE,
         ),
      array(
         'source' => 'blogPost:extra',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'blogPost:language',
         'target' => 'biblio_lang',
         'unique' => FALSE,
         ),
      array(
         'source' => 'blogPost:rights',
         'target' => 'biblio_custom7',
         'unique' => FALSE,
         ),
      array(
         'source' => 'blogPost:shortTitle',
         'target' => 'biblio_short_title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'blogPost:title',
         'target' => 'title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'blogPost:url',
         'target' => 'biblio_url',
         'unique' => FALSE,
         ),
      array(
         'source' => 'blogPost:websiteType',
         'target' => '',
         'unique' => FALSE,
         ),
      );
}