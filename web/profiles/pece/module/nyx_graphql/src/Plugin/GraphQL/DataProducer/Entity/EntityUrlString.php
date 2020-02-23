<?php

namespace Drupal\nyx_graphql\Plugin\GraphQL\DataProducer\Entity;

use Drupal\Core\Cache\CacheableResponse;
use Drupal\Core\Entity\EntityInterface;
use Drupal\graphql\Plugin\GraphQL\DataProducer\DataProducerPluginBase;
use http\Env\Response;

/**
 * @DataProducer(
 *   id = "entity_url_string",
 *   name = @Translation("Entity url"),
 *   description = @Translation("Returns the entity's url."),
 *   produces = @ContextDefinition("any",
 *     label = @Translation("Url")
 *   ),
 *   consumes = {
 *     "entity" = @ContextDefinition("entity",
 *       label = @Translation("Entity")
 *     )
 *   }
 * )
 */
class EntityUrlString extends DataProducerPluginBase {

  /**
   * @param \Drupal\Core\Entity\EntityInterface $entity
   *
   * @return \Drupal\Core\Url
   * @throws \Drupal\Core\Entity\EntityMalformedException
   */
  public function resolve(EntityInterface $entity) {
    $url = $entity->toUrl()->toString(TRUE);
    $url_string = $url->getGeneratedUrl();
    return $url_string;
  }

}
