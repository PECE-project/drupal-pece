<?php

namespace Drupal\pece_ai\EventSubscriber;

use Drupal\Core\Config\ConfigFactoryInterface;
use Drupal\Core\Entity\EntityInterface;
use Drupal\Core\Queue\QueueFactory;

/**
 * Queues entities for AI embedding on insert/update.
 */
class EntityEmbedSubscriber {

  public function __construct(
    private readonly QueueFactory $queueFactory,
    private readonly ConfigFactoryInterface $configFactory,
  ) {}

  /**
   * Queues an entity for embedding if its bundle is enabled.
   */
  public function onEntitySave(EntityInterface $entity): void {
    $config = $this->configFactory->get('pece_ai.settings');
    $enabledBundles = $config->get('enabled_bundles') ?? [];
    $key = $entity->getEntityTypeId() . ':' . $entity->bundle();
    if (!in_array($key, $enabledBundles, TRUE)) {
      return;
    }
    $queue = $this->queueFactory->get('pece_ai_embed');
    $queue->createItem([
      'entity_type' => $entity->getEntityTypeId(),
      'entity_id' => $entity->id(),
    ]);
  }

}
