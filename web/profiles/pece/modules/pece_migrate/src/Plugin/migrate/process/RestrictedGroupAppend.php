<?php

namespace Drupal\pece_migrate\Plugin\migrate\process;

use Drupal\migrate\ProcessPluginBase;
use Drupal\migrate\MigrateExecutableInterface;
use Drupal\migrate\Row;

/**
 * Provides a 'PeceUserMigrate' migrate process plugin.
 *
 * @MigrateProcessPlugin(
 *  id = "restricted_group_append"
 * )
 */
class RestrictedGroupAppend extends ProcessPluginBase {

  /**
   * {@inheritdoc}
   */
  public function transform($value, MigrateExecutableInterface $migrate_executable, Row $row, $destination_property) {
    $all_groups = $value[0];
    if (!empty($value[1])) {
      array_push($all_groups, $value[1][0]);
    }
    return $all_groups;
  }

}
