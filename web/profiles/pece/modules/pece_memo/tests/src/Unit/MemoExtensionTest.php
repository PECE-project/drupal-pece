<?php

namespace Drupal\Tests\pece_memo\Unit;

use Drupal\Core\Extension\ModuleHandlerInterface;
use Drupal\pece_memo\Plugin\GraphQL\SchemaExtension\MemoExtension;
use Drupal\Tests\UnitTestCase;

/**
 * @coversDefaultClass \Drupal\pece_memo\Plugin\GraphQL\SchemaExtension\MemoExtension
 * @group pece_memo
 */
class MemoExtensionTest extends UnitTestCase {

  protected MemoExtension $extension;

  protected function setUp(): void {
    parent::setUp();
    $moduleHandler = $this->createMock(ModuleHandlerInterface::class);
    $this->extension = new MemoExtension([], 'memo_extension', [], $moduleHandler);
  }

  public function testEntityTypeIsNode(): void {
    $this->assertEquals('node', $this->readEntityProperty()['type']);
  }

  public function testEntityBundleIsPeceMemo(): void {
    $this->assertEquals('pece_memo', $this->readEntityProperty()['bundle']);
  }

  public function testEntityPluralIsPeceMemos(): void {
    $this->assertEquals('peceMemos', $this->readEntityProperty()['plural']);
  }

  private function readEntityProperty(): array {
    $prop = new \ReflectionProperty($this->extension, 'entity');
    $prop->setAccessible(TRUE);
    return $prop->getValue($this->extension);
  }

}
