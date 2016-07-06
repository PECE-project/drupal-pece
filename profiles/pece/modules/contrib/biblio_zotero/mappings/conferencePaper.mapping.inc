<?php
function biblio_zotero_get_field_mappings__conferencePaper() {
   return array(
      array(
         'source' => 'conferencePaper:abstractNote',
         'target' => 'biblio_abst_e',
         'unique' => FALSE,
         ),
      array(
         'source' => 'conferencePaper:accessDate',
         'target' => 'biblio_access_date',
         'unique' => FALSE,
         ),
      array(
         'source' => 'conferencePaper:archive',
         'target' => 'biblio_publisher',
         'unique' => FALSE,
         ),
      array(
         'source' => 'conferencePaper:archiveLocation',
         'target' => 'biblio_place_published',
         'unique' => FALSE,
         ),
      array(
         'source' => 'conferencePaper:callNumber',
         'target' => 'biblio_call_number',
         'unique' => FALSE,
         ),
      array(
         'source' => 'conferencePaper:conferenceName',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'conferencePaper:date',
         'target' => 'biblio_year',
         'unique' => FALSE,
         ),
      array(
         'source' => 'conferencePaper:DOI',
         'target' => 'biblio_doi',
         'unique' => FALSE,
         ),
      array(
         'source' => 'conferencePaper:extra',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'conferencePaper:ISBN',
         'target' => 'biblio_isbn',
         'unique' => FALSE,
         ),
      array(
         'source' => 'conferencePaper:language',
         'target' => 'biblio_lang',
         'unique' => FALSE,
         ),
      array(
         'source' => 'conferencePaper:libraryCatalog',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'conferencePaper:pages',
         'target' => 'biblio_pages',
         'unique' => FALSE,
         ),
      array(
         'source' => 'conferencePaper:place',
         'target' => 'biblio_place_published',
         'unique' => FALSE,
         ),
      array(
         'source' => 'conferencePaper:proceedingsTitle',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'conferencePaper:publisher',
         'target' => 'biblio_publisher',
         'unique' => FALSE,
         ),
      array(
         'source' => 'conferencePaper:rights',
         'target' => 'biblio_custom7',
         'unique' => FALSE,
         ),
      array(
         'source' => 'conferencePaper:series',
         'target' => 'biblio_secondary_title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'conferencePaper:shortTitle',
         'target' => 'biblio_short_title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'conferencePaper:title',
         'target' => 'title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'conferencePaper:url',
         'target' => 'biblio_url',
         'unique' => FALSE,
         ),
      array(
         'source' => 'conferencePaper:volume',
         'target' => 'biblio_volume',
         'unique' => FALSE,
         ),
      );
}