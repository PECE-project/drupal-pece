<?php

/**
 * @file
 * Post update functions for the pece_ai module.
 */

/**
 * Creates the pece_ai_activity table on existing sites.
 */
function pece_ai_post_update_add_activity_table(): void {
  $schema = \Drupal::database()->schema();
  if (!$schema->tableExists('pece_ai_activity')) {
    $module_schema = pece_ai_schema();
    $schema->createTable('pece_ai_activity', $module_schema['pece_ai_activity']);
  }
}

/**
 * Places the DiscoveryFeedBlock on the PECE dashboard.
 */
function pece_ai_post_update_place_discovery_feed_block(): void {
  $config = \Drupal::configFactory()->getEditable('dashboards.dashboard.pece');
  $data = $config->getRawData();
  if (empty($data) || empty($data['sections'][0])) {
    return;
  }
  // Check if already placed (e.g. via config import).
  foreach ($data['sections'][0]['components'] ?? [] as $component) {
    if (($component['configuration']['id'] ?? '') === 'pece_ai_discovery_feed') {
      return;
    }
  }
  $uuid = \Drupal::service('uuid')->generate();
  $data['sections'][0]['components'][$uuid] = [
    'uuid' => $uuid,
    'region' => 'two_e',
    'configuration' => [
      'id' => 'pece_ai_discovery_feed',
      'label' => 'Suggested for You',
      'label_display' => '1',
      'provider' => 'pece_ai',
      'context_mapping' => [],
    ],
    'weight' => 0,
    'additional' => [],
  ];
  $config->setData($data)->save();
}
