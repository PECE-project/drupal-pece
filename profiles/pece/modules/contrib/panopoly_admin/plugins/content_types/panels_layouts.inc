<?php

/**
 * @file
 * A panel plugin to provide administrative information about the site's pages and layouts
 */

$plugin = array(
  'title' => t('Panels Layouts'),
  'description' => t('This is list of the panels layouts your modules and themes provide.'),
  'content_types' => array('panels_layouts'),
  'category' => t('Admin'),
  'required context' => new ctools_context_required(t('Panopoly Admin'), 'string'),
  'single' => TRUE,
);

/**
  * Put the output for you pages type in the blocks pages.
  */
function panopoly_admin_panels_layouts_content_type_render($subtype, $conf, $panel_args, $context) {

  // Find all the Panels layouts
  $layout_options = array();
  $panels_page_allowed_layouts = unserialize(variable_get('panels_page_allowed_layouts', serialize('')));
  foreach (panels_get_layouts() as $layout_option) {
    if (empty($layout_option['builder']) || $layout_option['builder'] == FALSE) {

      // Determine the type of panels layout
      if ($layout_option['module'] == 'panels') {
        if (!in_array($layout_option['theme'], array('panels_flexible', 'layout_responsive'))) {
          $layout_type = t('Default (Panels)');
        } 
        else if ($layout_option['theme'] == 'panels_flexible') {
          $layout_type = t('Custom (Flexible)');
        }
        else if ($layout_option['theme'] == 'layout_responsive') {
          $layout_type = t('Custom (Responsive)');
        }
      }
      else if ($layout_option['category'] == 'Radix') {
        $layout_type = t('Default (Radix)');
      }
      else if ($layout_option['category'] == 'Panopoly') {
        // These layouts are deprecated in favor of Radix. So skip them!
        continue;
      }
      else {
        $layout_type = 'Custom (Code)';
      }

      $layout_name = $layout_option['name'];
      $layout_status = (!empty($panels_page_allowed_layouts->allowed_layout_settings[$layout_name])) ? _panopoly_admin_general_layout_get_status($layout_name, 'enable') : _panopoly_admin_general_layout_get_status($layout_name, 'disable');
      $layout_options[$layout_option['title'] . '::' . $layout_option['category']] = array(
        'data' => array(
          theme('image', array('path' => $layout_option['path'] . '/' . $layout_option['icon'])),
          $layout_option['title'],
          $layout_option['category'],
          $layout_type,
          $layout_status,
        ),
      );
    }
  }

  // Create the Output
  $pane = new stdClass();
  ksort($layout_options);
  if (!empty($layout_options)) {
    $header = array(array('data' => '', 'style' => 'width: 30px'), t('Title'), t('Category'), t('Type'), t('Status'));
    $pane->content = theme('table', array('header' => $header, 'rows' => $layout_options, 'attributes' => array('class' => array('panels-layouts'))));
  }
  else {
    $pane->content = t('There are no Panels layouts available');
  }
  return $pane;
}
