<?php

/**
 * @file
 * Helper functions for PECE Analytics module.
 */

/**
 * Fetch all structured analytics terms.
 *
 * @return
 *   array term id.
 */
function pece_analytics_fetch_structured_analytics() {
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'taxonomy_term')
    ->entityCondition('bundle', array('pece_structured_analytics'))
    ->propertyOrderBy('weight');

  $result = $query->execute();
  $tids = array_keys($result['taxonomy_term']);

  return $tids;
}
