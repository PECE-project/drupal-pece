<?php

declare(strict_types = 1);

namespace OpenEuropa\Site\Tests\Behat;

use Drupal\DrupalExtension\Context\RawDrupalContext;

/**
 * Defines step definitions that are generally useful for the project.
 */
class FeatureContext extends RawDrupalContext {

  /**
   * Checks that a 403 Access Denied error occurred.
   *
   * @Then I should get an access denied error
   *
   * @throws \Behat\Mink\Exception\ExpectationException
   *   Thrown when a different HTTP response code was returned.
   */
  public function assertAccessDenied(): void {
    $this->assertSession()->statusCodeEquals(403);
  }

  /**
   * Checks that a 200 OK response occurred.
   *
   * @Then I should get a valid web page
   *
   * @throws \Behat\Mink\Exception\ExpectationException
   *   Thrown when a different HTTP response code was returned.
   */
  public function assertSuccessfulResponse(): void {
    $this->assertSession()->statusCodeEquals(200);
  }

}
