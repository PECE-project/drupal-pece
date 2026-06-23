<?php

namespace Drupal\Tests\pece_annotations\Unit;

use Drupal\Core\DependencyInjection\ContainerBuilder;
use Drupal\Core\Entity\ContentEntityInterface;
use Drupal\Core\Entity\EntityStorageInterface;
use Drupal\Core\Entity\EntityTypeManagerInterface;
use Drupal\node\NodeTypeInterface;
use Drupal\pece_annotations\Plugin\ExtraField\Display\SeeAnnotationsLink;
use Drupal\Tests\UnitTestCase;

/**
 * @coversDefaultClass \Drupal\pece_annotations\Plugin\ExtraField\Display\SeeAnnotationsLink
 * @group pece_annotations
 */
class SeeAnnotationsLinkTest extends UnitTestCase {

  /**
   * @var \Drupal\pece_annotations\Plugin\ExtraField\Display\SeeAnnotationsLink
   */
  protected $plugin;

  /**
   *
   */
  protected function setUp(): void {
    parent::setUp();

    $node_type = $this->createMock(NodeTypeInterface::class);
    $node_type->method('label')->willReturn('Test Artifact');

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

    $this->plugin = new SeeAnnotationsLink([], 'pece_annotations_see_annotations_link', []);
  }

  /**
   * @covers ::view
   */
  public function testViewReturnsNullForPageBundle(): void {
    $entity = $this->mockEntity('page', 1);
    $result = $this->plugin->view($entity);
    $this->assertNull($result);
  }

  /**
   * @covers ::view
   */
  public function testViewReturnsBuildForArtifactBundle(): void {
    $entity = $this->mockEntity('pece_artifact_image', 15);
    $result = $this->plugin->view($entity);
    $this->assertIsArray($result);
    $this->assertEquals('inline_template', $result['#type']);
  }

  /**
   * @covers ::view
   */
  public function testUrlContainsEntityIdAsFilterParam(): void {
    $entity = $this->mockEntity('pece_artifact_pdf', 99);
    $result = $this->plugin->view($entity);
    $this->assertStringContainsString('annotated_artifact[0]=99', $result['#context']['url']);
    $this->assertStringContainsString('analyze', $result['#context']['url']);
  }

  /**
   * @covers ::view
   */
  public function testViewReturnsBuildForEssayBundle(): void {
    $entity = $this->mockEntity('pece_essay', 20);
    $result = $this->plugin->view($entity);
    $this->assertIsArray($result);
    $this->assertStringContainsString('20', $result['#context']['url']);
  }

  /**
   * @covers ::view
   */
  public function testViewReturnsBuildForPeceMemoBundle(): void {
    $entity = $this->mockEntity('pece_memo', 8);
    $result = $this->plugin->view($entity);
    $this->assertIsArray($result);
  }

  /**
   * @covers ::view
   */
  public function testLinkLabelAndTooltipPresent(): void {
    $entity = $this->mockEntity('pece_artifact_video', 3);
    $result = $this->plugin->view($entity);
    $this->assertArrayHasKey('label', $result['#context']);
    $this->assertArrayHasKey('tooltip', $result['#context']);
    $this->assertArrayHasKey('url', $result['#context']);
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
