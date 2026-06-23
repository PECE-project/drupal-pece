<?php

namespace Drupal\graphql_people\Plugin\GraphQL\DataProducer\Entity;

use Drupal\graphql\Plugin\DataProducerPluginCachingInterface;
use Drupal\graphql\Plugin\GraphQL\DataProducer\DataProducerPluginBase;
use Drupal\user\UserInterface;

/**
 * @DataProducer(
 *   id = "user_email",
 *   name = @Translation("User email"),
 *   description = @Translation("Returns the user email."),
 *   produces = @ContextDefinition("string",
 *     label = @Translation("Email")
 *   ),
 *   consumes = {
 *     "entity" = @ContextDefinition("entity",
 *       label = @Translation("User")
 *     )
 *   }
 * )
 */
class UserEmail extends DataProducerPluginBase implements DataProducerPluginCachingInterface {

  /**
   * @param \Drupal\user\UserInterface $user
   *
   * @return string|null
   */
  public function resolve(UserInterface $user) {
    return $user->getEmail();
  }

}
