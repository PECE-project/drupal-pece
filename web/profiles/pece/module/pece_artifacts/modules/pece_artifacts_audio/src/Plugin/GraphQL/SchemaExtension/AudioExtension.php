<?php


namespace Drupal\pece_artifacts_audio\Plugin\GraphQL\SchemaExtension;


use Drupal\Core\Extension\ModuleHandlerInterface;
use Drupal\graphql\GraphQL\ResolverBuilder;
use Drupal\graphql\GraphQL\ResolverRegistryInterface;
use Drupal\nyx_graphql\Plugin\GraphQL\Schema\EntityExtension;

/**
 * @SchemaExtension(
 *   id = "audio_extension",
 *   name = "Artifacts Audio extension",
 *   description = "A extension that adds artifacts audio related fields.",
 *   schema = "entity"
 * )
 */
class AudioExtension extends EntityExtension {

  /**
   * @inheritDoc
   */
  public function __construct($configuration, $pluginId, $pluginDefinition, ModuleHandlerInterface $moduleHandler) {
    parent::__construct($configuration, $pluginId, $pluginDefinition, $moduleHandler);
    $this->entity = [
      'type' => 'node',
      'bundle' => 'pece_artifact_audio',
      'plural' => 'peceArtifactsAudio'
    ];
  }

  public function addFields(ResolverRegistryInterface $registry, ResolverBuilder $builder) {
    parent::addFields($registry, $builder, ['audio_']);
    $registry->addFieldResolver('Mutation', 'createAudio',
      $builder->produce('create_audio')
        ->map('data', $builder->fromArgument('data'))
    );
  }

}
