<?php

namespace Drupal\nyx_graphql\Plugin\GraphQL\DataProducer\Entity;

use Drupal\file\Entity\File;
use Drupal\graphql\Plugin\DataProducerPluginCachingInterface;
use Drupal\nyx_graphql\Plugin\GraphQL\DataProducer\ArrayValue;

/**
 * @DataProducer(
 *   id = "file_load",
 *   name = @Translation("Image load"),
 *   description = @Translation("Returns file Entity."),
 *   produces = @ContextDefinition("entity",
 *     label = @Translation("Entity"),
 *     multiple = TRUE
 *   ),
 *   consumes = {
 *     "value" = @ContextDefinition("any",
 *       label = @Translation("Root value")
 *     ),
 *     "path" = @ContextDefinition("string",
 *       label = @Translation("Property path")
 *     )
 *   }
 * )
 */
class FileLoad extends ArrayValue implements DataProducerPluginCachingInterface {

  /**
   * @return string|null
   */
  public function resolve($value, $path) {
    $fid = parent::resolve($value, $path);
    $file = File::load($fid);
    return $file;
  }

}
