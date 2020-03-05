<?php

namespace Drupal\nyx_graphql\Plugin\GraphQL\Schema;

use Drupal\Core\Extension\ModuleHandlerInterface;
use Drupal\field\Entity\FieldConfig;
use Drupal\graphql\GraphQL\ResolverBuilder;
use Drupal\graphql\GraphQL\ResolverRegistryInterface;
use Drupal\graphql\Plugin\GraphQL\SchemaExtension\SdlSchemaExtensionPluginBase;
use Drupal\nyx_graphql\Plugin\GraphQL\Schema\BaseSchema;
use Drupal\nyx_graphql\Wrappers\QueryConnection;


abstract class EntityExtension extends SdlSchemaExtensionPluginBase {

  protected $entity = [
      'type' => 'node',
      'bundle' => 'entity',
      'plural' => 'entities'
  ];

  public function __construct($configuration, $pluginId, $pluginDefinition, ModuleHandlerInterface $moduleHandler) {
    parent::__construct($configuration, $pluginId, $pluginDefinition, $moduleHandler);
  }

  /**
   * {@inheritdoc}
   */
  public function registerResolvers(ResolverRegistryInterface $registry) {
    $builder = new ResolverBuilder();

    $this->addQueryFields($registry, $builder);
    $this->addFields($registry, $builder);
    $baseEntityNameSingular = BaseSchema::formatFieldName($this->entity['bundle'], []);
    $this->addConnectionFields(ucfirst($baseEntityNameSingular).'Connection', $registry, $builder);
  }

  /**
   * @param \Drupal\graphql\GraphQL\ResolverRegistryInterface $registry
   * @param \Drupal\graphql\GraphQL\ResolverBuilder $builder
   * @param array $entity
   */
  protected function addFields(ResolverRegistryInterface $registry, ResolverBuilder $builder) {
    $fields = \Drupal::service('entity_field.manager')->getFieldDefinitions($this->entity['type'], $this->entity['bundle']);
    $baseEntityNameSingular = BaseSchema::formatFieldName($this->entity['bundle'], []);

    foreach ($fields as $field) {
      if ($field instanceof FieldConfig) {
        $fieldName = BaseSchema::formatFieldName($field->getName(),['field_' . $this->entity['bundle'] . '_', 'field_']);
        if ($field->getType() == 'entity_reference_revisions' || $field->getType() == 'entity_reference') {
          $registry->addFieldResolver(ucfirst($baseEntityNameSingular), $fieldName,
            $builder->produce('entity_reference')
              ->map('entity', $builder->fromParent())
              ->map('field', $builder->fromValue($field->getName()))
          );
          BaseSchema::addConfigField($registry, $builder, $field);
        }
        elseif ($field->getType() == 'image') {
          $registry->addFieldResolver(ucfirst($baseEntityNameSingular), $fieldName,
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
          $compose = [];

          if ($field->getFieldStorageDefinition()->getCardinality() != 1) {
            $compose[] = $builder->produce('property_path')
              ->map('type', $builder->fromValue(isset($this->entity['entity']) ? $this->entity['entity'] : 'entity:' . $this->entity['type'] . ':' . $this->entity['bundle']))
              ->map('value', $builder->fromParent())
              ->map('path', $builder->fromValue($field->getName()));
            $compose[] = $builder->produce('multi_value')
              ->map('values', $builder->fromParent());
          }
          else {
            $compose[] = $builder->produce('property_path')
              ->map('type', $builder->fromValue(isset($this->entity['entity']) ? $this->entity['entity'] : 'entity:' . $this->entity['type'] . ':' . $this->entity['bundle']))
              ->map('value', $builder->fromParent())
              ->map('path', $builder->fromValue($field->getName() . '.value'));
          }
          $registry->addFieldResolver(ucfirst($baseEntityNameSingular), $fieldName, $builder->compose(...$compose));

        }
      }
    }
    $registry->addFieldResolver(ucfirst($baseEntityNameSingular), 'id',
      $builder->produce('entity_id')
        ->map('entity', $builder->fromParent())
    );

    $registry->addFieldResolver(ucfirst($baseEntityNameSingular), 'title',
      $builder->compose(
        $builder->produce('entity_label')
          ->map('entity', $builder->fromParent()),
        $builder->produce('uppercase')
          ->map('string', $builder->fromParent())
      )
    );

    $registry->addFieldResolver(ucfirst($baseEntityNameSingular), 'author',
      $builder->produce('entity_owner')
        ->map('entity', $builder->fromParent())
    );

    $registry->addFieldResolver(ucfirst($baseEntityNameSingular), 'uuid',
      $builder->produce('entity_uuid')
        ->map('entity', $builder->fromParent())
    );
  }

  /**
   * Add queries fields to entities
   * @param \Drupal\graphql\GraphQL\ResolverRegistryInterface $registry
   * @param \Drupal\graphql\GraphQL\ResolverBuilder $builder
   */
  protected function addQueryFields(ResolverRegistryInterface $registry, ResolverBuilder $builder) {
    $baseEntityNameSingular = BaseSchema::formatFieldName($this->entity['bundle'], []);
    $baseEntityNamePlural = BaseSchema::formatFieldName($this->entity['plural'], []);

    $registry->addFieldResolver('Query', $baseEntityNameSingular,
      $builder->produce('entity_load')
        ->map('type', $builder->fromValue($this->entity['type']))
        ->map('bundles', $builder->fromValue([$this->entity['bundle']]))
        ->map('id', $builder->fromArgument('id'))
    );

    $registry->addFieldResolver('Query', $baseEntityNameSingular . 'ByUUID',
      $builder->produce('entity_load_by_uuid')
        ->map('type', $builder->fromValue($this->entity['type']))
        ->map('bundles', $builder->fromValue([$this->entity['bundle']]))
        ->map('uuid', $builder->fromArgument('uuid'))
    );

    $registry->addFieldResolver('Query', $baseEntityNamePlural,
      $builder->produce('query_entities')
        ->map('bundle', $builder->fromValue($this->entity['bundle']))
        ->map('type', $builder->fromValue($this->entity['type']))
        ->map('offset', $builder->fromArgument('offset'))
        ->map('limit', $builder->fromArgument('limit'))
        ->map('filters', $builder->fromArgument('filters'))
    );
  }

  /**
   * @param \Drupal\graphql\GraphQL\ResolverRegistry $registry
   * @param \Drupal\graphql\GraphQL\ResolverBuilder $builder
   */
  protected function addConnectionFields($type, ResolverRegistryInterface $registry, ResolverBuilder $builder) {
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
