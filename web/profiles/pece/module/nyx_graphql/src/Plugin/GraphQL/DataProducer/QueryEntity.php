<?php

namespace Drupal\nyx_graphql\Plugin\GraphQL\DataProducer;

use Drupal\Core\Cache\RefinableCacheableDependencyInterface;
use Drupal\Core\Entity\EntityTypeManagerInterface;
use Drupal\Core\Plugin\ContainerFactoryPluginInterface;
use Drupal\graphql\Plugin\GraphQL\DataProducer\DataProducerPluginBase;
use Drupal\nyx_graphql\Wrappers\QueryConnection;
use GraphQL\Error\UserError;
use Symfony\Component\DependencyInjection\ContainerInterface;

/**
 * @DataProducer(
 *   id = "query_entities",
 *   name = @Translation("Load Entities"),
 *   description = @Translation("Loads a list of entities."),
 *   produces = @ContextDefinition("any",
 *     label = @Translation("Entity connection")
 *   ),
 *   consumes = {
 *     "bundle" = @ContextDefinition("string",
 *       label = @Translation("Entity bundle"),
 *       required = FALSE
 *     ),
 *     "type" = @ContextDefinition("string",
 *       label = @Translation("Entity type"),
 *       required = TRUE
 *     ),
 *     "offset" = @ContextDefinition("integer",
 *       label = @Translation("Offset"),
 *       required = FALSE
 *     ),
 *     "limit" = @ContextDefinition("integer",
 *       label = @Translation("Limit"),
 *       required = FALSE
 *     ),
 *      "filters" = @ContextDefinition("any",
 *       label = @Translation("Filters"),
 *       required = FALSE
 *     )
 *   }
 * )
 */
class QueryEntity extends DataProducerPluginBase implements ContainerFactoryPluginInterface {

  const MAX_LIMIT = 100;

  /**
   * @var \Drupal\Core\Entity\EntityTypeManagerInterface
   */
  protected $entityManager;

  /**
   * {@inheritdoc}
   *
   * @codeCoverageIgnore
   */
  public static function create(ContainerInterface $container, array $configuration, $plugin_id, $plugin_definition) {
    return new static(
      $configuration,
      $plugin_id,
      $plugin_definition,
      $container->get('entity.manager')
    );
  }

  /**
   * Beer Project constructor.
   *
   * @param array $configuration
   *   The plugin configuration.
   * @param string $pluginId
   *   The plugin id.
   * @param mixed $pluginDefinition
   *   The plugin definition.
   *
   * @param \Drupal\Core\Entity\EntityTypeManagerInterface $entityManager
   *
   * @codeCoverageIgnore
   */
  public function __construct(
    array $configuration,
    $pluginId,
    $pluginDefinition,
    EntityTypeManagerInterface $entityManager
  ) {
    parent::__construct($configuration, $pluginId, $pluginDefinition);
    $this->entityManager = $entityManager;
  }

  /**
   * @param $bundle
   * @param $type
   * @param $offset
   * @param $limit
   * @param $filters
   * @param \Drupal\Core\Cache\RefinableCacheableDependencyInterface $metadata
   *
   * @return \Drupal\nyx_graphql\Wrappers\QueryConnection
   * @throws \Drupal\Component\Plugin\Exception\InvalidPluginDefinitionException
   * @throws \Drupal\Component\Plugin\Exception\PluginNotFoundException
   */
  public function resolve($bundle, $type, $offset, $limit, $filters = [], RefinableCacheableDependencyInterface $metadata) {
    if (!$limit > static::MAX_LIMIT) {
      throw new UserError(sprintf('Exceeded maximum query limit: %s.', static::MAX_LIMIT));
    }

    $storage = $this->entityManager->getStorage($type);
    $type = $storage->getEntityType();
    $query = $storage->getQuery()
      ->currentRevision()
      ->accessCheck();

    if ($bundle)
      $query->condition($type->getKey('bundle'), $bundle);

    if (count($filters)) {
      foreach ($filters as $filter) {
        $filter['operator'] = key_exists('operator',$filter) ? $filter['operator'] : "=";
        $query->condition($filter['key'],$filter['value'],$filter['operator']);
      }
    }

    $query->range($offset, $limit);

    $metadata->addCacheTags($type->getListCacheTags());
    $metadata->addCacheContexts($type->getListCacheContexts());

    return new QueryConnection($query);
  }
}
