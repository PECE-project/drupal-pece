<?php
/**
 * @file
 * PECE theme implementations.
 */

/**
 * Implements theme_panels_default_style_render_region().
 */
function pece_scholarly_lite_panels_default_style_render_region(&$variables) {
  return implode($variables['panes']);
}
