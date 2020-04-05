<?php

namespace Drupal\graphql_people\Plugin\GraphQL\DataProducer;

use Drupal\user\Entity\User;
use Drupal\Core\Session\AccountInterface;
use Drupal\Core\Plugin\ContainerFactoryPluginInterface;
use Drupal\graphql_people\Plugin\GraphQL\DataProducer\TraitUser;
use Symfony\Component\DependencyInjection\ContainerInterface;
use Drupal\graphql\Plugin\GraphQL\DataProducer\DataProducerPluginBase;

/**
 * Creates a new user.
 *
 * @DataProducer(
 *   id = "create_user",
 *   name = @Translation("Create User"),
 *   description = @Translation("Creates a new user."),
 *   produces = @ContextDefinition("any",
 *     label = @Translation("User")
 *   ),
 *   consumes = {
 *     "data" = @ContextDefinition("any",
 *       label = @Translation("User data")
 *     )
 *   }
 * )
 */
class CreateUser extends DataProducerPluginBase implements ContainerFactoryPluginInterface {

  use TraitUser;

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
   * CreateUser constructor.
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
   * Creates addresses.
   *
   * @param array $addresses
   *
   * @return array
   *   Paragraphs address
   *
   * @throws \Exception
   */
  private function createAddresses ($addresses) {
    $paragraphs = [];
    foreach ($addresses as $address) {
      $paragraph = $this->newAddress($address);
      $paragraphs[] = $paragraph;
    }
    return $paragraphs;
  }

  /**
   * Creates a user.
   *
   * @param array $data
   *   The fields of the user.
   *
   * @return \Drupal\user\UserInterface
   *   The newly created user.
   *
   * @throws \Exception
   */
  public function resolve(array $data) {
    if ($this->currentUser->hasPermission("administer users")) {
      $values = [];
      $values['vid'] = 'user';
      foreach ($data as $key => $value) {
        if (isset($this->mapFields[$key])) {
          $values[$this->mapFields[$key]] = $value;
        }
      }
      $account = User::create($values);
      $account->save();
      return $account;
    }
    return NULL;
  }

}
