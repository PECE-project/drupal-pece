<?php

namespace Drupal\pece_ai\Service;

use Drupal\Core\Config\ConfigFactoryInterface;
use Drupal\Core\Database\Connection;
use Drupal\Core\Entity\EntityTypeManagerInterface;

/**
 * Generates personalized discovery feed via weighted vector blending.
 */
class ActivityFeedService {

  public function __construct(
    private readonly Connection $database,
    private readonly ConfigFactoryInterface $configFactory,
    private readonly SimilarityService $similarityService,
    private readonly EntityTypeManagerInterface $entityTypeManager,
  ) {}

  /**
   * Returns ranked discovery feed items for a researcher.
   *
   * @param int $uid
   *   The researcher user ID.
   *
   * @return array
   *   Array of ['entity' => EntityInterface, 'score' => int].
   */
  public function getFeedForUser(int $uid): array {
    $config = $this->configFactory->get('pece_ai.settings');
    $activityLimit = (int) ($config->get('activity_limit') ?? 20);
    $feedLimit = (int) ($config->get('feed_limit') ?? 5);

    $query = $this->database->select('pece_ai_activity', 'a')
      ->fields('a', ['entity_type', 'entity_id'])
      ->condition('a.uid', $uid)
      ->range(0, $activityLimit);
    $query->addExpression('SUM(a.weight)', 'total_weight');
    $query->addExpression('MAX(a.timestamp)', 'last_seen');
    $query->groupBy('a.entity_type');
    $query->groupBy('a.entity_id');
    $query->orderBy('last_seen', 'DESC');
    $seeds = $query->execute()->fetchAll();

    if (empty($seeds)) {
      return [];
    }

    $blended = array_fill(0, 768, 0.0);
    $totalWeight = 0.0;
    $seenIds = [];

    foreach ($seeds as $seed) {
      $entity = $this->entityTypeManager
        ->getStorage($seed->entity_type)
        ->load($seed->entity_id);
      if (!$entity) {
        continue;
      }
      $vector = $this->similarityService->getVector($entity);
      if ($vector === NULL) {
        $seenIds[] = (int) $seed->entity_id;
        continue;
      }
      $w = (float) $seed->total_weight;
      foreach ($vector as $i => $v) {
        $blended[$i] += $v * $w;
      }
      $totalWeight += $w;
      $seenIds[] = (int) $seed->entity_id;
    }

    if ($totalWeight === 0.0) {
      return [];
    }

    $magnitude = sqrt(array_sum(array_map(fn($v) => $v * $v, $blended)));
    if ($magnitude > 0.0) {
      $blended = array_map(fn($v) => $v / $magnitude, $blended);
    }

    $groupIds = [];
    $userEntity = $this->entityTypeManager->getStorage('user')->load($uid);
    if ($userEntity
      && $userEntity->hasField('field_groups_with_view_access')
      && !$userEntity->get('field_groups_with_view_access')->isEmpty()
    ) {
      foreach ($userEntity->get('field_groups_with_view_access') as $item) {
        $groupIds[] = (string) $item->target_id;
      }
    }

    $hits = $this->similarityService->findSimilarByVector(
      $blended,
      $feedLimit + count($seenIds),
      $groupIds
    );

    $items = [];
    foreach ($hits as $hit) {
      if (in_array((int) $hit['entity_id'], $seenIds, TRUE)) {
        continue;
      }
      $entity = $this->entityTypeManager
        ->getStorage($hit['entity_type'])
        ->load($hit['entity_id']);
      if ($entity && $entity->access('view')) {
        $items[] = ['entity' => $entity, 'score' => $hit['score']];
      }
      if (count($items) >= $feedLimit) {
        break;
      }
    }

    return $items;
  }

}
