<?php

namespace Drupal\Tests\nyx_graphql\Kernel;

use Drupal\KernelTests\KernelTestBase;
use Drupal\Tests\nyx_graphql\Traits\GraphqlDrupal11CompatibilityTrait;

/**
 * @coversDefaultClass \Drupal\nyx_graphql\Plugin\GraphQL\DataProducer\MultiValue
 * @group nyx_graphql
 */
class MultiValueTest extends KernelTestBase {

  use GraphqlDrupal11CompatibilityTrait;

  protected static $modules = ['system', 'graphql', 'nyx_graphql'];

  /**
   * @var \Drupal\nyx_graphql\Plugin\GraphQL\DataProducer\MultiValue
   */
  protected $plugin;

  /**
   *
   */
  protected function setUp(): void {
    $this->skipIfDrupal11FileUploadIncompatible();
    parent::setUp();
    $this->plugin = \Drupal::service('plugin.manager.graphql.data_producer')
      ->createInstance('multi_value');
  }

  /**
   * @covers ::resolve
   */
  public function testResolveExtractsValues(): void {
    $values = [['value' => 'alpha'], ['value' => 'beta'], ['value' => 'gamma']];
    $result = $this->plugin->resolve($values);
    $this->assertEquals(['alpha', 'beta', 'gamma'], $result);
  }

  /**
   * @covers ::resolve
   */
  public function testResolveEmptyReturnsEmptyArray(): void {
    $result = $this->plugin->resolve([]);
    $this->assertEquals([], $result);
  }

  /**
   * @covers ::resolve
   */
  public function testResolveSingleValue(): void {
    $result = $this->plugin->resolve([['value' => 'only']]);
    $this->assertEquals(['only'], $result);
  }

  /**
   * @covers ::resolve
   */
  public function testResolvePreservesOrder(): void {
    $values = [
      ['value' => 'third'],
      ['value' => 'first'],
      ['value' => 'second'],
    ];
    $result = $this->plugin->resolve($values);
    $this->assertEquals(['third', 'first', 'second'], $result);
  }

}
