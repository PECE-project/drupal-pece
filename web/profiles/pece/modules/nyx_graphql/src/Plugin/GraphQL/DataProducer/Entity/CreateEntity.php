<?php

namespace Drupal\nyx_graphql\Plugin\GraphQL\DataProducer\Entity;

use Drupal\Core\Entity\EntityStorageException;
use Drupal\node\Entity\Node;
use Drupal\Core\Session\AccountInterface;
use Drupal\Core\Plugin\ContainerFactoryPluginInterface;
use Symfony\Component\DependencyInjection\ContainerInterface;
use Drupal\graphql\Plugin\GraphQL\DataProducer\DataProducerPluginBase;

/**
 * Creates a new Annotation.
 *
 * @DataProducer(
 *   id = "create_entity",
 *   name = @Translation("Create Entity"),
 *   description = @Translation("Creates a new Entity."),
 *   produces = @ContextDefinition("any",
 *     label = @Translation("Entity")
 *   ),
 *   consumes = {
 *     "data" = @ContextDefinition("any",
 *       label = @Translation("Entity data")
 *     ),
 *     "entity" = @ContextDefinition("string",
 *       label = @Translation("Entity type")
 *     ),
 *     "fieldsMap" = @ContextDefinition("any",
 *       label = @Translation("Map Fields")
 *     )
 *   }
 * )
 */
class CreateEntity extends DataProducerPluginBase implements ContainerFactoryPluginInterface {

  //@TODO: get this map dynamically
  /**
   * Map fields to Drupal
   * graphqlfield => drupalfield
   * @var string[]
   */
  protected $mapFields = [
    'title' => 'title',
  ];

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
   * Create Entity constructor.
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
   * Create an Entity.
   *
   * @param array $data
   *   The fields of the Entity.
   * @param string $entity
   *   Type entity
   * @param array $fieldsMap
   *   Field map to entity.
   *
   * @return \Drupal\Core\Entity\EntityBase|\Drupal\Core\Entity\EntityInterface
   *   The newly created entity.
   *
   * @throws \Exception
   */
  public function resolve(array $data, $entity, array $fieldsMap) {
    //@todo: set permission
    $values = ['type' => $entity];
    foreach ($data as $key => $value) {
      if (isset($fieldsMap[$key])) {
        $field = $fieldsMap[$key];
        $values[$field] = $value;
      }
    }
    try {
      $content = Node::create($values);
      $content->save();
      return $content;
    } catch (EntityStorageException $e) {
      throw new \Exception($e->getMessage(), $e->getCode());
    }
  }
}
