<?php

declare(strict_types = 1);

namespace OpenEuropa\Site\Tests\Behat;

use Drupal\DrupalExtension\Context\DrupalContext as DrupalExtensionDrupalContext;

/**
 * Provides step definitions for interacting with Drupal.
 */
class DrupalContext extends DrupalExtensionDrupalContext {

  /**
   * {@inheritdoc}
   */
  public function loggedIn() {
    $session = $this->getSession();
    $session->visit($this->locatePath('/'));

    // Check if the 'logged-in' class is present on the page.
    $element = $session->getPage();

    return $element->find('css', 'body.user-logged-in');
  }

}
