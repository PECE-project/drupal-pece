<?php

/**
 * @file
 *
 * "Taxonomy" content type. It shows users with permissions statistics
 * and links to manage terms in vocabularies on the site.
 *
 */

$plugin = array(
  'single' => TRUE,
  'title' => t('Admin - Taxonomy'),
  'defaults' => array('vids' => NULL),
  'icon' => 'cog.png',
  'description' => t('Provides links to administer taxonomy.'),
  'category' => t('Dashboard'),
  'edit text' => t('Configure'),
);

/**
 * 'Admin title' callback for the content type.
 */
function total_control_taxonomy_content_type_admin_title($subtype = NULL, $conf = NULL, $context = NULL) {
  return t('Administer Taxonomy');
}

/**
 * 'Admin info' callback for the content type.
 */
function total_control_taxonomy_content_type_admin_info($subtype = NULL, $conf = NULL, $context = NULL) {
  $block = new stdClass();
  $block->title = t('Provides links to administer taxonomy.');

  return $block;
}

/**
 * Run-time rendering of the body of the block.
 */
function total_control_taxonomy_content_type_render($subtype, $conf, $panel_args, &$context) {
  if (!module_exists('taxonomy')) {
    return;
  }
  $block = new stdClass();
  $block->module = t('total_control');
  $block->title = t('Administer Taxonomy');

  $vids = (isset($conf['vids']))? $conf['vids']: array();

  $vocabs = taxonomy_get_vocabularies();
  $options = array('query' => array('destination' => 'admin/dashboard'));
  $header = array(
    array('data' => t('Vocabulary')), 
    array('data' => t('Operations'), 'colspan' => 3));
  $rows = array();

  if (!empty($vocabs)) {  
    foreach ($vocabs as $vocab) {
      if ((in_array($vocab->vid, $vids)) || !array_key_exists('vids', $conf)) {  
        $term_count = db_query("SELECT count(*) FROM {taxonomy_term_data} WHERE vid = :vid", array(':vid' => $vocab->vid))->fetchField();
        if (user_access('administer taxonomy') || user_access('edit terms in ' . $vocab->vid)) {
          $terms = format_plural($term_count, '1 categories', '@count categories');
          $rows[] = array(
            'data' => array(
              t($vocab->name . ': ' . $terms),
              l(t('Configure'), 'admin/structure/taxonomy/' . $vocab->machine_name . '/edit', $options),
              l(t('Manage categories'), 'admin/structure/taxonomy/' . $vocab->machine_name, $options),
              l(t('Add new category'), 'admin/structure/taxonomy/' . $vocab->machine_name . '/add', $options),
            ),
          );
        }
      }
    }
  }

  if (empty($rows)) {
    $rows[] = array(
      array(
        'data' => t('There are no vocabularies to display.'),
        'colspan' => 4,
      )
    );
  }

  $link = '';
  if (user_access('administer taxonomy')) {
    $link = l(t('Taxonomy administration'), 'admin/structure/taxonomy');
  }

  $block->content = theme('total_control_admin_table', array('header' => $header, 'rows' => $rows, 'link' => $link));

  return $block;
}

/**
 * 'Edit form' callback for the content type.
 */
function total_control_taxonomy_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  if (!module_exists('taxonomy')) {
    return $form;
  }

  $vocabs = taxonomy_get_vocabularies();
  if (!empty($vocabs)) {
    $vocab_options = array();
    $vocab_defaults = array();
    foreach ($vocabs as $vid => $vocab) {
      $vocab_options[$vid] = $vocab->name;
      $vocab_defaults[$vid] = $vid;
    }

    if (isset($conf['vids'])) {
      $vocab_defaults = $conf['vids'];
    }

    $form['vids'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Include Vocabularies'),
      '#multiple' => TRUE,
      '#options' => $vocab_options,
      '#default_value' => $vocab_defaults,
      );
  }

  return $form;
}

/**
 * 'Edit form' submit callback for the content type.
 */
function total_control_taxonomy_content_type_edit_form_submit($form, &$form_state) {
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  } 
}
