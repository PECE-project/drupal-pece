<?php
/**
 * @file
 * PECE theme field preprocess implementations.
 */

/**
 * Implements theme_preprocess_field().
 */
function pece_scholarly_lite_preprocess_field(&$variables) {
  if ($variables['element']['#field_name'] == 'og_group_ref') {
    dsm($variables);
  }
}
