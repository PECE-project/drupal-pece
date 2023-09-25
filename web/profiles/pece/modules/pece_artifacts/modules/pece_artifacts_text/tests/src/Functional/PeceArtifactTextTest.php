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
    'workflow',
    'pece_core',
  );
  protected $profile = 'pece';
  protected $strictConfigSchema = FALSE;
  protected $defaultTheme = "pece_theme";

  /**
   * Setup.
   */
  public function setUp() {
    parent::setUp();
  }

  /**
   * Test the create node pece artifact text.
   */
  public function testCreateContent() {
    $this->artifactText1 = $this->drupalCreateNode(['type' => 'pece_artifact_text', 'title' => 'Artifact Text 1']);
    // Verify view access.
    $this->drupalLogout();
    $this->drupalGet('node/'. $this->artifactText1->id());

    $this->assertSession()->statusCodeEquals(200);
    $this->assertSession()->titleEquals('Artifact Text 1 | Drupal');
  }

  /**
   * Test the "pbf" node access with a Pbf field which reference node.
   */
  public function testNodeAccess() {
    $user = $this->createUser();

    $values = array(
      'type' => 'pece_artifact_text',
      'title' => 'Artifact Text 2',
      'body' => [
        'value' => 'Content body for Artifact Text 2',
      ],
    );

    $values['field_pbc_ref_user'] = [
      'target_id' => $user->id(),
      'grant_public' => 0,
      'grant_view' => 1,
      'grant_update' => 1,
      'grant_delete' => 1,
    ];

    $this->artifactText2 = $this->drupalCreateNode($values);

    $this->drupalLogin($this->createUser([
      'administer nodes',
      'create pece_artifact_text content',
      'edit any pece_artifact_text content'
    ]));
    $this->drupalGet('node/'. $this->artifactText2->id() . '/edit');
    $this->assertSession()->statusCodeEquals(200);
    $this->drupalLogout();
    $this->drupalGet('node/'. $this->artifactText2->id());
    $this->assertSession()->statusCodeEquals(403);
    $this->drupalLogin($user);
    $this->drupalGet('node/'. $this->artifactText2->id());
    $this->assertSession()->statusCodeEquals(200);
  }

}
