<?php

namespace Drupal\Tests\pece_ai\Unit;

use Drupal\Core\Config\ConfigFactoryInterface;
use Drupal\Core\Config\ImmutableConfig;
use Drupal\Core\Entity\ContentEntityInterface;
use Drupal\pece_ai\Service\EmbeddingService;
use Drupal\Tests\UnitTestCase;
use GuzzleHttp\ClientInterface;
use GuzzleHttp\Psr7\Response;

/**
 * @coversDefaultClass \Drupal\pece_ai\Service\EmbeddingService
 * @group pece_ai
 */
class EmbeddingServiceTest extends UnitTestCase {

  private EmbeddingService $service;
  private ClientInterface $httpClient;
  private ConfigFactoryInterface $configFactory;

  protected function setUp(): void {
    parent::setUp();

    $config = $this->createMock(ImmutableConfig::class);
    $config->method('get')->willReturnMap([
      ['embedding_url', 'http://ollama:11434'],
      ['embedding_model', 'nomic-embed-text'],
    ]);

    $this->configFactory = $this->createMock(ConfigFactoryInterface::class);
    $this->configFactory->method('get')
      ->with('pece_ai.settings')
      ->willReturn($config);

    $this->httpClient = $this->createMock(ClientInterface::class);
    $this->service = new EmbeddingService($this->httpClient, $this->configFactory);
  }

  public function testEmbedReturnsFloatArray(): void {
    $vector = array_fill(0, 768, 0.1);
    $body = json_encode(['embedding' => $vector]);
    $this->httpClient->method('request')->willReturn(new Response(200, [], $body));

    $result = $this->service->embed('some text');

    $this->assertCount(768, $result);
    $this->assertIsFloat($result[0]);
  }

  public function testEmbedCallsCorrectEndpoint(): void {
    $vector = array_fill(0, 768, 0.0);
    $this->httpClient->expects($this->once())
      ->method('request')
      ->with(
        'POST',
        'http://ollama:11434/api/embeddings',
        $this->callback(fn($opts) => $opts['json']['model'] === 'nomic-embed-text'
          && $opts['json']['prompt'] === 'hello world')
      )
      ->willReturn(new Response(200, [], json_encode(['embedding' => $vector])));

    $this->service->embed('hello world');
  }

  public function testExtractTextCombinesTitleAndBody(): void {
    $entity = $this->createMock(ContentEntityInterface::class);
    $entity->method('label')->willReturn('My Artifact');

    $bodyField = new class {
      public bool $isEmpty = FALSE;
      public string $value = 'Body content here.';
      public function isEmpty(): bool { return $this->isEmpty; }
    };

    $entity->method('hasField')->willReturnMap([
      ['body', TRUE],
      ['field_annotation_body', FALSE],
      ['field_description', FALSE],
    ]);
    $entity->method('get')->with('body')->willReturn($bodyField);

    $text = $this->service->extractText($entity);

    $this->assertStringContainsString('My Artifact', $text);
    $this->assertStringContainsString('Body content here.', $text);
  }

  public function testExtractTextFallsBackToTitleOnly(): void {
    $entity = $this->createMock(ContentEntityInterface::class);
    $entity->method('label')->willReturn('Title Only');
    $entity->method('hasField')->willReturn(FALSE);

    $text = $this->service->extractText($entity);

    $this->assertEquals('Title Only', $text);
  }

  public function testEmbedThrowsWhenOllamaIsDown(): void {
    $this->httpClient->method('request')
      ->willThrowException(new \GuzzleHttp\Exception\RequestException(
        'Connection refused',
        new \GuzzleHttp\Psr7\Request('POST', '/api/embeddings')
      ));

    $this->expectException(\RuntimeException::class);
    $this->expectExceptionMessageMatches('/Embedding service unavailable/');
    $this->service->embed('some text');
  }

  public function testEmbedThrowsOnMalformedResponse(): void {
    $this->httpClient->method('request')
      ->willReturn(new Response(200, [], json_encode(['wrong_key' => []])));

    $this->expectException(\RuntimeException::class);
    $this->expectExceptionMessageMatches('/Invalid embedding response/');
    $this->service->embed('some text');
  }

}
