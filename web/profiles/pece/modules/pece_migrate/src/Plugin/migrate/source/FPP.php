<?php
/**
 * @file
 * Contains \Drupal\pece_migrate\Plugin\migrate\source\FPP
 */
namespace  Drupal\pece_migrate\Plugin\migrate\source;
use Drupal\migrate\Row;
use Drupal\migrate_drupal\Plugin\migrate\source\d7\FieldableEntity;
use Exception;

/**
 * Gets all fieldable panels panes from the source.
 *
 * @MigrateSource(
 *   id = "v1_fpp",
 *   source_module = "fieldable_panels_panes"
 * )
 */
class FPP extends FieldableEntity {

  /**
   * The join options between the fieldable_panels_panes and the fieldable_panels_panes_revision table.
   */
  const JOIN = '[p].[vid] = [pr].[vid]';

  /**
   * {@inheritdoc}
   */
  public function query() {
    // Select Fieldable Panels Pane in its last revision.
    $query = $this->select('fieldable_panels_panes_revision', 'pr')
      ->fields('p', [
        'fpid',
        'vid',
        'bundle',
        'created',
        'changed',
        'uuid',
        'language',
      ])
      ->fields('pr', [
        'vid',
        'uid',
        'title',
        'timestamp',
      ]);
    $query->innerJoin('fieldable_panels_panes', 'p', static::JOIN);


    if (isset($this->configuration['bundle'])) {
      $query->condition('p.bundle', (array) $this->configuration['bundle'], 'IN');
    }

    return $query;
  }

  /**
   * {@inheritdoc}
   */
  public function prepareRow(Row $row) {
    $fpid = $row->getSourceProperty('fpid');
    $vid = $row->getSourceProperty('vid');
    $type = $row->getSourceProperty('bundle');

    if ($type = 'image') {
      $fid_query = $this->select('field_data_field_basic_image_image', 'fbii')
        ->fields('fbii', ['field_basic_image_image_fid'])
        ->condition('fbii.entity_id', $fpid);
      $alt_text = $this->select('field_data_field_file_image_alt_text', 'alt')
        ->fields('alt', ['field_file_image_alt_text_value'])
        ->condition('alt.entity_id', $fid_query, 'IN');
      $finished_value = $alt_text
        ->execute()->fetchField();
      $row->setSourceProperty('field_file_image_alt_text', $finished_value);
    }

    // Get Field API field values.
    foreach ($this->getFields('fieldable_panels_pane', $type) as $field_name => $field) {
      $row->setSourceProperty($field_name, $this->getFieldValues('fieldable_panels_pane', $field_name, $fpid, $vid));
    }

    // Make sure we always have a translation set.
    // if ($row->getSourceProperty('tnid') == 0) {
    //   $row->setSourceProperty('tnid', $row->getSourceProperty('nid'));
    // }

    return parent::prepareRow($row);
  }

  /**
   * {@inheritdoc}
   */
  public function fields() {
    $fields = [
      'fpid' => $this->t('Fieldable Panels Pane ID'),
      'bundle' => $this->t('Bundle'),
      'title' => $this->t('Title'),
      'uid' => $this->t('FPP authored by (uid)'),
      'uuid' => $this->t('UUID'),
      'created' => $this->t('Created timestamp'),
      'changed' => $this->t('Modified timestamp'),
      'language' => $this->t('Language (fr, en, ...)'),
      'timestamp' => $this->t('The timestamp the latest revision of this node was created.'),
      'field_file_image_alt_text' => $this->t('The alt text from the referenced image file entity'),
    ];
    return $fields;
  }
  /**
   * {@inheritdoc}
   */
  public function getIds() {
    $ids['fpid']['type'] = 'integer';
    $ids['fpid']['alias'] = 'p';
    return $ids;
  }
}
