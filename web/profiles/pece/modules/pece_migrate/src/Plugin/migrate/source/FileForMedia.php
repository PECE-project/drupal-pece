<?php

namespace  Drupal\pece_migrate\Plugin\migrate\source;

use Drupal\file\Plugin\migrate\source\d7\File as D7File;

/**
 * Drupal 7 file source from database.
 *
 * Available configuration keys:
 * - scheme: (optional) The scheme of the files to get from the source, for
 *   example, 'public' or 'private'. Can be a string or an array of schemes.
 *   The 'temporary' scheme is not supported. If omitted, all files in
 *   supported schemes are retrieved.
 *
 * Example:
 *
 * @code
 * source:
 *   plugin: v1_file
 *   scheme: public
 *   file_type: image
 *   inline_media: TRUE
 * @endcode
 *
 * In this example, public file values, that are CV files, are retrieved from the source database.
 * For complete example, refer to the d7_file.yml migration.
 *
 * For additional configuration keys, refer to the parent classes.
 *
 * @see \Drupal\migrate\Plugin\migrate\source\SqlBase
 * @see \Drupal\migrate\Plugin\migrate\source\SourcePluginBase
 * @see \Drupal\file\Plugin\migrate\source\d7\File
 * @see d7_file.yml
 *
 * @MigrateSource(
 *   id = "v1_file_media",
 *   source_module = "file"
 * )
 */
class FileForMedia extends D7File {

  /**
   * {@inheritdoc}
   */
  public function query() {
    $query = parent::query()->condition('f.type', $this->configuration['file_type']);

    if ($this->configuration['inline_media']) {
      // fid_locator is a custom table that collects file ids of embedded files, see scripts/token_parser.sql
      $fid_query = $this->select('fid_locator', 'fidl')
        ->fields('fidl', ['fid'])
        ->distinct();
      $query->condition('f.fid', $fid_query, 'IN');
    }

    return $query;
  }

}
