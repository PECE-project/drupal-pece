<?php

namespace Drupal\Tests\pece_subst_logic\Unit;

use Drupal\Core\Extension\ModuleHandlerInterface;
use Drupal\pece_subst_logic\Plugin\GraphQL\SchemaExtension\SubstantiveLogicExtension;
use Drupal\Tests\UnitTestCase;

/**
 * @coversDefaultClass \Drupal\pece_subst_logic\Plugin\GraphQL\SchemaExtension\SubstantiveLogicExtension
 * @group pece_subst_logic
 */
class SubstantiveLogicExtensionTest extends UnitTestCase {

  protected SubstantiveLogicExtension $extension;

  protected function setUp(): void {
    parent::setUp();
    $moduleHandler = $this->createMock(ModuleHandlerInterface::class);
    $this->extension = new SubstantiveLogicExtension([], 'substantive_logic_extension', [], $moduleHandler);
  }

  public function testEntityTypeIsNode(): void {
    $this->assertEquals('node', $this->readEntityProperty()['type']);
  }

  public function testEntityBundleIsPeceSubstantiveLogic(): void {
    $this->assertEquals('pece_substantive_logic', $this->readEntityProperty()['bundle']);
  }

  public function testEntityPluralIsPeceSubstantiveLogics(): void {
    $this->assertEquals('peceSubstantiveLogics', $this->readEntityProperty()['plural']);
  }

  private function readEntityProperty(): array {
    $prop = new \ReflectionProperty($this->extension, 'entity');
    $prop->setAccessible(TRUE);
    return $prop->getValue($this->extension);
  }

}
