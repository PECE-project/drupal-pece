<?php

/**
 * @file
 * Definition of the 'rounded_corners' panel style.
 */

// Plugin definition
$plugin = array(
  'title' => t('Panopoly Test: Style with settings'),
  'description' => t('Pane style to ensure Panopoly Magic does not disrupt style forms.'),
  'render region' => 'panopoly_test_settings_style_style_render_region',
  'render pane' => 'panopoly_test_settings_style_render_pane',
  'settings form' => 'panopoly_test_settings_style_style_settings_form',
  'pane settings form' => 'panopoly_test_settings_style_style_settings_form',
);

/**
 * Render callback.
 *
 * @ingroup themeable
 */
function theme_panopoly_test_settings_style_style_render_region($vars) {
  $output = '';
  $output .= implode('<div class="panel-separator"></div>', $vars['panes']);
  return $output;
}

/**
 * Render callback.
 *
 * @ingroup themeable
 */
function theme_panopoly_test_settings_style_render_pane($vars) {
  $content = $vars['content'];
  $settings = $vars['settings'];

  $output = '';

  // Add a simple header we can detect from the tests.
  if (empty($settings['add_text']) || $settings['add_text'] == 'awesome') {
    $output .= '<p>' . t('This widget is patentedly awesome!') . '</p>';
  }
  elseif ($settings['add_text'] == 'terrible') {
    $output .= '<p>' . t("Avert your eyes! It's not even worth to cast your gaze upon this widget.") . '</p>';
  }

  // Add the pane content.
  $output .= render($content->content);

  return $output;
}

/**
 * Settings form callback.
 */
function panopoly_test_settings_style_style_settings_form($settings) {
  $form['add_text'] = array(
    '#type' => 'select',
    '#title' => t('Quality of this widget'),
    '#options' => array(
      'awesome' => t('Awesome'),
      'terrible' => t('Terrible'),
    ),
    '#default_value' => !empty($settings['add_text']) ? $settings['add_text'] : 'awesome',
  );

  return $form;
}
