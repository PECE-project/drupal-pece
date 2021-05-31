<?php
/**
 * @file
 * Contains \Drupal\pece_migrate\Plugin\migrate\source\Node.
 */
namespace  Drupal\pece_migrate\Plugin\migrate\source;
use Drupal\migrate\Row;
use Drupal\node\Plugin\migrate\source\d7\NodeComplete as D7Node;

/**
 * Gets all node revisions from the source, including translation revisions.
 *
 * @MigrateSource(
 *   id = "v1_node",
 *   source_module = "node"
 * )
 */
class Node extends D7Node {
  /**
   * {@inheritdoc}
   */
  public function fields() {
    return parent::fields() + ['alias' => $this->t('Path alias')];
  }

  /**
   * {@inheritdoc}
   */
  public function prepareRow(Row $row) {
    // Include path alias.
    $nid = $row->getSourceProperty('nid');
    $query = $this->select('url_alias', 'ua')
      ->fields('ua', ['alias']);
    $query->condition('ua.source', 'node/' . $nid);
    $alias = $query->execute()->fetchField();
    if (!empty($alias)) {
      $row->setSourceProperty('alias', '/' . $alias);
    }
    return parent::prepareRow($row);
  }
}
