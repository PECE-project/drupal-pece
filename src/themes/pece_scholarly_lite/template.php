<?php
/**
 * @file
 * Theme functions
 */

include_once(dirname(__FILE__) . '/includes/preprocess.inc');

// @TODO: This overwrite should be in a PECE base theme.
function pece_scholarly_lite_item_list($variables) {
  $items = $variables['items'];
  $title = $variables['title'];
  $type = $variables['type'];
  $attributes = $variables['attributes'];

  // Only output the list container and title, if there are any list items.
  // Check to see whether the block title exists before adding a header.
  // Empty headers are not semantic and present accessibility challenges.
  $output = '<div class="item-list">';
  if (isset($title) && $title !== '') {
    $output .= '<h3>' . $title . '</h3>';
  }

  if (!empty($items)) {
    $output .= "<$type" . drupal_attributes($attributes) . '>';
    $num_items = count($items);
    $i = 0;
    foreach ($items as $item) {
      $attributes = array();
      $children = array();
      $data = '';
      $i++;
      if (is_array($item)) {
        foreach ($item as $key => $value) {
          if ($key == 'data' && is_array($value)) {
            $data = drupal_render($value);
          }
          elseif ($key == 'data') {
            $data = $value;
          }
          elseif ($key == 'children') {
            $children = $value;
          }
          else {
            $attributes[$key] = $value;
          }
        }
      }
      else {
        $data = $item;
      }
      if (count($children) > 0) {
        // Render nested list.
        $data .= theme_item_list(array('items' => $children, 'title' => NULL, 'type' => $type, 'attributes' => $attributes));
      }
      if ($i == 1) {
        $attributes['class'][] = 'first';
      }
      if ($i == $num_items) {
        $attributes['class'][] = 'last';
      }
      $output .= '<li' . drupal_attributes($attributes) . '>' . $data . "</li>\n";
    }
    $output .= "</$type>";
  }
  $output .= '</div>';
  return $output;
}

/**
 * Implements hook_css_alter().
 */
function pece_scholarly_lite_css_alter(&$css) {
  $exclude = array(
    drupal_get_path('module', 'panopoly_admin') . '/panopoly-admin.css',
  );

  $css = array_diff_key($css, drupal_map_assoc($exclude));
}

/**
 * Override or insert variables into the html template.
 */
function pece_scholarly_lite_preprocess_html(&$variables) {
  pece_scholarly_lite_add_css_overrides();
  pece_scholarly_lite_add_extra_styles();
}

/**
* Implements hook_preprocess_maintenance_page().
*/
function pece_scholarly_lite_preprocess_maintenance_page(&$variables) {
  pece_scholarly_lite_add_css_overrides();
}

/**
 * Adds styles overrides into the html template.
 */
function pece_scholarly_lite_add_css_overrides() {
  $custom_color_scheme = theme_get_setting('custom_color_scheme');
  $public_path = variable_get('file_public_path', conf_path() . '/files');
  if ($custom_color_scheme && is_dir('public://pece_scholarly_lite')) {
    $style_overrides = $public_path . '/pece_scholarly_lite/scheme_override.css';
    drupal_add_css($style_overrides, array(
      'group' => CSS_THEME,
      'type' => 'file',
      'weight' => 9999,
    ));
  }
}

/**
 * Adds PECE extra css based on color scheme.
 */
function pece_scholarly_lite_add_extra_styles() {
  $color_scheme = theme_get_setting('color_scheme');
  if (empty($color_scheme)) {
    return;
  }
  if ($color_scheme == 'gray-purple') {
    // Apply PECE's default overrides on gray-purple scheme.
    drupal_add_css(drupal_get_path('theme', 'pece_scholarly_lite') . '/assets/css/pece_header_override.css', array('group' => CSS_THEME, 'type' => 'file'));
  } else {
    // Adds PECE extra styles over base theme schemes.
    drupal_add_css(drupal_get_path('theme', 'pece_scholarly_lite') . '/assets/overrides/scheme_overrides.' . $color_scheme . '.css', array('group' => CSS_THEME, 'type' => 'file'));
  }
}