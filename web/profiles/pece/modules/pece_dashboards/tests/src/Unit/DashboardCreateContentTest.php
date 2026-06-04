<?php

namespace Drupal\Tests\pece_dashboards\Unit;

use Drupal\Core\DependencyInjection\ContainerBuilder;
use Drupal\Core\Entity\EntityTypeBundleInfoInterface;
use Drupal\pece_dashboards\Plugin\Block\DashboardCreateContent;
use Drupal\Tests\UnitTestCase;

/**
 * @coversDefaultClass \Drupal\pece_dashboards\Plugin\Block\DashboardCreateContent
 * @group pece_dashboards
 */
class DashboardCreateContentTest extends UnitTestCase {

  /**
   * The block under test.
   *
   * @var \Drupal\pece_dashboards\Plugin\Block\DashboardCreateContent
   */
  protected DashboardCreateContent $block;

  /**
   * The full set of node bundles used to seed the bundle info mock.
   *
   * @var array
   */
  protected array $allBundles = [
    'page'                => ['label' => 'Basic page'],
    'article'             => ['label' => 'Article'],
    'pece_annotation'     => ['label' => 'Annotation'],
    'about_page'          => ['label' => 'About Page'],
    'pece_slideshow_image' => ['label' => 'Slideshow Image'],
    'pece_artifact_text'  => ['label' => 'Artifact - Text'],
    'pece_project'        => ['label' => 'Project'],
  ];

  /**
   * {@inheritdoc}
   */
  protected function setUp(): void {
    parent::setUp();

    $bundleInfo = $this->createMock(EntityTypeBundleInfoInterface::class);
    $bundleInfo->method('getBundleInfo')
      ->with('node')
      ->willReturn($this->allBundles);

    $container = new ContainerBuilder();
    $container->set('entity_type.bundle.info', $bundleInfo);
    $container->set('string_translation', $this->getStringTranslationStub());
    \Drupal::setContainer($container);

    $this->block = new DashboardCreateContent([], 'pece_dashboards_user_dashboard_add_content', []);
  }

  /**
   * @covers ::getExistingContentTypes
   */
  public function testDefaultSkipTypesAreExcluded(): void {
    $types = $this->block->getExistingContentTypes([
      'about_page',
      'pece_annotation',
      'page',
      'pece_slideshow_image',
    ]);

    $this->assertArrayNotHasKey('about_page', $types);
    $this->assertArrayNotHasKey('pece_annotation', $types);
    $this->assertArrayNotHasKey('page', $types);
    $this->assertArrayNotHasKey('pece_slideshow_image', $types);
  }

  /**
   * @covers ::getExistingContentTypes
   */
  public function testNonSkippedTypesArePresent(): void {
    $types = $this->block->getExistingContentTypes([
      'about_page',
      'pece_annotation',
      'page',
      'pece_slideshow_image',
    ]);

    $this->assertArrayHasKey('article', $types);
    $this->assertArrayHasKey('pece_artifact_text', $types);
    $this->assertArrayHasKey('pece_project', $types);
  }

  /**
   * @covers ::getExistingContentTypes
   */
  public function testResultIsSortedAlphabeticallyByLabel(): void {
    $types = $this->block->getExistingContentTypes([]);
    $labels = array_values($types);
    $sorted = $labels;
    sort($sorted);
    $this->assertEquals($sorted, $labels);
  }

  /**
   * @covers ::getExistingContentTypes
   */
  public function testEmptySkipTypesReturnsAllBundles(): void {
    $types = $this->block->getExistingContentTypes([]);
    $this->assertCount(count($this->allBundles), $types);
  }

}
