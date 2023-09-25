<?php

namespace Drupal\nyx_graphql\Plugin\GraphQL\DataProducer\Entity;

use Drupal\node\Entity\Node;
use Drupal\Core\Session\AccountInterface;
use Drupal\Core\Plugin\ContainerFactoryPluginInterface;
use Drupal\graphql_people\Plugin\GraphQL\DataProducer\TraitUser;
use Symfony\Component\DependencyInjection\ContainerInterface;
use Drupal\graphql\Plugin\GraphQL\DataProducer\DataProducerPluginBase;

/**
 * Update a new user.
 *
 * @DataProducer(
 *   id = "update_entity",
 *   name = @Translation("Update entity"),
 *   description = @Translation("Update an entity."),
 *   produces = @ContextDefinition("any",
 *     label = @Translation("Entity")
 *   ),
 *   consumes = {
 *     "id" = @ContextDefinition("string",
 *       label = @Translation("Entity Identifier")
 *     ),
 *     "data" = @ContextDefinition("any",
 *       label = @Translation("Entity data")
 *     ),
 *    "entity" = @ContextDefinition("string",
 *       label = @Translation("Entity type")
 *     ),
 *     "fieldsMap" = @ContextDefinition("any",
 *       label = @Translation("Map Fields")
 *     )
 *   }
 * )
 */
class UpdateEntity extends DataProducerPluginBase implements ContainerFactoryPluginInterface {

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
   * Update Entity constructor.
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
   * Update a user.

   * @param int $id
   *   The id to update entity.
   * @param array $data
   *   The fields of the Entity.
   * @param string $entity
   *   Type entity
   * @param array $fieldsMap
   *   Field map to entity.
   *
   * @return \Drupal\Core\Entity\EntityBase|\Drupal\Core\Entity\EntityInterface
   *   The updated entity.
   *
   * @throws \Exception
   */
  public function resolve(int $id, array $data, string $entity, array $fieldsMap) {
      $content = Node::load($id);
      foreach ($data as $key => $value) {
        if (isset($fieldsMap[$key])) {
          $field = $fieldsMap[$key];
          $content->set($field, $value);
        }
      }
      $content->save();
      return $content;
  }

}
