<?php
namespace Drupal\Tests\pece_migrate\Kernel\AccessMatrix;

use Drupal\KernelTests\KernelTestBase;
use Drupal\Tests\node\Kernel\NodeAccessTestBase;

/**
 * Tests the access matrix.
 */
class AccessMatrix extends NodeAccessTestBase {

  protected $webUser = null;
  /**
   * {@inheritdoc}
   */
  protected static $modules = [
    'pece_access',
    'user',
    'pece_migrate',
  ];

  /**
   * {@inheritdoc}
   */
  protected function setUp(): void {
    parent::setUp();
    $this->installEntitySchema('user');
  }

}

