<?php

namespace Drupal\Tests\pece_ai\Kernel;

use Drupal\Core\Routing\RouteMatchInterface;
use Drupal\KernelTests\KernelTestBase;
use Drupal\node\Entity\Node;
use Drupal\node\Entity\NodeType;
use Drupal\pece_ai\Service\SimilarityService;

/**
 * Tests the RelatedContentBlock.
 *
 * @group pece_ai
 */
class RelatedContentBlockTest extends KernelTestBase {

  /**
   * {@inheritdoc}
   */
  protected static $modules = [
    'system', 'user', 'node', 'field', 'text', 'filter',
    'block', 'pece_ai',
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
    $this->installConfig(['system', 'user', 'node', 'filter', 'pece_ai']);
    NodeType::create(['type' => 'pece_essay', 'name' => 'PECE Essay'])->save();
  }

  /**
   * Tests that the block renders results returned by the similarity service.
   */
  public function testBlockRendersResultsFromSimilarityService(): void {
    $related = Node::create(['type' => 'pece_essay', 'title' => 'Related Essay', 'uid' => 0]);
    $related->save();
    $subject = Node::create(['type' => 'pece_essay', 'title' => 'Subject', 'uid' => 0]);
    $subject->save();

    $mockSimilarity = $this->createMock(SimilarityService::class);
    $mockSimilarity->method('getVector')->willReturn(array_fill(0, 768, 0.1));
    $mockSimilarity->method('findSimilar')->willReturn([
      ['entity_type' => 'node', 'entity_id' => $related->id(), 'score' => 92],
    ]);
    $this->container->set('pece_ai.similarity_service', $mockSimilarity);

    // Set up a fake route match providing the subject node.
    $routeMatch = $this->createMock(RouteMatchInterface::class);
    $routeMatch->method('getParameter')->with('node')->willReturn($subject);
    $this->container->set('current_route_match', $routeMatch);

    $block = $this->container->get('plugin.manager.block')
      ->createInstance('pece_ai_related_content', []);
    $build = $block->build();

    $this->assertEquals('pece_ai_related_content', $build['#theme']);
    $this->assertCount(1, $build['#items']);
    $this->assertEquals(92, $build['#items'][0]['score']);
  }

  /**
   * Tests that the block renders a pending message when no vector is stored.
   */
  public function testBlockRendersPendingStateWhenVectorAbsent(): void {
    $subject = Node::create(['type' => 'pece_essay', 'title' => 'Subject', 'uid' => 0]);
    $subject->save();

    $mockSimilarity = $this->createMock(SimilarityService::class);
    $mockSimilarity->method('getVector')->willReturn(NULL);
    $mockSimilarity->method('findSimilar')->willReturn([]);
    $this->container->set('pece_ai.similarity_service', $mockSimilarity);

    $routeMatch = $this->createMock(RouteMatchInterface::class);
    $routeMatch->method('getParameter')->with('node')->willReturn($subject);
    $this->container->set('current_route_match', $routeMatch);

    $block = $this->container->get('plugin.manager.block')
      ->createInstance('pece_ai_related_content', []);
    $build = $block->build();

    $this->assertStringContainsString('being indexed', (string) ($build['#markup'] ?? ''));
  }

  /**
   * Tests that the block returns an empty array when there is no current node.
   */
  public function testBlockReturnsEmptyArrayWithoutNode(): void {
    $routeMatch = $this->createMock(RouteMatchInterface::class);
    $routeMatch->method('getParameter')->with('node')->willReturn(NULL);
    $this->container->set('current_route_match', $routeMatch);

    $block = $this->container->get('plugin.manager.block')
      ->createInstance('pece_ai_related_content', []);
    $build = $block->build();

    $this->assertEmpty($build);
  }

}
