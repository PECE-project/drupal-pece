<?php

namespace Drupal\pece_migrate\Plugin\migrate\process;

use Drupal\migrate\MigrateException;
use Drupal\migrate\MigrateExecutableInterface;
use Drupal\migrate\Plugin\migrate\process\Concat;
use Drupal\migrate\ProcessPluginBase;
use Drupal\migrate\Row;

/**
 * Get variable from env a set of strings.
 *
 *
 * Examples:
 *
 * @code
 * process:
 *   new_text_field:
 *     plugin: concat_env
 *     source:
 *        - foo
 *        - env/MIGRATE_PATH
 * @endcode
 *
 * @see \Drupal\migrate\Plugin\MigrateProcessInterface
 *
 * @MigrateProcessPlugin(
 *   id = "concat_env",
 *   handle_multiples = TRUE
 * )
 */
class ConcatENV extends Concat {

  /**
   * {@inheritdoc}
   */
  public function transform($value, MigrateExecutableInterface $migrate_executable, Row $row, $destination_property) {
    foreach ($this->configuration['source'] as $key => $item) {
      $env = explode('env/', $item);
      if(count($env) > 1) {
        $value[$key] = getenv($env[1]);
      }
    }
    return parent::transform($value, $migrate_executable, $row, $destination_property);
  }

}
