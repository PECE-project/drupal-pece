<?php


namespace Drupal\pece_essay\Plugin\GraphQL\SchemaExtension;


use Drupal\Core\Extension\ModuleHandlerInterface;
use Drupal\graphql\GraphQL\ResolverBuilder;
use Drupal\graphql\GraphQL\ResolverRegistryInterface;
use Drupal\nyx_graphql\Plugin\GraphQL\Schema\EntityExtension;

/**
 * @SchemaExtension(
 *   id = "essay_extension",
 *   name = "Pece essay extension",
 *   description = "A extension that adds essays related fields.",
 *   schema = "entity"
 * )
 */
class EssayExtension extends EntityExtension {

  /**
   * @inheritDoc
   */
  public function __construct($configuration, $pluginId, $pluginDefinition, ModuleHandlerInterface $moduleHandler) {
    parent::__construct($configuration, $pluginId, $pluginDefinition, $moduleHandler);
    $this->entity = [
      'type' => 'node',
      'bundle' => 'pece_essay',
      'plural' => 'peceEssays'
    ];
  }

  public function addFields(ResolverRegistryInterface $registry, ResolverBuilder $builder) {
    parent::addFields($registry, $builder);
    $registry->addFieldResolver('Mutation', 'createEssay',
      $builder->produce('create_essay')
        ->map('data', $builder->fromArgument('data'))
    );
  }

}
