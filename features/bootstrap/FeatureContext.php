<?php

use Drupal\DrupalExtension\Context\RawDrupalContext;
use Behat\Gherkin\Node\PyStringNode;
use Behat\Gherkin\Node\TableNode;
use Behat\Behat\Tester\Exception\PendingException;

/**
 * Defines application features from the specific context.
 */
class FeatureContext extends RawDrupalContext {

  /**
   * Initializes context.
   *
   * Every scenario gets its own context instance.
   * You can also pass arbitrary arguments to the
   * context constructor through behat.yml.
   */
  public function __construct() {
  }

  /**
   * @Given I am logged in as user :name
   */
  public function iAmLoggedInAsUser($name) {
    $domain = $this->getMinkParameter('base_url');

    // Pass base url to drush command.
    $uli = $this->getDriver('drush')->drush('uli', [
      "--name '" . $name . "'",
      "--browser=0",
      "--uri=$domain",
    ]);

    // Trim EOL characters.
    $uli = trim($uli);

    // Log in.
    $this->getSession()->visit($uli);
  }

    /**
   * @Then I (should )see the heading :heading
   */
  // public function assertHeading($heading)
  // {
  //     $element = $this->getSession()->getPage();
  //     $this->getSession()
  //     ->executeScript("CKEDITOR.instances[\"$fieldId\"].setData(\"$value\");");
  //     foreach (['h1', 'h2', 'h3', 'h4', 'h5', 'h6'] as $tag) {
  //         $results = $element->findAll('css', $tag);
  //         foreach ($results as $result) {
  //             if ($result->getText() == $heading) {
  //                 return;
  //             }
  //         }
  //     }
  //     throw new \Exception(sprintf("The text '%s' was not found in any heading on the page %s", $heading, $this->getSession()->getCurrentUrl()));
  // }
}
