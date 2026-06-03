<?php

namespace Drupal\Tests\pece_project\Unit;

use Drupal\Core\Extension\ModuleHandlerInterface;
use Drupal\pece_project\Plugin\GraphQL\SchemaExtension\ProjectExtension;
use Drupal\Tests\UnitTestCase;

/**
 * @coversDefaultClass \Drupal\pece_project\Plugin\GraphQL\SchemaExtension\ProjectExtension
 * @group pece_project
 */
class ProjectExtensionTest extends UnitTestCase {

  protected ProjectExtension $extension;

  protected function setUp(): void {
    parent::setUp();
    $moduleHandler = $this->createMock(ModuleHandlerInterface::class);
    $this->extension = new ProjectExtension([], 'project_extension', [], $moduleHandler);
  }

  public function testEntityTypeIsNode(): void {
    $this->assertEquals('node', $this->readEntityProperty()['type']);
  }

  public function testEntityBundleIsPeceProject(): void {
    $this->assertEquals('pece_project', $this->readEntityProperty()['bundle']);
  }

  public function testEntityPluralIsPeceProjects(): void {
    $this->assertEquals('peceProjects', $this->readEntityProperty()['plural']);
  }

  private function readEntityProperty(): array {
    $prop = new \ReflectionProperty($this->extension, 'entity');
    $prop->setAccessible(TRUE);
    return $prop->getValue($this->extension);
  }

}
