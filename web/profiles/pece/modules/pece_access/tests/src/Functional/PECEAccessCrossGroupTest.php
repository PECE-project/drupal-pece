<?php

namespace Drupal\Tests\pece_access\Functional;

use Drupal\Tests\pbf\Functional\PbfAccessByNodeRefTest;

/**
 * Tests that group membership does not bleed across groups.
 *
 * @group pece_access
 */
class PECEAccessCrossGroupTest extends PbfAccessByNodeRefTest {

  /**
   * Modules to install.
   *
   * @var array
   */
  protected static $modules = [
    'pece_access',
  ];

  /**
   * The profile to install as a basis for testing.
   *
   * @var string
   */
  protected $profile = 'pece';

  /**
   * Tests that a user in group1 cannot view content restricted to group2.
   */
  public function testUserInGroup1CannotAccessGroup2Content(): void {
    $article = $this->createSimpleArticle(
      'Group2 Article',
      $this->fieldname,
      $this->group2->id(),
      0, 1, 0, 0
    );

    $this->setUserField(
      $this->normalUser->id(),
      $this->fieldname,
      ['target_id' => $this->group1->id()]
    );

    $this->drupalLogin($this->normalUser);
    $this->drupalGet('node/' . $article->id());
    $this->assertSession()->statusCodeEquals(403);
  }

  /**
   * Tests that joining group2 then grants access to its content.
   */
  public function testUserGainsAccessAfterJoiningGroup2(): void {
    $article = $this->createSimpleArticle(
      'Group2 Gated Article',
      $this->fieldname,
      $this->group2->id(),
      0, 1, 0, 0
    );

    $this->setUserField(
      $this->normalUser->id(),
      $this->fieldname,
      ['target_id' => $this->group1->id()]
    );

    $this->drupalLogin($this->normalUser);
    $this->drupalGet('node/' . $article->id());
    $this->assertSession()->statusCodeEquals(403);

    $this->setUserField(
      $this->normalUser->id(),
      $this->fieldname,
      ['target_id' => $this->group2->id()]
    );

    $this->drupalGet('node/' . $article->id());
    $this->assertSession()->statusCodeEquals(200);
  }

  /**
   * Tests that public group2 content is visible to users in group1.
   */
  public function testPublicGroup2ContentIsAccessibleToAll(): void {
    $article = $this->createSimpleArticle(
      'Group2 Public Article',
      $this->fieldname,
      $this->group2->id(),
      1, 0, 0, 0
    );

    $this->setUserField(
      $this->normalUser->id(),
      $this->fieldname,
      ['target_id' => $this->group1->id()]
    );

    $this->drupalLogin($this->normalUser);
    $this->drupalGet('node/' . $article->id());
    $this->assertSession()->statusCodeEquals(200);
  }

}
