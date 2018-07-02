<?php

/**
 * @file
 * 
 * Theme functions used in total control panel panes.
 *
 */

/*
 * Theme function for site overview.
 */
function theme_total_control_overview($variables) {
  $content = $variables['content'];
  $users = $variables['users'];

  $output  = '<div class="total-control-site-overview">';
  $output .= '<strong>' . t('Content') . '</strong>';
  $output .= theme('item_list', array('items' => $content));
  $output .= '<strong>' . t('Users') . '</strong>';
  $output .= theme('item_list', array('items' => $users));
  $output .= '</div>';

  return $output;
}

/*
 * Theme function for content overview.
 */
function theme_total_control_overview_content($variables) {
  $overview = $variables['overview'];

  $output  = '<div class="total-control-content-overview">';
  $output .= theme('item_list', array('items' => $overview));
  $output .= '</div>';

  return $output;
}

/*
 * Theme function for user overview.
 */
function theme_total_control_overview_user($variables) {
  $overview = $variables['overview'];

  $output  = '<div class="total-control-user-overview">';
  $output .= theme('item_list', array('items' => $overview));
  $output .= '</div>';

  return $output;
}

/*
 * Theme function for create content pane.
 */
function theme_total_control_create($variables) {
  $create = $variables['create'];

  $output  = '<div class="total-control-create">';
  $output .= theme('item_list', array('items' => $create));
  $output .= '</div>';

  return $output;
}

/*
 * Theme function for panel pages.
 */
function theme_total_control_admin_table($variables) {
  $header = $variables['header'];
  $rows = $variables['rows'];
  $link = $variables['link'];

  $output  = '<div class="total-control-panel-panes">';
  $output .= theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('class' => array('panels-manage'))));
  $output .= '  <div class="admin-page">' . $link . '</div>';
  $output .= '</div>';

  return $output;
}

