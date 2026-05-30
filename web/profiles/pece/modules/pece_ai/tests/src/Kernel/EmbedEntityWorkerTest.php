<?php

namespace Drupal\Tests\pece_ai\Kernel;

use Drupal\KernelTests\KernelTestBase;
use Drupal\node\Entity\Node;
use Drupal\node\Entity\NodeType;
use Drupal\pece_ai\Service\EmbeddingService;
use Drupal\pece_ai\Service\SimilarityService;

/**
 * Tests the EmbedEntityWorker queue processor.
 *
 * @group pece_ai
 */
class EmbedEntityWorkerTest extends KernelTestBase {

  /**
   * {@inheritdoc}
   */
  protected static $modules = ['system', 'user', 'node', 'field', 'text', 'filter', 'pece_ai'];

  /**
   * {@inheritdoc}
   */
  protected function setUp(): void {
    parent::setUp();
    $this->installEntitySchema('user');
    $this->installEntitySchema('node');
    $this->installSchema('system', ['sequences']);
    $this->installSchema('node', ['node_access']);
    $this->installConfig(['system', 'user', 'node', 'filter', 'pece_ai']);
    NodeType::create(['type' => 'pece_essay', 'name' => 'PECE Essay'])->save();
  }

  /**
   * Tests that processItem calls embed and upsert for a valid entity.
   */
  public function testProcessItemCallsEmbedAndUpsert(): void {
    $node = Node::create(['type' => 'pece_essay', 'title' => 'Essay Title', 'uid' => 0]);
    $node->save();

    $mockEmbedding = $this->createMock(EmbeddingService::class);
    $mockEmbedding->method('extractText')->willReturn('Essay Title');
    $mockEmbedding->expects($this->once())
      ->method('embed')
      ->with('Essay Title')
      ->willReturn(array_fill(0, 768, 0.1));

    $mockSimilarity = $this->createMock(SimilarityService::class);
    $mockSimilarity->expects($this->once())->method('upsert');

    $this->container->set('pece_ai.embedding_service', $mockEmbedding);
    $this->container->set('pece_ai.similarity_service', $mockSimilarity);

    $worker = $this->container->get('plugin.manager.queue_worker')
      ->createInstance('pece_ai_embed');
    $worker->processItem(['entity_type' => 'node', 'entity_id' => $node->id()]);
  }

  /**
   * Tests that processItem silently skips a missing entity.
   */
  public function testProcessItemSkipsMissingEntity(): void {
    $mockEmbedding = $this->createMock(EmbeddingService::class);
    $mockEmbedding->expects($this->never())->method('embed');

    $mockSimilarity = $this->createMock(SimilarityService::class);
    $mockSimilarity->expects($this->never())->method('upsert');

    $this->container->set('pece_ai.embedding_service', $mockEmbedding);
    $this->container->set('pece_ai.similarity_service', $mockSimilarity);

    $worker = $this->container->get('plugin.manager.queue_worker')
      ->createInstance('pece_ai_embed');
    $worker->processItem(['entity_type' => 'node', 'entity_id' => 99999]);
  }

  /**
   * Tests that processItem silently skips an entity with no extractable text.
   */
  public function testProcessItemSkipsEntityWithNoText(): void {
    $node = Node::create(['type' => 'pece_essay', 'title' => 'Has Title', 'uid' => 0]);
    $node->save();

    $mockEmbedding = $this->createMock(EmbeddingService::class);
    $mockEmbedding->method('extractText')->willReturn('');
    $mockEmbedding->expects($this->never())->method('embed');

    $mockSimilarity = $this->createMock(SimilarityService::class);
    $mockSimilarity->expects($this->never())->method('upsert');

    $this->container->set('pece_ai.embedding_service', $mockEmbedding);
    $this->container->set('pece_ai.similarity_service', $mockSimilarity);

    $worker = $this->container->get('plugin.manager.queue_worker')
      ->createInstance('pece_ai_embed');
    $worker->processItem(['entity_type' => 'node', 'entity_id' => $node->id()]);
  }

}
