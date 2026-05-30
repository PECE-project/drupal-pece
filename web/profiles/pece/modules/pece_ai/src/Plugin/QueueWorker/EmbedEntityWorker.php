<?php

namespace Drupal\pece_ai\Plugin\QueueWorker;

use Drupal\Core\Entity\EntityTypeManagerInterface;
use Drupal\Core\Plugin\ContainerFactoryPluginInterface;
use Drupal\Core\Queue\QueueWorkerBase;
use Drupal\pece_ai\Service\EmbeddingService;
use Drupal\pece_ai\Service\SimilarityService;
use Symfony\Component\DependencyInjection\ContainerInterface;

/**
 * Processes entities queued for vector embedding.
 *
 * @QueueWorker(
 *   id = "pece_ai_embed",
 *   title = @Translation("Embed entity for semantic search"),
 *   cron = {"time" = 30}
 * )
 */
class EmbedEntityWorker extends QueueWorkerBase implements ContainerFactoryPluginInterface {

  /**
   * Constructs an EmbedEntityWorker.
   *
   * @param array $configuration
   *   Plugin configuration.
   * @param string $plugin_id
   *   The plugin ID.
   * @param mixed $plugin_definition
   *   The plugin definition.
   * @param \Drupal\Core\Entity\EntityTypeManagerInterface $entityTypeManager
   *   The entity type manager.
   * @param \Drupal\pece_ai\Service\EmbeddingService $embeddingService
   *   The embedding service.
   * @param \Drupal\pece_ai\Service\SimilarityService $similarityService
   *   The similarity service.
   */
  public function __construct(
    array $configuration,
    $plugin_id,
    $plugin_definition,
    private readonly EntityTypeManagerInterface $entityTypeManager,
    private readonly EmbeddingService $embeddingService,
    private readonly SimilarityService $similarityService,
  ) {
    parent::__construct($configuration, $plugin_id, $plugin_definition);
  }

  /**
   * {@inheritdoc}
   */
  public static function create(ContainerInterface $container, array $configuration, $plugin_id, $plugin_definition): static {
    return new static(
      $configuration, $plugin_id, $plugin_definition,
      $container->get('entity_type.manager'),
      $container->get('pece_ai.embedding_service'),
      $container->get('pece_ai.similarity_service'),
    );
  }

  /**
   * {@inheritdoc}
   */
  public function processItem($data): void {
    $entity = $this->entityTypeManager
      ->getStorage($data['entity_type'])
      ->load($data['entity_id']);
    if (!$entity) {
      return;
    }
    $text = $this->embeddingService->extractText($entity);
    if (!$text) {
      return;
    }
    $vector = $this->embeddingService->embed($text);
    $this->similarityService->upsert($entity, $vector);
  }

}
