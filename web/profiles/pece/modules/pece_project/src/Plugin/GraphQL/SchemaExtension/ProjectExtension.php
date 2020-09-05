<?php


namespace Drupal\pece_project\Plugin\GraphQL\SchemaExtension;


use Drupal\Core\Extension\ModuleHandlerInterface;
use Drupal\graphql\GraphQL\ResolverBuilder;
use Drupal\graphql\GraphQL\ResolverRegistryInterface;
use Drupal\nyx_graphql\Plugin\GraphQL\Schema\EntityExtension;

/**
 * @SchemaExtension(
 *   id = "project_extension",
 *   name = "Project extension",
 *   description = "A extension that adds project related fields.",
 *   schema = "entity"
 * )
 */
class ProjectExtension extends EntityExtension {

  /**
   * @inheritDoc
   */
  public function __construct($configuration, $pluginId, $pluginDefinition, ModuleHandlerInterface $moduleHandler) {
    parent::__construct($configuration, $pluginId, $pluginDefinition, $moduleHandler);
    $this->entity = [
      'type' => 'node',
      'bundle' => 'pece_project',
      'plural' => 'peceProjects'
    ];
  }

  public function addFields(ResolverRegistryInterface $registry, ResolverBuilder $builder) {
    parent::addFields($registry, $builder, ['project_']);
    $registry->addFieldResolver('Mutation', 'createProject',
      $builder->produce('create_audio')
        ->map('data', $builder->fromArgument('data'))
    );
  }

}
