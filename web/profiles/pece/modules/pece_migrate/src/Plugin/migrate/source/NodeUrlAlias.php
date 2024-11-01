<?php

namespace Drupal\pece_migrate\Plugin\migrate\source;

use Drupal\migrate_drupal\Plugin\migrate\source\DrupalSqlBase;

/**
 * Fetch node aliases filtered by content type.
 *
 * Modeled after core URL alias migration.
 * @see \Drupal\path\Plugin\migrate\source\d7\UrlAlias
 *
 * @MigrateSource(
 *   id = "v1_node_url_alias",
 *   source_module = "path"
 * )
 */
class NodeUrlAlias extends DrupalSqlBase {

  /**
   * {@inheritdoc}
   */
  public function query() {
    $query = $this->select('url_alias', 'ua')
      ->fields('ua', ['source', 'alias'])
      ->orderBy('ua.pid')
      ->distinct();

    $query->innerJoin('node', 'n', "ua.source = CONCAT('node/', n.nid)");

    if ($bundle = $this->configuration['bundle']) {
      $query->condition('n.type', (array) $bundle, 'IN');
    }

    return $query;
  }

  /**
   * {@inheritdoc}
   */
  public function fields() {
    return [
      'source' => $this->t('The internal system path.'),
      'alias' => $this->t('The path alias.'),
    ];
  }

  /**
   * {@inheritdoc}
   */
  public function getIds() {
    $ids['source']['type'] = 'string';
    $ids['alias']['type'] = 'string';
    return $ids;
  }

}
