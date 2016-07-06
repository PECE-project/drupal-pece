<?php
function biblio_zotero_get_field_mappings__attachment() {
   return array(
      array(
         'source' => 'attachment:accessDate',
         'target' => 'biblio_access_date',
         'unique' => FALSE,
         ),
      array(
         'source' => 'attachment:title',
         'target' => 'title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'attachment:url',
         'target' => 'biblio_url',
         'unique' => FALSE,
         ),
      );
}