<?php

namespace Drupal\Tests\pece_ai\Kernel;

use Drupal\KernelTests\KernelTestBase;
use Drupal\node\Entity\Node;
use Drupal\node\Entity\NodeType;
use Drupal\user\Entity\User;
use Drupal\pece_ai\Service\SimilarityService;

/**
 * Tests the ActivityFeedService.
 *
 * @group pece_ai
 */
class ActivityFeedServiceTest extends KernelTestBase {

  /**
   * {@inheritdoc}
   */
  protected static $modules = [
    'system', 'user', 'node', 'field', 'text', 'filter', 'pece_ai',
  ];

  /**
   * {@inheritdoc}
   */
  protected function setUp(): void {
    parent::setUp();
    $this->installEntitySchema('user');
    $this->installEntitySchema('node');
    $this->installSchema('system', ['sequences']);
    $this->installSchema('node', ['node_access']);
    $this->installSchema('pece_ai', ['pece_ai_activity']);
    $this->installConfig(['system', 'user', 'node', 'filter', 'pece_ai']);
    NodeType::create(['type' => 'pece_essay', 'name' => 'PECE Essay'])->save();
    user_role_grant_permissions('anonymous', ['access content']);
  }

  /**
   * Inserts a direct activity row for testing.
   */
  private function insertActivity(int $uid, string $entityType, int $entityId, int $weight): void {
    \Drupal::database()->insert('pece_ai_activity')->fields([
      'uid' => $uid,
      'entity_type' => $entityType,
      'entity_id' => $entityId,
      'weight' => $weight,
      'timestamp' => \Drupal::time()->getRequestTime(),
    ])->execute();
  }

  /**
   * Tests that empty activity returns an empty feed.
   */
  public function testEmptyActivityReturnsEmptyFeed(): void {
    $user = User::create(['name' => 'researcher', 'status' => 1]);
    $user->save();

    $mockSimilarity = $this->createMock(SimilarityService::class);
    $mockSimilarity->expects($this->never())->method('findSimilarByVector');
    $this->container->set('pece_ai.similarity_service', $mockSimilarity);

    $service = $this->container->get('pece_ai.activity_feed_service');
    $result = $service->getFeedForUser((int) $user->id());

    $this->assertEmpty($result);
  }

  /**
   * Tests that entities already in activity are excluded from results.
   */
  public function testAlreadySeenEntitiesExcludedFromFeed(): void {
    $user = User::create(['name' => 'researcher2', 'status' => 1]);
    $user->save();
    $seen = Node::create(['type' => 'pece_essay', 'title' => 'Seen', 'uid' => $user->id()]);
    $seen->save();
    $related = Node::create(['type' => 'pece_essay', 'title' => 'Related', 'uid' => $user->id()]);
    $related->save();

    $this->insertActivity((int) $user->id(), 'node', (int) $seen->id(), 3);

    $vector = array_fill(0, 768, 0.1);
    $mockSimilarity = $this->createMock(SimilarityService::class);
    $mockSimilarity->method('getVector')->willReturn($vector);
    $mockSimilarity->method('findSimilarByVector')->willReturn([
      ['entity_type' => 'node', 'entity_id' => (int) $seen->id(), 'score' => 95],
      ['entity_type' => 'node', 'entity_id' => (int) $related->id(), 'score' => 88],
    ]);
    $this->container->set('pece_ai.similarity_service', $mockSimilarity);

    $service = $this->container->get('pece_ai.activity_feed_service');
    $result = $service->getFeedForUser((int) $user->id());

    $this->assertCount(1, $result);
    $this->assertEquals($related->id(), $result[0]['entity']->id());
  }

  /**
   * Tests that entities with null vectors are skipped without error.
   */
  public function testNullVectorsSkippedGracefully(): void {
    $user = User::create(['name' => 'researcher3', 'status' => 1]);
    $user->save();
    $node = Node::create(['type' => 'pece_essay', 'title' => 'Unindexed', 'uid' => $user->id()]);
    $node->save();

    $this->insertActivity((int) $user->id(), 'node', (int) $node->id(), 1);

    $mockSimilarity = $this->createMock(SimilarityService::class);
    $mockSimilarity->method('getVector')->willReturn(NULL);
    $mockSimilarity->expects($this->never())->method('findSimilarByVector');
    $this->container->set('pece_ai.similarity_service', $mockSimilarity);

    $service = $this->container->get('pece_ai.activity_feed_service');
    $result = $service->getFeedForUser((int) $user->id());

    $this->assertEmpty($result);
  }

}
