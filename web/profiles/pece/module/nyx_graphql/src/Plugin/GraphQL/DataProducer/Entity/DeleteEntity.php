<?php

namespace Drupal\nyx_graphql\Plugin\GraphQL\DataProducer\Entity;

use Drupal\node\Entity\Node;
use Drupal\Core\Session\AccountInterface;
use Drupal\Core\Plugin\ContainerFactoryPluginInterface;
use Symfony\Component\DependencyInjection\ContainerInterface;
use Drupal\graphql\Plugin\GraphQL\DataProducer\DataProducerPluginBase;

/**
 * Delete an Annotation.
 *
 * @DataProducer(
 *   id = "delete_entity",
 *   name = @Translation("Delete Entity"),
 *   description = @Translation("Delete an entity."),
 *   produces = @ContextDefinition("any",
 *     label = @Translation("Entity")
 *   ),
 *   consumes = {
 *     "id" = @ContextDefinition("string",
 *       label = @Translation("Entity Identifier")
 *     ),
 *     "bundle" = @ContextDefinition("string",
 *       label = @Translation("Entity bundle")
 *     )
 *   }
 * )
 */
class DeleteEntity extends DataProducerPluginBase implements ContainerFactoryPluginInterface {

  /**
   * The current user.
   *
   * @var \Drupal\Core\Session\AccountInterface
   */
  protected $currentUser;

  /**
   * {@inheritdoc}
   */
  public static function create(ContainerInterface $container, array $configuration, $plugin_id, $plugin_definition) {
    return new static(
      $configuration,
      $plugin_id,
      $plugin_definition,
      $container->get('current_user')
    );
  }

  /**
   * Delete entity constructor.
   *
   * @param array $configuration
   *   A configuration array containing information about the plugin instance.
   * @param string $plugin_id
   *   The plugin_id for the plugin instance.
   * @param array $plugin_definition
   *   The plugin implementation definition.
   * @param \Drupal\Core\Session\AccountInterface $current_user
   *   The current user.
   */
  public function __construct(array $configuration, string $plugin_id, array $plugin_definition, AccountInterface $current_user) {
    parent::__construct($configuration, $plugin_id, $plugin_definition);
    $this->currentUser = $current_user;
  }

  /**
   * Delete an entity.
   *
   * @param int $id
   *   The id to delete entity.
   * @param string $bundle
   *   The bundle entity to delete
   * @return \Drupal\Core\Entity\EntityBase|\Drupal\Core\Entity\EntityInterface|null
   *   The delete entity.
   *
   * @throws \Drupal\Core\Entity\EntityStorageException
   */
  public function resolve(int $id, string $bundle) {
    // @TODO: Create permission
    //if (isset($data['id']) && $this->currentUser->hasPermission("delete any pece_annotation content")) {
      $content = Node::load($id);
      $content->delete();
      return $content;
    //}
    //return NULL;
  }

}
