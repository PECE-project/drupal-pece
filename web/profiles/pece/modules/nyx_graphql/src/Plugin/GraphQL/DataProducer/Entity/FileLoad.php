<?php

namespace Drupal\nyx_graphql\Plugin\GraphQL\DataProducer\Entity;

use Drupal\Core\Entity\EntityInterface;
use Drupal\graphql\GraphQL\Execution\ResolveContext;
use Drupal\graphql\Plugin\DataProducerPluginCachingInterface;
use Drupal\graphql\Plugin\GraphQL\DataProducer\DataProducerPluginBase;
use Drupal\nyx_graphql\Plugin\GraphQL\DataProducer\ArrayValue;
use Drupal\user\Entity\User;
use Drupal\user\UserInterface;
use GraphQL\Type\Definition\ResolveInfo;

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
    $file = \Drupal\file\Entity\File::load($fid);
    return $file;
  }

}

