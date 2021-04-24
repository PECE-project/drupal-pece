<?php

namespace Drupal\graphql_people\Plugin\GraphQL\DataProducer;

use Drupal\user\Entity\User;
use Drupal\paragraphs\Entity\Paragraph;
use Drupal\Core\Session\AccountInterface;
use Drupal\Core\Plugin\ContainerFactoryPluginInterface;
use Drupal\graphql_people\Plugin\GraphQL\DataProducer\TraitUser;
use Symfony\Component\DependencyInjection\ContainerInterface;
use Drupal\graphql\Plugin\GraphQL\DataProducer\DataProducerPluginBase;

/**
 * Update a new user.
 *
 * @DataProducer(
 *   id = "update_user",
 *   name = @Translation("Update User"),
 *   description = @Translation("Update a new user."),
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
class UpdateUser extends DataProducerPluginBase implements ContainerFactoryPluginInterface {

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
   * UpdateUser constructor.
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
    if (isset($data['id']) && $this->currentUser->hasPermission("administer users")) {
      $account = User::load($data['id']);
      unset($data['id']);
      foreach ($data as $key => $value) {
        if (isset($this->mapFields[$key])) {
          $account->set($this->mapFields[$key], $value);
        }
      }
      $account->save();
      return $account;
    }
    return NULL;
  }

}
