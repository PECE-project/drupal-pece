<?php

namespace Drupal\Tests\nyx_graphql\Traits;

/**
 * Shared Drupal 11 skip-guard for drupal/graphql kernel tests.
 */
trait GraphqlDrupal11CompatibilityTrait {

  /**
   * Skips the test on Drupal 11+ where drupal/graphql cannot be booted.
   *
   * drupal/graphql's file_upload service depends on file.validator which was
   * removed in Drupal 11. Skip until the contrib module adds support.
   */
  protected function skipIfDrupal11FileUploadIncompatible(): void {
    if (version_compare(\Drupal::VERSION, '11.0', '>=')) {
      $this->markTestSkipped('drupal/graphql file_upload service incompatible with Drupal 11 (file.validator removed).');
    }
  }

}
