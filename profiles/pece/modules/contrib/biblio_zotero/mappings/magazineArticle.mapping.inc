<?php
function biblio_zotero_get_field_mappings__magazineArticle() {
   return array(
      array(
         'source' => 'magazineArticle:abstractNote',
         'target' => 'biblio_abst_e',
         'unique' => FALSE,
         ),
      array(
         'source' => 'magazineArticle:accessDate',
         'target' => 'biblio_access_date',
         'unique' => FALSE,
         ),
      array(
         'source' => 'magazineArticle:archive',
         'target' => 'biblio_publisher',
         'unique' => FALSE,
         ),
      array(
         'source' => 'magazineArticle:archiveLocation',
         'target' => 'biblio_place_published',
         'unique' => FALSE,
         ),
      array(
         'source' => 'magazineArticle:callNumber',
         'target' => 'biblio_call_number',
         'unique' => FALSE,
         ),
      array(
         'source' => 'magazineArticle:date',
         'target' => 'biblio_year',
         'unique' => FALSE,
         ),
      array(
         'source' => 'magazineArticle:extra',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'magazineArticle:ISSN',
         'target' => 'biblio_issn',
         'unique' => FALSE,
         ),
      array(
         'source' => 'magazineArticle:issue',
         'target' => 'biblio_issue',
         'unique' => FALSE,
         ),
      array(
         'source' => 'magazineArticle:language',
         'target' => 'biblio_lang',
         'unique' => FALSE,
         ),
      array(
         'source' => 'magazineArticle:libraryCatalog',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'magazineArticle:pages',
         'target' => 'biblio_pages',
         'unique' => FALSE,
         ),
      array(
         'source' => 'magazineArticle:publicationTitle',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'magazineArticle:rights',
         'target' => 'biblio_custom7',
         'unique' => FALSE,
         ),
      array(
         'source' => 'magazineArticle:shortTitle',
         'target' => 'biblio_short_title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'magazineArticle:title',
         'target' => 'title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'magazineArticle:url',
         'target' => 'biblio_url',
         'unique' => FALSE,
         ),
      array(
         'source' => 'magazineArticle:volume',
         'target' => 'biblio_volume',
         'unique' => FALSE,
         ),
      );
}