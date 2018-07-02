<?php

/**
 * @file
 *
 * "Welcome" panel content type. Displays a summary of content statistics 
 * including: number pieces of each type of content, number of comments, 
 * number of blocked comments (spam) and configuration links.
 *
 */

$plugin = array(
  'single' => TRUE,
  'title' => t('Welcome'),
  'no title override' => TRUE,
  'icon' => 'cog.png',
  'description' => t('Intro to Total Control'),
  'category' => t('Dashboard'),
);

/**
 * 'Admin title' callback for the content type.
 */
function total_control_welcome_content_type_admin_title($subtype = NULL, $conf = NULL, $context = NULL) {
  return t('Welcome');
}

/**
 * 'Admin info' callback for the content type.
 */
function total_control_welcome_content_type_admin_info($subtype = NULL, $conf = NULL, $context = NULL) {
  $block = new stdClass();
  $block->title = t('Intro to Total Control');

  return $block;
}

/**
 * Run-time rendering of the body of the block.
 */
function total_control_welcome_content_type_render($subtype, $conf, $panel_args, &$context) {
  // Build the content.
  $content =  '<div class="total-control-site-overview">';
  $content .= '  <p>' . t('Welcome to your administrative dashboard.  !panel 
    to add more content panes here, or configure those provided by default. 
    Views content panes can be created for you automatically according to your 
    !settings.  Make this dashboard the perfect hub for all your administrative 
    needs.', array(
     '!panel' => l(t('Edit this panel'), 'admin/structure/pages/nojs/operation/page-dashboard/handlers/page_dashboard_panel_context/content'), 
     '!settings' => l(t('Total Control Settings'), 'admin/config/administration/control'))) . '</p>';
  $content .= '</div>';

  $block = new stdClass();
  $block->module = t('total_control');
  $block->title = t('Take Total Control.');
  $block->content = $content;

  return $block;
}
