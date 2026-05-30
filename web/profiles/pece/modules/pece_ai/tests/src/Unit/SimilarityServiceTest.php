<?php

namespace Drupal\Tests\pece_ai\Unit;

use Drupal\Core\Config\ConfigFactoryInterface;
use Drupal\Core\Config\ImmutableConfig;
use Drupal\Core\Entity\ContentEntityInterface;
use Drupal\Core\Entity\EntityTypeManagerInterface;
use Drupal\pece_ai\Service\SimilarityService;
use Drupal\Tests\UnitTestCase;
use GuzzleHttp\ClientInterface;
use GuzzleHttp\Exception\RequestException;
use GuzzleHttp\Psr7\Request;
use GuzzleHttp\Psr7\Response;

/**
 * @coversDefaultClass \Drupal\pece_ai\Service\SimilarityService
 * @group pece_ai
 */
class SimilarityServiceTest extends UnitTestCase {

  /**
   * The similarity service under test.
   *
   * @var \Drupal\pece_ai\Service\SimilarityService
   */
  private SimilarityService $service;

  /**
   * The mocked HTTP client.
   *
   * @var \GuzzleHttp\ClientInterface|\PHPUnit\Framework\MockObject\MockObject
   */
  private ClientInterface $httpClient;

  /**
   * {@inheritdoc}
   */
  protected function setUp(): void {
    parent::setUp();

    $config = $this->createMock(ImmutableConfig::class);
    $config->method('get')->willReturnMap([
      ['qdrant_url', 'http://qdrant:6333'],
      ['sidebar_limit', 5],
    ]);
    $configFactory = $this->createMock(ConfigFactoryInterface::class);
    $configFactory->method('get')->with('pece_ai.settings')->willReturn($config);

    $this->httpClient = $this->createMock(ClientInterface::class);
    $entityTypeManager = $this->createMock(EntityTypeManagerInterface::class);

    $this->service = new SimilarityService($this->httpClient, $configFactory, $entityTypeManager);
  }

  /**
   * Tests that findSimilar() returns the top matching results.
   */
  public function testFindSimilarReturnsTopMatches(): void {
    $vector = array_fill(0, 768, 0.1);
    $getResponse = new Response(200, [], json_encode([
      'result' => ['vector' => $vector],
    ]));
    $searchResponse = new Response(200, [], json_encode([
      'result' => [
        [
          'id' => 99,
          'score' => 0.95,
          'payload' => [
            'entity_type' => 'node',
            'entity_id' => 99,
            'bundle' => 'pece_essay',
            'group_ids' => [],
          ],
        ],
        [
          'id' => 42,
          'score' => 0.88,
          'payload' => [
            'entity_type' => 'node',
            'entity_id' => 42,
            'bundle' => 'pece_artifact_pdf',
            'group_ids' => [],
          ],
        ],
      ],
    ]));

    $entity = $this->mockEntity(1);
    $this->httpClient->method('request')
      ->willReturnOnConsecutiveCalls($getResponse, $searchResponse);

    $results = $this->service->findSimilar($entity);

    $this->assertCount(2, $results);
    $this->assertEquals(99, $results[0]['entity_id']);
    $this->assertEquals(95, $results[0]['score']);
  }

  /**
   * Tests that findSimilar() excludes the source entity from results.
   */
  public function testFindSimilarExcludesSelf(): void {
    $vector = array_fill(0, 768, 0.1);
    $getResponse = new Response(200, [], json_encode(['result' => ['vector' => $vector]]));
    $searchResponse = new Response(200, [], json_encode([
      'result' => [
        [
          'id' => 1,
          'score' => 1.0,
          'payload' => [
            'entity_type' => 'node',
            'entity_id' => 1,
            'bundle' => 'pece_essay',
            'group_ids' => [],
          ],
        ],
        [
          'id' => 2,
          'score' => 0.9,
          'payload' => [
            'entity_type' => 'node',
            'entity_id' => 2,
            'bundle' => 'pece_essay',
            'group_ids' => [],
          ],
        ],
      ],
    ]));

    $entity = $this->mockEntity(1);
    $this->httpClient->method('request')
      ->willReturnOnConsecutiveCalls($getResponse, $searchResponse);

    $results = $this->service->findSimilar($entity);

    $this->assertCount(1, $results);
    $this->assertEquals(2, $results[0]['entity_id']);
  }

  /**
   * Tests that findSimilar() applies a group filter when group IDs are given.
   */
  public function testFindSimilarAppliesGroupFilter(): void {
    $vector = array_fill(0, 768, 0.1);
    $getResponse = new Response(200, [], json_encode(['result' => ['vector' => $vector]]));

    $entity = $this->mockEntity(5);
    $this->httpClient->expects($this->exactly(2))
      ->method('request')
      ->willReturnCallback(function ($method, $url, $opts) use ($getResponse) {
        if (str_contains($url, '/search')) {
          $this->assertArrayHasKey('filter', $opts['json']);
          return new Response(200, [], json_encode(['result' => []]));
        }
        return $getResponse;
      });

    $this->service->findSimilar($entity, 5, ['10', '20']);
  }

  /**
   * Tests that findSimilar() returns an empty array when Qdrant is unavailable.
   */
  public function testFindSimilarReturnsEmptyWhenQdrantUnavailable(): void {
    $entity = $this->mockEntity(1);
    $this->httpClient->method('request')->willThrowException(
      new RequestException('Connection refused', new Request('GET', '/'))
    );

    $results = $this->service->findSimilar($entity);

    $this->assertSame([], $results);
  }

  /**
   * Tests that getVector() returns NULL when the entity is not found.
   */
  public function testGetVectorReturnsNullWhenNotFound(): void {
    $entity = $this->mockEntity(1);
    $this->httpClient->method('request')->willThrowException(
      new RequestException('Not found', new Request('GET', '/'))
    );

    $result = $this->service->getVector($entity);

    $this->assertNull($result);
  }

  /**
   * Tests that upsert() sends the correct payload to Qdrant.
   */
  public function testUpsertSendsCorrectPayload(): void {
    $entity = $this->mockEntity(7);
    $entity->method('getEntityTypeId')->willReturn('node');
    $entity->method('bundle')->willReturn('pece_essay');
    $entity->method('hasField')->with('field_groups_with_view_access')->willReturn(FALSE);

    $this->httpClient->expects($this->once())
      ->method('request')
      ->with(
        'PUT',
        'http://qdrant:6333/collections/pece_entities/points',
        $this->callback(fn($opts) =>
          $opts['json']['points'][0]['id'] === 7 &&
          $opts['json']['points'][0]['payload']['entity_type'] === 'node'
        )
      )
      ->willReturn(new Response(200, [], json_encode(['result' => ['status' => 'ok']])));

    $this->service->upsert($entity, array_fill(0, 768, 0.1));
  }

  /**
   * Tests that upsert() throws a RuntimeException when Qdrant is unavailable.
   */
  public function testUpsertThrowsWhenQdrantUnavailable(): void {
    $entity = $this->mockEntity(7);
    $entity->method('getEntityTypeId')->willReturn('node');
    $entity->method('bundle')->willReturn('pece_essay');
    $entity->method('hasField')->with('field_groups_with_view_access')->willReturn(FALSE);

    $this->httpClient->method('request')
      ->willThrowException(new RequestException('Connection refused', new Request('PUT', '/')));

    $this->expectException(\RuntimeException::class);
    $this->expectExceptionMessageMatches('/Failed to upsert entity/');
    $this->service->upsert($entity, array_fill(0, 768, 0.1));
  }

  /**
   * Tests that findSimilarByVector queries Qdrant with the provided vector.
   */
  public function testFindSimilarByVectorQueriesQdrantWithVector(): void {
    $vector = array_fill(0, 768, 0.5);
    $responseBody = json_encode([
      'result' => [
        [
          'id' => 42,
          'score' => 0.91,
          'payload' => [
            'entity_type' => 'node',
            'entity_id' => 42,
            'bundle' => 'pece_essay',
            'group_ids' => [],
          ],
        ],
      ],
    ]);

    $httpClient = $this->createMock(ClientInterface::class);
    $httpClient->expects($this->once())
      ->method('request')
      ->with('POST', 'http://qdrant:6333/collections/pece_entities/points/search',
        $this->callback(fn($opts) => $opts['json']['vector'] === $vector))
      ->willReturn(new Response(200, [], $responseBody));

    $config = $this->createMock(ImmutableConfig::class);
    $config->method('get')->willReturnMap([
      ['qdrant_url', 'http://qdrant:6333'],
    ]);
    $configFactory = $this->createMock(ConfigFactoryInterface::class);
    $configFactory->method('get')->with('pece_ai.settings')->willReturn($config);

    $entityTypeManager = $this->createMock(EntityTypeManagerInterface::class);
    $service = new SimilarityService($httpClient, $configFactory, $entityTypeManager);

    $results = $service->findSimilarByVector($vector, 5);

    $this->assertCount(1, $results);
    $this->assertEquals(91, $results[0]['score']);
    $this->assertEquals(42, $results[0]['entity_id']);
  }

  /**
   * Creates a mock ContentEntityInterface with the given ID.
   *
   * @param int $id
   *   The entity ID to mock.
   *
   * @return \Drupal\Core\Entity\ContentEntityInterface|\PHPUnit\Framework\MockObject\MockObject
   *   The mocked entity.
   */
  private function mockEntity(int $id): ContentEntityInterface {
    $entity = $this->createMock(ContentEntityInterface::class);
    $entity->method('id')->willReturn($id);
    $entity->method('getEntityTypeId')->willReturn('node');
    $entity->method('bundle')->willReturn('pece_essay');
    $entity->method('hasField')->willReturn(FALSE);
    return $entity;
  }

}
