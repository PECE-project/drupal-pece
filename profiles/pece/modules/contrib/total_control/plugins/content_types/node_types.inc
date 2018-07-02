<?php

/**
 * @file
 *
 * "Create content" panels content type. It shows users links to
 * create new content of all types for which they have permissions,
 * and users with "administer content types" permission an optional
 * "configure" link as well.
 *
 */
 
$plugin = array(
  'single' => TRUE,
  'title' => t('Admin - Content types'),
  'defaults' => array('types' => NULL),
  'icon' => 'cog.png',
  'description' => t('Provides links to administer content types.'),
  'category' => t('Dashboard'),
  'edit text' => t('Configure'),
);

/**
 * 'Admin title' callback for the content type.
 */
function total_control_node_types_content_type_admin_title($subtype = NULL, $conf = NULL, $context = NULL) {
  return t('Administer Content types');
}

/**
 * 'Admin info' callback for the content type.
 */
function total_control_node_types_content_type_admin_info($subtype = NULL, $conf = NULL, $context = NULL) {
  $block = new stdClass();
  $block->title = t('Provides links to administer content types.');

  return $block;
}

/**
 * Run-time rendering of the body of the pane.
 */
function total_control_node_types_content_type_render($subtype, $conf, $panel_args, &$context) {
  $types = node_type_get_types();
  $access = user_access('administer content types');
  $options = array('query' => array('destination' => 'admin/dashboard'));
  $header = array(
    array('data' => t('Content type')), 
    array('data' => t('Operations'), 'colspan' => 3)
  );
  $rows = array();

  foreach ($types as $type => $object) {
    // Config data says to include the type.
    if ((!array_key_exists($type, $conf['types'])) || (isset($conf['types']) && $conf['types'][$type]) == $type) {  
      // Check access, then add a link to create content.
      if ($access) {
        $type_url_str = str_replace('_', '-', $object->type);  
        $rows[] = array(
          'data' => array(
            t($object->name),
            l(t('Configure'), 'admin/structure/types/manage/' . $type_url_str, $options),
            l(t('Manage fields'), 'admin/structure/types/manage/' . $type_url_str . '/fields', $options),
            l(t('Manage display'), 'admin/structure/types/manage/' . $type_url_str . '/display', $options)
          ),
        );
      }
    }
  }

  if (empty($rows)) {
    $rows[] = array(
      array(
        'data' => t('There are no content types to display.'),
        'colspan' => 4,
      )
    );
  }

  $link = '';
  if (user_access('administer content types')) {
    $link = l(t('Content type administration'), 'admin/structure/types');
  }

  $block = new stdClass();
  $block->module = t('total_control');
  $block->title = t('Administer Content types');
  $block->content =  theme('total_control_admin_table', array('header' => $header, 'rows' => $rows, 'link' => $link));

  return $block;
}

/**
 * 'Edit form' callback for the content type.
 */
function total_control_node_types_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  $types = node_type_get_types();
  $type_options = array();
  $type_defaults = array();

  if (isset($conf['types'])) {
    $type_defaults = $conf['types'];
  }

  foreach ($types as $type => $object) {
    $type_options[$type] = $object->name;
    if (!array_key_exists($type, $type_defaults)) {
      $type_defaults[$type] = $type;
    }
  }

  $form['types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Include Create links for Content Types'),
    '#options' => $type_options,
    '#default_value' => $type_defaults,
  );

  return $form;
}

/**
 * Submit handler for for create settings.
 */
function total_control_node_types_content_type_edit_form_submit($form, &$form_state) {
  // Copy everything from our defaults.
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}

