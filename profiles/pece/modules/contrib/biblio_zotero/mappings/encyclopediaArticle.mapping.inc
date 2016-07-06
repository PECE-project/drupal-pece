<?php
function biblio_zotero_get_field_mappings__encyclopediaArticle() {
   return array(
      array(
         'source' => 'encyclopediaArticle:abstractNote',
         'target' => 'biblio_abst_e',
         'unique' => FALSE,
         ),
      array(
         'source' => 'encyclopediaArticle:accessDate',
         'target' => 'biblio_access_date',
         'unique' => FALSE,
         ),
      array(
         'source' => 'encyclopediaArticle:archive',
         'target' => 'biblio_publisher',
         'unique' => FALSE,
         ),
      array(
         'source' => 'encyclopediaArticle:archiveLocation',
         'target' => 'biblio_place_published',
         'unique' => FALSE,
         ),
      array(
         'source' => 'encyclopediaArticle:callNumber',
         'target' => 'biblio_call_number',
         'unique' => FALSE,
         ),
      array(
         'source' => 'encyclopediaArticle:date',
         'target' => 'biblio_year',
         'unique' => FALSE,
         ),
      array(
         'source' => 'encyclopediaArticle:edition',
         'target' => 'biblio_edition',
         'unique' => FALSE,
         ),
      array(
         'source' => 'encyclopediaArticle:encyclopediaTitle',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'encyclopediaArticle:extra',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'encyclopediaArticle:ISBN',
         'target' => 'biblio_isbn',
         'unique' => FALSE,
         ),
      array(
         'source' => 'encyclopediaArticle:language',
         'target' => 'biblio_lang',
         'unique' => FALSE,
         ),
      array(
         'source' => 'encyclopediaArticle:libraryCatalog',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'encyclopediaArticle:numberOfVolumes',
         'target' => 'biblio_number_of_volumes',
         'unique' => FALSE,
         ),
      array(
         'source' => 'encyclopediaArticle:pages',
         'target' => 'biblio_pages',
         'unique' => FALSE,
         ),
      array(
         'source' => 'encyclopediaArticle:place',
         'target' => 'biblio_place_published',
         'unique' => FALSE,
         ),
      array(
         'source' => 'encyclopediaArticle:publisher',
         'target' => 'biblio_publisher',
         'unique' => FALSE,
         ),
      array(
         'source' => 'encyclopediaArticle:rights',
         'target' => 'biblio_custom7',
         'unique' => FALSE,
         ),
      array(
         'source' => 'encyclopediaArticle:series',
         'target' => 'biblio_secondary_title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'encyclopediaArticle:seriesNumber',
         'target' => 'biblio_number',
         'unique' => FALSE,
         ),
      array(
         'source' => 'encyclopediaArticle:shortTitle',
         'target' => 'biblio_short_title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'encyclopediaArticle:title',
         'target' => 'title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'encyclopediaArticle:url',
         'target' => 'biblio_url',
         'unique' => FALSE,
         ),
      array(
         'source' => 'encyclopediaArticle:volume',
         'target' => 'biblio_volume',
         'unique' => FALSE,
         ),
      );
}