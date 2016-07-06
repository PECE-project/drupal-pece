<?php
/**
 * @file
 * Functions relating to queue management and batch processing
 */

/**
 * Implements hook_cron().
 */
function amber_cron() {
  if (variable_get('amber_enabled', 1)) {
    $status_service = amber_get_status();
    $urls = $status_service->get_urls_to_check();
    if ($urls) {
      amber_enqueue_check_links($urls, AMBER_QUEUE_CHECK_EXISTING);
    }
  }
}

/**
 * Check whether an item already exists in the queue, to avoid filling up the queue with
 * duplicate entries. This isn't provided by the Drupal Queue interface, so we need to go
 * directly to the database to find out, unfortunately.
 * @param $queue_name string with name of the queue
 * @param $url string with URL to check
 */
function amber_exists_in_queue($queue, $url) {
  // @ignore sql_count
  $result = db_query("SELECT COUNT(*) FROM {queue} WHERE name=:name AND data=:data",
                      array(':name' => $queue, ':data' => serialize($url)))->fetchCol();
  return ($result[0] > 0);
}

/**
 * Add a list of URLs to a queue of links to be checked. We have multiple queues for checking links so that
 * new links (which we want to check soon) don't get stuck behind a backlog of existing links to recheck
 * @param $links array of URLs to be cached
 */
function amber_enqueue_check_links($links, $queue_name = AMBER_QUEUE_CHECK_NEW) {
  $queue = DrupalQueue::get($queue_name);
  $queue->createQueue();
  foreach ($links as $link) {
    if ($link && !amber_exists_in_queue($queue_name, $link)) {
      $queue->createItem($link);
    }
  }
}

/**
 * Implements hook_cron_queue_info().
 */
function amber_cron_queue_info() {
  return array(
    AMBER_QUEUE_CHECK_NEW  => array(
      'worker callback' => 'amber_process_check_queue',
    ),
    AMBER_QUEUE_CHECK_EXISTING => array(
      'worker callback' => 'amber_process_check_queue',
    ),
  );
}

/**
 * Setup a batch (for use with the Batch API) to scan all nodes on the site for links to cache
 * @return array|null
 */
function amber_batch_scan_all_setup() {
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')->propertyCondition('status', 1);
  $result = $query->execute();
  if (!empty($result['node'])) {
    $operations = array();
    $nids = array_keys($result['node']);
    foreach ($nids as $nid) {
      $operations[] = array('amber_batch_scan_process', array($nid));
    }
  }
  if (!empty($operations)) {
    $batch = array(
      'operations' => $operations,
      'finished' => 'amber_batch_scan_all_finished',
    );
    return $batch;
  }
  else {
    return NULL;
  }
}

/**
 * Scan a node for links to cache (for use with the Batch API)
 * @param $nid string if of the node to scan
 * @param $context
 */
function amber_batch_scan_process($nid, $context) {
  $node = node_load($nid, NULL, TRUE);
  if ($node) {
    amber_cache_node($node);
    $context['results'][] = $node->nid . ' : ' . check_plain($node->title);
  }
  $context['message'] = t('Scanned node "@title"', array('@title' => $node->title));
}

/**
 * Final step in batch processing to scan nodes for links to cache
 * @param $success
 * @param $results
 * @param $operations
 */
function amber_batch_scan_all_finished($success, $results, $operations) {
  if ($success) {
    drupal_set_message(t('@count nodes scanned', array('@count' => count($results))));
  }
  else {
    $error_operation = reset($operations);
    drupal_set_message(t('An error occurred while processing @operation with arguments : @args', array('@operation' => $error_operation[0], '@args' => print_r($error_operation[0], TRUE))));
  }
}

/**
 * Setup a batch (for use with the Batch API) to cache all links scheduled for caching immediately
 * Rather than adding URLs to the batch, we add items containing the name of a queue which holds an item to be cached,
 * @return array|null
 */
function amber_batch_cache_all_setup() {
  foreach (array(AMBER_QUEUE_CHECK_NEW, AMBER_QUEUE_CHECK_EXISTING) as $queue_name) {
    $queue = DrupalQueue::get($queue_name);
    $queue->createQueue();
    $queue_size = $queue->numberOfItems();
    for ($i = 0; $i < $queue_size; $i++) {
      $operations[] = array('amber_batch_cache_process', array($queue_name));
    }
  }
  if (!empty($operations)) {
    $batch = array(
      'operations' => $operations,
      'finished' => 'amber_batch_cache_all_finished',
    );
    return $batch;
  }
  else {
    return NULL;
  }
}

/**
 * Take an item with a queue name from the batch, and retrieve the next item from that queue
 * @param $item name of the queue from which to pull an object to be checked
 * @param $context
 */
function amber_batch_cache_process($queue_name, $context) {
  $queue = DrupalQueue::get($queue_name);
  $queue->createQueue();
  if ($queue->numberOfItems() == 0) {
    return;
  }
  $item = $queue->claimItem(60);
  if (!$item) {
    return;
  }
  $url = $item->data;
  amber_process_check_queue($url, TRUE);
  $queue->deleteItem($item);
  $context['results'][] = $url;
  $context['message'] = t('Preserved URL "@url"', array('@url' => $url));
}

/**
 * Final step in batch processing to cache all links
 * @param $success
 * @param $results
 * @param $operations
 */
function amber_batch_cache_all_finished($success, $results, $operations) {
  if ($success) {
    $count = count($results);
    if ($count == 1)
      drupal_set_message(t('@count URL preserved', array('@count' => $count)));
    else
      drupal_set_message(t('@count URLs preserved', array('@count' => $count)));
    cache_clear_all('*', 'cache_filter', TRUE);
    cache_clear_all('*', 'cache_field', TRUE);
  }
  else {
    $error_operation = reset($operations);
    drupal_set_message(t('An error occurred while processing @operation with arguments : @args', array('@operation' => $error_operation[0], '@args' => print_r($error_operation, TRUE))));
  }
}

/**
 * Process an item in the queue to be checked and cached
 * @param $item string url of the item to be checked
 */
function amber_process_check_queue($item, $force = FALSE) {
  try {
    amber_cache_link($item, TRUE);
    variable_set(AMBER_VAR_LAST_CHECK_RUN, time());
  } catch (Exception $e) {
    // If there is an error, log the error, and then continue. Otherwise the bad item will not be removed from the queue
    watchdog('amber', "Error checking @url : @msg ", array('@url' => $item, '@msg' => $e->getMessage()), WATCHDOG_NOTICE);
  }
}

/**
 * Check and cache a link
 */
function amber_cache_link($item, $force = FALSE) {
  $start = time();
  watchdog('amber', "Checking and caching: @url ", array('@url' => $item), WATCHDOG_DEBUG);

  $checker = amber_get_checker();
  $status = amber_get_status();
  $fetcher = amber_get_fetcher();

  /* Check whether the site is up */
  $last_check = $status->get_check($item);
  if (($update = $checker->check(empty($last_check) ? array('url' => $item) : $last_check, $force)) !== FALSE) {

    /* There's an updated check result to save */
    $status->save_check($update);

    /* Report the results of the check to NetClerk (if configured) */
    $availability = amber_get_availability();
    if ($availability && isset($update['details']) && (variable_get('amber_report_availability', AMBER_REPORT_AVAILABILITY_NONE) == AMBER_REPORT_AVAILABILITY_NETCLERK)) {
      watchdog("amber", "Reporting @url availability to NetClerk", array("@url" => $item), WATCHDOG_DEBUG);
      $availability->report_status($item, $update['details']);
    }

    /* Now cache the item if we should */
    if ($update['status'] && (!variable_get('amber_update_strategy', 0) || !$status->has_cache($item))) {

        /* Save the item to the primary storage location */
        watchdog('amber', "Caching: @url using @object", array('@url' => $item, '@object' => get_class($fetcher)), WATCHDOG_DEBUG);
        $result = _amber_fetch_item($item, $fetcher, $status);

        /* Save the item to any alternate storage locations */
        foreach (amber_get_alternate_fetchers() as $alternate_fetcher) {
          watchdog('amber', "Caching: @url using @object", array('@url' => $item, '@object' => get_class($alternate_fetcher)), WATCHDOG_DEBUG);
          _amber_fetch_item($item, $alternate_fetcher, $status);
        }

        if ($result) {
          watchdog('amber', "Cached: @url in @seconds seconds", array('@url' => $item, '@seconds' => time() - $start), WATCHDOG_DEBUG);
          /* Clear caches that could contain HTML with versions of the links that don't contain data- attributes */
          /* TODO: Ideally we would clear the cache only once per cron job */
          cache_clear_all('*', 'cache_filter', TRUE);
          cache_clear_all('*', 'cache_field', TRUE);
          amber_disk_space_purge();
        }
        return $result;
    }
  }
  else {
    return FALSE;
  }
}

/**
 * Fetch an item and save the metadata
 * @param  string $item    url to fetch
 * @param  iAmberFetcher $fetcher instance of a fetcher to use to get the item
 * @param  iAmberStatus  $status  instance of a status to use to save the item
 * @return boolean  TRUE if successfully cached
 */
function _amber_fetch_item($item, $fetcher, $status) {
  $cache_metadata = array();
  try {
    $cache_metadata = $fetcher->fetch($item);
  } catch (RuntimeException $re) {
    watchdog('amber', "Did not cache: @url: @message", array('@url' => $item, '@message' => $re->getMessage()), WATCHDOG_NOTICE);
    $update['message'] = $re->getMessage();
    $status->save_check($update);
    return FALSE;
  }
  if ($cache_metadata) {
    $status->save_cache($cache_metadata);
    return TRUE;
  }
  else {
    return FALSE;
  }
}


/**
 * If the total disk space usage is over the configured limit, delete enough items to bring it under
 */
function amber_disk_space_purge() {
  $status = amber_get_status();
  $purge = $status->get_items_to_purge(variable_get('amber_max_disk', 1000) * 1024 * 1024);
  if ($purge) {
    $storage = amber_get_storage();
    foreach ($purge as $item) {
      $storage->delete($item['id']);
      $status->delete($item['id']);
      watchdog('amber', "Deleting to stay under disk space limits: @url", array('@url' => $item['url']), WATCHDOG_NOTICE);
    }
  }
}
