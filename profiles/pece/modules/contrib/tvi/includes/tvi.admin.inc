<?php
/**
 * @file
 * Administration functions for the tvi module.
 */

/**
 * Adds TVI administration form to the vocabulary edit page
 *
 * admin/content/taxonomy/edit/vocabulary/$vid
 */
function tvi_vocab_form(&$form) {
  if (array_key_exists('#vocabulary', $form)) {
    $vid = '_autocreate';
    if (!empty($form['#vocabulary']->vid)) {
      $vid = (int) $form['#vocabulary']->vid;
    }

    tvi_include('query');
    tvi_taxonomy_admin_form($form, tvi_load_settings($vid, TVI_TYPE_VOCAB));
  }
}

/**
 * Adds TVI administration form to the term edit page
 *
 * admin/content/taxonomy/edit/term/$tid
 */
function tvi_term_form(&$form) {
  if (array_key_exists('#term', $form)) {
    $tid = '_autocreate';
    if (!empty($form['#term']['tid'])) {
      $tid = (int) $form['#term']['tid'];
    }

    tvi_include('query');
    tvi_taxonomy_admin_form($form, tvi_load_settings($tid, TVI_TYPE_TERM));
  }
}

/**
 * Create the main settings form.
 *
 * admin/config/user-interface/tvi
 */
function tvi_settings_form($form, &$form_state) {
  tvi_include('query');
  tvi_taxonomy_admin_form($form, tvi_load_settings('default', TVI_TYPE_ALL));

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * The main TVI administration form.
 *
 * This is added to both vocabulary and term edit forms.
 */
function tvi_taxonomy_admin_form(&$form, $settings) {
  // Add validate and submit handlers
  $form['#validate'][] = 'tvi_validate_handler';
  $form['#submit'][]   = 'tvi_submit_handler';
  // Add JS & CSS
  $form['#attached']['js'][] = drupal_get_path('module', 'tvi') . '/tvi.js';
  $form['#attached']['css'][] = drupal_get_path('module', 'tvi') . '/tvi.css';

  // Form container
  $form['tvi'] = array(
    '#type' => 'fieldset',
    '#title' => t('View usage'),
    '#weight' => -10,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#tree' => TRUE,
  );

  // Javascript warning message
  $js_msg = t('This form is best used with Javascript enabled. Please enable your Javascript, then refresh this page.');
  $js_msg = '<p class="javascript-warning">' . $js_msg . '</p>';
  $form['tvi']['javascript_message'] = array(
    '#type' => 'markup',
    '#value' => check_plain($js_msg),
  );

  $form['tvi']['is_default'] = array(
    '#type' => 'value',
    '#value' => $settings->is_default && $settings->type != TVI_TYPE_ALL,
  );

  $form['tvi']['type'] = array(
    '#type'  => 'value',
    '#value' => $settings->type,
  );

  $form['tvi']['xid'] = array(
    '#type'  => 'value',
    '#value' => $settings->xid,
  );

  // Status toggle switch
  $form['tvi']['status'] = array(
    '#id' => 'tvi-status-check',
    '#type' => 'checkbox',
    '#title' => t('Use view override.'),
    '#default_value' => $settings->status,
    '#description' => t('Unchecking this field will disable the use of the view when displaying this taxonomy page.'),
  );

  if ($settings->type == TVI_TYPE_TERM) {
    // Inheritance switch
    $form['tvi']['inherit'] = array(
      '#id' => 'tvi-inherit-check',
      '#type' => 'checkbox',
      '#title' => t('Child terms will use this settings.'),
      '#default_value' => $settings->inherit,
      '#description' => t('Checking this field will allow to define a view used by the current term and its children recursively while these children does not have their own settings.'),
      '#states' => array(
        'disabled' => array(
          '#tvi-status-check' => array('checked' => FALSE),
        ),
        'visible' => array(
          '#tvi-status-check' => array('checked' => TRUE),
        ),
      ),
    );
  }

  //  View selector
  $form['tvi']['view_name'] = array(
    '#id' => 'tvi-view-selector',
    '#type' => 'select',
    '#title' => t('Using the view'),
    '#default_value' => ($settings->view_name ? $settings->view_name : NULL),
    '#options' => tvi_get_views(),
    '#description' => t('The view that you wish to use for this display'),
    '#states' => array(
      'disabled' => array(
        '#tvi-status-check' => array('checked' => FALSE),
      ),
      'visible' => array(
        '#tvi-status-check' => array('checked' => TRUE),
      ),
    ),
  );
  // Display selector
  $form['tvi']['display'] = array(
    '#id' => 'tvi-display-selector',
    '#type' => 'select',
    '#title' => t('View display'),
    '#default_value' => (
      $settings->view_name
      ? $settings->view_name . ':' . $settings->display
      : NULL
    ),
    '#options' => tvi_get_view_displays(), // Assume no Javascript
    '#states' => array(
      'disabled' => array(
        '#tvi-status-check' => array('checked' => FALSE),
      ),
      'visible' => array(
        '#tvi-status-check' => array('checked' => TRUE),
      ),
    ),
  );
  // Pass arguments
  $form['tvi']['pass_arguments'] = array(
    '#id' => 'tvi-pass-arguments',
    '#type' => 'checkbox',
    '#title' => t('Pass all arguments to views.'),
    '#description' => t("Enable this checkbox, and your view's display will receive all arguments going after <em>/taxonomy/term/</em> in the path. If disabled, your view's display will only receive <em>tid</em>, and <em>tid_depth</em>."),
    '#default_value' => isset($settings->pass_arguments) ? $settings->pass_arguments : 0,
    '#states' => array(
      'disabled' => array(
        '#tvi-status-check' => array('checked' => FALSE),
      ),
      'visible' => array(
        '#tvi-status-check' => array('checked' => TRUE),
      ),
    ),
  );
  if ($settings->type == TVI_TYPE_TERM) {
    $form['tvi']['display']['#description'] =
      t('The view display you select from the option above will be used to render this taxonomy term.');
  }
  elseif ($settings->type == TVI_TYPE_VOCAB) {
    $form['tvi']['display']['#description'] =
      t('The view display you select from the option above will be used to render all the taxonomy terms of this vocabulary except if their settings are overriden.');
  }
  else {
    $form['tvi']['display']['#description'] =
      t('The view display you select from the option above will be used to render all the taxonomy terms in all the defined vocabularies except if their vocabularies settings or their terms settings are overriden.');
  }
}

/**
 * Validate the TVI administration form submission.
 *
 * If the view and the display do not line up, throw an error.
 */
function tvi_validate_handler($form, &$form_state) {
  $values = $form_state['values']['tvi'];

  if(!empty($values['display'])) {
    list($view_name, $display_name) = explode(':', $values['display']);
    $form_state['values']['tvi']['display'] = $display_name;
  }
}

/**
 * Save the view taxonomy data to the database.
 */
function tvi_submit_handler($form, &$form_state) {
  $settings = (object) $form_state['values']['tvi'];

  // Handle the case of the creation form
  if (empty($settings->xid) ||$settings->xid == '_autocreate') {
    if ($settings->type == TVI_TYPE_VOCAB) {
      $settings->xid = $form_state['vocabulary']->vid;
    }
    elseif ($settings->type == TVI_TYPE_TERM) {
      $settings->xid = $form_state['term']->tid;
    }
    $settings->xid = _tvi_get_xid($settings->xid, $settings->type);
  }

  if (!$settings->is_default || $settings->status) {
    tvi_update_settings($settings);
    if ($settings->type == TVI_TYPE_ALL) {
      drupal_set_message(t('The configuration options have been saved.'));
    }
  }
}

/**
 * Gather a listing of all views so that the admin may choose ANY view
 */
function tvi_get_views($return_object = FALSE) {
  $views = array();

  foreach (views_get_enabled_views() as $view) {
    // Filter views having no display
    if (count($view->display) > 1) {
      if ($return_object) {
        $views[$view->name] = $view;
      }
      else {
        $views[$view->name] = $view->name;
      }
    }
  }

  return $views;
}

/**
 * Gathers the available display options for the view operating on this term
 * or vocabulary.
 */
function tvi_get_view_displays() {
  $displays = array();

  foreach (tvi_get_views(TRUE) as $view_name => $view) {
    foreach ($view->display as $display_name => $display) {
      // Ignore the "default" displays
      if ($display_name == 'default' || $display->display_plugin == 'default') {
        continue;
      }
      // Ignore disabled displays
      if (array_key_exists('enabled', $display->display_options) && $display->display_options['enabled'] === FALSE) {
        continue;
      }

      $displays[$view_name . ':' . $display_name] = $view->name . ' - ' . $display->display_title . ' [' . $display->id . ']';
    }
  }

  return $displays;
}