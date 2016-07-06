<?php
function biblio_zotero_get_field_mappings__newspaperArticle() {
   return array(
      array(
         'source' => 'newspaperArticle:abstractNote',
         'target' => 'biblio_abst_e',
         'unique' => FALSE,
         ),
      array(
         'source' => 'newspaperArticle:accessDate',
         'target' => 'biblio_access_date',
         'unique' => FALSE,
         ),
      array(
         'source' => 'newspaperArticle:archive',
         'target' => 'biblio_publisher',
         'unique' => FALSE,
         ),
      array(
         'source' => 'newspaperArticle:archiveLocation',
         'target' => 'biblio_place_published',
         'unique' => FALSE,
         ),
      array(
         'source' => 'newspaperArticle:callNumber',
         'target' => 'biblio_call_number',
         'unique' => FALSE,
         ),
      array(
         'source' => 'newspaperArticle:date',
         'target' => 'biblio_year',
         'unique' => FALSE,
         ),
      array(
         'source' => 'newspaperArticle:edition',
         'target' => 'biblio_edition',
         'unique' => FALSE,
         ),
      array(
         'source' => 'newspaperArticle:extra',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'newspaperArticle:ISSN',
         'target' => 'biblio_issn',
         'unique' => FALSE,
         ),
      array(
         'source' => 'newspaperArticle:language',
         'target' => 'biblio_lang',
         'unique' => FALSE,
         ),
      array(
         'source' => 'newspaperArticle:libraryCatalog',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'newspaperArticle:pages',
         'target' => 'biblio_pages',
         'unique' => FALSE,
         ),
      array(
         'source' => 'newspaperArticle:place',
         'target' => 'biblio_place_published',
         'unique' => FALSE,
         ),
      array(
         'source' => 'newspaperArticle:publicationTitle',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'newspaperArticle:rights',
         'target' => 'biblio_custom7',
         'unique' => FALSE,
         ),
      array(
         'source' => 'newspaperArticle:section',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'newspaperArticle:shortTitle',
         'target' => 'biblio_short_title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'newspaperArticle:title',
         'target' => 'title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'newspaperArticle:url',
         'target' => 'biblio_url',
         'unique' => FALSE,
         ),
      );
}