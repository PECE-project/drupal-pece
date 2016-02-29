<?php

/**
 * @file
 * API documentation for the Publication Date module.
 */

/**
 * Allows modules to alter the publication date before it is saved to the
 * database on node update/insert.
 *
 * @param integer $published_at
 *   A Unix timestamp representing the publication date to be altered.
 * @param object $node
 *   The node object.
 * @param string $op
 *   The node opperation being performed:
 *   - 'insert': a new node was created
 *   - 'update': an existing node was updated
 *
 * @see _publication_date_set_date()
 */
function hook_publication_date_alter(&$published_at, $node, $op) {
  // Check if the node is being published.
  if ($node->status == 1) {
    // If a future publication date was set, change it to the curret time.
    $now = REQUEST_TIME;
    $published_at = ($published_at > $now) ? $now : $published_at;
  }
  else {
    // If the node isn't published then reset the published date to zero.
    $published_at = 0;
  }
}
