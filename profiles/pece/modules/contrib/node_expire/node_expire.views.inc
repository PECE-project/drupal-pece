<?php

/**
 * @file
 * Views module integration.
 */

use Drupal\node_expire\Module\Hook\ViewsHookHandler;

/**
 * Implements hook_views_data().
 */
function node_expire_views_data() {
  return ViewsHookHandler::hookViewsData();
}
