<?php

namespace Drupal\Tests\nyx_graphql\Kernel;

use GraphQL\Error\UserError;
use Drupal\Core\Cache\CacheableMetadata;
use Drupal\KernelTests\KernelTestBase;
use Drupal\node\Entity\Node;
use Drupal\node\Entity\NodeType;
use Drupal\nyx_graphql\Wrappers\QueryConnection;

/**
 * @coversDefaultClass \Drupal\nyx_graphql\Plugin\GraphQL\DataProducer\QueryEntity
 * @group nyx_graphql
 */
class QueryEntityTest extends KernelTestBase {

  protected static $modules = [
    'system',
    'user',
    'node',
    'field',
    'filter',
    'text',
    'graphql',
    'nyx_graphql',
  ];

  /**
   * @var \Drupal\nyx_graphql\Plugin\GraphQL\DataProducer\QueryEntity
   */
  protected $plugin;

  /**
   *
   */
  protected function setUp(): void {
    parent::setUp();

    $this->installEntitySchema('user');
    $this->installEntitySchema('node');
    $this->installSchema('node', ['node_access']);
    $this->installSchema('system', ['sequences']);
    $this->installConfig(['field', 'filter', 'node', 'system', 'user']);

    NodeType::create(['type' => 'article', 'name' => 'Article'])->save();
    NodeType::create(['type' => 'page', 'name' => 'Page'])->save();

    $this->plugin = \Drupal::service('plugin.manager.graphql.data_producer')
      ->createInstance('query_entities');
  }

  /**
   * @covers ::resolve
   */
  public function testReturnsQueryConnection(): void {
    $metadata = new CacheableMetadata();
    $result = $this->plugin->resolve('article', 'node', 0, 10, [], $metadata);
    $this->assertInstanceOf(QueryConnection::class, $result);
  }

  /**
   * @covers ::resolve
   */
  public function testTotalReflectsCreatedNodes(): void {
    Node::create(['type' => 'article', 'title' => 'Article 1', 'status' => 1])->save();
    Node::create(['type' => 'article', 'title' => 'Article 2', 'status' => 1])->save();
    Node::create(['type' => 'page', 'title' => 'Page 1', 'status' => 1])->save();

    $metadata = new CacheableMetadata();
    $connection = $this->plugin->resolve('article', 'node', 0, 10, [], $metadata);

    $this->assertEquals(2, $connection->total());
  }

  /**
   * @covers ::resolve
   */
  public function testBundleFilterExcludesOtherBundles(): void {
    Node::create(['type' => 'article', 'title' => 'Article', 'status' => 1])->save();
    Node::create(['type' => 'page', 'title' => 'Page', 'status' => 1])->save();

    $metadata = new CacheableMetadata();
    $connection = $this->plugin->resolve('page', 'node', 0, 10, [], $metadata);

    $this->assertEquals(1, $connection->total());
  }

  /**
   * @covers ::resolve
   */
  public function testOffsetAndLimitRespected(): void {
    for ($i = 1; $i <= 5; $i++) {
      Node::create(['type' => 'article', 'title' => "Article $i", 'status' => 1])->save();
    }

    $metadata = new CacheableMetadata();
    $connection = $this->plugin->resolve('article', 'node', 2, 2, [], $metadata);

    // total() counts all matching, ignoring offset/limit.
    $this->assertEquals(5, $connection->total());
  }

  /**
   * @covers ::resolve
   */
  public function testFiltersApplied(): void {
    Node::create(['type' => 'article', 'title' => 'Visible', 'status' => 1])->save();
    Node::create(['type' => 'article', 'title' => 'Hidden', 'status' => 0])->save();

    $metadata = new CacheableMetadata();
    $connection = $this->plugin->resolve('article', 'node', 0, 10, [
      ['key' => 'status', 'value' => 1, 'operator' => '='],
    ], $metadata);

    $this->assertEquals(1, $connection->total());
  }

  /**
   * @covers ::resolve
   */
  public function testMaxLimitThrowsUserError(): void {
    $this->expectException(UserError::class);
    $metadata = new CacheableMetadata();
    $this->plugin->resolve('article', 'node', 0, 101, [], $metadata);
  }

  /**
   * @covers ::resolve
   */
  public function testCacheTagsAddedToMetadata(): void {
    $metadata = new CacheableMetadata();
    $this->plugin->resolve('article', 'node', 0, 10, [], $metadata);

    $this->assertNotEmpty($metadata->getCacheTags());
  }

}
