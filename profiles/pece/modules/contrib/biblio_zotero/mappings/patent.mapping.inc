<?php
function biblio_zotero_get_field_mappings__patent() {
   return array(
      array(
         'source' => 'patent:abstractNote',
         'target' => 'biblio_abst_e',
         'unique' => FALSE,
         ),
      array(
         'source' => 'patent:accessDate',
         'target' => 'biblio_access_date',
         'unique' => FALSE,
         ),
      array(
         'source' => 'patent:applicationNumber',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'patent:assignee',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'patent:country',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'patent:extra',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'patent:filingDate',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'patent:issueDate',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'patent:issuingAuthority',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'patent:language',
         'target' => 'biblio_lang',
         'unique' => FALSE,
         ),
      array(
         'source' => 'patent:legalStatus',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'patent:pages',
         'target' => 'biblio_pages',
         'unique' => FALSE,
         ),
      array(
         'source' => 'patent:patentNumber',
         'target' => 'biblio_number',
         'unique' => FALSE,
         ),
      array(
         'source' => 'patent:place',
         'target' => 'biblio_place_published',
         'unique' => FALSE,
         ),
      array(
         'source' => 'patent:priorityNumbers',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'patent:references',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'patent:rights',
         'target' => 'biblio_custom7',
         'unique' => FALSE,
         ),
      array(
         'source' => 'patent:shortTitle',
         'target' => 'biblio_short_title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'patent:title',
         'target' => 'title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'patent:url',
         'target' => 'biblio_url',
         'unique' => FALSE,
         ),
      );
}