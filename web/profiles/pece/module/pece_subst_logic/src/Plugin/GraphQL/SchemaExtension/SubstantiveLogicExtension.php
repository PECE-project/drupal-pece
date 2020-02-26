<?php


namespace Drupal\pece_subst_logic\Plugin\GraphQL\SchemaExtension;


use Drupal\Core\Extension\ModuleHandlerInterface;
use Drupal\graphql\GraphQL\ResolverBuilder;
use Drupal\graphql\GraphQL\ResolverRegistryInterface;
use Drupal\nyx_graphql\Plugin\GraphQL\Schema\EntityExtension;

/**
 * @SchemaExtension(
 *   id = "substantive_logic_extension",
 *   name = "Substantive Logic extension",
 *   description = "A extension that adds Substantive Logic related fields.",
 *   schema = "entity"
 * )
 */
class SubstantiveLogicExtension extends EntityExtension {

  /**
   * @inheritDoc
   */
  public function __construct($configuration, $pluginId, $pluginDefinition, ModuleHandlerInterface $moduleHandler) {
    parent::__construct($configuration, $pluginId, $pluginDefinition, $moduleHandler);
    $this->entity = [
      'type' => 'node',
      'bundle' => 'pece_substantive_logic',
      'plural' => 'peceSubstantiveLogics'
    ];
  }

  public function addFields(ResolverRegistryInterface $registry, ResolverBuilder $builder) {
    parent::addFields($registry, $builder, ['subst_logic_']);
    $registry->addFieldResolver('Mutation', 'createSubstantiveLogic',
      $builder->produce('create_audio')
        ->map('data', $builder->fromArgument('data'))
    );
  }

}
