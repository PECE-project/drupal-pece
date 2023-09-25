<?php

namespace Drupal\pece_rules_webhook\Plugin\RulesAction;

use Drupal\rules\Core\RulesActionBase;
use Drupal\Core\Logger\LoggerChannelFactoryInterface;
use Drupal\Core\Plugin\ContainerFactoryPluginInterface;
use Symfony\Component\DependencyInjection\ContainerInterface;
use GuzzleHttp\ClientInterface;
use GuzzleHttp\Exception\RequestException;

/**
 * Provides "Rules Webhook Post" rules action.
 *
 * @RulesAction(
 *   id = "RulesWebhookPost",
 *   label = @Translation("Webhook POST"),
 *   category = @Translation("Data"),
 *   context = {
 *     "url" = @ContextDefinition("string",
 *       label = @Translation("URL"),
 *       description = @Translation("The Url address to the webhook request send. <br><b>Example:</b> https://example.com/webhook/service/token "),
 *       required = TRUE,
 *     ),
 *     "data" = @ContextDefinition("any",
 *       label = @Translation("Value do send the webhook"),
 *       description = @Translation("Value to send the webhook. If is object, then change to json."),
 *       required = TRUE,
 *       multiple = TRUE
 *      ),
 *     "apiuser" = @ContextDefinition("string",
 *       label = @Translation("API User Name"),
 *       description = @Translation("Username for API Access"),
 *       required = FALSE,
 *      ),
 *     "apipass" = @ContextDefinition("string",
 *       label = @Translation("API User Password"),
 *       description = @Translation("Password for API Access"),
 *       required = FALSE,
 *      ),
 *     "apitoken" = @ContextDefinition("string",
 *       label = @Translation("API Session Token"),
 *       description = @Translation("Session Token for API Access"),
 *       required = FALSE,
 *      ),
 *   },
 *   provides = {
 *     "http_response" = @ContextDefinition("string",
 *       label = @Translation("HTTP data")
 *     )
 *   }
 * )
 *
 */
class RulesWebhookPost extends RulesActionBase implements ContainerFactoryPluginInterface {

  /**
   * The logger for the rules channel.
   *
   * @var \Psr\Log\LoggerInterface
   */
  protected $logger;

  /**
   * The HTTP client to fetch the feed data with.
   *
   * @var \GuzzleHttp\ClientInterface
   */
  protected $httpClient;

  /**
   * Set up form variables
   *
   * @param string $url
   *   Url addresses to Webhook post.
   * @param mixed $data
   *   Value to send the webhook.
   * @param string $apiuser
   *   (optional) The User Name for webhook call
   * @param string $apipass
   *   (optional) The User Password for webhook call
   * @param string $apitoken
   *   (optional) The Session Token for webhook call
   */
  protected function doExecute($url, $data, $apiuser = NULL, $apipass = NULL, $apitoken = NULL ) {
    $this->logger->info("Start webhook post");
    // Logs a notice

    if (is_object($data)) {
      if (method_exists($data, 'toArray')) {
        $dataValue = json_encode($data->toArray());
      }
      if (method_exists($data, 'getValue')) {
        $dataValue = json_encode($data->getValue());
      }
      else {
        $dataValue = json_encode($data);
      }
    }
    else
      $dataValue = $data;

    \Drupal::moduleHandler()->alter('value_to_webhook', $dataValue);

    $client = \Drupal::httpClient();
    $method = 'POST';
    $options = [
      'body' => $dataValue,
      'headers' => [
        'Content-Type' => 'application/json',
        'Accept' => 'application/json'
      ],
    ];

    if ($apiuser) {
      $options['auth'] = [$apiuser, $apipass];
    }
    if ($apitoken) {
      $options['headers']['X-CSRF-Token'] = $apitoken;
    }

    try {
      $response = $client->request($method, $url, $options);
      $code = $response->getStatusCode();
      if ($code == 200) {
        $body = $response->getBody()->getContents();
        return $body;
      }
    }
    catch (RequestException $e) {
      watchdog_exception('rules_webhook_post', $e);
    }
  }

  /**
   * Constructs a httpClient object.
   *
   * @param array $configuration
   *   A configuration array containing information about the plugin instance.
   * @param string $plugin_id
   *   The plugin ID for the plugin instance.
   * @param mixed $plugin_definition
   *   The plugin implementation definition.
   * @param \Drupal\Core\Logger\LoggerChannelFactoryInterface $logger_factory
   *   The logger factory service.
   * @param GuzzleHttp\ClientInterface $http_client
   *   The guzzle http client instance.
   */
  public function __construct(array $configuration, $plugin_id, $plugin_definition, LoggerChannelFactoryInterface $logger_factory, ClientInterface $http_client) {
    parent::__construct($configuration, $plugin_id, $plugin_definition);
    $this->logger = $logger_factory->get('rules_webhook_post');
    $this->http_client = $http_client;
  }

  /**
   * {@inheritdoc}
   */
  public static function create(ContainerInterface $container, array $configuration, $plugin_id, $plugin_definition) {
    return new static(
      $configuration,
      $plugin_id,
      $plugin_definition,
      $container->get('logger.factory'),
      $container->get('http_client')
    );
  }
}
