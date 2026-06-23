<?php

namespace Drupal\Tests\pece_annotations\Unit;

use Drupal\Core\DependencyInjection\ContainerBuilder;
use Drupal\Core\Entity\ContentEntityInterface;
use Drupal\Core\Entity\EntityStorageInterface;
use Drupal\Core\Entity\EntityTypeManagerInterface;
use Drupal\node\NodeTypeInterface;
use Drupal\pece_annotations\Plugin\ExtraField\Display\AnnotateButton;
use Drupal\Tests\UnitTestCase;

/**
 * @coversDefaultClass \Drupal\pece_annotations\Plugin\ExtraField\Display\AnnotateButton
 * @group pece_annotations
 */
class AnnotateButtonTest extends UnitTestCase {

  /**
   * @var \Drupal\pece_annotations\Plugin\ExtraField\Display\AnnotateButton
   */
  protected $plugin;

  /**
   *
   */
  protected function setUp(): void {
    parent::setUp();

    // Wire up a minimal container with entity_type.manager mock.
    $node_type = $this->createMock(NodeTypeInterface::class);
    $node_type->method('label')->willReturnCallback(function () {
      return 'Test Artifact';
    });

    $node_type_storage = $this->createMock(EntityStorageInterface::class);
    $node_type_storage->method('load')->willReturn($node_type);

    $entity_type_manager = $this->createMock(EntityTypeManagerInterface::class);
    $entity_type_manager->method('getStorage')
      ->with('node_type')
      ->willReturn($node_type_storage);

    $container = new ContainerBuilder();
    $container->set('entity_type.manager', $entity_type_manager);
    $container->set('string_translation', $this->getStringTranslationStub());
    \Drupal::setContainer($container);

    $this->plugin = new AnnotateButton([], 'pece_annotations_annotate_button', []);
  }

  /**
   * @covers ::view
   */
  public function testViewReturnsNullForGenericPageBundle(): void {
    $entity = $this->mockEntity('page', 1);
    $result = $this->plugin->view($entity);
    $this->assertNull($result);
  }

  /**
   * @covers ::view
   */
  public function testViewReturnsNullForUnrelatedBundle(): void {
    $entity = $this->mockEntity('pece_analytic', 99);
    $result = $this->plugin->view($entity);
    $this->assertNull($result);
  }

  /**
   * @covers ::view
   */
  public function testViewReturnsBuildForArtifactBundle(): void {
    $entity = $this->mockEntity('pece_artifact_image', 42);
    $result = $this->plugin->view($entity);
    $this->assertIsArray($result);
    $this->assertEquals('inline_template', $result['#type']);
    $this->assertStringContainsString('42', $result['#context']['url']);
    $this->assertStringContainsString('node/pece_annotation/step_1', $result['#context']['url']);
  }

  /**
   * @covers ::view
   */
  public function testViewReturnsBuildForEssayBundle(): void {
    $entity = $this->mockEntity('pece_essay', 7);
    $result = $this->plugin->view($entity);
    $this->assertIsArray($result);
    $this->assertStringContainsString('7', $result['#context']['url']);
  }

  /**
   * @covers ::view
   */
  public function testViewReturnsBuildForPeceMemoBundle(): void {
    $entity = $this->mockEntity('pece_memo', 5);
    $result = $this->plugin->view($entity);
    $this->assertIsArray($result);
    $this->assertStringContainsString('5', $result['#context']['url']);
  }

  /**
   * @covers ::view
   */
  public function testViewReturnsBuildForPhotoEssayBundle(): void {
    $entity = $this->mockEntity('pece_photo_essay', 11);
    $result = $this->plugin->view($entity);
    $this->assertIsArray($result);
  }

  /**
   * @covers ::view
   */
  public function testAnnotateLabelPresent(): void {
    $entity = $this->mockEntity('pece_artifact_pdf', 3);
    $result = $this->plugin->view($entity);
    $this->assertIsArray($result);
    $this->assertArrayHasKey('label', $result['#context']);
  }

  /**
   * Helper: create a mocked entity with the given bundle and ID.
   */
  private function mockEntity(string $bundle, int $id): ContentEntityInterface {
    $entity = $this->createMock(ContentEntityInterface::class);
    $entity->method('bundle')->willReturn($bundle);
    $entity->method('id')->willReturn($id);
    return $entity;
  }

}
