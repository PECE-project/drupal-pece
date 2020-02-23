<?php

namespace Drupal\nyx_graphql\Plugin\GraphQL\Schema;

use Drupal\field\Entity\FieldConfig;
use Drupal\graphql\GraphQL\ResolverBuilder;
use Drupal\graphql\GraphQL\ResolverRegistry;
use Drupal\node\NodeInterface;
use Drupal\nyx_graphql\Wrappers\QueryConnection;

/**
 * @Schema(
 *   id = "entity",
 *   name = "Entity schema"
 * )
 */
class EntitySchema extends BaseSchema {

  /**
   * {@inheritdoc}
   */
  public function getResolverRegistry() {
    $builder = new ResolverBuilder();
    $registry = new ResolverRegistry();

    // Tell GraphQL how to resolve types of a common interface.
    $registry->addTypeResolver('NodeInterface', function ($value) {
      if ($value instanceof NodeInterface) {
        switch ($value->bundle()) {
          case 'page': return 'Page';
        }
      }
      throw new \Error('Could not resolve content type.');
    });

    $this->addQueryFields($registry, $builder);
    $this->addPageFields($registry, $builder);
    $this->addConnectionFields('PageConnection', $registry, $builder);
    $this->addConnectionFields('PageTagsConnection', $registry, $builder);

    return $registry;
  }

  /**
   * @param \Drupal\graphql\GraphQL\ResolverRegistry $registry
   * @param \Drupal\graphql\GraphQL\ResolverBuilder $builder
   */
  protected function addPageFields(ResolverRegistry $registry, ResolverBuilder $builder) {
    $fields = \Drupal::service('entity_field.manager')->getFieldDefinitions('node', 'page');

    foreach ($fields as $field) {
      if ($field instanceof FieldConfig) {
        $fieldName = BaseSchema::formatFieldName($field->getName());
        if ($field->getType() == 'entity_reference_revisions' || $field->getType() == 'entity_reference') {
          $registry->addFieldResolver('Page', $fieldName,
            $builder->produce('entity_reference')
              ->map('entity', $builder->fromParent())
              ->map('field', $builder->fromValue($field->getName()))
          );
          BaseSchema::addConfigField($registry,$builder, $field);
        }
        elseif ($field->getType() == 'image') {
          $registry->addFieldResolver('Page', $fieldName,
            $builder->compose(
              $builder->produce('property_path')
                ->map('type', $builder->fromValue('entity:'. $field->get('entity_type'). ':' . $field->get('bundle')))
                ->map('value', $builder->fromParent())
                ->map('path', $builder->fromValue($field->getName())),
              $builder->callback(function ($parent) {
                return reset($parent);
              })
            )
          );

          BaseSchema::addMediaImageFields($registry, $builder, ucfirst($fieldName));
        }
        else {
          $registry->addFieldResolver('Page', $fieldName,
            $builder->produce('property_path')
              ->map('type', $builder->fromValue('entity:node:page'))
              ->map('value', $builder->fromParent())
              ->map('path', $builder->fromValue($field->getName() . '.value'))
          );
        }
      }
    }
    $registry->addFieldResolver('Page', 'id',
      $builder->produce('entity_id')
        ->map('entity', $builder->fromParent())
    );

    $registry->addFieldResolver('Page', 'title',
      $builder->compose(
        $builder->produce('entity_label')
          ->map('entity', $builder->fromParent()),
        $builder->produce('uppercase')
          ->map('string', $builder->fromParent())
      )
    );

    $registry->addFieldResolver('Page', 'author',
      $builder->produce('entity_owner')
        ->map('entity', $builder->fromParent())
    );

    $registry->addFieldResolver('Page', 'uuid',
      $builder->produce('entity_uuid')
        ->map('entity', $builder->fromParent())
    );

    $registry->addFieldResolver('Page', 'created',
      $builder->produce('entity_created')
        ->map('entity', $builder->fromParent())
    );

    $registry->addFieldResolver('Page', 'url',
      $builder->produce('entity_url_string')
        ->map('entity', $builder->fromParent())
    );
  }

  /**
   * @param \Drupal\graphql\GraphQL\ResolverRegistry $registry
   * @param \Drupal\graphql\GraphQL\ResolverBuilder $builder
   */
  protected function addQueryFields(ResolverRegistry $registry, ResolverBuilder $builder) {
    $registry->addFieldResolver('Query', 'page',
      $builder->produce('entity_load')
        ->map('type', $builder->fromValue('node'))
        ->map('bundles', $builder->fromValue(['page']))
        ->map('id', $builder->fromArgument('id'))
    );

    $registry->addFieldResolver('Query', 'pageByUUID',
      $builder->produce('entity_load_by_uuid')
        ->map('entity_type', $builder->fromValue('node'))
        ->map('entity_bundles', $builder->fromValue(['page']))
        ->map('entity_uuid', $builder->fromArgument('uuid'))
    );

    $registry->addFieldResolver('Query', 'pages',
      $builder->produce('query_pages')
        ->map('offset', $builder->fromArgument('offset'))
        ->map('limit', $builder->fromArgument('limit'))
        ->map('filters', $builder->fromArgument('filters'))
    );

    $registry->addFieldResolver('Query', 'route', $builder->compose(
      $builder->produce('route_load')
        ->map('path', $builder->fromArgument('path')),
      $builder->produce('route_entity')
        ->map('url', $builder->fromParent())
    ));
  }

  /**
   * @param \Drupal\graphql\GraphQL\ResolverRegistry $registry
   * @param \Drupal\graphql\GraphQL\ResolverBuilder $builder
   */
  protected function addConnectionFields($type, ResolverRegistry $registry, ResolverBuilder $builder) {
    $registry->addFieldResolver($type, 'total',
      $builder->callback(function (QueryConnection $connection) {
        return $connection->total();
      })
    );
    $registry->addFieldResolver($type, 'items',
      $builder->callback(function (QueryConnection $connection) {
        return $connection->items();
      })
    );
  }
}
