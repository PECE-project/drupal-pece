<?php
function biblio_zotero_get_field_mappings__journalArticle() {
   return array(
      array(
         'source' => 'journalArticle:abstractNote',
         'target' => 'biblio_abst_e',
         'unique' => FALSE,
         ),
      array(
         'source' => 'journalArticle:accessDate',
         'target' => 'biblio_access_date',
         'unique' => FALSE,
         ),
      array(
         'source' => 'journalArticle:archive',
         'target' => 'biblio_publisher',
         'unique' => FALSE,
         ),
      array(
         'source' => 'journalArticle:archiveLocation',
         'target' => 'biblio_place_published',
         'unique' => FALSE,
         ),
      array(
         'source' => 'journalArticle:callNumber',
         'target' => 'biblio_call_number',
         'unique' => FALSE,
         ),
      array(
         'source' => 'journalArticle:date',
         'target' => 'biblio_year',
         'unique' => FALSE,
         ),
      array(
         'source' => 'journalArticle:DOI',
         'target' => 'biblio_doi',
         'unique' => FALSE,
         ),
      array(
         'source' => 'journalArticle:extra',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'journalArticle:ISSN',
         'target' => 'biblio_issn',
         'unique' => FALSE,
         ),
      array(
         'source' => 'journalArticle:issue',
         'target' => 'biblio_issue',
         'unique' => FALSE,
         ),
      array(
         'source' => 'journalArticle:journalAbbreviation',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'journalArticle:language',
         'target' => 'biblio_lang',
         'unique' => FALSE,
         ),
      array(
         'source' => 'journalArticle:libraryCatalog',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'journalArticle:pages',
         'target' => 'biblio_pages',
         'unique' => FALSE,
         ),
      array(
         'source' => 'journalArticle:publicationTitle',
         'target' => 'biblio_secondary_title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'journalArticle:rights',
         'target' => 'biblio_custom7',
         'unique' => FALSE,
         ),
      array(
         'source' => 'journalArticle:series',
         'target' => 'biblio_alternate_title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'journalArticle:seriesText',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'journalArticle:shortTitle',
         'target' => 'biblio_short_title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'journalArticle:title',
         'target' => 'title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'journalArticle:url',
         'target' => 'biblio_url',
         'unique' => FALSE,
         ),
      array(
         'source' => 'journalArticle:volume',
         'target' => 'biblio_volume',
         'unique' => FALSE,
         ),
      );
}