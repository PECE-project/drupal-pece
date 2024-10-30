<?php
/**
 * @file
 * Contains \Drupal\pece_migrate\Plugin\migrate\source\EssayNode.
 */
namespace  Drupal\pece_migrate\Plugin\migrate\source;

use Drupal\pece_migrate\Plugin\migrate\source\Node;

/**
 * PECE Essay Source.
 *
 * @MigrateSource(
 *   id = "v1_essay_node",
 *   source_module = "node"
 * )
 */
class EssayNode extends Node {

  /**
   * {@inheritdoc}
   */
  public function fields() {
    $fields = parent::fields();
    $fields += ['static_legacy_content' => $this->t('Static legacy content')];
    return $fields;
  }

  /**
   * {@inheritdoc}
   * @throws Exception
   */
  public function prepareRow(Row $row) {
    $nid = $row->getSourceProperty('nid');
    $html = $this->select('field_static_legacy_content', 'fslc')
      ->fields('fslc', ['static_html'])
      ->condition('fslc.nid', $nid)
      ->execute()->fetchField();

    $row->setSourceProperty('static_legacy_content', $html);
    return parent::prepareRow($row);
  }
}
