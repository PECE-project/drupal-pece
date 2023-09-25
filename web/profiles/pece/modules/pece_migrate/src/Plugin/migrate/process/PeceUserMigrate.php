<?php

namespace Drupal\pece_migrate\Plugin\migrate\process;

use Drupal\migrate\ProcessPluginBase;
use Drupal\migrate\MigrateExecutableInterface;
use Drupal\migrate\Row;

/**
 * Provides a 'PeceUserMigrate' migrate process plugin.
 *
 * @MigrateProcessPlugin(
 *  id = "pece_user_migrate"
 * )
 */
class PeceUserMigrate extends ProcessPluginBase {

  /**
   * {@inheritdoc}
   */
  public function transform($value, MigrateExecutableInterface $migrate_executable, Row $row, $destination_property) {
    // Plugin logic goes here.
  }

}
