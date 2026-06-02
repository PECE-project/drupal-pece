<?php

namespace Drupal\Tests\pece_ai\Kernel;

use Drupal\KernelTests\KernelTestBase;
use Drupal\node\Entity\Node;
use Drupal\node\Entity\NodeType;
use Drupal\user\Entity\User;
use Drupal\pece_ai\Service\ActivityFeedService;

/**
 * Tests the DiscoveryFeedBlock.
 *
 * @group pece_ai
 */
class DiscoveryFeedBlockTest extends KernelTestBase {

  /**
   * {@inheritdoc}
   */
  protected static $modules = [
    'system', 'user', 'node', 'field', 'text', 'filter', 'block', 'pece_ai',
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
   * Tests that the block renders items when the feed returns results.
   */
  public function testBlockRendersFeedItems(): void {
    $user = User::create(['name' => 'researcher', 'status' => 1]);
    $user->save();
    $node = Node::create(['type' => 'pece_essay', 'title' => 'Suggested Essay', 'uid' => $user->id()]);
    $node->save();

    $mockFeed = $this->createMock(ActivityFeedService::class);
    $mockFeed->method('getFeedForUser')->willReturn([
      ['entity' => $node, 'score' => 88],
    ]);
    $this->container->set('pece_ai.activity_feed_service', $mockFeed);
    $this->container->get('current_user')->setAccount($user);

    $block = $this->container->get('plugin.manager.block')
      ->createInstance('pece_ai_discovery_feed', []);
    $build = $block->build();

    $this->assertEquals('pece_ai_related_content', $build['#theme']);
    $this->assertCount(1, $build['#items']);
    $this->assertEquals(88, $build['#items'][0]['score']);
  }

  /**
   * Tests that the block renders an empty state message with no activity.
   */
  public function testBlockRendersEmptyStateWhenNoFeed(): void {
    $user = User::create(['name' => 'researcher2', 'status' => 1]);
    $user->save();

    $mockFeed = $this->createMock(ActivityFeedService::class);
    $mockFeed->method('getFeedForUser')->willReturn([]);
    $this->container->set('pece_ai.activity_feed_service', $mockFeed);
    $this->container->get('current_user')->setAccount($user);

    $block = $this->container->get('plugin.manager.block')
      ->createInstance('pece_ai_discovery_feed', []);
    $build = $block->build();

    $this->assertArrayHasKey('#markup', $build);
    $this->assertStringContainsString('exploring', (string) $build['#markup']);
  }

  /**
   * Tests that the block returns empty for anonymous users.
   */
  public function testBlockReturnsEmptyForAnonymous(): void {
    // current_user is anonymous by default in kernel tests.
    $block = $this->container->get('plugin.manager.block')
      ->createInstance('pece_ai_discovery_feed', []);
    $build = $block->build();

    $this->assertEmpty($build);
  }

}
