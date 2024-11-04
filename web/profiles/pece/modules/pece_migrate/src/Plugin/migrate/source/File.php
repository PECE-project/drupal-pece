<?php

namespace  Drupal\pece_migrate\Plugin\migrate\source;

use Drupal\file\Plugin\migrate\source\d7\File as D7File;
use Drupal\migrate\Row;

/**
 * Drupal 7 file source from database.
 *
 * Available configuration keys:
 * - scheme: (optional) The scheme of the files to get from the source, for
 *   example, 'public' or 'private'. Can be a string or an array of schemes.
 *   The 'temporary' scheme is not supported. If omitted, all files in
 *   supported schemes are retrieved.
 * - pece_essay
 * Example:
 *
 * @code
 * source:
 *   plugin: v1_file
 *   scheme: public
 *   pece_essay: TRUE
 * @endcode
 *
 * In this example, public file values, that are referenced in field_basic_image_image from node entities of the pece_project bundle, are retrieved from the source database.
 *
 * For additional configuration keys, refer to the parent classes.
 *
 * @see \Drupal\migrate\Plugin\migrate\source\SqlBase
 * @see \Drupal\migrate\Plugin\migrate\source\SourcePluginBase
 * @see \Drupal\file\Plugin\migrate\source\d7\File
 * @see d7_file.yml
 *
 * @MigrateSource(
 *   id = "v1_file",
 *   source_module = "file"
 * )
 */
class File extends D7File {

  /**
   * {@inheritdoc}
   */
  public function query() {
    $query = parent::query();

    // fid_locator is a custom table, a collection of data about embedded files, see scripts/token_parser.sql
    // Get all files that appear inline in panes
    $fidl_query = $this->select('fid_locator', 'fidl')
      ->fields('fidl', ['fid'])
      ->condition('fidl.entity_type', 'fieldable_panels_pane');
    // Get all files that appear in an image panes image field
    $fppi_query = $this->select('field_data_field_basic_image_image', 'fbii')
      ->fields('fbii', ['field_basic_image_image_fid']);

    if ($this->configuration['pece_essay']) {
      $orGroup = $query->orConditionGroup()
        ->condition('f.fid', $fidl_query, 'IN')
        ->condition('f.fid', $fppi_query, 'IN');
      $query->condition($orGroup);
    } else {
      $query
        ->condition('f.fid', $fidl_query, 'NOT IN')
        ->condition('f.fid', $fppi_query, 'NOT IN');
    }

    return $query;
  }

}
