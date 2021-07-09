<?php


namespace Drupal\pece_memo\Plugin\GraphQL\SchemaExtension;


use Drupal\Core\Extension\ModuleHandlerInterface;
use Drupal\graphql\GraphQL\ResolverBuilder;
use Drupal\graphql\GraphQL\ResolverRegistryInterface;
use Drupal\nyx_graphql\Plugin\GraphQL\Schema\EntityExtension;

/**
 * @SchemaExtension(
 *   id = "memo_extension",
 *   name = "Pece memo extension",
 *   description = "A extension that adds memos related fields.",
 *   schema = "entity"
 * )
 */
class MemoExtension extends EntityExtension {

  /**
   * @inheritDoc
   */
  public function __construct($configuration, $pluginId, $pluginDefinition, ModuleHandlerInterface $moduleHandler) {
    parent::__construct($configuration, $pluginId, $pluginDefinition, $moduleHandler);
    $this->entity = [
      'type' => 'node',
      'bundle' => 'pece_memo',
      'plural' => 'peceMemos',
    ];
  }

  public function addFields(ResolverRegistryInterface $registry, ResolverBuilder $builder) {
    parent::addFields($registry, $builder, ['memo_']);
    $registry->addFieldResolver('Mutation', 'createMemo',
      $builder->produce('create_memo')
        ->map('data', $builder->fromArgument('data'))
    );
  }

}
