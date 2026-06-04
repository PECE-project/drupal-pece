<?php

namespace Drupal\rules\Core;

/**
 * Stub for Drupal\rules\Core\RulesActionBase.
 *
 * Drupal/rules is not installed in this project. This stub allows
 * RulesWebhookPost to be unit-tested without the full Rules module.
 */
abstract class RulesActionBase {

  /**
   * Constructs a RulesActionBase object.
   *
   * @param array $configuration
   *   Plugin configuration.
   * @param string $plugin_id
   *   The plugin ID.
   * @param mixed $plugin_definition
   *   The plugin definition.
   */
  public function __construct(array $configuration, $plugin_id, $plugin_definition) {}

}
