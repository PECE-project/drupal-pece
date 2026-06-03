<?php

namespace Drupal\Tests\pece_annotations\Unit;

use Drupal\Core\Extension\ModuleHandlerInterface;
use Drupal\pece_annotations\Plugin\GraphQL\SchemaExtension\AnnotationExtension;
use Drupal\Tests\UnitTestCase;

/**
 * @coversDefaultClass \Drupal\pece_annotations\Plugin\GraphQL\SchemaExtension\AnnotationExtension
 * @group pece_annotations
 */
class AnnotationExtensionTest extends UnitTestCase {

  protected AnnotationExtension $extension;

  protected function setUp(): void {
    parent::setUp();
    $moduleHandler = $this->createMock(ModuleHandlerInterface::class);
    $this->extension = new AnnotationExtension([], 'annotation_extension', [], $moduleHandler);
  }

  public function testEntityTypeIsNode(): void {
    $this->assertEquals('node', $this->readEntityProperty()['type']);
  }

  public function testEntityBundleIsPeceAnnotation(): void {
    $this->assertEquals('pece_annotation', $this->readEntityProperty()['bundle']);
  }

  public function testEntityPluralIsPeceAnnotations(): void {
    $this->assertEquals('peceAnnotations', $this->readEntityProperty()['plural']);
  }

  private function readEntityProperty(): array {
    $prop = new \ReflectionProperty($this->extension, 'entity');
    $prop->setAccessible(TRUE);
    return $prop->getValue($this->extension);
  }

}
