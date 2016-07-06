<?php
/**
 * @file
 * Routines to extract links from a Drupal entities as candidates for caching.
 *
 * Much of this module is based on code from https://drupal.org/project/linkchecker
 */

/**
 * Returns the language code of the given entity.
 *
 * Backward compatibility layer to ensure that installations running an older
 * version of core (<7.15) where entity_language() is not available do not break.
 *
 * @param string $entity_type
 *   An entity type.
 * @param object $entity
 *   An entity object.
 *
 * @return string
 *   The entity language code.
 */
function _amber_entity_language($entity_type, $entity) {
  $langcode = NULL;
  if (function_exists('entity_language')) {
    $langcode = entity_language($entity_type, $entity);
  }
  elseif (!empty($entity->language)) {
    $langcode = $entity->language;
  }
  return $langcode;
}

/**
 * Return all the values of one-dimensional and multidimensional arrays.
 *
 * @return array
 *   Returns all the values from the input array and indexes the array numerically.
 */
function _amber_array_values_recursive(array $array) {
  $array_values = array();

  foreach ($array as $value) {
    if (is_array($value)) {
      $array_values = array_merge($array_values, _amber_array_values_recursive($value));
    }
    else {
      $array_values[] = $value;
    }
  }

  return $array_values;
}

/**
 * Filter links that are candidates for caching to exclude local links, or links to URLs on the blacklist
 * @param $links array of links to check
 * @param $blacklist array of hostnames to exclude
 */
function _amber_filter_links($links, $blacklist) {
  if (!$blacklist) {
    return $links;
  }
  $result = array('cache' => array(), 'excluded' => array());
  foreach ($links as $link) {
    $host = parse_url($link, PHP_URL_HOST);
    if ($host) {
      $exclude = FALSE;
      foreach ($blacklist as $blacklistitem) {
        $blacklistitem = trim($blacklistitem);
        $blacklistitem = preg_replace("/https?:\\/\\//i", "", $blacklistitem);
        if (strcasecmp($host, $blacklistitem) === 0) {
          $exclude = TRUE;
        }
      }
      if ($exclude) {
        $result['excluded'][] = $link;
      }
      else {
          $result['cache'][] = $link;
      }
    }
  }
  return $result;
}

/**
 * Filter links that are candidates for caching to exclude local links, or links to URLs on the blacklist
 * @param $links array of links to check
 * @param $blacklist array of regular expressions to exclude
 */
function _amber_regexp_filter_links($links, $blacklist) {
  if (!$blacklist) {
    return $links;
  }
  $result = array('cache' => array(), 'excluded' => array());
  foreach ($links as $link) {
    $exclude = FALSE;
    foreach ($blacklist as $blacklistitem) {
      $blacklistitem = trim($blacklistitem);
      if ($blacklistitem) {
        $blacklistitem = preg_replace("/https?:\\/\\//i", "", $blacklistitem);
        $blacklistitem = str_replace("@", "\@", $blacklistitem);
        $blacklistitem = '@' . $blacklistitem . '@';
        $cleanedlink = preg_replace("/https?:\\/\\//i", "", $link);
        if (preg_match($blacklistitem, $cleanedlink)) {
          $exclude = TRUE;
        }
      }
    }
    if ($exclude) {
      $result['excluded'][] = $link;
    }
    else {
        $result['cache'][] = $link;
    }
  }
  return $result;
}


/**
 * Extract links from the provided text
 *
 * @param $text string to search for links
 * @return array of links
 */
function _amber_extract_links($text) {
  // TODO: Don't duplicate regexp with that defined in _amber_filter_process. Define it only once
  $re = '/href=["\'](http[^\v()<>{}\[\]"\']+)[\'"]/i';
  $count = preg_match_all($re, $text, $matches);
  return $count ? $matches[1] : array();
}

/**
 * Parse the urls from entity fields.
 *
 * This function parse all fields from the entity and returns an array of
 * filtered field items.
 *
 * @param string $entity_type
 *   The type of entity; e.g., 'node', 'comment'.
 * @param string $bundle_name
 *   The name of the bundle aka node type, e.g., 'article', 'page'.
 * @param object $entity
 *   The entity to parse, a $node or a $comment object.
 *
 * @return array
 *   Array of field items with filters applied.
 */
function _amber_parse_fields($entity_type, $bundle_name, $entity) {
  $text_items = array();
  // Collect the fields from this entity_type and bundle.
  foreach (field_info_instances($entity_type, $bundle_name) as $field_name => $instance) {
    $field = field_info_field($field_name);
    if (!isset($entity->$field['field_name'])) {
      continue;
    }
    $entity_field = $entity->$field['field_name'];
    switch ($field['type']) {
      // Core fields.
      case 'text_with_summary':
      case 'text_long':
      case 'text':
        foreach ($entity_field as $language) {
          foreach ($language as $item) {
            $format = isset($item['format']) ? $item['format'] : NULL;
            // TODO: Don't run the Amber filter as part of check_markup
            $text_items[] = check_markup($item['value'], $format, _amber_entity_language($entity_type, $entity), TRUE);
            if ($field['type'] == 'text_with_summary') {
              $text_items[] = check_markup($item['summary'], $format, _amber_entity_language($entity_type, $entity), TRUE);
            }
          }
        }
        break;

      // Link module field, http://drupal.org/project/link.
      case 'link_field':
        foreach ($entity_field as $language) {
          foreach ($language as $item) {
            $options = drupal_parse_url($item['url']);
            $title = !empty($item['title']) ? $item['title'] : '';
            // TODO: Handle link items that don't specify a protocol (e.g., "http://")
            $text_items[] = l($title, $options['path'], $options);
            $text_items[] = check_markup($title, NULL, _amber_entity_language($entity_type, $entity), TRUE);
          }
        }
        break;
    }
  }
  return $text_items;
}


/**
 * Extracts links from a node.
 *
 * @param object $node
 *   The fully populated node object.
 *
 * @return array
 *   An array whose keys are fully qualified and unique URLs found in the node
 *   (as returned by _amber_extract_links())
 */
function _amber_extract_node_links($node) {

  $filter = new stdClass();
  $filter->settings['filter_url_length'] = 72;

  // Create array of node fields to scan.
  $text_items_by_field = array();
  $text_items_by_field = array_merge($text_items_by_field, _amber_parse_fields('node', $node->type, $node, TRUE));
  $text_items_by_field['title'][] = _filter_url($node->title, $filter);
  $text_items = _amber_array_values_recursive($text_items_by_field);
  $links = _amber_extract_links(implode(' ', $text_items));
  global $base_url;
  $links = _amber_regexp_filter_links($links, explode(PHP_EOL, variable_get("amber_excluded_sites", parse_url($base_url, PHP_URL_HOST))));
  return $links;
}
