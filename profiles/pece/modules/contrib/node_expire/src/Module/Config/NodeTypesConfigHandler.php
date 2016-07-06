<?php

/**
 * @file
 * NodeTypesConfigHandler class.
 */

namespace Drupal\node_expire\Module\Config;


/**
 * NodeTypesConfigHandler class.
 *
 * Defines config handler for node types.
 */
class NodeTypesConfigHandler {

  /**
   * Array with configs for node types.
   *
   * @var array
   */
  protected $nodeTypeConfigs;

  /**
   * Constructs a NodeTypesConfigHandler object.
   */
  public function __construct() {
    $this->loadConfig();
  }

  /**
   * Loads configuration array.
   */
  public function loadConfig() {
    $this->nodeTypeConfigs = variable_get('node_expire_ntypes', array());
  }

  /**
   * Saves configuration array.
   */
  public function saveConfig() {
    variable_set('node_expire_ntypes', $this->nodeTypeConfigs);
  }

  /**
   * Returns single node type config.
   *
   * @param string $node_type
   *   Node type.
   */
  public function getNodeTypeConfig($node_type) {
    if ((isset($this->nodeTypeConfigs[$node_type]))
      and ($n_type_config = $this->nodeTypeConfigs[$node_type])) {
      return $n_type_config;
    }
    else {
      return $this->getNodeTypeConfigDefault();
    }
  }

  /**
   * Returns default node type config.
   */
  protected function getNodeTypeConfigDefault() {
    $config_default = array(
      'enabled' => 1,
      'default' => '2038-01-01',
      'max' => '',
      'required' => 0,
      'action_type' => 0,
    );

    return $config_default;
  }

  /**
   * Returns action type.
   *
   * @param string $node_type
   *   Node type.
   */
  public function getActionType($node_type) {
    $config = $this->getNodeTypeConfig($node_type);
    if (isset($config['action_type'])) {
      $action_type = $config['action_type'];
    }
    else {
      $action_type = 0;
    }

    return $action_type;
  }

}
