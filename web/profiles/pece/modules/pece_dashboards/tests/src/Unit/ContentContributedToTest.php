<?php

namespace Drupal\Tests\pece_dashboards\Unit;

use Drupal\Core\Cache\Context\CacheContextsManager;
use Drupal\Core\DependencyInjection\ContainerBuilder;
use Drupal\Core\Session\AccountProxyInterface;
use Drupal\pece_dashboards\Plugin\Block\ContentContributedTo;
use Drupal\Tests\UnitTestCase;

/**
 * @coversDefaultClass \Drupal\pece_dashboards\Plugin\Block\ContentContributedTo
 * @group pece_dashboards
 */
class ContentContributedToTest extends UnitTestCase {

  /**
   * The block under test.
   *
   * @var \Drupal\pece_dashboards\Plugin\Block\ContentContributedTo
   */
  protected ContentContributedTo $block;

  /**
   * {@inheritdoc}
   */
  protected function setUp(): void {
    parent::setUp();

    $account = $this->createMock(AccountProxyInterface::class);
    $account->method('id')->willReturn(42);

    $cacheContextsManager = $this->createMock(CacheContextsManager::class);
    $cacheContextsManager->method('assertValidTokens')->willReturn(TRUE);

    $container = new ContainerBuilder();
    $container->set('current_user', $account);
    $container->set('string_translation', $this->getStringTranslationStub());
    $container->set('cache_contexts_manager', $cacheContextsManager);
    \Drupal::setContainer($container);

    $this->block = new ContentContributedTo([], 'pece_dashboards_content_contributed_to', ['provider' => 'pece_dashboards']);
  }

  /**
   * @covers ::getCacheContexts
   */
  public function testCacheContextsIncludeUser(): void {
    $this->assertContains('user', $this->block->getCacheContexts());
  }

  /**
   * @covers ::build
   */
  public function testBuildReturnsBuildArrayWithButtonKey(): void {
    $build = $this->block->build();
    $this->assertArrayHasKey('button', $build);
    $this->assertEquals('component', $build['button']['#type']);
    $this->assertEquals('pece_dashboards:button', $build['button']['#component']);
  }

  /**
   * @covers ::build
   */
  public function testBuildUrlContainsCurrentUserId(): void {
    $build = $this->block->build();
    $this->assertStringContainsString('contributor[0]=42', $build['button']['#props']['url']);
  }

}

// Define base_path() in the source class namespace so unit tests can call it
// without a full Drupal bootstrap.
namespace Drupal\pece_dashboards\Plugin\Block;

if (!function_exists('Drupal\pece_dashboards\Plugin\Block\base_path')) {

  /**
   * Stub for base_path() so unit tests can call it without a Drupal bootstrap.
   */
  function base_path(): string {
    return '/';
  }

}
