<?php

namespace Drupal\pece_photo_essay\Plugin\GraphQL\SchemaExtension;

use Drupal\Core\Extension\ModuleHandlerInterface;
use Drupal\graphql\GraphQL\ResolverBuilder;
use Drupal\graphql\GraphQL\ResolverRegistryInterface;
use Drupal\nyx_graphql\Plugin\GraphQL\Schema\EntityExtension;

/**
 * Photo Essay Content Type.
 *
 * @SchemaExtension(
 *   id = "photo_essay_extension",
 *   name = "Pece photo essay extension",
 *   description = "A extension that adds photo essays related fields.",
 *   schema = "entity"
 * )
 */
class PhotoEssayExtension extends EntityExtension {

  /**
   * {@inheritDoc}
   */
  public function __construct($configuration, $pluginId, $pluginDefinition, ModuleHandlerInterface $moduleHandler) {
    parent::__construct($configuration, $pluginId, $pluginDefinition, $moduleHandler);
    $this->entity = [
      'type' => 'node',
      'bundle' => 'pece_photo_essay',
      'plural' => 'pecePhotoEssays',
    ];
  }

  public function addFields(ResolverRegistryInterface $registry, ResolverBuilder $builder) {
    parent::addFields($registry, $builder, ['photo_essay_']);
    $registry->addFieldResolver('Mutation', 'createPhotoEssay',
      $builder->produce('create_photo_essay')
        ->map('data', $builder->fromArgument('data'))
    );
  }

}
