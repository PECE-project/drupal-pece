<?php

/**
 * @file
 * An example key provider just for tests.
 *
 * @ingroup encrypt
 */

$plugin = array(
  'title' => t('Test Key Provider'),
  'description' => t('This is just a test key provider.'),
  'encrypt callback' => 'encrypt_test_key_providers_test',
);

/**
 * Callback for encryption.
 *
 * Just return the text since we're not concerned with testing encryption.
 */
function encrypt_test_key_providers_test($settings) {
  return 'Some long key';
}
