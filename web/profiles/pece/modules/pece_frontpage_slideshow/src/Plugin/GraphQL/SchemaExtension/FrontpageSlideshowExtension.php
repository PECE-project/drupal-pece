<?php


namespace Drupal\pece_essay\Plugin\GraphQL\SchemaExtension;


use Drupal\Core\Extension\ModuleHandlerInterface;
use Drupal\graphql\GraphQL\ResolverBuilder;
use Drupal\graphql\GraphQL\ResolverRegistryInterface;
use Drupal\nyx_graphql\Plugin\GraphQL\Schema\EntityExtension;

/**
 * @SchemaExtension(
 *   id = "frontpage_slideshow_extension",
 *   name = "Pece frontpage slideshow extension",
 *   description = "A extension that adds frontpage slideshows related fields.",
 *   schema = "entity"
 * )
 */
class FrontpageSlideshowExtension extends EntityExtension {

  /**
   * @inheritDoc
   */
  public function __construct($configuration, $pluginId, $pluginDefinition, ModuleHandlerInterface $moduleHandler) {
    parent::__construct($configuration, $pluginId, $pluginDefinition, $moduleHandler);
    $this->entity = [
      'type' => 'node',
      'bundle' => 'pece_frontpage_slideshow',
      'plural' => 'peceFrontpageSlideshows'
    ];
  }

  public function addFields(ResolverRegistryInterface $registry, ResolverBuilder $builder) {
    parent::addFields($registry, $builder, ['frontpage_slideshow_']);
    $registry->addFieldResolver('Mutation', 'createFrontpageSlideshow',
      $builder->produce('create_frontpage_slideshow')
        ->map('data', $builder->fromArgument('data'))
    );
  }

}
