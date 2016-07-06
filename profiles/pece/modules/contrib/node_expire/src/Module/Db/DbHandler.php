<?php

/**
 * @file
 * DbHandler class.
 */

namespace Drupal\node_expire\Module\Db;

/**
 * DbHandler class.
 */
class DbHandler {

  /**
   * Sets node as expired by $nid.
   *
   * @param int $nid
   *   Node ID that should set the expired flag.
   */
  public static function setExpired($nid) {
    db_update('node_expire')
      ->fields(
        array(
          'expired' => 1,
          'lastnotify' => REQUEST_TIME,
        )
      )
      ->condition('nid', $nid)
      ->condition(db_or()
        ->condition('lastnotify', 0)
        ->condition('expired', 1, '!='))
      ->execute();
  }

  /**
   * Deletes node_expire record by $nid.
   *
   * Used in hook_node_delete() implementation.
   */
  public static function deleteNodeExpire($nid) {
    db_delete('node_expire')
      ->condition('nid', $nid)
      ->execute();
  }

  /**
   * Returns count of node_expire record by $nid.
   */
  public static function getNodeExpireCountByNid($nid) {
    $cnt = db_query(
      'SELECT count(nid)
      FROM {node_expire} ne
      WHERE ne.nid = :nid',
      array(':nid' => $nid))->fetchField();

    return $cnt;
  }

  /**
   * Writes node_expire record.
   */
  public static function writeRecord($node_expire, $nid) {
    // Check, is it insert or update.
    $cnt = self::getNodeExpireCountByNid($nid);

    // Write the record.
    if ($cnt == 0) {
      // Insert.
      drupal_write_record('node_expire', $node_expire);
    }
    else {
      // Update.
      drupal_write_record('node_expire', $node_expire, 'nid');
    }
  }

  /**
   * Returns expired node_expire records.
   */
  public static function selectExpired() {
    $result = db_query('SELECT n.nid, n.type FROM {node} n
      JOIN {node_expire} ne ON n.nid = ne.nid
      WHERE ne.expire <= :ne_expire',
      array(':ne_expire' => REQUEST_TIME));

    return $result;
  }

  /**
   * Returns expired node_expire records where expired flag is not set.
   */
  public static function selectExpiredNonFlagged() {
    $result = db_query('SELECT n.nid, n.type FROM {node} n
      JOIN {node_expire} ne ON n.nid = ne.nid
      WHERE ne.expire <= :ne_expire AND ne.expired = 0',
      array(':ne_expire' => REQUEST_TIME));

    return $result;
  }

  /**
   * Returns node_expire records for hook_node_load().
   */
  public static function selectForNodeLoad($node_expire_enabled) {
    $result = db_query(
      'SELECT n.nid, n.type, expire, expired, lastnotify
       FROM {node} n
         INNER JOIN {node_expire} ne
           ON n.nid = ne.nid
       WHERE n.nid
         IN (:node_expire_enabled)',
      array(':node_expire_enabled' => $node_expire_enabled));

    return $result;
  }

}
