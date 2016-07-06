<?php

/**
 * @file
 * NodeHelper class.
 */

namespace Drupal\node_expire\Module\CommonExpire\Node;

/**
 * NodeHelper class.
 */
class NodeHelper {

  /**
   * Publishes node by $nid.
   */
  public static function publishNode($nid) {
    // Load the node object.
    $node = node_load($nid);
    // Set status property to 1.
    $node->status = 1;
    // Save the node.
    node_save($node);
  }

  /**
   * Unpublishes node by $nid.
   */
  public static function unpublishNode($nid) {
    // Load the node object.
    $node = node_load($nid);
    // Set status property to 0.
    $node->status = 0;
    // Save the node.
    node_save($node);
  }

  /**
   * Makes node sticky by $nid.
   */
  public static function makeNodeSticky($nid) {
    // Load the node object.
    $node = node_load($nid);
    // Set sticky property to 1.
    $node->sticky = 1;
    // Save the node.
    node_save($node);
  }

  /**
   * Makes node unsticky by $nid.
   */
  public static function makeNodeUnsticky($nid) {
    // Load the node object.
    $node = node_load($nid);
    // Set sticky property to 0.
    $node->sticky = 0;
    // Save the node.
    node_save($node);
  }

  /**
   * Promotes node to front page by $nid.
   */
  public static function promoteNode($nid) {
    // Load the node object.
    $node = node_load($nid);
    // Set promote property to 1.
    $node->promote = 1;
    // Save the node.
    node_save($node);
  }

  /**
   * Removes node from front page by $nid.
   */
  public static function unpromoteNode($nid) {
    // Load the node object.
    $node = node_load($nid);
    // Set promote property to 0.
    $node->promote = 0;
    // Save the node.
    node_save($node);
  }

}
