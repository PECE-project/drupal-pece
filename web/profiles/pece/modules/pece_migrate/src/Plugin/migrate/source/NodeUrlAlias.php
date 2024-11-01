<?php

namespace Drupal\pece_migrate\Plugin\migrate\source;

use Drupal\path\Plugin\migrate\source\d7\UrlAlias;

/**
 * Fetch node aliases filtered by content type.
 *
 * @MigrateSource(
 *   id = "v1_node_url_alias",
 *   source_module = "path"
 * )
 */
class NodeUrlAlias extends UrlAlias {

  /**
   * {@inheritdoc}
   */
  public function query() {
    $query = parent::query();

    $query->innerJoin('node', 'n', "ua.source = CONCAT('node/', n.nid)");

    if ($bundle = $this->configuration['bundle']) {
      $query->condition('n.type', (array) $bundle, 'IN');
    }

    return $query;
  }

}
