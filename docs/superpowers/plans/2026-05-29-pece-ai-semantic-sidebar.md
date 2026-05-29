# PECE AI Semantic Sidebar Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Build the `pece_ai` Drupal module — a vector similarity sidebar surfacing related artifacts, essays, annotations, and memos on content view pages.

**Architecture:** Async embedding pipeline (entity save → Drupal queue → Ollama → Qdrant upsert) and a synchronous Block plugin (page load → Qdrant search → entity render). All external HTTP calls are mocked in tests; Qdrant and Ollama are only required for local dev and production. Group-scoped by default via entity's `field_groups` field; `?ai_scope=global` query param shows platform-wide results.

**Tech Stack:** Drupal 11, PHP 8.3, Qdrant (vector DB, Docker), Ollama `nomic-embed-text` (768-dim embeddings, CPU-only), Guzzle HTTP (already in Drupal core), PHPUnit 10 (Unit + Kernel suites).

---

## File Map

```
.ddev/docker-compose.ai.yaml                                   ← Qdrant + Ollama containers
web/profiles/pece/modules/pece_ai/
├── pece_ai.info.yml
├── pece_ai.module                                             ← hook_entity_insert/update + hook_theme
├── pece_ai.services.yml
├── config/install/pece_ai.settings.yml
├── src/
│   ├── EventSubscriber/EntityEmbedSubscriber.php              ← queues entities on save
│   ├── Plugin/QueueWorker/EmbedEntityWorker.php               ← embeds queued entities
│   ├── Plugin/Block/RelatedContentBlock.php                   ← sidebar block
│   ├── Service/EmbeddingService.php                           ← Ollama HTTP wrapper
│   ├── Service/SimilarityService.php                          ← Qdrant HTTP wrapper
│   └── Commands/PeceAiCommands.php                            ← drush pece-ai:setup + pece-ai:backfill
├── templates/pece-ai-related-content.html.twig
└── tests/src/
    ├── Unit/
    │   ├── EmbeddingServiceTest.php
    │   └── SimilarityServiceTest.php
    └── Kernel/
        ├── EntityEmbedSubscriberTest.php
        ├── EmbedEntityWorkerTest.php
        └── RelatedContentBlockTest.php
```

---

## Task 0: DDEV AI Infrastructure

**Files:**
- Create: `.ddev/docker-compose.ai.yaml`

- [ ] **Step 1: Create the Docker Compose file**

```yaml
# .ddev/docker-compose.ai.yaml
services:
  qdrant:
    image: qdrant/qdrant:latest
    ports:
      - "6333:6333"
    volumes:
      - qdrant_storage:/qdrant/storage

  ollama:
    image: ollama/ollama:latest
    ports:
      - "11434:11434"
    volumes:
      - ollama_models:/root/.ollama
    entrypoint: ["/bin/sh", "-c",
      "ollama serve & sleep 5 && ollama pull nomic-embed-text && wait"]

volumes:
  qdrant_storage:
  ollama_models:
```

- [ ] **Step 2: Restart DDEV and verify services start**

```bash
ddev restart
ddev exec curl -s http://qdrant:6333/healthz
```

Expected output: `{"title":"qdrant - healthy",...}` (or similar health response)

- [ ] **Step 3: Commit**

```bash
git add .ddev/docker-compose.ai.yaml
git commit -m "feat(pece_ai): add Qdrant and Ollama DDEV services"
```

---

## Task 1: Module Scaffold

**Files:**
- Create: `web/profiles/pece/modules/pece_ai/pece_ai.info.yml`
- Create: `web/profiles/pece/modules/pece_ai/pece_ai.services.yml`
- Create: `web/profiles/pece/modules/pece_ai/pece_ai.module`
- Create: `web/profiles/pece/modules/pece_ai/config/install/pece_ai.settings.yml`

- [ ] **Step 1: Create `pece_ai.info.yml`**

```yaml
name: PECE AI
type: module
description: 'Semantic similarity sidebar powered by self-hosted vector embeddings.'
package: PECE
core_version_requirement: ^11
dependencies:
  - drupal:system
  - drupal:node
  - drupal:user
  - drupal:taxonomy
```

- [ ] **Step 2: Create `pece_ai.services.yml`**

```yaml
services:
  pece_ai.embedding_service:
    class: Drupal\pece_ai\Service\EmbeddingService
    arguments: ['@http_client', '@config.factory']

  pece_ai.similarity_service:
    class: Drupal\pece_ai\Service\SimilarityService
    arguments: ['@http_client', '@config.factory', '@entity_type.manager']

  pece_ai.entity_embed_subscriber:
    class: Drupal\pece_ai\EventSubscriber\EntityEmbedSubscriber
    arguments: ['@queue', '@config.factory']

  pece_ai.commands:
    class: Drupal\pece_ai\Commands\PeceAiCommands
    arguments:
      - '@entity_type.manager'
      - '@queue'
      - '@pece_ai.embedding_service'
      - '@pece_ai.similarity_service'
      - '@config.factory'
    tags:
      - { name: drush.command }
```

- [ ] **Step 3: Create `pece_ai.module`**

```php
<?php

use Drupal\Core\Entity\EntityInterface;

function pece_ai_entity_insert(EntityInterface $entity): void {
  \Drupal::service('pece_ai.entity_embed_subscriber')->onEntitySave($entity);
}

function pece_ai_entity_update(EntityInterface $entity): void {
  \Drupal::service('pece_ai.entity_embed_subscriber')->onEntitySave($entity);
}

function pece_ai_theme(): array {
  return [
    'pece_ai_related_content' => [
      'variables' => ['items' => [], 'scope_label' => NULL, 'toggle_url' => NULL],
    ],
  ];
}
```

- [ ] **Step 4: Create `config/install/pece_ai.settings.yml`**

```yaml
qdrant_url: 'http://qdrant:6333'
embedding_url: 'http://ollama:11434'
embedding_model: 'nomic-embed-text'
sidebar_limit: 5
enabled_bundles:
  - 'node:pece_artifact_pdf'
  - 'node:pece_artifact_image'
  - 'node:pece_artifact_video'
  - 'node:pece_artifact_audio'
  - 'node:pece_artifact_text'
  - 'node:pece_artifact_website'
  - 'node:pece_artifact_fieldsite'
  - 'node:pece_artifact_bundle'
  - 'node:pece_essay'
  - 'node:pece_photo_essay'
  - 'node:pece_timeline_essay'
  - 'node:pece_annotation'
  - 'node:pece_memo'
```

- [ ] **Step 5: Commit**

```bash
git add web/profiles/pece/modules/pece_ai/
git commit -m "feat(pece_ai): scaffold module with services and config"
```

---

## Task 2: EmbeddingService

**Files:**
- Create: `web/profiles/pece/modules/pece_ai/src/Service/EmbeddingService.php`
- Create: `web/profiles/pece/modules/pece_ai/tests/src/Unit/EmbeddingServiceTest.php`

- [ ] **Step 1: Write the failing tests**

```php
<?php
// web/profiles/pece/modules/pece_ai/tests/src/Unit/EmbeddingServiceTest.php

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
    $this->httpClient->method('post')->willReturn(new Response(200, [], $body));

    $result = $this->service->embed('some text');

    $this->assertCount(768, $result);
    $this->assertIsFloat($result[0]);
  }

  public function testEmbedCallsCorrectEndpoint(): void {
    $vector = array_fill(0, 768, 0.0);
    $this->httpClient->expects($this->once())
      ->method('post')
      ->with(
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

}
```

- [ ] **Step 2: Run test to verify it fails**

```bash
SIMPLETEST_DB='mysql://drupal:drupal@127.0.0.1/drupal' \
vendor/bin/phpunit --testsuite unit \
  web/profiles/pece/modules/pece_ai/tests/src/Unit/EmbeddingServiceTest.php -v
```

Expected: FAIL — `Class "Drupal\pece_ai\Service\EmbeddingService" not found`

- [ ] **Step 3: Implement `EmbeddingService`**

```php
<?php
// web/profiles/pece/modules/pece_ai/src/Service/EmbeddingService.php

namespace Drupal\pece_ai\Service;

use Drupal\Core\Config\ConfigFactoryInterface;
use Drupal\Core\Entity\EntityInterface;
use GuzzleHttp\ClientInterface;

class EmbeddingService {

  public function __construct(
    private readonly ClientInterface $httpClient,
    private readonly ConfigFactoryInterface $configFactory,
  ) {}

  public function embed(string $text): array {
    $config = $this->configFactory->get('pece_ai.settings');
    $response = $this->httpClient->post($config->get('embedding_url') . '/api/embeddings', [
      'json' => [
        'model' => $config->get('embedding_model'),
        'prompt' => $text,
      ],
    ]);
    $data = json_decode($response->getBody()->getContents(), TRUE);
    return $data['embedding'];
  }

  public function extractText(EntityInterface $entity): string {
    $parts = [$entity->label()];
    foreach (['body', 'field_annotation_body', 'field_description'] as $field) {
      if ($entity->hasField($field)) {
        $value = $entity->get($field);
        if (!$value->isEmpty()) {
          $parts[] = $value->value;
        }
      }
    }
    return implode("\n\n", array_filter($parts));
  }

}
```

- [ ] **Step 4: Run tests to verify they pass**

```bash
SIMPLETEST_DB='mysql://drupal:drupal@127.0.0.1/drupal' \
vendor/bin/phpunit --testsuite unit \
  web/profiles/pece/modules/pece_ai/tests/src/Unit/EmbeddingServiceTest.php -v
```

Expected: 4 tests, 0 failures

- [ ] **Step 5: Commit**

```bash
git add web/profiles/pece/modules/pece_ai/src/Service/EmbeddingService.php \
        web/profiles/pece/modules/pece_ai/tests/src/Unit/EmbeddingServiceTest.php
git commit -m "feat(pece_ai): add EmbeddingService with unit tests"
```

---

## Task 3: SimilarityService

**Files:**
- Create: `web/profiles/pece/modules/pece_ai/src/Service/SimilarityService.php`
- Create: `web/profiles/pece/modules/pece_ai/tests/src/Unit/SimilarityServiceTest.php`

- [ ] **Step 1: Write the failing tests**

```php
<?php
// web/profiles/pece/modules/pece_ai/tests/src/Unit/SimilarityServiceTest.php

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

  private SimilarityService $service;
  private ClientInterface $httpClient;

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

  public function testFindSimilarReturnsTopMatches(): void {
    $vector = array_fill(0, 768, 0.1);
    $getResponse = new Response(200, [], json_encode([
      'result' => ['vector' => $vector],
    ]));
    $searchResponse = new Response(200, [], json_encode([
      'result' => [
        ['id' => 99, 'score' => 0.95, 'payload' => ['entity_type' => 'node', 'entity_id' => 99, 'bundle' => 'pece_essay', 'group_ids' => []]],
        ['id' => 42, 'score' => 0.88, 'payload' => ['entity_type' => 'node', 'entity_id' => 42, 'bundle' => 'pece_artifact_pdf', 'group_ids' => []]],
      ],
    ]));

    $entity = $this->mockEntity(1);
    $this->httpClient->method('get')->willReturn($getResponse);
    $this->httpClient->method('post')->willReturn($searchResponse);

    $results = $this->service->findSimilar($entity);

    $this->assertCount(2, $results);
    $this->assertEquals(99, $results[0]['entity_id']);
    $this->assertEquals(95, $results[0]['score']);
  }

  public function testFindSimilarExcludesSelf(): void {
    $vector = array_fill(0, 768, 0.1);
    $getResponse = new Response(200, [], json_encode(['result' => ['vector' => $vector]]));
    $searchResponse = new Response(200, [], json_encode([
      'result' => [
        ['id' => 1, 'score' => 1.0, 'payload' => ['entity_type' => 'node', 'entity_id' => 1, 'bundle' => 'pece_essay', 'group_ids' => []]],
        ['id' => 2, 'score' => 0.9, 'payload' => ['entity_type' => 'node', 'entity_id' => 2, 'bundle' => 'pece_essay', 'group_ids' => []]],
      ],
    ]));

    $entity = $this->mockEntity(1);
    $this->httpClient->method('get')->willReturn($getResponse);
    $this->httpClient->method('post')->willReturn($searchResponse);

    $results = $this->service->findSimilar($entity);

    $this->assertCount(1, $results);
    $this->assertEquals(2, $results[0]['entity_id']);
  }

  public function testFindSimilarAppliesGroupFilter(): void {
    $vector = array_fill(0, 768, 0.1);
    $getResponse = new Response(200, [], json_encode(['result' => ['vector' => $vector]]));

    $entity = $this->mockEntity(5);
    $this->httpClient->method('get')->willReturn($getResponse);
    $this->httpClient->expects($this->once())
      ->method('post')
      ->with(
        $this->anything(),
        $this->callback(fn($opts) => isset($opts['json']['filter']['must']))
      )
      ->willReturn(new Response(200, [], json_encode(['result' => []])));

    $this->service->findSimilar($entity, 5, ['10', '20']);
  }

  public function testFindSimilarReturnsEmptyWhenQdrantUnavailable(): void {
    $entity = $this->mockEntity(1);
    $this->httpClient->method('get')->willThrowException(
      new RequestException('Connection refused', new Request('GET', '/'))
    );

    $results = $this->service->findSimilar($entity);

    $this->assertSame([], $results);
  }

  public function testGetVectorReturnsNullWhenNotFound(): void {
    $entity = $this->mockEntity(1);
    $this->httpClient->method('get')->willThrowException(
      new RequestException('Not found', new Request('GET', '/'))
    );

    $result = $this->service->getVector($entity);

    $this->assertNull($result);
  }

  public function testUpsertSendsCorrectPayload(): void {
    $entity = $this->mockEntity(7);
    $entity->method('getEntityTypeId')->willReturn('node');
    $entity->method('bundle')->willReturn('pece_essay');
    $entity->method('hasField')->with('field_groups')->willReturn(FALSE);

    $this->httpClient->expects($this->once())
      ->method('put')
      ->with(
        'http://qdrant:6333/collections/pece_entities/points',
        $this->callback(fn($opts) =>
          $opts['json']['points'][0]['id'] === 7 &&
          $opts['json']['points'][0]['payload']['entity_type'] === 'node'
        )
      )
      ->willReturn(new Response(200, [], json_encode(['result' => ['status' => 'ok']])));

    $this->service->upsert($entity, array_fill(0, 768, 0.1));
  }

  private function mockEntity(int $id): ContentEntityInterface {
    $entity = $this->createMock(ContentEntityInterface::class);
    $entity->method('id')->willReturn($id);
    $entity->method('getEntityTypeId')->willReturn('node');
    $entity->method('bundle')->willReturn('pece_essay');
    $entity->method('hasField')->willReturn(FALSE);
    return $entity;
  }

}
```

- [ ] **Step 2: Run test to verify it fails**

```bash
SIMPLETEST_DB='mysql://drupal:drupal@127.0.0.1/drupal' \
vendor/bin/phpunit --testsuite unit \
  web/profiles/pece/modules/pece_ai/tests/src/Unit/SimilarityServiceTest.php -v
```

Expected: FAIL — `Class "Drupal\pece_ai\Service\SimilarityService" not found`

- [ ] **Step 3: Implement `SimilarityService`**

```php
<?php
// web/profiles/pece/modules/pece_ai/src/Service/SimilarityService.php

namespace Drupal\pece_ai\Service;

use Drupal\Core\Config\ConfigFactoryInterface;
use Drupal\Core\Entity\EntityInterface;
use Drupal\Core\Entity\EntityTypeManagerInterface;
use GuzzleHttp\ClientInterface;
use GuzzleHttp\Exception\GuzzleException;

class SimilarityService {

  const COLLECTION = 'pece_entities';

  public function __construct(
    private readonly ClientInterface $httpClient,
    private readonly ConfigFactoryInterface $configFactory,
    private readonly EntityTypeManagerInterface $entityTypeManager,
  ) {}

  public function upsert(EntityInterface $entity, array $vector): void {
    $config = $this->configFactory->get('pece_ai.settings');
    $groupIds = [];
    if ($entity->hasField('field_groups') && !$entity->get('field_groups')->isEmpty()) {
      foreach ($entity->get('field_groups') as $item) {
        $groupIds[] = (string) $item->target_id;
      }
    }
    $this->httpClient->put(
      $config->get('qdrant_url') . '/collections/' . self::COLLECTION . '/points',
      [
        'json' => [
          'points' => [[
            'id' => (int) $entity->id(),
            'vector' => $vector,
            'payload' => [
              'entity_type' => $entity->getEntityTypeId(),
              'entity_id' => (int) $entity->id(),
              'bundle' => $entity->bundle(),
              'group_ids' => $groupIds,
            ],
          ]],
        ],
      ]
    );
  }

  public function getVector(EntityInterface $entity): ?array {
    $config = $this->configFactory->get('pece_ai.settings');
    try {
      $response = $this->httpClient->get(
        $config->get('qdrant_url') . '/collections/' . self::COLLECTION . '/points/' . (int) $entity->id(),
        ['query' => ['with_vector' => 'true']]
      );
      $data = json_decode($response->getBody()->getContents(), TRUE);
      return $data['result']['vector'] ?? NULL;
    }
    catch (GuzzleException $e) {
      return NULL;
    }
  }

  public function findSimilar(EntityInterface $entity, int $limit = 5, array $groupIds = []): array {
    $vector = $this->getVector($entity);
    if ($vector === NULL) {
      return [];
    }
    $config = $this->configFactory->get('pece_ai.settings');
    $payload = ['vector' => $vector, 'limit' => $limit + 1, 'with_payload' => TRUE];
    if ($groupIds) {
      $payload['filter'] = [
        'must' => [['key' => 'group_ids', 'match' => ['any' => $groupIds]]],
      ];
    }
    try {
      $response = $this->httpClient->post(
        $config->get('qdrant_url') . '/collections/' . self::COLLECTION . '/points/search',
        ['json' => $payload]
      );
      $data = json_decode($response->getBody()->getContents(), TRUE);
      $results = [];
      foreach ($data['result'] ?? [] as $hit) {
        if ((int) $hit['id'] === (int) $entity->id()) {
          continue;
        }
        $results[] = [
          'entity_type' => $hit['payload']['entity_type'],
          'entity_id' => (int) $hit['payload']['entity_id'],
          'score' => (int) round($hit['score'] * 100),
        ];
        if (count($results) >= $limit) {
          break;
        }
      }
      return $results;
    }
    catch (GuzzleException $e) {
      return [];
    }
  }

}
```

- [ ] **Step 4: Run tests to verify they pass**

```bash
SIMPLETEST_DB='mysql://drupal:drupal@127.0.0.1/drupal' \
vendor/bin/phpunit --testsuite unit \
  web/profiles/pece/modules/pece_ai/tests/src/Unit/SimilarityServiceTest.php -v
```

Expected: 6 tests, 0 failures

- [ ] **Step 5: Commit**

```bash
git add web/profiles/pece/modules/pece_ai/src/Service/SimilarityService.php \
        web/profiles/pece/modules/pece_ai/tests/src/Unit/SimilarityServiceTest.php
git commit -m "feat(pece_ai): add SimilarityService with unit tests"
```

---

## Task 4: EntityEmbedSubscriber

**Files:**
- Create: `web/profiles/pece/modules/pece_ai/src/EventSubscriber/EntityEmbedSubscriber.php`
- Create: `web/profiles/pece/modules/pece_ai/tests/src/Kernel/EntityEmbedSubscriberTest.php`

- [ ] **Step 1: Write the failing Kernel test**

```php
<?php
// web/profiles/pece/modules/pece_ai/tests/src/Kernel/EntityEmbedSubscriberTest.php

namespace Drupal\Tests\pece_ai\Kernel;

use Drupal\KernelTests\KernelTestBase;
use Drupal\node\Entity\Node;
use Drupal\node\Entity\NodeType;

/**
 * Tests EntityEmbedSubscriber queues entities on save.
 *
 * @group pece_ai
 */
class EntityEmbedSubscriberTest extends KernelTestBase {

  protected static $modules = ['system', 'user', 'node', 'field', 'text', 'filter', 'pece_ai'];

  protected function setUp(): void {
    parent::setUp();
    $this->installEntitySchema('user');
    $this->installEntitySchema('node');
    $this->installSchema('system', ['sequences']);
    $this->installConfig(['system', 'user', 'node', 'filter']);

    NodeType::create(['type' => 'pece_essay', 'name' => 'PECE Essay'])->save();
    NodeType::create(['type' => 'page', 'name' => 'Page'])->save();
  }

  public function testEnabledBundleQueuesItemOnInsert(): void {
    $queue = \Drupal::queue('pece_ai_embed');
    $this->assertEquals(0, $queue->numberOfItems());

    Node::create(['type' => 'pece_essay', 'title' => 'Test Essay', 'uid' => 0])->save();

    $this->assertEquals(1, $queue->numberOfItems());
    $item = $queue->claimItem();
    $this->assertEquals('node', $item->data['entity_type']);
  }

  public function testDisabledBundleDoesNotQueue(): void {
    $queue = \Drupal::queue('pece_ai_embed');

    Node::create(['type' => 'page', 'title' => 'A Page', 'uid' => 0])->save();

    $this->assertEquals(0, $queue->numberOfItems());
  }

  public function testUpdateAlsoQueuesItem(): void {
    $node = Node::create(['type' => 'pece_essay', 'title' => 'Original', 'uid' => 0]);
    $node->save();
    $queue = \Drupal::queue('pece_ai_embed');
    // Clear insert item.
    $queue->claimItem();
    $queue->deleteQueue();

    $node->setTitle('Updated')->save();

    $this->assertEquals(1, $queue->numberOfItems());
  }

}
```

- [ ] **Step 2: Run test to verify it fails**

```bash
SIMPLETEST_DB='mysql://drupal:drupal@127.0.0.1/drupal' \
vendor/bin/phpunit --testsuite kernel \
  web/profiles/pece/modules/pece_ai/tests/src/Kernel/EntityEmbedSubscriberTest.php -v
```

Expected: FAIL — `Class "Drupal\pece_ai\EventSubscriber\EntityEmbedSubscriber" not found`

- [ ] **Step 3: Implement `EntityEmbedSubscriber`**

```php
<?php
// web/profiles/pece/modules/pece_ai/src/EventSubscriber/EntityEmbedSubscriber.php

namespace Drupal\pece_ai\EventSubscriber;

use Drupal\Core\Config\ConfigFactoryInterface;
use Drupal\Core\Entity\EntityInterface;
use Drupal\Core\Queue\QueueFactory;

class EntityEmbedSubscriber {

  public function __construct(
    private readonly QueueFactory $queueFactory,
    private readonly ConfigFactoryInterface $configFactory,
  ) {}

  public function onEntitySave(EntityInterface $entity): void {
    $config = $this->configFactory->get('pece_ai.settings');
    $enabledBundles = $config->get('enabled_bundles') ?? [];
    $key = $entity->getEntityTypeId() . ':' . $entity->bundle();
    if (!in_array($key, $enabledBundles, TRUE)) {
      return;
    }
    $queue = $this->queueFactory->get('pece_ai_embed');
    $queue->createItem([
      'entity_type' => $entity->getEntityTypeId(),
      'entity_id' => $entity->id(),
    ]);
  }

}
```

- [ ] **Step 4: Run tests to verify they pass**

```bash
SIMPLETEST_DB='mysql://drupal:drupal@127.0.0.1/drupal' \
vendor/bin/phpunit --testsuite kernel \
  web/profiles/pece/modules/pece_ai/tests/src/Kernel/EntityEmbedSubscriberTest.php -v
```

Expected: 3 tests, 0 failures

- [ ] **Step 5: Commit**

```bash
git add web/profiles/pece/modules/pece_ai/src/EventSubscriber/EntityEmbedSubscriber.php \
        web/profiles/pece/modules/pece_ai/tests/src/Kernel/EntityEmbedSubscriberTest.php
git commit -m "feat(pece_ai): add EntityEmbedSubscriber with kernel tests"
```

---

## Task 5: EmbedEntityWorker

**Files:**
- Create: `web/profiles/pece/modules/pece_ai/src/Plugin/QueueWorker/EmbedEntityWorker.php`
- Create: `web/profiles/pece/modules/pece_ai/tests/src/Kernel/EmbedEntityWorkerTest.php`

- [ ] **Step 1: Write the failing Kernel test**

```php
<?php
// web/profiles/pece/modules/pece_ai/tests/src/Kernel/EmbedEntityWorkerTest.php

namespace Drupal\Tests\pece_ai\Kernel;

use Drupal\KernelTests\KernelTestBase;
use Drupal\node\Entity\Node;
use Drupal\node\Entity\NodeType;
use Drupal\pece_ai\Service\EmbeddingService;
use Drupal\pece_ai\Service\SimilarityService;

/**
 * Tests the EmbedEntityWorker queue processor.
 *
 * @group pece_ai
 */
class EmbedEntityWorkerTest extends KernelTestBase {

  protected static $modules = ['system', 'user', 'node', 'field', 'text', 'filter', 'pece_ai'];

  protected function setUp(): void {
    parent::setUp();
    $this->installEntitySchema('user');
    $this->installEntitySchema('node');
    $this->installSchema('system', ['sequences']);
    $this->installConfig(['system', 'user', 'node', 'filter']);
    NodeType::create(['type' => 'pece_essay', 'name' => 'PECE Essay'])->save();
  }

  public function testProcessItemCallsEmbedAndUpsert(): void {
    $node = Node::create(['type' => 'pece_essay', 'title' => 'Essay Title', 'uid' => 0]);
    $node->save();

    $mockEmbedding = $this->createMock(EmbeddingService::class);
    $mockEmbedding->method('extractText')->willReturn('Essay Title');
    $mockEmbedding->expects($this->once())
      ->method('embed')
      ->with('Essay Title')
      ->willReturn(array_fill(0, 768, 0.1));

    $mockSimilarity = $this->createMock(SimilarityService::class);
    $mockSimilarity->expects($this->once())->method('upsert');

    $this->container->set('pece_ai.embedding_service', $mockEmbedding);
    $this->container->set('pece_ai.similarity_service', $mockSimilarity);

    $worker = $this->container->get('plugin.manager.queue_worker')
      ->createInstance('pece_ai_embed');
    $worker->processItem(['entity_type' => 'node', 'entity_id' => $node->id()]);
  }

  public function testProcessItemSkipsMissingEntity(): void {
    $mockEmbedding = $this->createMock(EmbeddingService::class);
    $mockEmbedding->expects($this->never())->method('embed');

    $mockSimilarity = $this->createMock(SimilarityService::class);
    $mockSimilarity->expects($this->never())->method('upsert');

    $this->container->set('pece_ai.embedding_service', $mockEmbedding);
    $this->container->set('pece_ai.similarity_service', $mockSimilarity);

    $worker = $this->container->get('plugin.manager.queue_worker')
      ->createInstance('pece_ai_embed');
    $worker->processItem(['entity_type' => 'node', 'entity_id' => 99999]);
  }

  public function testProcessItemSkipsEntityWithNoText(): void {
    $node = Node::create(['type' => 'pece_essay', 'title' => '', 'uid' => 0]);
    $node->save();

    $mockEmbedding = $this->createMock(EmbeddingService::class);
    $mockEmbedding->method('extractText')->willReturn('');
    $mockEmbedding->expects($this->never())->method('embed');

    $mockSimilarity = $this->createMock(SimilarityService::class);
    $mockSimilarity->expects($this->never())->method('upsert');

    $this->container->set('pece_ai.embedding_service', $mockEmbedding);
    $this->container->set('pece_ai.similarity_service', $mockSimilarity);

    $worker = $this->container->get('plugin.manager.queue_worker')
      ->createInstance('pece_ai_embed');
    $worker->processItem(['entity_type' => 'node', 'entity_id' => $node->id()]);
  }

}
```

- [ ] **Step 2: Run test to verify it fails**

```bash
SIMPLETEST_DB='mysql://drupal:drupal@127.0.0.1/drupal' \
vendor/bin/phpunit --testsuite kernel \
  web/profiles/pece/modules/pece_ai/tests/src/Kernel/EmbedEntityWorkerTest.php -v
```

Expected: FAIL — `Class "Drupal\pece_ai\Plugin\QueueWorker\EmbedEntityWorker" not found`

- [ ] **Step 3: Implement `EmbedEntityWorker`**

```php
<?php
// web/profiles/pece/modules/pece_ai/src/Plugin/QueueWorker/EmbedEntityWorker.php

namespace Drupal\pece_ai\Plugin\QueueWorker;

use Drupal\Core\Entity\EntityTypeManagerInterface;
use Drupal\Core\Plugin\ContainerFactoryPluginInterface;
use Drupal\Core\Queue\QueueWorkerBase;
use Drupal\pece_ai\Service\EmbeddingService;
use Drupal\pece_ai\Service\SimilarityService;
use Symfony\Component\DependencyInjection\ContainerInterface;

/**
 * @QueueWorker(
 *   id = "pece_ai_embed",
 *   title = @Translation("Embed entity for semantic search"),
 *   cron = {"time" = 30}
 * )
 */
class EmbedEntityWorker extends QueueWorkerBase implements ContainerFactoryPluginInterface {

  public function __construct(
    array $configuration,
    $plugin_id,
    $plugin_definition,
    private readonly EntityTypeManagerInterface $entityTypeManager,
    private readonly EmbeddingService $embeddingService,
    private readonly SimilarityService $similarityService,
  ) {
    parent::__construct($configuration, $plugin_id, $plugin_definition);
  }

  public static function create(ContainerInterface $container, array $configuration, $plugin_id, $plugin_definition): static {
    return new static(
      $configuration, $plugin_id, $plugin_definition,
      $container->get('entity_type.manager'),
      $container->get('pece_ai.embedding_service'),
      $container->get('pece_ai.similarity_service'),
    );
  }

  public function processItem($data): void {
    $entity = $this->entityTypeManager
      ->getStorage($data['entity_type'])
      ->load($data['entity_id']);
    if (!$entity) {
      return;
    }
    $text = $this->embeddingService->extractText($entity);
    if (!$text) {
      return;
    }
    $vector = $this->embeddingService->embed($text);
    $this->similarityService->upsert($entity, $vector);
  }

}
```

- [ ] **Step 4: Run tests to verify they pass**

```bash
SIMPLETEST_DB='mysql://drupal:drupal@127.0.0.1/drupal' \
vendor/bin/phpunit --testsuite kernel \
  web/profiles/pece/modules/pece_ai/tests/src/Kernel/EmbedEntityWorkerTest.php -v
```

Expected: 3 tests, 0 failures

- [ ] **Step 5: Commit**

```bash
git add web/profiles/pece/modules/pece_ai/src/Plugin/QueueWorker/EmbedEntityWorker.php \
        web/profiles/pece/modules/pece_ai/tests/src/Kernel/EmbedEntityWorkerTest.php
git commit -m "feat(pece_ai): add EmbedEntityWorker queue plugin with kernel tests"
```

---

## Task 6: RelatedContentBlock

**Files:**
- Create: `web/profiles/pece/modules/pece_ai/src/Plugin/Block/RelatedContentBlock.php`
- Create: `web/profiles/pece/modules/pece_ai/tests/src/Kernel/RelatedContentBlockTest.php`

- [ ] **Step 1: Write the failing Kernel test**

```php
<?php
// web/profiles/pece/modules/pece_ai/tests/src/Kernel/RelatedContentBlockTest.php

namespace Drupal\Tests\pece_ai\Kernel;

use Drupal\KernelTests\KernelTestBase;
use Drupal\node\Entity\Node;
use Drupal\node\Entity\NodeType;
use Drupal\pece_ai\Service\SimilarityService;

/**
 * Tests the RelatedContentBlock.
 *
 * @group pece_ai
 */
class RelatedContentBlockTest extends KernelTestBase {

  protected static $modules = [
    'system', 'user', 'node', 'field', 'text', 'filter',
    'block', 'pece_ai',
  ];

  protected function setUp(): void {
    parent::setUp();
    $this->installEntitySchema('user');
    $this->installEntitySchema('node');
    $this->installSchema('system', ['sequences']);
    $this->installConfig(['system', 'user', 'node', 'filter']);
    NodeType::create(['type' => 'pece_essay', 'name' => 'PECE Essay'])->save();
  }

  public function testBlockRendersResultsFromSimilarityService(): void {
    $related = Node::create(['type' => 'pece_essay', 'title' => 'Related Essay', 'uid' => 0]);
    $related->save();
    $subject = Node::create(['type' => 'pece_essay', 'title' => 'Subject', 'uid' => 0]);
    $subject->save();

    $mockSimilarity = $this->createMock(SimilarityService::class);
    $mockSimilarity->method('getVector')->willReturn(array_fill(0, 768, 0.1));
    $mockSimilarity->method('findSimilar')->willReturn([
      ['entity_type' => 'node', 'entity_id' => $related->id(), 'score' => 92],
    ]);
    $this->container->set('pece_ai.similarity_service', $mockSimilarity);

    // Set up a fake route match providing the subject node.
    $routeMatch = $this->createMock(\Drupal\Core\Routing\RouteMatchInterface::class);
    $routeMatch->method('getParameter')->with('node')->willReturn($subject);
    $this->container->set('current_route_match', $routeMatch);

    $block = $this->container->get('plugin.manager.block')
      ->createInstance('pece_ai_related_content', []);
    $build = $block->build();

    $this->assertEquals('pece_ai_related_content', $build['#theme']);
    $this->assertCount(1, $build['#items']);
    $this->assertEquals(92, $build['#items'][0]['score']);
  }

  public function testBlockRendersPendingStateWhenVectorAbsent(): void {
    $subject = Node::create(['type' => 'pece_essay', 'title' => 'Subject', 'uid' => 0]);
    $subject->save();

    $mockSimilarity = $this->createMock(SimilarityService::class);
    $mockSimilarity->method('getVector')->willReturn(NULL);
    $mockSimilarity->method('findSimilar')->willReturn([]);
    $this->container->set('pece_ai.similarity_service', $mockSimilarity);

    $routeMatch = $this->createMock(\Drupal\Core\Routing\RouteMatchInterface::class);
    $routeMatch->method('getParameter')->with('node')->willReturn($subject);
    $this->container->set('current_route_match', $routeMatch);

    $block = $this->container->get('plugin.manager.block')
      ->createInstance('pece_ai_related_content', []);
    $build = $block->build();

    $this->assertStringContainsString('being indexed', (string) ($build['#markup'] ?? ''));
  }

  public function testBlockReturnsEmptyArrayWithoutNode(): void {
    $routeMatch = $this->createMock(\Drupal\Core\Routing\RouteMatchInterface::class);
    $routeMatch->method('getParameter')->with('node')->willReturn(NULL);
    $this->container->set('current_route_match', $routeMatch);

    $block = $this->container->get('plugin.manager.block')
      ->createInstance('pece_ai_related_content', []);
    $build = $block->build();

    $this->assertEmpty($build);
  }

}
```

- [ ] **Step 2: Run test to verify it fails**

```bash
SIMPLETEST_DB='mysql://drupal:drupal@127.0.0.1/drupal' \
vendor/bin/phpunit --testsuite kernel \
  web/profiles/pece/modules/pece_ai/tests/src/Kernel/RelatedContentBlockTest.php -v
```

Expected: FAIL — `Class "Drupal\pece_ai\Plugin\Block\RelatedContentBlock" not found`

- [ ] **Step 3: Implement `RelatedContentBlock`**

```php
<?php
// web/profiles/pece/modules/pece_ai/src/Plugin/Block/RelatedContentBlock.php

namespace Drupal\pece_ai\Plugin\Block;

use Drupal\Core\Block\BlockBase;
use Drupal\Core\Entity\EntityTypeManagerInterface;
use Drupal\Core\Plugin\ContainerFactoryPluginInterface;
use Drupal\Core\Routing\RouteMatchInterface;
use Drupal\pece_ai\Service\SimilarityService;
use Symfony\Component\DependencyInjection\ContainerInterface;
use Symfony\Component\HttpFoundation\RequestStack;

/**
 * @Block(
 *   id = "pece_ai_related_content",
 *   admin_label = @Translation("Related Content (AI)"),
 *   category = @Translation("PECE")
 * )
 */
class RelatedContentBlock extends BlockBase implements ContainerFactoryPluginInterface {

  public function __construct(
    array $configuration,
    $plugin_id,
    $plugin_definition,
    private readonly RouteMatchInterface $routeMatch,
    private readonly SimilarityService $similarityService,
    private readonly EntityTypeManagerInterface $entityTypeManager,
    private readonly RequestStack $requestStack,
  ) {
    parent::__construct($configuration, $plugin_id, $plugin_definition);
  }

  public static function create(ContainerInterface $container, array $configuration, $plugin_id, $plugin_definition): static {
    return new static(
      $configuration, $plugin_id, $plugin_definition,
      $container->get('current_route_match'),
      $container->get('pece_ai.similarity_service'),
      $container->get('entity_type.manager'),
      $container->get('request_stack'),
    );
  }

  public function build(): array {
    $node = $this->routeMatch->getParameter('node');
    if (!$node) {
      return [];
    }

    $isGlobal = $this->requestStack->getCurrentRequest()?->query->get('ai_scope') === 'global';
    $groupIds = [];
    if (!$isGlobal && $node->hasField('field_groups') && !$node->get('field_groups')->isEmpty()) {
      foreach ($node->get('field_groups') as $item) {
        $groupIds[] = (string) $item->target_id;
      }
    }

    $results = $this->similarityService->findSimilar($node, 5, $groupIds);

    if (empty($results) && $this->similarityService->getVector($node) === NULL) {
      return [
        '#markup' => $this->t('Related content is being indexed…'),
        '#cache' => ['max-age' => 60],
      ];
    }

    $items = [];
    foreach ($results as $result) {
      $entity = $this->entityTypeManager
        ->getStorage($result['entity_type'])
        ->load($result['entity_id']);
      if ($entity) {
        $items[] = ['entity' => $entity, 'score' => $result['score']];
      }
    }

    $request = $this->requestStack->getCurrentRequest();
    $toggleUrl = $request ? $request->getPathInfo() . ($isGlobal ? '' : '?ai_scope=global') : '';
    $scopeLabel = $isGlobal ? $this->t('Platform-wide') : (
      $groupIds ? $this->t('Within group') : $this->t('Platform-wide')
    );

    return [
      '#theme' => 'pece_ai_related_content',
      '#items' => $items,
      '#scope_label' => $scopeLabel,
      '#toggle_url' => $isGlobal ? $request?->getPathInfo() : $toggleUrl,
      '#cache' => [
        'tags' => $node->getCacheTags(),
        'contexts' => ['url.query_args:ai_scope'],
      ],
    ];
  }

}
```

- [ ] **Step 4: Run tests to verify they pass**

```bash
SIMPLETEST_DB='mysql://drupal:drupal@127.0.0.1/drupal' \
vendor/bin/phpunit --testsuite kernel \
  web/profiles/pece/modules/pece_ai/tests/src/Kernel/RelatedContentBlockTest.php -v
```

Expected: 3 tests, 0 failures

- [ ] **Step 5: Commit**

```bash
git add web/profiles/pece/modules/pece_ai/src/Plugin/Block/RelatedContentBlock.php \
        web/profiles/pece/modules/pece_ai/tests/src/Kernel/RelatedContentBlockTest.php
git commit -m "feat(pece_ai): add RelatedContentBlock with kernel tests"
```

---

## Task 7: Twig Template

**Files:**
- Create: `web/profiles/pece/modules/pece_ai/templates/pece-ai-related-content.html.twig`

- [ ] **Step 1: Create the Twig template**

```twig
{#
  pece-ai-related-content.html.twig
  Variables:
    items: list of {entity, score}
    scope_label: string — e.g. "Within group"
    toggle_url: string — URL to switch scope
#}
<div class="panel pece-ai-related-content">
  <div class="panel-heading is-flex is-justify-content-space-between is-align-items-center">
    <span>{{ 'Related Content'|t }}</span>
    {% if toggle_url %}
      <a href="{{ toggle_url }}" class="is-size-7 has-text-link">
        {% if scope_label == 'Platform-wide' %}
          {{ 'Within group'|t }}
        {% else %}
          {{ 'Platform-wide'|t }} ↗
        {% endif %}
      </a>
    {% endif %}
  </div>

  {% if scope_label %}
    <p class="panel-block is-size-7 has-text-grey">{{ scope_label }}</p>
  {% endif %}

  {% for item in items %}
    <a class="panel-block" href="{{ path('entity.node.canonical', {node: item.entity.id()}) }}">
      <span class="panel-icon">
        <i class="fas fa-circle is-size-7" aria-hidden="true"></i>
      </span>
      <span class="is-flex-grow-1">
        {{ item.entity.label() }}
        <span class="tag is-light is-pulled-right">{{ item.score }}%</span>
      </span>
    </a>
  {% else %}
    <div class="panel-block has-text-grey">
      {{ 'No related content found.'|t }}
    </div>
  {% endfor %}
</div>
```

- [ ] **Step 2: Verify `hook_theme` is already in `pece_ai.module`**

Open `web/profiles/pece/modules/pece_ai/pece_ai.module`. Confirm `pece_ai_theme()` returns:

```php
'pece_ai_related_content' => [
  'variables' => ['items' => [], 'scope_label' => NULL, 'toggle_url' => NULL],
],
```

If not present, add it now.

- [ ] **Step 3: Commit**

```bash
git add web/profiles/pece/modules/pece_ai/templates/pece-ai-related-content.html.twig
git commit -m "feat(pece_ai): add Bulma-based sidebar template"
```

---

## Task 8: Drush Commands

**Files:**
- Create: `web/profiles/pece/modules/pece_ai/src/Commands/PeceAiCommands.php`

Two commands:
- `pece-ai:setup` — creates the Qdrant collection (run once after deploy)
- `pece-ai:backfill` — queues all existing enabled-bundle entities for embedding

- [ ] **Step 1: Implement `PeceAiCommands`**

```php
<?php
// web/profiles/pece/modules/pece_ai/src/Commands/PeceAiCommands.php

namespace Drupal\pece_ai\Commands;

use Drupal\Core\Config\ConfigFactoryInterface;
use Drupal\Core\Entity\EntityTypeManagerInterface;
use Drupal\Core\Queue\QueueFactory;
use Drupal\pece_ai\Service\EmbeddingService;
use Drupal\pece_ai\Service\SimilarityService;
use Drush\Commands\DrushCommands;
use GuzzleHttp\ClientInterface;

class PeceAiCommands extends DrushCommands {

  public function __construct(
    private readonly EntityTypeManagerInterface $entityTypeManager,
    private readonly QueueFactory $queueFactory,
    private readonly EmbeddingService $embeddingService,
    private readonly SimilarityService $similarityService,
    private readonly ConfigFactoryInterface $configFactory,
  ) {
    parent::__construct();
  }

  /**
   * Create the Qdrant collection for PECE entities. Run once after deploy.
   *
   * @command pece-ai:setup
   * @aliases pece-ai-setup
   */
  public function setup(): void {
    $config = $this->configFactory->get('pece_ai.settings');
    $qdrantUrl = $config->get('qdrant_url');

    /** @var ClientInterface $httpClient */
    $httpClient = \Drupal::service('http_client');

    try {
      $httpClient->put($qdrantUrl . '/collections/' . SimilarityService::COLLECTION, [
        'json' => [
          'vectors' => ['size' => 768, 'distance' => 'Cosine'],
          'payload_schema' => [
            'entity_type' => ['data_type' => 'keyword'],
            'entity_id' => ['data_type' => 'integer'],
            'bundle' => ['data_type' => 'keyword'],
            'group_ids' => ['data_type' => 'keyword'],
          ],
        ],
      ]);
      $this->output()->writeln('<info>Qdrant collection created successfully.</info>');
    }
    catch (\Exception $e) {
      $this->output()->writeln('<error>Failed: ' . $e->getMessage() . '</error>');
    }
  }

  /**
   * Queue all existing enabled-bundle entities for embedding.
   *
   * @command pece-ai:backfill
   * @aliases pece-ai-backfill
   */
  public function backfill(): void {
    $config = $this->configFactory->get('pece_ai.settings');
    $enabledBundles = $config->get('enabled_bundles') ?? [];
    $queue = $this->queueFactory->get('pece_ai_embed');
    $count = 0;

    foreach ($enabledBundles as $key) {
      [$entityType, $bundle] = explode(':', $key, 2);
      $storage = $this->entityTypeManager->getStorage($entityType);
      $ids = $storage->getQuery()
        ->condition($storage->getEntityType()->getKey('bundle'), $bundle)
        ->accessCheck(FALSE)
        ->execute();

      foreach ($ids as $id) {
        $queue->createItem(['entity_type' => $entityType, 'entity_id' => $id]);
        $count++;
      }
    }

    $this->output()->writeln("<info>Queued {$count} entities for embedding.</info>");
    $this->output()->writeln('<info>Run `drush queue:run pece_ai_embed` to process.</info>');
  }

}
```

- [ ] **Step 2: Verify the service is registered in `pece_ai.services.yml`**

Confirm `pece_ai.commands` is in `pece_ai.services.yml` with tag `drush.command` (added in Task 1, Step 2). No changes needed if it was done correctly.

- [ ] **Step 3: Commit**

```bash
git add web/profiles/pece/modules/pece_ai/src/Commands/PeceAiCommands.php
git commit -m "feat(pece_ai): add drush pece-ai:setup and pece-ai:backfill commands"
```

---

## Task 9: Full Test Suite Run + Smoke Test

- [ ] **Step 1: Run all pece_ai tests**

```bash
SIMPLETEST_DB='mysql://drupal:drupal@127.0.0.1/drupal' \
SIMPLETEST_BASE_URL='http://localhost' \
vendor/bin/phpunit --testsuite unit,kernel \
  web/profiles/pece/modules/pece_ai/tests/ -v
```

Expected: 19 tests, 0 failures, 0 errors

- [ ] **Step 2: Enable the module and run setup (DDEV required)**

```bash
ddev drush en pece_ai -y
ddev drush pece-ai:setup
```

Expected output: `Qdrant collection created successfully.`

- [ ] **Step 3: Run backfill**

```bash
ddev drush pece-ai:backfill
ddev drush queue:run pece_ai_embed
```

Expected output: `Queued N entities for embedding.` followed by the queue draining with no errors.

- [ ] **Step 4: Place the block via Drupal admin**

1. Go to `/admin/structure/block`
2. Click "Place block" in the sidebar region
3. Find "Related Content (AI)" under PECE category
4. Enable for all content types → Save
5. Visit any artifact or essay page — confirm the "Related content is being indexed…" message appears until the queue worker runs, then switches to results

- [ ] **Step 5: Commit**

```bash
git add web/profiles/pece/modules/pece_ai/
git commit -m "feat(pece_ai): complete semantic sidebar MVP — all tests passing"
```

---

## Deployment Checklist

When deploying to a server for the first time:

1. Add Qdrant and Ollama to the production Docker Compose stack (same config as DDEV)
2. `drush en pece_ai -y`
3. `drush pece-ai:setup` — creates the Qdrant collection
4. `drush pece-ai:backfill` — queues existing content
5. `drush queue:run pece_ai_embed` — or let cron process the queue over time
6. Place the "Related Content (AI)" block in the sidebar region via admin UI
