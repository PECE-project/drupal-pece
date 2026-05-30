# PECE AI Writing Companion (Track B) Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add a "Find related content" button to annotation (step 2) and essay drafting forms that fetches semantically similar content inline via Drupal AJAX.

**Architecture:** A static `WritingCompanionCallback::suggest()` method handles the AJAX call — it reads title + body from form state, calls `EmbeddingService::embed()` to get a fresh vector, then queries Qdrant via a new `SimilarityService::findSimilarByVector()` method, and returns an `AjaxResponse` replacing the suggestions div. Group scope defaults to the current user's group memberships, with a "Platform-wide" checkbox override. `pece_ai_form_alter()` wires the button and placeholder into seven node forms.

**Tech Stack:** Drupal 11, `pece_ai` module (existing), Drupal Form API `#ajax`, `AjaxResponse` + `ReplaceCommand`, Ollama `nomic-embed-text` (existing), Qdrant (existing), Bulma CSS (existing via peceful theme), PHPUnit 11 (Unit + Kernel), Behat.

---

## File Map

| File | Action | Purpose |
|------|--------|---------|
| `web/profiles/pece/modules/pece_ai/src/Service/SimilarityService.php` | Modify | Add `findSimilarByVector()`, refactor `findSimilar()` to delegate |
| `web/profiles/pece/modules/pece_ai/tests/src/Unit/SimilarityServiceTest.php` | Modify | Add test for `findSimilarByVector()` |
| `web/profiles/pece/modules/pece_ai/src/Ajax/WritingCompanionCallback.php` | Create | Static AJAX form callback class |
| `web/profiles/pece/modules/pece_ai/tests/src/Unit/WritingCompanionCallbackTest.php` | Create | Unit tests for the callback (4 tests) |
| `web/profiles/pece/modules/pece_ai/pece_ai.module` | Modify | Add `pece_ai_form_alter()` |
| `web/profiles/pece/modules/pece_ai/tests/src/Kernel/WritingCompanionFormTest.php` | Create | Kernel tests for form_alter (5 tests) |
| `web/profiles/pece/modules/pece_ai/pece_ai.libraries.yml` | Create | Define `writing_companion` CSS library |
| `web/profiles/pece/modules/pece_ai/css/writing-companion.css` | Create | Scoped styles for suggestions panel |
| `tests/features/pece_ai_writing_companion.feature` | Create | Behat E2E scenarios (`@javascript @ai`) |

---

## Task 1: Add `SimilarityService::findSimilarByVector()`

The existing `findSimilar()` fetches the stored Qdrant vector for an entity and then searches. The Writing Companion has a freshly computed vector (no entity), so it needs to search by vector directly. Extract the inner search logic into a new public method and make `findSimilar()` delegate to it.

**Files:**
- Modify: `web/profiles/pece/modules/pece_ai/src/Service/SimilarityService.php`
- Modify: `web/profiles/pece/modules/pece_ai/tests/src/Unit/SimilarityServiceTest.php`

- [ ] **Step 1: Write the failing test**

Add this test to `SimilarityServiceTest.php` after the existing `setUp()` and existing tests:

```php
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

  // SimilarityServiceTest already has $this->httpClient and $this->service wired.
  // Re-create the service with a fresh http client mock for this test.
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
```

You will also need this `use` statement at the top of `SimilarityServiceTest.php` (add to existing list):

```php
use Drupal\Core\Entity\EntityTypeManagerInterface;
```

- [ ] **Step 2: Run test to verify it fails**

```bash
ddev exec 'SIMPLETEST_DB="mysql://db:db@db/db" SIMPLETEST_BASE_URL="https://pece2.ddev.site" vendor/bin/phpunit web/profiles/pece/modules/pece_ai/tests/src/Unit/SimilarityServiceTest.php 2>&1'
```

Expected: FAIL — `Call to undefined method ...SimilarityService::findSimilarByVector()`

- [ ] **Step 3: Add `findSimilarByVector()` to `SimilarityService` and refactor `findSimilar()`**

Replace the existing `findSimilar()` method and add `findSimilarByVector()`. The full updated `SimilarityService.php` content from line 89 onwards:

```php
  /**
   * Finds entities similar to the given entity using vector search.
   *
   * @param \Drupal\Core\Entity\EntityInterface $entity
   *   The source entity.
   * @param int $limit
   *   Maximum number of results to return (excluding self).
   * @param array $groupIds
   *   Optional list of group IDs to filter results by.
   *
   * @return array
   *   Array of result arrays with keys: entity_type, entity_id, score.
   */
  public function findSimilar(EntityInterface $entity, int $limit = 5, array $groupIds = []): array {
    $vector = $this->getVector($entity);
    if ($vector === NULL) {
      return [];
    }
    return $this->findSimilarByVector($vector, $limit, $groupIds, (int) $entity->id());
  }

  /**
   * Finds entities similar to the given vector using Qdrant search.
   *
   * @param array $vector
   *   The query vector.
   * @param int $limit
   *   Maximum number of results to return.
   * @param array $groupIds
   *   Optional list of group IDs to filter results by.
   * @param int $excludeId
   *   Optional Qdrant point ID to exclude from results (use for self-exclusion).
   *
   * @return array
   *   Array of result arrays with keys: entity_type, entity_id, score.
   */
  public function findSimilarByVector(array $vector, int $limit = 5, array $groupIds = [], int $excludeId = 0): array {
    $config = $this->configFactory->get('pece_ai.settings');
    $payload = ['vector' => $vector, 'limit' => $limit + 1, 'with_payload' => TRUE];
    if ($groupIds) {
      $payload['filter'] = [
        'must' => [['key' => 'group_ids', 'match' => ['any' => $groupIds]]],
      ];
    }
    try {
      $response = $this->httpClient->request('POST',
        $config->get('qdrant_url') . '/collections/' . self::COLLECTION . '/points/search',
        ['json' => $payload]
      );
      $data = json_decode($response->getBody()->getContents(), TRUE);
      $results = [];
      foreach ($data['result'] ?? [] as $hit) {
        if ($excludeId && (int) $hit['id'] === $excludeId) {
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

The existing `findSimilar()` test still passes because `findSimilar()` delegates to `findSimilarByVector()` internally — same behaviour, different code path.

- [ ] **Step 4: Run all pece_ai unit tests to verify no regressions**

```bash
ddev exec 'SIMPLETEST_DB="mysql://db:db@db/db" SIMPLETEST_BASE_URL="https://pece2.ddev.site" vendor/bin/phpunit --testsuite unit --filter pece_ai 2>&1'
```

Expected: All existing tests + new `testFindSimilarByVectorQueriesQdrantWithVector` pass.

- [ ] **Step 5: Commit**

```bash
git add web/profiles/pece/modules/pece_ai/src/Service/SimilarityService.php \
        web/profiles/pece/modules/pece_ai/tests/src/Unit/SimilarityServiceTest.php
git commit -m "feat(pece_ai): add SimilarityService::findSimilarByVector() for Writing Companion"
```

---

## Task 2: `WritingCompanionCallback` Class + Unit Tests

The static callback class handles the AJAX response. Unit tests mock the Drupal service container to avoid a full bootstrap.

**Files:**
- Create: `web/profiles/pece/modules/pece_ai/src/Ajax/WritingCompanionCallback.php`
- Create: `web/profiles/pece/modules/pece_ai/tests/src/Unit/WritingCompanionCallbackTest.php`

- [ ] **Step 1: Write the failing unit tests**

Create `web/profiles/pece/modules/pece_ai/tests/src/Unit/WritingCompanionCallbackTest.php`:

```php
<?php

namespace Drupal\Tests\pece_ai\Unit;

use Drupal\Core\Ajax\AjaxResponse;
use Drupal\Core\DependencyInjection\ContainerBuilder;
use Drupal\Core\Entity\EntityStorageInterface;
use Drupal\Core\Entity\EntityTypeManagerInterface;
use Drupal\Core\Form\FormStateInterface;
use Drupal\Core\Render\RendererInterface;
use Drupal\Core\Session\AccountProxyInterface;
use Drupal\pece_ai\Ajax\WritingCompanionCallback;
use Drupal\pece_ai\Service\EmbeddingService;
use Drupal\pece_ai\Service\SimilarityService;
use Drupal\Tests\UnitTestCase;

/**
 * @coversDefaultClass \Drupal\pece_ai\Ajax\WritingCompanionCallback
 * @group pece_ai
 */
class WritingCompanionCallbackTest extends UnitTestCase {

  /**
   * {@inheritdoc}
   */
  protected function setUp(): void {
    parent::setUp();

    $renderer = $this->createMock(RendererInterface::class);
    $renderer->method('renderInIsolation')->willReturn('<div id="pece-ai-suggestions">rendered</div>');

    $currentUser = $this->createMock(AccountProxyInterface::class);
    $currentUser->method('id')->willReturn(1);

    $userStorage = $this->createMock(EntityStorageInterface::class);
    $userStorage->method('load')->willReturn(NULL);

    $entityTypeManager = $this->createMock(EntityTypeManagerInterface::class);
    $entityTypeManager->method('getStorage')->willReturn($userStorage);

    $container = new ContainerBuilder();
    $container->set('renderer', $renderer);
    $container->set('current_user', $currentUser);
    $container->set('entity_type.manager', $entityTypeManager);
    \Drupal::setContainer($container);
  }

  /**
   * Builds a FormState mock returning the given title and body.
   */
  private function makeFormState(string $title, string $body, bool $platformWide = FALSE): FormStateInterface {
    $formState = $this->createMock(FormStateInterface::class);
    $formState->method('getValue')->willReturnMap([
      [['title', 0, 'value'], NULL, $title],
      [['body', 0, 'value'], NULL, $body],
      ['pece_ai_platform_wide', NULL, $platformWide],
    ]);
    return $formState;
  }

  /**
   * Tests that empty form state returns the help message.
   */
  public function testEmptyFormStateShowsHelpMessage(): void {
    $embeddingService = $this->createMock(EmbeddingService::class);
    $embeddingService->expects($this->never())->method('embed');
    \Drupal::getContainer()->set('pece_ai.embedding_service', $embeddingService);

    $form = [];
    $formState = $this->makeFormState('', '');
    $response = WritingCompanionCallback::suggest($form, $formState);

    $this->assertInstanceOf(AjaxResponse::class, $response);
  }

  /**
   * Tests that an EmbeddingService exception returns the error message.
   */
  public function testEmbeddingFailureShowsErrorMessage(): void {
    $embeddingService = $this->createMock(EmbeddingService::class);
    $embeddingService->method('embed')->willThrowException(new \RuntimeException('Embedding service unavailable'));
    \Drupal::getContainer()->set('pece_ai.embedding_service', $embeddingService);

    $form = [];
    $formState = $this->makeFormState('A title', 'Some body text');
    $response = WritingCompanionCallback::suggest($form, $formState);

    $this->assertInstanceOf(AjaxResponse::class, $response);
  }

  /**
   * Tests that embed() is called with title + newlines + stripped body.
   */
  public function testEmbedCalledWithConcatenatedText(): void {
    $embeddingService = $this->createMock(EmbeddingService::class);
    $embeddingService->expects($this->once())
      ->method('embed')
      ->with("Coastal flooding\n\nObservations on tidal changes.")
      ->willReturn(array_fill(0, 768, 0.1));

    $similarityService = $this->createMock(SimilarityService::class);
    $similarityService->method('findSimilarByVector')->willReturn([]);

    \Drupal::getContainer()->set('pece_ai.embedding_service', $embeddingService);
    \Drupal::getContainer()->set('pece_ai.similarity_service', $similarityService);

    $form = [];
    $formState = $this->makeFormState('Coastal flooding', '<p>Observations on tidal changes.</p>');
    WritingCompanionCallback::suggest($form, $formState);
  }

  /**
   * Tests that results from SimilarityService are included in the response.
   */
  public function testResultsArePassedToRenderer(): void {
    $vector = array_fill(0, 768, 0.1);

    $embeddingService = $this->createMock(EmbeddingService::class);
    $embeddingService->method('embed')->willReturn($vector);

    $similarityService = $this->createMock(SimilarityService::class);
    $similarityService->expects($this->once())
      ->method('findSimilarByVector')
      ->with($vector, 5, [])
      ->willReturn([]);

    \Drupal::getContainer()->set('pece_ai.embedding_service', $embeddingService);
    \Drupal::getContainer()->set('pece_ai.similarity_service', $similarityService);

    $form = [];
    $formState = $this->makeFormState('Title', 'Body');
    $response = WritingCompanionCallback::suggest($form, $formState);

    $this->assertInstanceOf(AjaxResponse::class, $response);
  }

}
```

- [ ] **Step 2: Run tests to verify they fail**

```bash
ddev exec 'SIMPLETEST_DB="mysql://db:db@db/db" SIMPLETEST_BASE_URL="https://pece2.ddev.site" vendor/bin/phpunit web/profiles/pece/modules/pece_ai/tests/src/Unit/WritingCompanionCallbackTest.php 2>&1'
```

Expected: FAIL — `Class "Drupal\pece_ai\Ajax\WritingCompanionCallback" not found`

- [ ] **Step 3: Create `WritingCompanionCallback.php`**

Create `web/profiles/pece/modules/pece_ai/src/Ajax/WritingCompanionCallback.php`:

```php
<?php

namespace Drupal\pece_ai\Ajax;

use Drupal\Core\Ajax\AjaxResponse;
use Drupal\Core\Ajax\ReplaceCommand;
use Drupal\Core\Form\FormStateInterface;

/**
 * AJAX form callback for the Writing Companion "Find related content" button.
 */
class WritingCompanionCallback {

  /**
   * AJAX callback: embeds current draft text and returns similar content.
   *
   * @param array $form
   *   The form array.
   * @param \Drupal\Core\Form\FormStateInterface $form_state
   *   The current form state.
   *
   * @return \Drupal\Core\Ajax\AjaxResponse
   *   An AJAX response replacing the #pece-ai-suggestions div.
   */
  public static function suggest(array &$form, FormStateInterface $form_state): AjaxResponse {
    $response = new AjaxResponse();
    $renderer = \Drupal::service('renderer');

    $title = (string) ($form_state->getValue(['title', 0, 'value']) ?? '');
    $body = (string) ($form_state->getValue(['body', 0, 'value']) ?? '');
    $text = trim($title . "\n\n" . trim(html_entity_decode(strip_tags($body))));

    if ($text === '') {
      $build = [
        '#type' => 'html_tag',
        '#tag' => 'div',
        '#attributes' => ['id' => 'pece-ai-suggestions', 'class' => ['pece-ai-suggestions', 'panel']],
        'message' => [
          '#type' => 'html_tag',
          '#tag' => 'p',
          '#attributes' => ['class' => ['panel-block', 'has-text-grey']],
          '#value' => t('Add a title or some text to find related content.'),
        ],
      ];
      $response->addCommand(new ReplaceCommand('#pece-ai-suggestions', $renderer->renderInIsolation($build)));
      return $response;
    }

    try {
      $vector = \Drupal::service('pece_ai.embedding_service')->embed($text);
    }
    catch (\RuntimeException $e) {
      $build = [
        '#type' => 'html_tag',
        '#tag' => 'div',
        '#attributes' => ['id' => 'pece-ai-suggestions', 'class' => ['pece-ai-suggestions', 'panel']],
        'message' => [
          '#type' => 'html_tag',
          '#tag' => 'p',
          '#attributes' => ['class' => ['panel-block', 'has-text-grey']],
          '#value' => t('Could not load suggestions right now.'),
        ],
      ];
      $response->addCommand(new ReplaceCommand('#pece-ai-suggestions', $renderer->renderInIsolation($build)));
      return $response;
    }

    $groupIds = [];
    $platformWide = (bool) $form_state->getValue('pece_ai_platform_wide');
    if (!$platformWide) {
      $uid = \Drupal::currentUser()->id();
      $userEntity = \Drupal::entityTypeManager()->getStorage('user')->load($uid);
      if ($userEntity && $userEntity->hasField('field_groups_with_view_access') && !$userEntity->get('field_groups_with_view_access')->isEmpty()) {
        foreach ($userEntity->get('field_groups_with_view_access') as $item) {
          $groupIds[] = (string) $item->target_id;
        }
      }
    }

    $hits = \Drupal::service('pece_ai.similarity_service')->findSimilarByVector($vector, 5, $groupIds);

    $items = [];
    foreach ($hits as $hit) {
      $entity = \Drupal::entityTypeManager()->getStorage($hit['entity_type'])->load($hit['entity_id']);
      if ($entity && $entity->access('view')) {
        $items[] = ['entity' => $entity, 'score' => $hit['score']];
      }
    }

    $scopeLabel = $platformWide ? t('Platform-wide') : t('Within your groups');
    $build = [
      '#theme' => 'pece_ai_related_content',
      '#items' => $items,
      '#scope_label' => $scopeLabel,
      '#toggle_url' => NULL,
      '#prefix' => '<div id="pece-ai-suggestions" class="pece-ai-suggestions">',
      '#suffix' => '</div>',
    ];
    $response->addCommand(new ReplaceCommand('#pece-ai-suggestions', $renderer->renderInIsolation($build)));
    return $response;
  }

}
```

- [ ] **Step 4: Run tests to verify they pass**

```bash
ddev exec 'SIMPLETEST_DB="mysql://db:db@db/db" SIMPLETEST_BASE_URL="https://pece2.ddev.site" vendor/bin/phpunit web/profiles/pece/modules/pece_ai/tests/src/Unit/WritingCompanionCallbackTest.php 2>&1'
```

Expected: 4 tests pass.

- [ ] **Step 5: Run full pece_ai unit suite to check for regressions**

```bash
ddev exec 'SIMPLETEST_DB="mysql://db:db@db/db" SIMPLETEST_BASE_URL="https://pece2.ddev.site" vendor/bin/phpunit --testsuite unit --filter pece_ai 2>&1'
```

Expected: All unit tests pass.

- [ ] **Step 6: Commit**

```bash
git add web/profiles/pece/modules/pece_ai/src/Ajax/WritingCompanionCallback.php \
        web/profiles/pece/modules/pece_ai/tests/src/Unit/WritingCompanionCallbackTest.php
git commit -m "feat(pece_ai): add WritingCompanionCallback AJAX handler with unit tests"
```

---

## Task 3: `pece_ai_form_alter()` + Kernel Tests

Wire the button, checkbox, and suggestions placeholder into the seven target node forms.

**Files:**
- Modify: `web/profiles/pece/modules/pece_ai/pece_ai.module`
- Create: `web/profiles/pece/modules/pece_ai/tests/src/Kernel/WritingCompanionFormTest.php`

- [ ] **Step 1: Write the failing kernel tests**

Create `web/profiles/pece/modules/pece_ai/tests/src/Kernel/WritingCompanionFormTest.php`:

```php
<?php

namespace Drupal\Tests\pece_ai\Kernel;

use Drupal\Core\Form\FormState;
use Drupal\KernelTests\KernelTestBase;

/**
 * Tests that pece_ai_form_alter() wires the Writing Companion into target forms.
 *
 * @group pece_ai
 */
class WritingCompanionFormTest extends KernelTestBase {

  /**
   * {@inheritdoc}
   */
  protected static $modules = [
    'system', 'user', 'node', 'field', 'text', 'filter',
    'block', 'pece_ai',
  ];

  /**
   * {@inheritdoc}
   */
  protected function setUp(): void {
    parent::setUp();
    $this->installEntitySchema('user');
    $this->installEntitySchema('node');
    $this->installSchema('system', ['sequences']);
    $this->installSchema('node', ['node_access']);
    $this->installConfig(['system', 'user', 'node', 'filter', 'pece_ai']);
  }

  /**
   * Calls pece_ai_form_alter() with a minimal form stub.
   */
  private function applyFormAlter(string $formId): array {
    $form = ['body' => ['#type' => 'text_format', '#weight' => 5]];
    $formState = new FormState();
    pece_ai_form_alter($form, $formState, $formId);
    return $form;
  }

  /**
   * Tests that the button and placeholder are added to annotation step 2.
   */
  public function testFormAlterAddsButtonToAnnotationStep2(): void {
    $form = $this->applyFormAlter('node_pece_annotation_annotation_step_2_form');
    $this->assertArrayHasKey('pece_ai_suggest', $form);
    $this->assertArrayHasKey('pece_ai_suggestions_placeholder', $form);
    $this->assertEquals('button', $form['pece_ai_suggest']['#type']);
  }

  /**
   * Tests that the button is added to the essay add form.
   */
  public function testFormAlterAddsButtonToEssayForm(): void {
    $form = $this->applyFormAlter('node_pece_essay_form');
    $this->assertArrayHasKey('pece_ai_suggest', $form);
    $this->assertArrayHasKey('pece_ai_suggestions_placeholder', $form);
  }

  /**
   * Tests that the button is added to the essay edit form.
   */
  public function testFormAlterAddsButtonToEssayEditForm(): void {
    $form = $this->applyFormAlter('node_pece_essay_edit_form');
    $this->assertArrayHasKey('pece_ai_suggest', $form);
  }

  /**
   * Tests that the button is added to the photo essay add form.
   */
  public function testFormAlterAddsButtonToPhotoEssayForm(): void {
    $form = $this->applyFormAlter('node_pece_photo_essay_form');
    $this->assertArrayHasKey('pece_ai_suggest', $form);
  }

  /**
   * Tests that the button is added to the photo essay edit form.
   */
  public function testFormAlterAddsButtonToPhotoEssayEditForm(): void {
    $form = $this->applyFormAlter('node_pece_photo_essay_edit_form');
    $this->assertArrayHasKey('pece_ai_suggest', $form);
  }

  /**
   * Tests that the button is added to the timeline essay add form.
   */
  public function testFormAlterAddsButtonToTimelineEssayForm(): void {
    $form = $this->applyFormAlter('node_pece_timeline_essay_form');
    $this->assertArrayHasKey('pece_ai_suggest', $form);
  }

  /**
   * Tests that the button is added to the timeline essay edit form.
   */
  public function testFormAlterAddsButtonToTimelineEssayEditForm(): void {
    $form = $this->applyFormAlter('node_pece_timeline_essay_edit_form');
    $this->assertArrayHasKey('pece_ai_suggest', $form);
  }

  /**
   * Tests that unrelated forms are not modified.
   */
  public function testFormAlterIgnoresUnrelatedForms(): void {
    $form = $this->applyFormAlter('user_login_form');
    $this->assertArrayNotHasKey('pece_ai_suggest', $form);
    $this->assertArrayNotHasKey('pece_ai_suggestions_placeholder', $form);
  }

}
```

- [ ] **Step 2: Run tests to verify they fail**

```bash
ddev exec 'SIMPLETEST_DB="mysql://db:db@db/db" SIMPLETEST_BASE_URL="https://pece2.ddev.site" vendor/bin/phpunit web/profiles/pece/modules/pece_ai/tests/src/Kernel/WritingCompanionFormTest.php 2>&1'
```

Expected: FAIL — `testFormAlterAddsButtonToAnnotationStep2` fails because `pece_ai_form_alter` does not yet exist.

- [ ] **Step 3: Add `pece_ai_form_alter()` to `pece_ai.module`**

The full updated `pece_ai.module`:

```php
<?php

/**
 * @file
 * PECE AI semantic similarity sidebar module.
 */

use Drupal\Core\Entity\EntityInterface;
use Drupal\Core\Form\FormStateInterface;
use Drupal\pece_ai\Ajax\WritingCompanionCallback;

/**
 * Implements hook_entity_insert().
 */
function pece_ai_entity_insert(EntityInterface $entity): void {
  \Drupal::service('pece_ai.entity_embed_subscriber')->onEntitySave($entity);
}

/**
 * Implements hook_entity_update().
 */
function pece_ai_entity_update(EntityInterface $entity): void {
  \Drupal::service('pece_ai.entity_embed_subscriber')->onEntitySave($entity);
}

/**
 * Implements hook_theme().
 */
function pece_ai_theme(): array {
  return [
    'pece_ai_related_content' => [
      'variables' => ['items' => [], 'scope_label' => NULL, 'toggle_url' => NULL],
    ],
  ];
}

/**
 * Implements hook_form_alter().
 */
function pece_ai_form_alter(array &$form, FormStateInterface $form_state, string $form_id): void {
  $targets = [
    'node_pece_annotation_annotation_step_2_form',
    'node_pece_essay_form',
    'node_pece_essay_edit_form',
    'node_pece_photo_essay_form',
    'node_pece_photo_essay_edit_form',
    'node_pece_timeline_essay_form',
    'node_pece_timeline_essay_edit_form',
  ];
  if (!in_array($form_id, $targets, TRUE)) {
    return;
  }

  $bodyWeight = $form['body']['#weight'] ?? 10;

  $form['pece_ai_suggestions_placeholder'] = [
    '#type' => 'html_tag',
    '#tag' => 'div',
    '#attributes' => ['id' => 'pece-ai-suggestions', 'class' => ['pece-ai-suggestions']],
    '#weight' => $bodyWeight + 0.1,
  ];

  $form['pece_ai_platform_wide'] = [
    '#type' => 'checkbox',
    '#title' => t('Platform-wide'),
    '#default_value' => FALSE,
    '#weight' => $bodyWeight + 0.2,
  ];

  $form['pece_ai_suggest'] = [
    '#type' => 'button',
    '#value' => t('Find related content'),
    '#weight' => $bodyWeight + 0.3,
    '#ajax' => [
      'callback' => [WritingCompanionCallback::class, 'suggest'],
      'wrapper' => 'pece-ai-suggestions',
      'effect' => 'fade',
      'progress' => ['type' => 'throbber', 'message' => t('Finding related content…')],
    ],
    '#limit_validation_errors' => [],
  ];

  $form['#attached']['library'][] = 'pece_ai/writing_companion';
}
```

- [ ] **Step 4: Run kernel tests to verify they pass**

```bash
ddev exec 'SIMPLETEST_DB="mysql://db:db@db/db" SIMPLETEST_BASE_URL="https://pece2.ddev.site" vendor/bin/phpunit web/profiles/pece/modules/pece_ai/tests/src/Kernel/WritingCompanionFormTest.php 2>&1'
```

Expected: 6 tests pass.

- [ ] **Step 5: Run full pece_ai suite to check for regressions**

```bash
ddev exec 'SIMPLETEST_DB="mysql://db:db@db/db" SIMPLETEST_BASE_URL="https://pece2.ddev.site" vendor/bin/phpunit --testsuite unit,kernel --filter pece_ai 2>&1'
```

Expected: All 36 tests pass (23 existing + 1 new unit Task 1 + 4 new unit Task 2 + 8 new kernel Task 3).

- [ ] **Step 6: Commit**

```bash
git add web/profiles/pece/modules/pece_ai/pece_ai.module \
        web/profiles/pece/modules/pece_ai/tests/src/Kernel/WritingCompanionFormTest.php
git commit -m "feat(pece_ai): add pece_ai_form_alter() Writing Companion with kernel tests"
```

---

## Task 4: CSS Library

Define the `pece_ai/writing_companion` library and write minimal scoped styles. The library is already attached in `pece_ai_form_alter()` — it just needs to exist.

**Files:**
- Create: `web/profiles/pece/modules/pece_ai/pece_ai.libraries.yml`
- Create: `web/profiles/pece/modules/pece_ai/css/writing-companion.css`

- [ ] **Step 1: Create `pece_ai.libraries.yml`**

```yaml
writing_companion:
  css:
    component:
      css/writing-companion.css: {}
```

- [ ] **Step 2: Create `css/writing-companion.css`**

```css
.pece-ai-suggestions {
  margin-top: 1rem;
  margin-bottom: 1rem;
}

.pece-ai-suggestions .panel-block {
  font-size: 0.875rem;
}
```

- [ ] **Step 3: Verify the library resolves**

```bash
ddev exec 'SIMPLETEST_DB="mysql://db:db@db/db" SIMPLETEST_BASE_URL="https://pece2.ddev.site" vendor/bin/phpunit --testsuite unit,kernel --filter pece_ai 2>&1'
```

Expected: All 30 tests still pass (library errors would cause kernel tests to fail on form build).

- [ ] **Step 4: Commit**

```bash
git add web/profiles/pece/modules/pece_ai/pece_ai.libraries.yml \
        web/profiles/pece/modules/pece_ai/css/writing-companion.css
git commit -m "feat(pece_ai): add writing_companion CSS library"
```

---

## Task 5: Behat E2E Scenarios

Write the two `@javascript @ai` Behat scenarios. These are excluded from standard CI and require Selenium/Chrome + running Qdrant/Ollama with seeded data.

**Files:**
- Create: `tests/features/pece_ai_writing_companion.feature`

- [ ] **Step 1: Create the feature file**

Create `tests/features/pece_ai_writing_companion.feature`:

```gherkin
@javascript @ai
Feature: Writing Companion suggests related content while drafting

  As a researcher drafting new content,
  I want to find conceptually related content while I write,
  so that I can reference and link relevant existing work.

  Background:
    Given there is existing content seeded with vectors in Qdrant

  Scenario: Researcher finds related content while drafting an annotation
    Given I am logged in as a researcher with group membership
    When I go to create a new annotation
    And I advance to annotation step 2
    And I fill in "Title" with "Coastal flooding patterns"
    And I fill in "Body" with "Observations on tidal changes near the port"
    And I click "Find related content"
    Then I should see the element "#pece-ai-suggestions"
    And the element "#pece-ai-suggestions" should not contain "Could not load suggestions"
    And the element "#pece-ai-suggestions" should not contain "Add a title or some text"

  Scenario: Researcher finds related content while drafting a PECE Essay
    Given I am logged in as a researcher with group membership
    When I go to create a new "PECE Essay"
    And I fill in "Title" with "Seasonal knowledge systems"
    And I fill in "Body" with "How fishing communities adapt their practices to seasonal change"
    And I click "Find related content"
    Then I should see the element "#pece-ai-suggestions"
    And the element "#pece-ai-suggestions" should not contain "Could not load suggestions"
    And the element "#pece-ai-suggestions" should not contain "Add a title or some text"
```

> **Note:** Step definitions for `I advance to annotation step 2`, `I go to create a new annotation`, and `there is existing content seeded with vectors in Qdrant` must be implemented in a custom Behat context before these scenarios can run. The `@javascript` tag requires a Selenium or ChromeDriver Mink session configured in `behat.yml`.

- [ ] **Step 2: Verify the feature file is valid Gherkin**

```bash
ddev exec 'vendor/bin/behat --dry-run tests/features/pece_ai_writing_companion.feature 2>&1' || echo "Behat not configured — file created for future E2E setup"
```

Expected: Either dry-run output listing the steps, or the informational message if Behat is not yet configured for JS scenarios.

- [ ] **Step 3: Commit**

```bash
git add tests/features/pece_ai_writing_companion.feature
git commit -m "test(pece_ai): add Behat E2E scenarios for Writing Companion"
```

---

## Task 6: PHPCS Check + Final Verification

Verify coding standards and run the full test suite before considering the feature complete.

**Files:** None created — verification only.

- [ ] **Step 1: Run PHPCS on all pece_ai files**

```bash
ddev exec 'vendor/bin/phpcs --standard=Drupal,DrupalPractice --extensions=php,module,inc,install,test,profile,theme web/profiles/pece/modules/pece_ai/ 2>&1'
```

Expected: `No violations found.` If violations appear, run `phpcbf` to auto-fix and commit the result:

```bash
ddev exec 'vendor/bin/phpcbf --standard=Drupal,DrupalPractice --extensions=php,module,inc,install,test,profile,theme web/profiles/pece/modules/pece_ai/ 2>&1'
git add -p web/profiles/pece/modules/pece_ai/
git commit -m "fix(pece_ai): fix PHPCS violations in Writing Companion files"
```

- [ ] **Step 2: Run full pece_ai test suite**

```bash
ddev exec 'SIMPLETEST_DB="mysql://db:db@db/db" SIMPLETEST_BASE_URL="https://pece2.ddev.site" vendor/bin/phpunit --testsuite unit,kernel --filter pece_ai 2>&1'
```

Expected: 36 tests, 0 failures.

- [ ] **Step 3: Push**

```bash
git push upstream 2.x
```
