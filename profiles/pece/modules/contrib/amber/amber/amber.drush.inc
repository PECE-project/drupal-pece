<?php

/**
 * @file
 * Drush interface to Amber
 */

/**
 * Implements hook_drush_command().
 */
function amber_drush_command() {
  $commands = array();

  $commands['amber-scan'] = array(
    'description' => 'Scans content for links to cache',
    'arguments' => array(
      'node' => 'The ID node of the scan, or \'all\'',
    ),
  );
  $commands['amber-clear-cache'] = array(
    'description' => 'Delete the contents of the cache',
  );
  $commands['amber-cache-url'] = array(
    'description' => 'Cache a single URL',
    'arguments' => array(
      'url' => 'A URL to save to the cache',
    ),
    'aliases' => array('ccu'),
  );

  $commands['amber-check-up'] = array(
    'description' => 'Check a single URL to see if it is up',
    'arguments' => array(
      'url' => 'A URL to check',
    ),
    'aliases' => array('cup'),
  );

  $commands['amber-check-url'] = array(
    'description' => 'Run the availability check on a single URL',
    'arguments' => array(
      'url' => 'A URL to check',
    ),
  );

  $commands['amber-delete'] = array(
    'description' => 'Delete an id from the cache',
    'arguments' => array(
      'id' => 'ID of URL to delete',
    ),
  );

  return $commands;
}

/**
 * Scan a single node, or all nodes, for links to cache
 * @param null $nid
 * @return bool
 */
function drush_amber_scan($nid = NULL) {
  if (!$nid) {
    drush_set_error(dt("Specify either a node ID to scan, or 'all'."));
    return FALSE;
  }
  if ($nid) {
    if ($nid == 'all') {
      amber_cache_all();
    } else {
      $node = node_load($nid);
      if (!$node) {
        drush_set_error(dt("Could not load node"));
        return FALSE;
      }
      amber_cache_node($node);
    }
    drush_print("Queued links for caching");
  }
}

/**
 * Delete the entire cache
 */
function drush_amber_delete_all() {
  amber_delete_all();
  drush_print("Cache cleared");
}

function drush_amber_cache_url($url) {
  if ($url) {
    amber_process_cache_queue($url);
    drush_print("URL fetched");
  } else {
    drush_set_error(dt("Specify a URL to cache"));
    return FALSE;
  }
}

function drush_amber_check_up($url) {
  if ($url) {
    $checker = amber_get_checker();
    if ($checker->up($url)) {
      drush_print("Up");
    } else {
      drush_print("Down");
    }
  } else {
    drush_set_error(dt("Specify a URL to check"));
    return FALSE;
  }
}

function drush_amber_check_url($url) {
  if ($url) {
    amber_process_check_queue($url, true);
    drush_print("URL checked");
  } else {
    drush_set_error(dt("Specify a URL to check"));
    return FALSE;
  }
}

function drush_amber_delete_url($id) {
  if ($id) {
    if (amber_delete_item($id)) {
      drush_print("Item deleted");      
    } else {
      drush_print("Could not delete item");      
    }
  } else {
    drush_set_error(dt("Specify an ID to delete"));
    return FALSE;
  }
}

