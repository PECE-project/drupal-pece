<?php

namespace Drupal\Tests\pece_annotations\Unit;

use Drupal\pece_annotations\Plugin\views\style\AnalyticEntityBrowser;
use Drupal\Tests\UnitTestCase;

/**
 * @coversDefaultClass \Drupal\pece_annotations\Plugin\views\style\AnalyticEntityBrowser
 * @group pece_annotations
 */
class AnalyticEntityBrowserTest extends UnitTestCase {

  /**
   * Tests that the plugin declares it uses row plugins.
   */
  public function testUsesRowPluginIsTrue(): void {
    $defaults = (new \ReflectionClass(AnalyticEntityBrowser::class))->getDefaultProperties();
    $this->assertTrue($defaults['usesRowPlugin']);
  }

  /**
   * Tests that the plugin class is in the correct namespace.
   */
  public function testClassIsInCorrectNamespace(): void {
    $this->assertEquals(
      'Drupal\pece_annotations\Plugin\views\style\AnalyticEntityBrowser',
      AnalyticEntityBrowser::class
    );
  }

  /**
   * Tests that the plugin extends StylePluginBase.
   */
  public function testExtendsStylePluginBase(): void {
    $this->assertTrue(
      is_a(AnalyticEntityBrowser::class, 'Drupal\views\Plugin\views\style\StylePluginBase', TRUE)
    );
  }

}
