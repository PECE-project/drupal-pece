<?php

namespace Drupal\Tests\nyx_graphql\Kernel;

use Drupal\KernelTests\KernelTestBase;
use Drupal\node\Entity\Node;
use Drupal\node\Entity\NodeType;
use Drupal\user\Entity\User;

/**
 * @coversDefaultClass \Drupal\nyx_graphql\Plugin\GraphQL\DataProducer\Entity\CreateEntity
 * @group nyx_graphql
 */
class CreateEntityTest extends KernelTestBase {

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
   * @var \Drupal\nyx_graphql\Plugin\GraphQL\DataProducer\Entity\CreateEntity
   */
  protected $plugin;

  /**
   *
   */
  protected function setUp(): void {
    // drupal/graphql's file_upload service depends on file.validator which was
    // removed in Drupal 11. Skip until the contrib module adds support.
    if (version_compare(\Drupal::VERSION, '11.0', '>=')) {
      $this->markTestSkipped('drupal/graphql file_upload service incompatible with Drupal 11 (file.validator removed).');
    }
    parent::setUp();

    $this->installEntitySchema('user');
    $this->installEntitySchema('node');
    $this->installSchema('node', ['node_access']);
    $this->installSchema('system', ['sequences']);
    $this->installConfig(['field', 'filter', 'node', 'system', 'user']);

    NodeType::create(['type' => 'article', 'name' => 'Article'])->save();

    // Set an authenticated user as current user so Node::create() has an owner.
    $account = User::create(['name' => 'test_author', 'mail' => 'author@example.com', 'status' => 1]);
    $account->save();
    \Drupal::currentUser()->setAccount($account);

    $this->plugin = \Drupal::service('plugin.manager.graphql.data_producer')
      ->createInstance('create_entity');
  }

  /**
   * @covers ::resolve
   */
  public function testCreatesNodeAndReturnsIt(): void {
    $result = $this->plugin->resolve(
      ['title' => 'My Article'],
      'article',
      ['title' => 'title']
    );

    $this->assertInstanceOf(Node::class, $result);
    $this->assertNotNull($result->id());
    $this->assertEquals('article', $result->bundle());
  }

  /**
   * @covers ::resolve
   */
  public function testFieldMappingApplied(): void {
    $result = $this->plugin->resolve(
      ['title' => 'Mapped Title'],
      'article',
      ['title' => 'title']
    );

    $this->assertEquals('Mapped Title', $result->getTitle());
  }

  /**
   * @covers ::resolve
   */
  public function testUnmappedFieldsIgnored(): void {
    // 'body' is not in fieldsMap, so it should be ignored gracefully.
    $result = $this->plugin->resolve(
      ['title' => 'No Body', 'body' => 'Should be ignored'],
      'article',
      ['title' => 'title']
    );

    $this->assertInstanceOf(Node::class, $result);
    $this->assertEquals('No Body', $result->getTitle());
  }

  /**
   * @covers ::resolve
   */
  public function testNodePersistsInDatabase(): void {
    $this->plugin->resolve(
      ['title' => 'Persisted'],
      'article',
      ['title' => 'title']
    );

    $nodes = \Drupal::entityTypeManager()
      ->getStorage('node')
      ->loadByProperties(['title' => 'Persisted']);
    $this->assertCount(1, $nodes);
  }

  /**
   * @covers ::resolve
   */
  public function testMultipleNodesCreated(): void {
    $this->plugin->resolve(['title' => 'First'], 'article', ['title' => 'title']);
    $this->plugin->resolve(['title' => 'Second'], 'article', ['title' => 'title']);

    $nodes = \Drupal::entityTypeManager()
      ->getStorage('node')
      ->loadByProperties(['type' => 'article']);
    $this->assertCount(2, $nodes);
  }

}
