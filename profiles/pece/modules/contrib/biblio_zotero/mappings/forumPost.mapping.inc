<?php
function biblio_zotero_get_field_mappings__forumPost() {
   return array(
      array(
         'source' => 'forumPost:abstractNote',
         'target' => 'biblio_abst_e',
         'unique' => FALSE,
         ),
      array(
         'source' => 'forumPost:accessDate',
         'target' => 'biblio_access_date',
         'unique' => FALSE,
         ),
      array(
         'source' => 'forumPost:date',
         'target' => 'biblio_year',
         'unique' => FALSE,
         ),
      array(
         'source' => 'forumPost:extra',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'forumPost:forumTitle',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'forumPost:language',
         'target' => 'biblio_lang',
         'unique' => FALSE,
         ),
      array(
         'source' => 'forumPost:postType',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'forumPost:rights',
         'target' => 'biblio_custom7',
         'unique' => FALSE,
         ),
      array(
         'source' => 'forumPost:shortTitle',
         'target' => 'biblio_short_title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'forumPost:title',
         'target' => 'title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'forumPost:url',
         'target' => 'biblio_url',
         'unique' => FALSE,
         ),
      );
}