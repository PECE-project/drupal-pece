<?php

namespace Drupal\Tests\pece_artifacts_bundle\Functional;

use Drupal\Tests\BrowserTestBase;

/**
 * Test create artifact bundle.
 *
 * @group pece_artifacts
 * @group pece_artifacts_bundle
 */
class PeceArtifactBundleTest extends BrowserTestBase {

  /**
   * Modules to install.
   *
   * @var array
   */
  protected static $modules = [
    'pece_artifacts_bundle',
    'components',
    'node',
    'token',
    'typed_data',
    'update',
    'user',
    'views',
  ];

  protected $profile = 'pece';
  protected $strictConfigSchema = FALSE;
  protected $defaultTheme = 'peceful';

  /**
   * Test the create node pece artifact bundle.
   */
  public function testCreateContent(): void {
    $node = $this->drupalCreateNode([
      'type'  => 'pece_artifact_bundle',
      'title' => 'Bundle Artifact 1',
    ]);

    $this->drupalGet('node/' . $node->id());
    $this->assertSession()->statusCodeEquals(200);
    $this->assertSession()->titleEquals('Bundle Artifact 1 | Drupal');
  }

  /**
   * Test the "pbf" node access with a Pbf field which reference node.
   */
  public function testNodeAccess(): void {
    $owner = $this->createUser();

    $node = $this->drupalCreateNode([
      'type'               => 'pece_artifact_bundle',
      'title'              => 'Bundle Artifact 2',
      'field_pbc_ref_user' => [
        'target_id'    => $owner->id(),
        'grant_public' => 0,
        'grant_view'   => 1,
        'grant_update' => 1,
        'grant_delete' => 1,
      ],
    ]);

    $this->drupalResetSession();
    $this->drupalGet('node/' . $node->id());
    $this->assertSession()->statusCodeEquals(403);

    $this->drupalLogin($owner);
    $this->drupalGet('node/' . $node->id());
    $this->assertSession()->statusCodeEquals(200);
  }

}
