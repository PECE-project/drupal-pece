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
 * - inline_media
 * - file_type
 * - source_entity_type
 * - source_bundle
 * - source_field
 * Example:
 *
 * @code
 * source:
 *   plugin: v1_file_media
 *   scheme: public
 *   file_type: image
 *   source_entity_type: node
 *   source_bundle: pece_project
 *   source_field: field_basic_image_image
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
      // fid_locator is a custom table, a collection of data about embedded files, see scripts/token_parser.sql
      // All inline media should migrate to private inline media.
      $fid_query = $this->select('fid_locator', 'fidl')
        ->fields('fidl', ['fid'])
        ->distinct();
      $query->condition('f.fid', $fid_query, 'IN');

      return $query;
    }

    if ($this->configuration['source_field'] && $this->configuration['source_entity_type'] && $this->configuration['source_bundle']) {
      $field_query = $this->select('field_data_' . $this->configuration['source_field'], 'fd')
        ->fields('fd', [$this->configuration['source_field'] . '_fid'])
        ->condition('fd.entity_type', $this->configuration['source_entity_type'])
        ->condition('fd.bundle', $this->configuration['source_bundle']);

      $query->condition('f.fid', $field_query, 'IN');
    }

    return $query;
  }

  /**
   * {@inheritDoc}
   */
  public function prepareRow(Row $row) {
    $fid = $row->getSourceProperty('fid');

    if ($this->configuration['file_type'] === 'image') {
      $alt_text = $this->select('field_data_field_file_image_alt_text', 'alt')
        ->fields('alt', ['field_file_image_alt_text_value'])
        ->condition('alt.entity_id', $fid)
        ->execute()->fetchField();
      $row->setSourceProperty('alt_text', $alt_text);
    }

    return parent::prepareRow($row);
  }

  /**
   * {@inheritdoc}
   */
  public function fields() {
    $fields = parent::fields();
    $fields += [
      'alt_text' => $this->t('The alt text from the associated image file entity'),
    ];
    return $fields;
  }

}
