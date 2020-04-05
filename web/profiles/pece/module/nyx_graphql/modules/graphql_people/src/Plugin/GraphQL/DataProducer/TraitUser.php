<?php
namespace Drupal\graphql_people\Plugin\GraphQL\DataProducer;

use Drupal\paragraphs\Entity\Paragraph;

trait TraitUser {
    /**
     * Mapping fields
     *
     */
    protected $map_fields = [
        'mail' => 'mail',
        'pass' => 'pass',
        'username' => 'name',
        'status' => 'status',
        'name' => 'field_name',
    ];
}
