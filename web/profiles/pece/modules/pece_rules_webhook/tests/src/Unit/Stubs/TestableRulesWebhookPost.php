<?php

namespace Drupal\Tests\pece_rules_webhook\Unit\Stubs;

use Drupal\pece_rules_webhook\Plugin\RulesAction\RulesWebhookPost;

/**
 * Exposes doExecute() for testing.
 */
class TestableRulesWebhookPost extends RulesWebhookPost {

  /**
   * Public wrapper for the protected doExecute() method.
   */
  public function publicDoExecute($url, $data, $apiuser = NULL, $apipass = NULL, $apitoken = NULL) {
    return $this->doExecute($url, $data, $apiuser, $apipass, $apitoken);
  }

}
