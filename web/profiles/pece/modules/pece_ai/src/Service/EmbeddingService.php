<?php

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
    try {
      $response = $this->httpClient->request('POST', $config->get('embedding_url') . '/api/embeddings', [
        'json' => [
          'model' => $config->get('embedding_model'),
          'prompt' => $text,
        ],
      ]);
      $data = json_decode($response->getBody()->getContents(), TRUE);
      if (!is_array($data) || !isset($data['embedding'])) {
        throw new \RuntimeException('Invalid embedding response: missing or malformed embedding field.');
      }
      return $data['embedding'];
    }
    catch (\GuzzleHttp\Exception\GuzzleException $e) {
      throw new \RuntimeException('Embedding service unavailable: ' . $e->getMessage(), 0, $e);
    }
    catch (\RuntimeException $e) {
      throw $e;
    }
    catch (\Exception $e) {
      throw new \RuntimeException('Embedding service unavailable: ' . $e->getMessage(), 0, $e);
    }
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
