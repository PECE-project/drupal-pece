<?php

namespace Drupal\nyx_graphql\Plugin\GraphQL\DataProducer;

use Drupal\graphql\Plugin\DataProducerPluginCachingInterface;
use Drupal\graphql\Plugin\GraphQL\DataProducer\DataProducerPluginBase;


/**
 * @DataProducer(
 *   id = "array_value",
 *   name = @Translation("Value from Array"),
 *   description = @Translation("Returns value in array."),
 *   produces = @ContextDefinition("any",
 *     label = @Translation("Data Array")
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
class ArrayValue extends DataProducerPluginBase implements DataProducerPluginCachingInterface {

  /**
   * @param $path
   * @param $value
   *
   * @return mixed
   */
  public function resolve($value, $path) {
    $pathArray = explode('.', $path);
    $result = $value;
    foreach ($pathArray as $item) {
      $result = $result[$item];
    }
    return $result;
  }

}
