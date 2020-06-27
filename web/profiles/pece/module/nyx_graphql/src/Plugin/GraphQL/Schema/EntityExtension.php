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


  protected $mapFields = [];

  /**
   * Map fields to this entity.
   * @return array
   */
  public function &getMapFields () {
    return $this->mapFields;
  }


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
   * Add field resolvers dynamically from the field definitions in the Drupal.
   *
   * @param \Drupal\graphql\GraphQL\ResolverRegistryInterface $registry
   * @param \Drupal\graphql\GraphQL\ResolverBuilder $builder
   * @param array $entity
   */
  protected function addFields(ResolverRegistryInterface $registry, ResolverBuilder $builder, array $prefix = []) {
    // Get all field informations about this entity
    $fields = \Drupal::service('entity_field.manager')->getFieldDefinitions($this->entity['type'], $this->entity['bundle']);
    $baseEntityNameSingular = ucfirst(BaseSchema::formatFieldName($this->entity['bundle'], []));

    // This array is used to clean graphql properties. Got to BaseSchema::formatFieldName to more details.
    $prefix = array_merge($prefix, ['field_' . $this->entity['bundle'] . '_', 'field_']);
    foreach ($fields as $field) {
      if ($field instanceof FieldConfig) {
        $fieldName = BaseSchema::formatFieldName($field->getName(), $prefix);
        $this->mapFields[$fieldName] = $field->getName();
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

          if ($field->getType() == 'image')
            BaseSchema::addMediaImageFields($registry, $builder, ucfirst($fieldName));
          else
            BaseSchema::addFileFields($registry, $builder, ucfirst($fieldName));

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
          $registry->addFieldResolver($baseEntityNameSingular, $fieldName, $builder->compose(...$compose));

        }
      }
    }

    $this->mapFields['id'] = 'id';
    $registry->addFieldResolver($baseEntityNameSingular, 'id',
      $builder->produce('entity_id')
        ->map('entity', $builder->fromParent())
        ->map('field', $builder->fromValue('id'))
    );

    $this->mapFields['title'] = 'title';
    $registry->addFieldResolver($baseEntityNameSingular, 'title',
      $builder->compose(
        $builder->produce('entity_label')
          ->map('entity', $builder->fromParent()),
        $builder->produce('uppercase')
          ->map('string', $builder->fromParent())
      )
    );

    $this->mapFields['author'] = 'author';
    $registry->addFieldResolver($baseEntityNameSingular, 'author',
      $builder->produce('entity_owner')
        ->map('entity', $builder->fromParent())
    );

    $this->mapFields['created'] = 'created';
    $registry->addFieldResolver($baseEntityNameSingular, 'created',
      $builder->produce('entity_created')
        ->map('entity', $builder->fromParent())
    );

    $this->mapFields['uuid'] = 'uuid';
    $registry->addFieldResolver($baseEntityNameSingular, 'uuid',
      $builder->produce('entity_uuid')
        ->map('entity', $builder->fromParent())
    );

    if (isset($this->entity['bundle'])) {
      $registry->addFieldResolver('Mutation', 'create' . $baseEntityNameSingular,
        $builder->produce('create_entity')
          ->map('data', $builder->fromArgument('data'))
          ->map('entity', $builder->fromValue($this->entity['bundle']))
          ->map('fieldsMap', $builder->fromValue($this->getMapFields()))
      );
    }
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
