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

  /**
   * The schema extension under test.
   *
   * @var \Drupal\pece_annotations\Plugin\GraphQL\SchemaExtension\AnnotationExtension
   */
  protected AnnotationExtension $extension;

  /**
   * {@inheritdoc}
   */
  protected function setUp(): void {
    parent::setUp();
    $moduleHandler = $this->createMock(ModuleHandlerInterface::class);
    $this->extension = new AnnotationExtension([], 'annotation_extension', [], $moduleHandler);
  }

  /**
   * Tests that the configured entity type is node.
   */
  public function testEntityTypeIsNode(): void {
    $this->assertEquals('node', $this->readEntityProperty()['type']);
  }

  /**
   * Tests that the configured entity bundle is pece_annotation.
   */
  public function testEntityBundleIsPeceAnnotation(): void {
    $this->assertEquals('pece_annotation', $this->readEntityProperty()['bundle']);
  }

  /**
   * Tests that the configured entity plural is peceAnnotations.
   */
  public function testEntityPluralIsPeceAnnotations(): void {
    $this->assertEquals('peceAnnotations', $this->readEntityProperty()['plural']);
  }

  /**
   * Reads the protected entity property via reflection.
   */
  private function readEntityProperty(): array {
    $prop = new \ReflectionProperty($this->extension, 'entity');
    $prop->setAccessible(TRUE);
    return $prop->getValue($this->extension);
  }

}
