<?php


namespace Drupal\pece_annotations\Plugin\GraphQL\SchemaExtension;


use Drupal\Core\Extension\ModuleHandlerInterface;
use Drupal\graphql\GraphQL\ResolverBuilder;
use Drupal\graphql\GraphQL\ResolverRegistryInterface;
use Drupal\nyx_graphql\Plugin\GraphQL\Schema\EntityExtension;

/**
 * @SchemaExtension(
 *   id = "annotation_extension",
 *   name = "Pece Annotation extension",
 *   description = "A extension that adds Annotations related fields.",
 *   schema = "entity"
 * )
 */
class AnnotationExtension extends EntityExtension {

  /**
   * @inheritDoc
   */
  public function __construct($configuration, $pluginId, $pluginDefinition, ModuleHandlerInterface $moduleHandler) {
    parent::__construct($configuration, $pluginId, $pluginDefinition, $moduleHandler);
    $this->entity = [
      'type' => 'node',
      'bundle' => 'pece_annotation',
      'plural' => 'peceAnnotations'
    ];
  }
}
