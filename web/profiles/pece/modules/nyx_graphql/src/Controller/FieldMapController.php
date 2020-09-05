<?php

namespace Drupal\nyx_graphql\Controller;

use Drupal\Component\Plugin\ConfigurableInterface;
use Drupal\Core\DependencyInjection\ContainerInjectionInterface;
use Drupal\graphql\Entity\ServerInterface;
use Drupal\graphql\GraphQL\Utility\Introspection;
use Symfony\Component\DependencyInjection\ContainerInterface;

/**
 * Controller for the GraphQL Fields Maps visualisation API.
 *
 * @codeCoverageIgnore
 */
class FieldMapController implements ContainerInjectionInterface {
  /**
   * The introspection service.
   *
   * @var \Drupal\graphql\GraphQL\Utility\Introspection
   */
  protected $introspection;

  /**
   * {@inheritdoc}
   *
   * @codeCoverageIgnore
   */
  public static function create(ContainerInterface $container) {
    return new static($container->get('graphql.introspection'));
  }

  /**
   * VoyagerController constructor.
   *
   * @param \Drupal\graphql\GraphQL\Utility\Introspection $introspection
   *   The GraphQL introspection service.
   *
   * @codeCoverageIgnore
   */
  public function __construct(Introspection $introspection) {
    $this->introspection = $introspection;
  }

  /**
   * Display for the GraphQL Fields Map visualization API.
   *
   * @param \Drupal\graphql\Entity\ServerInterface $graphql_server
   *   The server.
   *
   * @return array The render array.
   *   The render array.
   */
  public function viewFieldsMap(ServerInterface $graphql_server) {
    $introspectionData = $this->introspection->introspect($graphql_server);
    $schema = $graphql_server->get('schema');
    $manager = \Drupal::service('plugin.manager.graphql.schema');

    /** @var \Drupal\graphql\Plugin\SchemaPluginInterface $plugin */
    $plugin = $manager->createInstance($schema);
    if ($plugin instanceof ConfigurableInterface && $config = $graphql_server->get('schema_configuration')) {
      $plugin->setConfiguration($config[$schema] ?? []);
    }

    // Create the server config.
    $registry = $plugin->getResolverRegistry();
    $plugin->getSchema($registry);
    $resolvers = $registry->getAllFieldResolvers();
    $print = "<ul>";
    foreach ($resolvers as $name => $objects) {
      $print .= "<li>$name<ul>";
      foreach ($objects as $field => $object) {
        $print .= "<li>$field</li>";
      }
      $print .= "</ul></li>";
    }
    $print .= "</ul>";

    return [
      '#type' => 'markup',
      '#markup' => '<div id="graphql-field-maps"> ' . $print.'</div>',
    ];
  }

}
