<?php

namespace Drupal\Tests\pece_artifacts_text\Functional;

use Drupal\Tests\BrowserTestBase;
use Drupal\Tests\node\Functional\NodeTestBase;
/**
 * Test create artifact text.
 *
 * @group pece_artifacts
 * @group pece_artifacts_text
 */
class PeceArtifactTextTest extends BrowserTestBase {

  private $artifactText1;
  private $artifactText2;
  /**
   * Modules to install.
   *
   * @var array
   */
  public static $modules = array(
    'pece_artifacts_text',
    'components',
    'token',
    'typed_data',
    'update',
    'user',
    'views',
    'workflow'
  );
  protected $profile = 'pece';
  protected $strictConfigSchema = FALSE;
  protected $defaultTheme = "pece_theme";

  /**
   * Setup and create content with Pbf field.
   */
  public function setUp() {
    parent::setUp();
  }

  /**
   * Test the "pbf" node access with a Pbf field which reference node.
   */
  public function testCreateContent() {
    $this->artifactText1 = $this->drupalCreateNode(['type' => 'pece_artifact_text', 'title' => 'Artifact Text 1']);
    // Verify view access.
    $this->drupalGet('node/'. $this->artifactText1->id());
    $this->assertSession()->statusCodeEquals(200);
  }

}
