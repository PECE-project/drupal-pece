<?php

namespace Drupal\pece_ai\Commands;

use Drupal\Core\Config\ConfigFactoryInterface;
use Drupal\Core\Entity\EntityTypeManagerInterface;
use Drupal\Core\Queue\QueueFactory;
use Drupal\pece_ai\Service\EmbeddingService;
use Drupal\pece_ai\Service\SimilarityService;
use Drush\Attributes as CLI;
use Drush\Commands\DrushCommands;
use GuzzleHttp\Exception\GuzzleException;

/**
 * Drush commands for the pece_ai module.
 */
class PeceAiCommands extends DrushCommands {

  /**
   * Constructs PeceAiCommands.
   */
  public function __construct(
    private readonly EntityTypeManagerInterface $entityTypeManager,
    private readonly QueueFactory $queueFactory,
    private readonly EmbeddingService $embeddingService,
    private readonly SimilarityService $similarityService,
    private readonly ConfigFactoryInterface $configFactory,
  ) {
    parent::__construct();
  }

  /**
   * Create the Qdrant collection for PECE entities. Run once after deploy.
   */
  #[CLI\Command(name: 'pece-ai:setup', aliases: ['pece-ai-setup'])]
  #[CLI\Help(description: 'Create the Qdrant collection for PECE entities. Run once after deploy.')]
  public function setup(): void {
    $config = $this->configFactory->get('pece_ai.settings');
    $qdrantUrl = $config->get('qdrant_url');

    /** @var \GuzzleHttp\ClientInterface $httpClient */
    $httpClient = \Drupal::service('http_client'); // @phpcs:ignore DrupalPractice.Objects.GlobalDrupal.GlobalDrupal

    try {
      $httpClient->request('PUT', $qdrantUrl . '/collections/' . SimilarityService::COLLECTION, [
        'json' => [
          'vectors' => ['size' => 768, 'distance' => 'Cosine'],
          'payload_schema' => [
            'entity_type' => ['data_type' => 'keyword'],
            'entity_id' => ['data_type' => 'integer'],
            'bundle' => ['data_type' => 'keyword'],
            'group_ids' => ['data_type' => 'keyword'],
          ],
        ],
      ]);
      $this->output()->writeln('<info>Qdrant collection created successfully.</info>');
    }
    catch (GuzzleException $e) {
      $this->output()->writeln('<error>Failed: ' . $e->getMessage() . '</error>');
    }
  }

  /**
   * Queue all existing enabled-bundle entities for embedding.
   */
  #[CLI\Command(name: 'pece-ai:backfill', aliases: ['pece-ai-backfill'])]
  #[CLI\Help(description: 'Queue all existing enabled-bundle entities for embedding.')]
  public function backfill(): void {
    $config = $this->configFactory->get('pece_ai.settings');
    $enabledBundles = $config->get('enabled_bundles') ?? [];
    $queue = $this->queueFactory->get('pece_ai_embed');
    $count = 0;

    foreach ($enabledBundles as $key) {
      [$entityType, $bundle] = explode(':', $key, 2);
      $storage = $this->entityTypeManager->getStorage($entityType);
      $ids = $storage->getQuery()
        ->condition($storage->getEntityType()->getKey('bundle'), $bundle)
        ->accessCheck(FALSE)
        ->execute();

      foreach ($ids as $id) {
        $queue->createItem(['entity_type' => $entityType, 'entity_id' => $id]);
        $count++;
      }
    }

    $this->output()->writeln("<info>Queued {$count} entities for embedding.</info>");
    $this->output()->writeln('<info>Run `drush queue:run pece_ai_embed` to process.</info>');
  }

}
