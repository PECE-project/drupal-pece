<?php

namespace Drupal\Tests\pece_rules_webhook\Unit;

use Drupal\Core\DependencyInjection\ContainerBuilder;
use Drupal\Core\Extension\ModuleHandlerInterface;
use Drupal\Core\Logger\LoggerChannelFactoryInterface;
use Drupal\Tests\pece_rules_webhook\Unit\Stubs\TestableRulesWebhookPost;
use Drupal\Tests\UnitTestCase;
use GuzzleHttp\ClientInterface;
use Psr\Http\Message\ResponseInterface;
use Psr\Http\Message\StreamInterface;
use Psr\Log\LoggerInterface;

// phpcs:ignore -- stub required because drupal/rules is not installed.
if (!class_exists('Drupal\rules\Core\RulesActionBase')) {
  require_once __DIR__ . '/Stubs/RulesActionBase.php';
}

/**
 * @coversDefaultClass \Drupal\pece_rules_webhook\Plugin\RulesAction\RulesWebhookPost
 * @group pece_rules_webhook
 */
class RulesWebhookPostTest extends UnitTestCase {

  /**
   * The plugin under test.
   *
   * @var \Drupal\Tests\pece_rules_webhook\Unit\TestableRulesWebhookPost
   */
  protected TestableRulesWebhookPost $plugin;

  /**
   * The mocked HTTP client.
   *
   * @var \GuzzleHttp\ClientInterface
   */
  protected ClientInterface $httpClient;

  /**
   * {@inheritdoc}
   */
  protected function setUp(): void {
    parent::setUp();

    $logger = $this->createMock(LoggerInterface::class);
    $loggerFactory = $this->createMock(LoggerChannelFactoryInterface::class);
    $loggerFactory->method('get')->willReturn($logger);

    $stream = $this->createMock(StreamInterface::class);
    $stream->method('getContents')->willReturn('{"ok":true}');

    $guzzleResponse = $this->createMock(ResponseInterface::class);
    $guzzleResponse->method('getStatusCode')->willReturn(200);
    $guzzleResponse->method('getBody')->willReturn($stream);

    $this->httpClient = $this->createMock(ClientInterface::class);
    $this->httpClient->method('request')->willReturn($guzzleResponse);

    $moduleHandler = $this->createMock(ModuleHandlerInterface::class);

    $container = new ContainerBuilder();
    $container->set('http_client', $this->httpClient);
    $container->set('module_handler', $moduleHandler);
    $container->set('string_translation', $this->getStringTranslationStub());
    \Drupal::setContainer($container);

    $this->plugin = new TestableRulesWebhookPost(
      [], 'RulesWebhookPost', [], $loggerFactory, $this->httpClient
    );
  }

  /**
   * @covers ::doExecute
   */
  public function testPlainStringDataPassesThroughUnchanged(): void {
    $captured = NULL;
    $this->httpClient
      ->expects($this->once())
      ->method('request')
      ->willReturnCallback(function ($method, $url, $options) use (&$captured) {
        $captured = $options['body'];
        $stream = $this->createMock(StreamInterface::class);
        $stream->method('getContents')->willReturn('ok');
        $response = $this->createMock(ResponseInterface::class);
        $response->method('getStatusCode')->willReturn(200);
        $response->method('getBody')->willReturn($stream);
        return $response;
      });

    $this->plugin->publicDoExecute('https://example.com/hook', 'plain text');
    $this->assertEquals('plain text', $captured);
  }

  /**
   * @covers ::doExecute
   */
  public function testObjectWithToArrayGetsJsonEncoded(): void {
    $captured = NULL;
    $this->httpClient
      ->expects($this->once())
      ->method('request')
      ->willReturnCallback(function ($method, $url, $options) use (&$captured) {
        $captured = $options['body'];
        $stream = $this->createMock(StreamInterface::class);
        $stream->method('getContents')->willReturn('ok');
        $response = $this->createMock(ResponseInterface::class);
        $response->method('getStatusCode')->willReturn(200);
        $response->method('getBody')->willReturn($stream);
        return $response;
      });

    // Object with only toArray() — no getValue(). Proves the elseif fix works.
    $data = new class {

      /**
       * Returns the array representation of the data.
       */
      public function toArray(): array {
        return ['key' => 'value'];
      }

    };

    $this->plugin->publicDoExecute('https://example.com/hook', $data);
    $this->assertEquals('{"key":"value"}', $captured);
  }

  /**
   * @covers ::doExecute
   */
  public function testApitokenAddsXcsrfTokenHeader(): void {
    $capturedOptions = NULL;
    $this->httpClient
      ->expects($this->once())
      ->method('request')
      ->willReturnCallback(function ($method, $url, $options) use (&$capturedOptions) {
        $capturedOptions = $options;
        $stream = $this->createMock(StreamInterface::class);
        $stream->method('getContents')->willReturn('ok');
        $response = $this->createMock(ResponseInterface::class);
        $response->method('getStatusCode')->willReturn(200);
        $response->method('getBody')->willReturn($stream);
        return $response;
      });

    $this->plugin->publicDoExecute('https://example.com/hook', 'data', NULL, NULL, 'my-token');
    $this->assertEquals('my-token', $capturedOptions['headers']['X-CSRF-Token']);
  }

  /**
   * @covers ::doExecute
   */
  public function testApiUserSetsBasicAuthOption(): void {
    $capturedOptions = NULL;
    $this->httpClient
      ->expects($this->once())
      ->method('request')
      ->willReturnCallback(function ($method, $url, $options) use (&$capturedOptions) {
        $capturedOptions = $options;
        $stream = $this->createMock(StreamInterface::class);
        $stream->method('getContents')->willReturn('ok');
        $response = $this->createMock(ResponseInterface::class);
        $response->method('getStatusCode')->willReturn(200);
        $response->method('getBody')->willReturn($stream);
        return $response;
      });

    $this->plugin->publicDoExecute('https://example.com/hook', 'data', 'user', 'pass');
    $this->assertEquals(['user', 'pass'], $capturedOptions['auth']);
  }

}
