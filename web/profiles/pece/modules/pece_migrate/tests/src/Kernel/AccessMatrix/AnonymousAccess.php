<?php
namespace Drupal\Tests\pece_migrate\Tests\Kernel\AccessMatrix;

use Drupal\Tests\pece_migrate\Kernel\AccessMatrix\AccessMatrix;

/**
 * Tests the anonymous access after migration.
 *
 * @group pece_migrate_access_matrix
 */
class AnonymousAccess extends AccessMatrix {

  /**
   * Test access matrix.
   */
  public function testAccessMatrix() {
    $expected_node_access = ['view' => TRUE, 'update' => FALSE, 'delete' => FALSE];
    $node = $this->drupalCreateNode(['type' => 'page']);
    $this->webUser = $this->drupalCreateUser(['access content']);
    $this->assertNodeAccess($expected_node_access, $node, $this->webUser);
  }

}
