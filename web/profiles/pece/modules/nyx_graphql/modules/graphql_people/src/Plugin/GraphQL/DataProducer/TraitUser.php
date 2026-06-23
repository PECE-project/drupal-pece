<?php

namespace Drupal\graphql_people\Plugin\GraphQL\DataProducer;

/**
 *
 */
trait TraitUser {
  /**
   * Mapping fields.
   */
  protected $mapFields = [
    'mail' => 'mail',
    'pass' => 'pass',
    'username' => 'name',
    'status' => 'status',
    'name' => 'field_name',
  ];

}
