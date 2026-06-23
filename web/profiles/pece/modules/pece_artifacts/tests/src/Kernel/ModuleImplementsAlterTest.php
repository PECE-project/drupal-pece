<?php

namespace Drupal\Tests\pece_artifacts\Kernel;

use Drupal\KernelTests\KernelTestBase;

/**
 * Tests the pece_artifacts_module_implements_alter hook.
 *
 * @group pece_artifacts
 */
class ModuleImplementsAlterTest extends KernelTestBase {

  protected static $modules = ['system', 'pece_artifacts'];

  /**
   *
   */
  protected function setUp(): void {
    parent::setUp();
    if (!function_exists('pece_artifacts_module_implements_alter')) {
      require_once \Drupal::root() . '/profiles/pece/modules/pece_artifacts/pece_artifacts.module';
    }
  }

  /**
   * Tests that licenses_vocabulary is removed from modules_installed implementations.
   */
  public function testLicensesVocabularyRemovedForModulesInstalledHook(): void {
    $implementations = [
      'other_module'        => 1,
      'licenses_vocabulary' => 1,
    ];
    pece_artifacts_module_implements_alter($implementations, 'modules_installed');

    $this->assertArrayNotHasKey('licenses_vocabulary', $implementations);
    $this->assertArrayHasKey('other_module', $implementations);
  }

  /**
   * Tests that unrelated hooks are not affected.
   */
  public function testOtherHooksAreNotModified(): void {
    $implementations = [
      'licenses_vocabulary' => 1,
      'other_module'        => 1,
    ];
    pece_artifacts_module_implements_alter($implementations, 'node_insert');

    $this->assertArrayHasKey('licenses_vocabulary', $implementations);
    $this->assertArrayHasKey('other_module', $implementations);
  }

  /**
   * Tests that an empty implementations array is handled without errors.
   */
  public function testEmptyImplementationsHandledGracefully(): void {
    $implementations = [];
    pece_artifacts_module_implements_alter($implementations, 'modules_installed');
    $this->assertEmpty($implementations);
  }

}
