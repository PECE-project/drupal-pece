<?php

namespace Drupal\pece_people\Plugin\GraphQL\DataProducer\Entity;

use Drupal\graphql\Plugin\DataProducerPluginCachingInterface;
use Drupal\graphql\Plugin\GraphQL\DataProducer\DataProducerPluginBase;
use Drupal\user\UserInterface;

/**
 * @DataProducer(
 *   id = "user_status",
 *   name = @Translation("User account status"),
 *   description = @Translation("Returns the account status."),
 *   produces = @ContextDefinition("string",
 *     label = @Translation("Account Status")
 *   ),
 *   consumes = {
 *     "entity" = @ContextDefinition("entity",
 *       label = @Translation("User")
 *     )
 *   }
 * )
 */
class UserStatus extends DataProducerPluginBase implements DataProducerPluginCachingInterface {

  /**
   * @param \Drupal\user\UserInterface $user
   *
   * @return string|null
   */
  public function resolve(UserInterface $user) {
    return $user->isActive();
  }

}
