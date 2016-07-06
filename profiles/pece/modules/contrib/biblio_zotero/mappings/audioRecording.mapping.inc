<?php
function biblio_zotero_get_field_mappings__audioRecording() {
   return array(
      array(
         'source' => 'audioRecording:abstractNote',
         'target' => 'biblio_abst_e',
         'unique' => FALSE,
         ),
      array(
         'source' => 'audioRecording:accessDate',
         'target' => 'biblio_access_date',
         'unique' => FALSE,
         ),
      array(
         'source' => 'audioRecording:archive',
         'target' => 'biblio_publisher',
         'unique' => FALSE,
         ),
      array(
         'source' => 'audioRecording:archiveLocation',
         'target' => 'biblio_place_published',
         'unique' => FALSE,
         ),
      array(
         'source' => 'audioRecording:audioRecordingFormat',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'audioRecording:callNumber',
         'target' => 'biblio_call_number',
         'unique' => FALSE,
         ),
      array(
         'source' => 'audioRecording:date',
         'target' => 'biblio_year',
         'unique' => FALSE,
         ),
      array(
         'source' => 'audioRecording:extra',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'audioRecording:ISBN',
         'target' => 'biblio_isbn',
         'unique' => FALSE,
         ),
      array(
         'source' => 'audioRecording:label',
         'target' => 'biblio_label',
         'unique' => FALSE,
         ),
      array(
         'source' => 'audioRecording:language',
         'target' => 'biblio_lang',
         'unique' => FALSE,
         ),
      array(
         'source' => 'audioRecording:libraryCatalog',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'audioRecording:numberOfVolumes',
         'target' => 'biblio_number_of_volumes',
         'unique' => FALSE,
         ),
      array(
         'source' => 'audioRecording:place',
         'target' => 'biblio_place_published',
         'unique' => FALSE,
         ),
      array(
         'source' => 'audioRecording:rights',
         'target' => 'biblio_custom7',
         'unique' => FALSE,
         ),
      array(
         'source' => 'audioRecording:runningTime',
         'target' => '',
         'unique' => FALSE,
         ),
      array(
         'source' => 'audioRecording:series',
         'target' => 'biblio_secondary_title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'audioRecording:shortTitle',
         'target' => 'biblio_short_title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'audioRecording:title',
         'target' => 'title',
         'unique' => FALSE,
         ),
      array(
         'source' => 'audioRecording:url',
         'target' => 'biblio_url',
         'unique' => FALSE,
         ),
      array(
         'source' => 'audioRecording:volume',
         'target' => 'biblio_volume',
         'unique' => FALSE,
         ),
      );
}