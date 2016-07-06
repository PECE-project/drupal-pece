<?php

/**
 * @file
 * NodeTypeConfigHandler class.
 */

namespace Drupal\node_expire\Module\Config;


/**
 * NodeTypeConfigHandler class.
 *
 * Defines config handler for particular node type.
 */
class NodeTypeConfigHandler {

  /**
   * Node type.
   *
   * @var string
   */
  protected $nodeType;

  /**
   * Period.
   *
   * @var array
   */
  protected $nodeTypeConfigs;

  /**
   * Constructs a NodeTypeConfigHandler object.
   *
   * @param string $node_type
   *   Node type.
   */
  public function __construct($node_type) {
    $this->nodeType = $node_type;
    $this->loadConfig();
  }

  /**
   * Loads configuration array.
   */
  protected function loadConfig() {
    $this->nodeTypeConfigs = variable_get('node_expire_ntypes', array());
  }

  /**
   * Returns default node type config.
   */
  protected function getNodeTypeConfigDefault() {
    $config_default = array(
      // Current date.
      'update_expiry_start'  => 1,
      // Year.
      'update_expiry_interval' => 4,
      'update_expiry_multiplier' => 1,
    );

    return $config_default;
  }

  /**
   * Returns single node type config.
   */
  public function getNodeTypeConfig() {
    if ((isset($this->nodeTypeConfigs[$this->nodeType]))
      and ($n_type_config = $this->nodeTypeConfigs[$this->nodeType])) {
      return $n_type_config;
    }
    else {
      return $this->getNodeTypeConfigDefault();
    }
  }

  /**
   * Returns update expiry start.
   */
  public function getUpdateExpiryStart() {
    $config = $this->getNodeTypeConfig();
    if (isset($config['update_expiry_start'])) {
      return $config['update_expiry_start'];
    }
    else {
      return 1;
    }
  }

  /**
   * Returns update expiry interval.
   */
  public function getUpdateExpiryInterval() {
    $config = $this->getNodeTypeConfig();
    if (isset($config['update_expiry_interval'])) {
      return $config['update_expiry_interval'];
    }
    else {
      return 4;
    }
  }

  /**
   * Returns update expiry multiplier.
   */
  public function getUpdateExpiryMultiplier() {
    $config = $this->getNodeTypeConfig();
    if (isset($config['update_expiry_multiplier'])) {
      return $config['update_expiry_multiplier'];
    }
    else {
      return 1;
    }
  }

}
