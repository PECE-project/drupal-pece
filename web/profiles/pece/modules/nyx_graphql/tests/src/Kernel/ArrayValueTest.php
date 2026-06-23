<?php

namespace Drupal\Tests\nyx_graphql\Kernel;

use Drupal\KernelTests\KernelTestBase;

/**
 * @coversDefaultClass \Drupal\nyx_graphql\Plugin\GraphQL\DataProducer\ArrayValue
 * @group nyx_graphql
 */
class ArrayValueTest extends KernelTestBase {

  protected static $modules = ['system', 'graphql', 'nyx_graphql'];

  /**
   * @var \Drupal\nyx_graphql\Plugin\GraphQL\DataProducer\ArrayValue
   */
  protected $plugin;

  /**
   *
   */
  protected function setUp(): void {
    parent::setUp();
    $this->plugin = \Drupal::service('plugin.manager.graphql.data_producer')
      ->createInstance('array_value');
  }

  /**
   * @covers ::resolve
   */
  public function testResolveSingleKey(): void {
    $result = $this->plugin->resolve(['foo' => 'bar'], 'foo');
    $this->assertEquals('bar', $result);
  }

  /**
   * @covers ::resolve
   */
  public function testResolveDotNotation(): void {
    $result = $this->plugin->resolve(['a' => ['b' => 'value']], 'a.b');
    $this->assertEquals('value', $result);
  }

  /**
   * @covers ::resolve
   */
  public function testResolveDeepNested(): void {
    $data = ['level1' => ['level2' => ['level3' => 'deep']]];
    $result = $this->plugin->resolve($data, 'level1.level2.level3');
    $this->assertEquals('deep', $result);
  }

  /**
   * @covers ::resolve
   */
  public function testResolveIntegerIndex(): void {
    $result = $this->plugin->resolve([0 => 'first', 1 => 'second'], '0');
    $this->assertEquals('first', $result);
  }

  /**
   * @covers ::resolve
   */
  public function testResolveMixedPathWithDotNotation(): void {
    $data = ['items' => [0 => ['value' => 'item_value']]];
    $result = $this->plugin->resolve($data, 'items.0.value');
    $this->assertEquals('item_value', $result);
  }

}
