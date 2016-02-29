<?php

require_once drupal_get_path('module', 'kw_itemnames_entity') . '/kw_itemnames_entity.kw_itemnames.inc';

function kw_itemnames_file_kw_itemnames_type_info() {
  $result = array();

  $result['file'] = array(
    'item load callback' => 'kw_itemnames_file_item_load',
    'item create callback' => 'kw_itemnames_file_item_create',
    'item update callback' => 'kw_itemnames_file_item_update',
    'item delete callback' => 'kw_itemnames_file_item_delete',
    'item extract id callback' => 'kw_itemnames_file_item_extract_id',
  );

  return $result;
}

function kw_itemnames_file_item_load($fid) {
  $file = file_load($fid);
  return $file ? $file : FALSE;
}

function kw_itemnames_file_item_create($default, $required) {
  $file = (object) ($required + $default + array(
    'status' => FILE_STATUS_PERMANENT,
    'timestamp' => REQUEST_TIME,
  ));

  if (isset($file->source) && isset($file->destination)) {
    $dest = _kw_itemnames_file_download($file->source);
    $destination = file_unmanaged_copy($dest, $file->destination);
    $file->uri = $destination;
  }

  if (!isset($file->filename)) {
    $file->filename = basename($file->uri);
  }
  if (!isset($file->filemime)) {
    $file->filemime = file_get_mimetype($file->filename);
  }
  if (!isset($file->filesize)) {
    if ($info = image_get_info($file->uri)) {
      $file->filesize = $info['file_size'];
    }
  }

  file_save($file);

  return $file;
}

function kw_itemnames_file_item_update($file, $required) {
  if (isset($required['source'])) {
    $dest = _kw_itemnames_file_download($required['source']);
    $destination = isset($required['destination']) ? $required['destination'] : $file->uri;

    $old_md5 = md5_file($file->uri);
    $new_md5 = md5_file($dest);

    if ($old_md5 != $new_md5) {
      $destination = file_unmanaged_copy($dest, $destination);
      $file->uri = $destination;
    }
  }

  foreach ($required as $key => $value) {
    $file->{$key} = $value;
  }

  file_save($file);

  return $file;
}

function kw_itemnames_file_item_delete($fid) {
  $file = file_load($fid);
  file_delete($file);
}

function kw_itemnames_file_item_extract_id($file) {
  return $file->fid;
}

function _kw_itemnames_file_download($source) {
  $dest = tempnam(sys_get_temp_dir(), 'kwm-');
  $options = array(
    CURLOPT_FILE => fopen($dest, "wb"),
    CURLOPT_URL => $source,
  );

  $ch = curl_init();
  curl_setopt_array($ch, $options);
  curl_exec($ch);

  return $dest;
}
