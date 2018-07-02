<?php

/**
 * @file
 *
 * "Webform" content type. It shows users with permissions all of the 
 * webform submissions and provides links directly manage them.
 *
 */

$plugin = array(
  'single' => TRUE,
  'title' => t('Admin - Webforms'),
  'defaults' => array(),
  'icon' => 'cog.png',
  'description' => t('Provides links to administer Webforms.'),
  'category' => t('Dashboard'),
  'edit text' => t('Configure'),
);

/**
 * 'Admin title' callback for the content type.
 */
function total_control_webform_content_type_admin_title($subtype = NULL, $conf = NULL, $context = NULL) {
  return t('Administer Webforms');
}

/**
 * 'Admin info' callback for the content type.
 */
function total_control_webform_content_type_admin_info($subtype = NULL, $conf = NULL, $context = NULL) {
  $block = new stdClass();
  $block->title = t('Provides links to administer Webforms.');

  return $block;
}

/**
 * Run-time rendering of the body of the block.
 */
function total_control_webform_content_type_render($subtype, $conf, $args, &$context) {
  // Check for nodequeue module. 
  if (module_exists('webform')) {
    // Get webform types.
    $webform_types = webform_variable_get('webform_node_types');

    $nodes = array();
    if ($webform_types) {
      $nodes = db_select('node', 'n')
        ->fields('n')
        ->condition('n.type', $webform_types, 'IN')
        ->execute()
        ->fetchAllAssoc('nid');
    }

    $options = array('query' => array('destination' => 'admin/dashboard'));
    $header = array(
      array('data' => t('Title'),),
      array('data' => t('Submissions')),
      array('data' => t('Operations'), 'colspan' => 2),
    );

    $rows = array();
    foreach ($nodes as $node) {
      // Count the submissions.
      $query = db_select('webform_submissions', 'ws')
        ->condition('ws.nid', $node->nid)
        ->condition('ws.is_draft', 0);
      $count = $query->countQuery()->execute()->fetchField();
      $rows[] = array(
        array('class' => 'webform-title', 'data' => l($node->title, 'node/' . $node->nid)),
        array('class' => 'webform-no-subs', 'data' => $count == 0 ? t('No submissions') : $count),
        array('data' => l(t('Configure'), 'node/' . $node->nid . '/webform', $options)),
        array('data' => node_access('update', $node) ? l(t('View results'), 'node/' . $node->nid . '/webform-results/table', $options) : ''),
      );
    }
    
    $empty_text = t('There are no Webforms to display.');
    $link = '';
    if (user_access('access all webform results')) {
      $link = l(t('Webform administration'), 'admin/content/webform');
    }
  }
  else {
    $header = array();
    $empty_text = t('Dashboard administration for the <a href="!href">webform</a> module.', array('!href' => 'http://drupal.org/project/webform'));
    $link = '';
  }

  if (empty($rows)) {
    $rows[] = array(
      array(
        'data' => $empty_text,
        'colspan' => 5,
      )
    );
  }

  $block = new stdClass();
  $block->module = t('total_control');
  $block->title = t('Administer Webforms');
  $block->content = $block->content = theme('total_control_admin_table', array('header' => $header, 'rows' => $rows, 'link' => $link));

  return $block;

}

/**
 * 'Edit form' callback for the content type.
 */
function total_control_webform_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
  // TODO add content type selection for weform admin page

  return $form;
}

/**
 * 'Edit form' submit callback for the content type.
 */
function total_control_webform_content_type_edit_form_submit($form, &$form_state) {
  foreach (array('item1', 'item2') as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}
