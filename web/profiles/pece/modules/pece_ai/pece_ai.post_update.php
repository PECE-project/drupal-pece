<?php

/**
 * @file
 * Post update functions for the pece_ai module.
 */

/**
 * Creates the pece_ai_activity table and adds activity config on existing sites.
 */
function pece_ai_post_update_add_activity_table(): void {
  $schema = \Drupal::database()->schema();
  if (!$schema->tableExists('pece_ai_activity')) {
    $table_spec = [
      'description' => 'Tracks researcher activity for personalized discovery feed.',
      'fields' => [
        'id' => [
          'type' => 'serial',
          'unsigned' => TRUE,
          'not null' => TRUE,
        ],
        'uid' => [
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
        ],
        'entity_type' => [
          'type' => 'varchar',
          'length' => 32,
          'not null' => TRUE,
        ],
        'entity_id' => [
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
        ],
        'weight' => [
          'type' => 'int',
          'size' => 'tiny',
          'unsigned' => TRUE,
          'not null' => TRUE,
          'default' => 1,
        ],
        'timestamp' => [
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => TRUE,
        ],
      ],
      'primary key' => ['id'],
      'indexes' => [
        'uid_timestamp' => ['uid', 'timestamp'],
        'uid_entity' => ['uid', 'entity_type', 'entity_id'],
      ],
    ];
    $schema->createTable('pece_ai_activity', $table_spec);
  }
}

/**
 * Places the DiscoveryFeedBlock on the PECE dashboard.
 */
function pece_ai_post_update_place_discovery_feed_block(): void {
  $config = \Drupal::configFactory()->getEditable('dashboards.dashboard.pece');
  $data = $config->getRawData();
  if (empty($data)) {
    return;
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
