<?php

/**
 * @file
 * Builds placeholder replacement tokens for node-related data.
 */

/**
 * Implements hook_token_info().
 */
function publication_date_token_info_alter(&$data) {
  $data['tokens']['node']['published'] = array(
    'name' => t("Date published"),
    'description' => t("The date the node was published."),
    'type' => 'date',
  );
}

/**
 * Implements hook_tokens().
 */
function publication_date_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $url_options = array('absolute' => TRUE);
  if (isset($options['language'])) {
    $url_options['language'] = $options['language'];
    $language_code = $options['language']->language;
  }
  else {
    $language_code = NULL;
  }
  $sanitize = !empty($options['sanitize']);

  $replacements = array();

  if ($type == 'node' && !empty($data['node'])) {
    $node = $data['node'];

    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'published':
          $replacements[$original] = format_date($node->published_at, 'medium', '', NULL, $language_code);
          break;
      }
    }

    if ($published_tokens = token_find_with_prefix($tokens, 'published')) {
      $replacements += token_generate('date', $published_tokens, array('date' => $node->published_at), $options);
    }
  }

  return $replacements;
}
