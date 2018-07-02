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
  'title' => t('Create content'),
  'defaults' => array('types' => NULL),
  'icon' => 'cog.png',
  'description' => t('Provides links to create new content.'),
  'category' => t('Dashboard'),
  'edit text' => t('Configure'),
);

/**
 * 'Admin title' callback for the content type.
 */
function total_control_create_content_type_admin_title($subtype = NULL, $conf = NULL, $context = NULL) {
  return t('Content creation links');
}

/**
 * 'Admin info' callback for the content type.
 */
function total_control_create_content_type_admin_info($subtype = NULL, $conf = NULL, $context = NULL) {
  $block = new stdClass();
  $block->title = t('Provides links to create new content.');

  return $block;
}

/**
 * Run-time rendering of the body of the pane.
 */
function total_control_create_content_type_render($subtype, $conf, $panel_args, &$context) {
  $block = new stdClass();
  $block->module = t('total_control');
  $block->title = t('Create content');

  $types = node_type_get_types();
  $create = array();  

  foreach ($types as $type => $object) {
    // Check against pane config for type.
    if ((!array_key_exists($type, $conf['types'])) || (isset($conf['types']) && $conf['types'][$type])) {  
      // Check access, then add a link to create content.
      if (node_access('create', $type)) { 
        $type_url_str = str_replace('_', '-', $object->type);  
        $create[] = l(t('Add new  ' . $object->name), 'node/add/' . $type_url_str);
      }
    }
  }

  $block->content =  theme('total_control_create', array('create' => $create));

  return $block;
}

/**
 * 'Edit form' callback for the content type.
 */
function total_control_create_content_type_edit_form($form, &$form_state) {
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
function total_control_create_content_type_edit_form_submit($form, &$form_state) {
  // Copy everything from our defaults.
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}

