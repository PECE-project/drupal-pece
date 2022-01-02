<?php
namespace Drupal\Tests\pece_migrate\Kernel\AccessMatrix;

use Drupal\KernelTests\KernelTestBase;
use Drupal\Tests\node\Kernel\NodeAccessTestBase;

/**
 * Tests the access matrix.
 */
class AccessMatrix extends NodeAccessTestBase {

  /**
   * {@inheritdoc}
   */
  protected static $modules = [
    'pece_access',
    'user',
    'pece',
    'pece_migrate',
  ];

  /**
   * {@inheritdoc}
   */
  protected function setUp(): void {
    parent::setUp();
    $this->installEntitySchema('user');
  }

  /**
   * Test access matrix.
   */
  public function testAccessMatrix() {
    $expected_node_access = ['view' => TRUE, 'update' => FALSE, 'delete' => FALSE];
    $node = node_revision_load(1);
    $this->assertNodeAccess($expected_node_access, $node, $this->webUser);
  }

}

