<?php

namespace Drupal\pece_people\Plugin\GraphQL\DataProducer\Entity;

use Drupal\graphql\Plugin\DataProducerPluginCachingInterface;
use Drupal\graphql\Plugin\GraphQL\DataProducer\DataProducerPluginBase;
use Drupal\user\UserInterface;

/**
 * @DataProducer(
 *   id = "user_roles",
 *   name = @Translation("User roles"),
 *   description = @Translation("Returns the user roles."),
 *   produces = @ContextDefinition("string",
 *     label = @Translation("User roles")
 *   ),
 *   consumes = {
 *     "entity" = @ContextDefinition("entity",
 *       label = @Translation("User")
 *     )
 *   }
 * )
 */
class UserRoles extends DataProducerPluginBase implements DataProducerPluginCachingInterface {

  /**
   * @param \Drupal\user\UserInterface $user
   *
   * @return string|null
   */
  public function resolve(UserInterface $user) {
    return $user->getRoles();
  }

}
