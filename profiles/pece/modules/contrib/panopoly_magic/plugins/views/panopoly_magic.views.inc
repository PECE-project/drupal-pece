<?php
/**
 * @file
 * Contains Views plugin definitions for the panel pane display.
 */

/**
 * Implements hook_views_plugins_alter().
 */
function panopoly_magic_views_plugins_alter(&$plugins) {
  if (isset($plugins['display']['panel_pane'])) {
    $plugins['display']['panel_pane']['handler'] = 'panopoly_magic_plugin_display_panel_pane';
  }
}
