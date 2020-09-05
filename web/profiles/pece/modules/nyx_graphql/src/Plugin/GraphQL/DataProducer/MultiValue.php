<?php

namespace Drupal\nyx_graphql\Plugin\GraphQL\DataProducer;

use Drupal\graphql\Plugin\DataProducerPluginCachingInterface;
use Drupal\graphql\Plugin\GraphQL\DataProducer\DataProducerPluginBase;


/**
 * @DataProducer(
 *   id = "multi_value",
 *   name = @Translation("All values from field multivalues"),
 *   description = @Translation("Returns all field's values."),
 *   produces = @ContextDefinition("any",
 *     label = @Translation("Data Field")
 *   ),
 *   consumes = {
 *     "values" = @ContextDefinition("any",
 *       label = @Translation("Array with values")
 *     )
 *   }
 * )
 */
class MultiValue extends DataProducerPluginBase implements DataProducerPluginCachingInterface {

  /**
   * @param $path
   * @param $value
   *
   * @return mixed
   */
  public function resolve($values) {
    $data = [];
    foreach ($values as $value) {
      $data[] = $value['value'];
    }

    return $data;
  }

}
