<?php

namespace Drupal\Tests\pece_ai\Kernel;

use Drupal\KernelTests\KernelTestBase;
use Drupal\node\Entity\Node;
use Drupal\node\Entity\NodeType;

/**
 * Tests EntityEmbedSubscriber queues entities on save.
 *
 * @group pece_ai
 */
class EntityEmbedSubscriberTest extends KernelTestBase {

  protected static $modules = ['system', 'user', 'node', 'field', 'text', 'filter', 'pece_ai'];

  protected function setUp(): void {
    parent::setUp();
    $this->installEntitySchema('user');
    $this->installEntitySchema('node');
    $this->installSchema('system', ['sequences']);
    $this->installSchema('node', ['node_access']);
    $this->installConfig(['system', 'user', 'node', 'filter', 'pece_ai']);

    NodeType::create(['type' => 'pece_essay', 'name' => 'PECE Essay'])->save();
    NodeType::create(['type' => 'page', 'name' => 'Page'])->save();
  }

  public function testEnabledBundleQueuesItemOnInsert(): void {
    $queue = \Drupal::queue('pece_ai_embed');
    $this->assertEquals(0, $queue->numberOfItems());

    Node::create(['type' => 'pece_essay', 'title' => 'Test Essay', 'uid' => 0])->save();

    $this->assertEquals(1, $queue->numberOfItems());
    $item = $queue->claimItem();
    $this->assertEquals('node', $item->data['entity_type']);
  }

  public function testDisabledBundleDoesNotQueue(): void {
    $queue = \Drupal::queue('pece_ai_embed');

    Node::create(['type' => 'page', 'title' => 'A Page', 'uid' => 0])->save();

    $this->assertEquals(0, $queue->numberOfItems());
  }

  public function testUpdateAlsoQueuesItem(): void {
    $node = Node::create(['type' => 'pece_essay', 'title' => 'Original', 'uid' => 0]);
    $node->save();
    $queue = \Drupal::queue('pece_ai_embed');
    // Clear insert item.
    $queue->claimItem();
    $queue->deleteQueue();

    $node->setTitle('Updated')->save();

    $this->assertEquals(1, $queue->numberOfItems());
  }

}
