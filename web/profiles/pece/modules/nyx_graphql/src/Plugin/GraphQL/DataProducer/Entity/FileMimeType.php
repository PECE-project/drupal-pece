<?php

namespace Drupal\nyx_graphql\Plugin\GraphQL\DataProducer\Entity;

use Drupal\file\Entity\File;
use Drupal\graphql\Plugin\GraphQL\DataProducer\DataProducerPluginBase;

/**
 * @DataProducer(
 *   id = "file_mimetype",
 *   name = @Translation("File mime type"),
 *   description = @Translation("Returns the file's mime type."),
 *   produces = @ContextDefinition("any",
 *     label = @Translation("Mime Type")
 *   ),
 *   consumes = {
 *     "entity" = @ContextDefinition("entity",
 *       label = @Translation("Entity")
 *     )
 *   }
 * )
 */
class FileMimeType extends DataProducerPluginBase {

  /**
   * @param \Drupal\file\Entity\File $entity
   *
   * @return \Drupal\Core\Url
   * @throws \Drupal\Core\Entity\EntityMalformedException
   */
  public function resolve(File $entity) {
    return $entity->getMimeType();
  }

}
