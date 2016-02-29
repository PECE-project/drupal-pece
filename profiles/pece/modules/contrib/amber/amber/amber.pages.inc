<?php

function amber_dashboard_summary_form() {

  $header = array(t("Global Statistics"),"");
  $rows = array();
  $rows[] = array(t('Snapshots preserved'), _amber_cache_size());
  $rows[] = array(t('Links to snapshot'), _amber_queue_size(AMBER_QUEUE_CHECK_NEW) + _amber_queue_size(AMBER_QUEUE_CHECK_EXISTING));
  $rows[] = array(t('Last check'), _amber_last_run(AMBER_VAR_LAST_CHECK_RUN));
  $rows[] = array(t('Disk space used'), _amber_disk_usage());

  $build['amber_summary_table'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
  );

  $build['buttons']['clear'] = array(
    '#type' => 'submit',
    '#value' => t('Delete all snapshots'),
    '#submit' => array('amber_dashboard_summary_form_clear')
  );
  $build['buttons']['cache'] = array(
    '#type' => 'submit',
    '#value' => t('Scan content for links to preserve'),
    '#submit' => array('amber_dashboard_summary_form_scan')
  );
  $build['buttons']['cache_now'] = array(
    '#type' => 'submit',
    '#value' => t('Preserve all new links'),
    '#submit' => array('amber_dashboard_summary_form_cache')
  );

  if (!variable_get('amber_content_scanned', 0) && (_amber_queue_size(AMBER_QUEUE_CHECK_NEW) == 0)) {
    drupal_set_message(t('You should scan all existing content for links to preserve'),'warning',FALSE);
  }

  return $build;
}

function _amber_get_view_link($row) {
  $p = isset($row['provider']) ? $row['provider'] : AMBER_BACKEND_LOCAL;
  switch ($p) {
    case AMBER_BACKEND_PERMA:
      return l('View on Perma', $row['location']);
      break;
    case AMBER_BACKEND_INTERNET_ARCHIVE:
      return l('View on Internet Archive', $row['location']);
      break;
    case AMBER_BACKEND_LOCAL:
    case AMBER_BACKEND_AMAZON_S3:
      return isset($row['size']) ? l('View', $row['location']) : "";
      break;
  } 
}

function _amber_get_size_column($row) {
  $p = isset($row['provider']) ? $row['provider'] : AMBER_BACKEND_LOCAL;
  $size = isset($row['size']) ? format_size($row['size']) : (isset($row['message']) ? $row['message'] : "");
  switch ($p) {
    case AMBER_BACKEND_PERMA:
      return "";
      break;
    case AMBER_BACKEND_INTERNET_ARCHIVE:
    case AMBER_BACKEND_AMAZON_S3:
    case AMBER_BACKEND_LOCAL:
      return $size;
      break;
  } 
}

function _amber_get_method_column($row) {
  $p = isset($row['provider']) ? $row['provider'] : "";
  if (!isset($row['size'])) {
    return "";
  }
  switch ($p) {
    case AMBER_BACKEND_PERMA:
      return "Perma";
      break;
    case AMBER_BACKEND_INTERNET_ARCHIVE:
      return "Internet Archive";
      break;
    case AMBER_BACKEND_AMAZON_S3:
      return "Amazon S3";
      break;
    case AMBER_BACKEND_LOCAL:
      return "Local storage";
      break;
  } 
}

function amber_dashboard_detail_form() {

  $build = array();
  $header = array(
    array('data' => t('Site'), 'field' => 'url_sort'),
    array('data' => t('URL'), 'field' => 'url_sort'),
    array('data' => t('Status'), 'field' => 'status'),
    array('data' => t('Last checked'), 'field' => 'last_checked', 'sort' => 'desc'),
    array('data' => t('Date preserved'), 'field' => 'ca.date'),
    array('data' => t('Size'), 'field' => 'ca.size' ),
    array('data' => t('Last viewed'), 'field' => 'a.date' ),
    array('data' => t('Total views'), 'field' => 'a.views' ),
    array('data' => t('Storage method'),),
    array('data' => t(''),  ),
    array('data' => t(''),  ),
  );

  $query = _amber_dashboard_detail_query();
  $query = $query->extend('PagerDefault');
  $query = $query->extend('TableSort');
  $query = $query->limit(20);
  $query = $query->orderByHeader($header);
  $result = $query->execute();

  $rows = array();
  while ($r = $result->fetchAssoc()) {
    $host = parse_url($r['url'],PHP_URL_HOST);
    $rows[] = array(
      'data' => array(
        'site' => "$host (" . l('Blacklist', 'admin/reports/amber/blacklist/' . $host, array('query' => array('destination' => current_path()))) . ")",
        'url' => l($r['url'], $r['url']),
        'status' => $r['status'] ? t('Up') : t('Down'),
        'last_checked' => isset($r['last_checked']) ? format_date($r['last_checked']) : "",
        'date' => isset($r['date']) ? format_date($r['date']) : "",
        'size' => _amber_get_size_column($r),
        'a.date' => isset($r['a_date']) ? format_date($r['a_date']) : "",
        'views' => isset($r['views']) ? $r['views'] : "",
        'method' => _amber_get_method_column($r),
        'view' => _amber_get_view_link($r),
        'delete' => l('Delete', 'admin/reports/amber/delete/' . $r['id'] . "/" . $r['provider'], array('query' => array('destination' => current_path()))),
      ),
      'data-url' => $r['url']);
  }

  // add the content
  $build['amber_detail_table'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
  );
  // Add the pager
  $build['pager'] = array(
    '#theme' => 'pager',
    '#weight' => 5,
  );

  $build['buttons']['export'] = array(
    '#type' => 'submit',
    '#value' => t('Export as CSV'),
    '#submit' => array('amber_dashboard_detail_form_export')
  );

  return $build;
}

function _amber_cache_size() {
  $result = db_query("SELECT COUNT(*) FROM amber_cache")->fetchCol();
  return $result[0];
}

function _amber_queue_size($q) {
  $queue = DrupalQueue::get($q);
  return ($queue) ? $queue->numberOfItems() : 0;
}

function _amber_last_run($var) {
  $time = variable_get($var,0);
  return ($time) ? format_date($time) : t('Never');
}

function _amber_disk_usage() {
  $status = amber_get_status();
  $max_size = variable_get('amber_max_disk', '1000') * 1024 * 1024;
  $formatted_max = format_size($max_size);
  $current_size = $status->get_cache_size();
  $formatted_current_size = $current_size ? format_size($current_size) : t('0 MB');
  if ($current_size > (0.9 * $max_size)) {
    drupal_set_message(t("You are approaching the maximum space allocated for preserved content."),'warning',FALSE);
  }
  return t('@current (of @max)', array('@current' => $formatted_current_size, '@max' => $formatted_max));
}

function amber_dashboard_summary_form_clear($form, &$form_state) {
  amber_delete_all();
  cache_clear_all('*', 'cache_filter',TRUE);
  cache_clear_all('*', 'cache_field',TRUE);
  drupal_set_message("All snapshots have been deleted");
}

function amber_dashboard_summary_form_scan($form, &$form_state) {
  drupal_get_messages(); /* Clear the 'You should scan for content' message */
  variable_set('amber_content_scanned', 1);
  $scan_batch = amber_batch_scan_all_setup();
  if ($scan_batch) {
    batch_set($scan_batch);
  }
}

function amber_dashboard_summary_form_cache($form, &$form_state) {
  $cache_batch = amber_batch_cache_all_setup();
  if ($cache_batch) {
    batch_set($cache_batch);
  }
}

/**
 * Export contents of the dashboard detail page as CSV
 * @param $form
 * @param $form_state
 */
function amber_dashboard_detail_form_export($form, &$form_state) {
  $query = _amber_dashboard_detail_query();
  $result = $query->execute();

  $header = array(
    t('Site'),
    t('URL'),
    t('Status'),
    t('Last Checked'),
    t('Date preserved'),
    t('Size'),
    t('Last viewed'),
    t('Total views'),
    t('Notes')
  );

  $rows = array();
  while ($r = $result->fetchAssoc()) {
    $host = parse_url($r['url'],PHP_URL_HOST);
    $rows[] = array(
      'site' => $host,
      'url' => $r['url'],
      'status' => $r['status'] ? t('Up') : t('Down'),
      'last_checked' => isset($r['last_checked']) ? date('c',$r['last_checked']) : "",
      'date' => isset($r['date']) ? date('c',$r['date']) : "",
      'size' => $r['size'],
      'a.date' => isset($r['a_date']) ? date('c',$r['a_date']) : "",
      'views' => isset($r['views']) ? $r['views'] : 0,
      'message' => isset($r['message']) ? $r['message'] : ""
    );
  }

  drupal_add_http_header('Content-Type', 'text/csv');
  drupal_add_http_header('Content-Disposition', 'attachment;filename=report.csv');

  $fp = fopen('php://output', 'w');
  fputcsv($fp, $header);
  foreach($rows as $line){
    fputcsv($fp, $line);
  }
  fclose($fp);
  drupal_exit();
}

/**
 * Get the base query for returning data for the dashboard detail page
 */
function _amber_dashboard_detail_query() {
  $query = db_select('amber_check', 'c');
  $query->leftjoin('amber_cache', 'ca','ca.id = c.id');
  $query->leftJoin('amber_activity', 'a','ca.id = a.id');
  $query = $query->fields('c', array('id', 'url', 'status','last_checked', 'message'));
  $query = $query->fields('ca', array('id', 'date', 'size', 'location', 'provider'));
  $query = $query->fields('a', array('id', 'views', 'date'));
  $query->addExpression('substring_index(c.url,\'://\',-1)', 'url_sort');
  return $query;
}

/**
 * Callback function to delete single item from the cache
 * @param $id
 */
function amber_dashboard_delete_item($id, $provider = 0) {
  if ($id) {
    if (amber_delete_item($id, $provider)) {
      drupal_set_message(t("Deleted record with id: @id.", array('@id' => $id)));
    } else {
      drupal_set_message(t("Could not delete record with id: @id.", array('@id' => $id)), 'warning');
    }
  }
  drupal_goto(drupal_get_destination());
}

/**
 * Callback function to add a site to the list of sites not to cache
 * @param $id
 */
function amber_dashboard_blacklist_site($site) {
  if ($site) {
    $list = variable_get('amber_excluded_sites','');
    $list .= PHP_EOL . filter_xss($site);
    variable_set('amber_excluded_sites',$list);
    drupal_set_message("Added $site to list of excluded sites");
  }
  drupal_goto(drupal_get_destination());
}
