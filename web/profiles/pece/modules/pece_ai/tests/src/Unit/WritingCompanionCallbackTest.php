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
    $renderer->method('renderInIsolation')
      ->willReturn('<div id="pece-ai-suggestions">rendered</div>');

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
  private function makeFormState(
    string $title,
    string $body,
    bool $platformWide = FALSE,
  ): FormStateInterface {
    $formState = $this->createMock(FormStateInterface::class);
    $formState->method('getValue')->willReturnMap([
      [['title', 0, 'value'], NULL, $title],
      [['body', 0, 'value'], NULL, $body],
      ['pece_ai_platform_wide', NULL, $platformWide],
    ]);
    return $formState;
  }

  /**
   * Tests that empty form state returns an AJAX response without calling embed.
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
   * Tests that an EmbeddingService exception returns an error AJAX response.
   */
  public function testEmbeddingFailureShowsErrorMessage(): void {
    $embeddingService = $this->createMock(EmbeddingService::class);
    $embeddingService->method('embed')
      ->willThrowException(
        new \RuntimeException('Embedding service unavailable')
      );
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
    \Drupal::getContainer()
      ->set('pece_ai.similarity_service', $similarityService);

    $form = [];
    $formState = $this->makeFormState(
      'Coastal flooding',
      '<p>Observations on tidal changes.</p>'
    );
    WritingCompanionCallback::suggest($form, $formState);
  }

  /**
   * Tests that findSimilarByVector is called and response is AjaxResponse.
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
    \Drupal::getContainer()
      ->set('pece_ai.similarity_service', $similarityService);

    $form = [];
    $formState = $this->makeFormState('Title', 'Body');
    $response = WritingCompanionCallback::suggest($form, $formState);

    $this->assertInstanceOf(AjaxResponse::class, $response);
  }

}
