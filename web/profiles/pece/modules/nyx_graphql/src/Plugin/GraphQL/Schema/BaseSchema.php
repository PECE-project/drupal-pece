<?php

namespace Drupal\nyx_graphql\Plugin\GraphQL\Schema;

use Drupal\field\Entity\FieldConfig;
use Drupal\graphql\GraphQL\ResolverBuilder;
use Drupal\graphql\GraphQL\ResolverRegistry;
use Drupal\graphql\Plugin\GraphQL\Schema\SdlSchemaPluginBase;
use Drupal\nyx_graphql\Wrappers\QueryConnection;


abstract class BaseSchema extends SdlSchemaPluginBase {

  /**
   * Format field machine name to graphql name
   * @example field_project_name -> (remove field_) -> project_name -> (explode _)
   * [project, name] -> (ucfirst to second element onwards and merge) -> projectName
   * @param $fieldName
   *  Field name
   * @param array $prefixs
   *  if exist, will apply the replace
   *
   * @return string
   */
  public static function formatFieldName ($fieldName, $prefixs = ['field_project_','field_']) {
    foreach ($prefixs as $prefix) {
      $fieldName = str_replace($prefix,'',$fieldName);
    }
    $nameArray = explode('_',$fieldName);

    $newName = $nameArray[0];
    unset($nameArray[0]);
    foreach ($nameArray as $item) {
      $newName .= ucfirst($item);
    }
    return $newName;
  }

  public static function addConfigField(ResolverRegistry $registry, ResolverBuilder $builder, FieldConfig $fieldConfig) {
    //passar o bundle como parametro???
    if ($bundles = $fieldConfig->getSetting('handler_settings')['target_bundles']) {
      foreach ($bundles as $bundle) {
        self::addConfigFieldWithBundle($registry, $builder, $fieldConfig, $bundle);
      }
    }
  }

  public static function addConfigFieldWithBundle(ResolverRegistry $registry, ResolverBuilder $builder, FieldConfig $fieldConfig, $bundle) {
    $fields = \Drupal::service('entity_field.manager')
      ->getFieldDefinitions($fieldConfig->getSetting('target_type'), $bundle);

    $type = ucfirst(self::formatFieldName($fieldConfig->getName()));

    $registry->addFieldResolver($type, 'id',
      $builder->produce('entity_id')
        ->map('entity', $builder->fromParent())
    );

    if (is_null($registry->getFieldResolver($type, 'title'))) {
      $registry->addFieldResolver($type, 'title',
        $builder->compose(
          $builder->produce('entity_label')
            ->map('entity', $builder->fromParent()),
          $builder->produce('uppercase')
            ->map('string', $builder->fromParent())
        )
      );
    }


    if (is_null($registry->getFieldResolver($type, 'type'))) {
      $registry->addFieldResolver($type, 'type',
        $builder->compose(
          $builder->produce('entity_bundle')
            ->map('entity', $builder->fromParent()),
          $builder->callback(function ($parent) {
            return self::formatFieldName($parent);
          })
        )
      );
    }

    $removePrefixField = explode('_', $bundle);
    $removePrefixField[] = 'field';
    $removePrefix = array_map(
      function ($name) {
        return $name . "_";
      },
      $removePrefixField
    );
    foreach ($fields as $field) {
      if ($field instanceof FieldConfig) {
        $fieldName = self::formatFieldName($field->getName(), $removePrefix);
        if (is_null($registry->getFieldResolver($type, $fieldName))) {
          switch ($field->getType()) {
            case 'image':
            case 'file':
              $registry->addFieldResolver($type, $fieldName,
                $builder->compose(
                  $builder->produce('property_path')
                    ->map('type', $builder->fromValue('entity:' . $field->get('entity_type') . ':' . $field->get('bundle')))
                    ->map('value', $builder->fromParent())
                    ->map('path', $builder->fromValue($field->getName())),
                  $builder->callback(function ($parent) {
                    return reset($parent);
                  })
                )
              );

              if ($field->getType() == 'image')
                self::addMediaImageFields($registry, $builder, ucfirst($fieldName));
              else
                self::addFileFields($registry, $builder, ucfirst($fieldName));
              break;
            case 'entity_reference_revisions':
            case 'entity_reference':
              $registry->addFieldResolver($type, $fieldName,
                $builder->produce('entity_reference')
                  ->map('entity', $builder->fromParent())
                  ->map('field', $builder->fromValue($field->getName()))
              );

              self::addConfigField($registry, $builder, $field);
              break;
            default:
              if ($fieldConfig->getTargetEntityTypeId() != 'user') {
                $typeDefinition = 'entity:' . $field->getTargetEntityTypeId() . ':' . $field->getTargetBundle();
              }
              else {
                $typeDefinition = 'entity:' . $field->getTargetEntityTypeId();
              }

              if (key_exists('max', $field->getSettings()) &&
                ($field->getSetting('max') == NULL || $field->getSetting('max') > 1)) {
                $registry->addFieldResolver($type, $fieldName,
                  $builder->compose(
                    $builder->produce('property_path')
                      ->map('type', $builder->fromValue($typeDefinition))
                      ->map('value', $builder->fromParent())
                      ->map('path', $builder->fromValue($field->getName())),
                    $builder->callback(function ($parent) {
                      if ($parent) {
                        foreach ($parent as $key => $item) {
                          $parent[$key] = $item['value'];
                        }
                      }
                      return $parent;
                    })
                  )
                );
              }
              else {
                $compose = [];

                if ($field->getFieldStorageDefinition()->getCardinality() != 1) {
                  $compose[] = $builder->produce('property_path')
                    ->map('type', $builder->fromValue($typeDefinition))
                    ->map('value', $builder->fromParent())
                    ->map('path', $builder->fromValue($field->getName()));
                  $compose[] = $builder->produce('multi_value')
                    ->map('values', $builder->fromParent());
                }
                else {
                  $compose[] = $builder->produce('property_path')
                    ->map('type', $builder->fromValue($typeDefinition))
                    ->map('value', $builder->fromParent())
                    ->map('path', $builder->fromValue($field->getName() . '.value'));
                }
                $registry->addFieldResolver($type, $fieldName, $builder->compose(...$compose));
              }
          }
        }
      }
    }
  }

  /**
   * @param \Drupal\graphql\GraphQL\ResolverRegistry $registry
   * @param \Drupal\graphql\GraphQL\ResolverBuilder $builder
   */
  protected function addQueryFields(ResolverRegistry $registry, ResolverBuilder $builder) {

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

  public static function addMediaImageFields(ResolverRegistry $registry, ResolverBuilder $builder, $type) {

    $registry->addFieldResolver($type, 'url',
      $builder->compose(
        $builder->produce('file_load')
          ->map('value', $builder->fromParent())
          ->map('path', $builder->fromValue('target_id')),
        $builder->produce('image_derivative')
          ->map('entity', $builder->fromParent())
          ->map('style', $builder->callback([static::class, 'mapImageStyleEnum'])),
        $builder->produce('image_style_url')
          ->map('derivative', $builder->fromParent())
      )
    );

    $registry->addFieldResolver($type, 'alt',
      $builder->compose(
        $builder->produce('array_value')
          ->map('value', $builder->fromParent())
          ->map('path', $builder->fromValue('alt'))
      ));

    $registry->addFieldResolver($type, 'mimetype',
      $builder->compose(
        $builder->produce('file_load')
          ->map('value', $builder->fromParent())
          ->map('path', $builder->fromValue('target_id')),
        $builder->produce('file_mimetype')
          ->map('entity', $builder->fromParent())
      )
    );
  }

  public static function addFileFields(ResolverRegistry $registry, ResolverBuilder $builder, $type) {

    $registry->addFieldResolver($type, 'url',
      $builder->compose(
        $builder->produce('file_load')
          ->map('value', $builder->fromParent())
          ->map('path', $builder->fromValue('target_id')),
        $builder->produce('file_url')
          ->map('entity', $builder->fromParent())
      )
    );

    $registry->addFieldResolver($type, 'mimetype',
      $builder->compose(
        $builder->produce('file_load')
          ->map('value', $builder->fromParent())
          ->map('path', $builder->fromValue('target_id')),
        $builder->produce('file_mimetype')
          ->map('entity', $builder->fromParent())
      )
    );
  }

  public static function mapImageStyleEnum($_, $args) {
    $map = [
      'LARGE_480x480' => 'large',
      'MEDIUM_220x220' => 'medium',
      'THUMBNAIL_100x100' => 'thumbnail',
      'S350x200' => 'media_entity_browser_thumbnail',
    ];

    return $map[$args['style']];
  }
}
