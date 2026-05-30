<?php

namespace Drupal\pece_ai\Service;

use Drupal\Core\Config\ConfigFactoryInterface;
use Drupal\Core\Entity\EntityInterface;
use Drupal\Core\Entity\EntityTypeManagerInterface;
use GuzzleHttp\ClientInterface;
use GuzzleHttp\Exception\GuzzleException;

/**
 * Provides vector similarity search via Qdrant.
 */
class SimilarityService {

  const COLLECTION = 'pece_entities';

  public function __construct(
    private readonly ClientInterface $httpClient,
    private readonly ConfigFactoryInterface $configFactory,
    private readonly EntityTypeManagerInterface $entityTypeManager,
  ) {}

  /**
   * Upserts an entity's vector into Qdrant.
   *
   * @param \Drupal\Core\Entity\EntityInterface $entity
   *   The entity to index.
   * @param array $vector
   *   The embedding vector.
   */
  public function upsert(EntityInterface $entity, array $vector): void {
    $config = $this->configFactory->get('pece_ai.settings');
    $groupIds = [];
    if ($entity->hasField('field_groups_with_view_access') && !$entity->get('field_groups_with_view_access')->isEmpty()) {
      foreach ($entity->get('field_groups_with_view_access') as $item) {
        $groupIds[] = (string) $item->target_id;
      }
    }
    try {
      $this->httpClient->request('PUT',
        $config->get('qdrant_url') . '/collections/' . self::COLLECTION . '/points',
        [
          'json' => [
            'points' => [[
              'id' => (int) $entity->id(),
              'vector' => $vector,
              'payload' => [
                'entity_type' => $entity->getEntityTypeId(),
                'entity_id' => (int) $entity->id(),
                'bundle' => $entity->bundle(),
                'group_ids' => $groupIds,
              ],
            ],
            ],
          ],
        ]
      );
    }
    catch (GuzzleException $e) {
      throw new \RuntimeException('Failed to upsert entity to Qdrant: ' . $e->getMessage(), 0, $e);
    }
  }

  /**
   * Retrieves the stored vector for an entity from Qdrant.
   *
   * @param \Drupal\Core\Entity\EntityInterface $entity
   *   The entity whose vector to retrieve.
   *
   * @return array|null
   *   The vector, or NULL if not found or Qdrant is unavailable.
   */
  public function getVector(EntityInterface $entity): ?array {
    $config = $this->configFactory->get('pece_ai.settings');
    try {
      $response = $this->httpClient->request('GET',
        $config->get('qdrant_url') . '/collections/' . self::COLLECTION . '/points/' . (int) $entity->id(),
        ['query' => ['with_vector' => 'true']]
      );
      $data = json_decode($response->getBody()->getContents(), TRUE);
      return $data['result']['vector'] ?? NULL;
    }
    catch (GuzzleException $e) {
      return NULL;
    }
  }

  /**
   * Finds entities similar to the given vector using Qdrant search.
   *
   * @param array $vector
   *   The query vector.
   * @param int $limit
   *   Maximum number of results to return.
   * @param array $groupIds
   *   Optional list of group IDs to filter results by.
   * @param int $excludeId
   *   Optional Qdrant point ID to exclude from results (use for self-exclusion).
   *
   * @return array
   *   Array of result arrays with keys: entity_type, entity_id, score.
   */
  public function findSimilarByVector(array $vector, int $limit = 5, array $groupIds = [], int $excludeId = 0): array {
    $config = $this->configFactory->get('pece_ai.settings');
    $payload = ['vector' => $vector, 'limit' => $limit + 1, 'with_payload' => TRUE];
    if ($groupIds) {
      $payload['filter'] = [
        'must' => [['key' => 'group_ids', 'match' => ['any' => $groupIds]]],
      ];
    }
    try {
      $response = $this->httpClient->request('POST',
        $config->get('qdrant_url') . '/collections/' . self::COLLECTION . '/points/search',
        ['json' => $payload]
      );
      $data = json_decode($response->getBody()->getContents(), TRUE);
      $results = [];
      foreach ($data['result'] ?? [] as $hit) {
        if ($excludeId && (int) $hit['id'] === $excludeId) {
          continue;
        }
        $results[] = [
          'entity_type' => $hit['payload']['entity_type'],
          'entity_id' => (int) $hit['payload']['entity_id'],
          'score' => (int) round($hit['score'] * 100),
        ];
        if (count($results) >= $limit) {
          break;
        }
      }
      return $results;
    }
    catch (GuzzleException $e) {
      return [];
    }
  }

  /**
   * Finds entities similar to the given entity using vector search.
   *
   * @param \Drupal\Core\Entity\EntityInterface $entity
   *   The source entity.
   * @param int $limit
   *   Maximum number of results to return (excluding self).
   * @param array $groupIds
   *   Optional list of group IDs to filter results by.
   *
   * @return array
   *   Array of result arrays with keys: entity_type, entity_id, score.
   */
  public function findSimilar(EntityInterface $entity, int $limit = 5, array $groupIds = []): array {
    $vector = $this->getVector($entity);
    if ($vector === NULL) {
      return [];
    }
    return $this->findSimilarByVector($vector, $limit, $groupIds, (int) $entity->id());
  }

}
