<?php
/**
 *  @file
 *  Provides theme functions for apps module.
 */


/**
 * Themes a list of apps.
 */
function theme_apps_list($vars) {
  // Check if Apps grouping mode is enabled.
  if (variable_get('apps_grouping_mode', FALSE)) {
    $packages = array();
    $other = array();
    foreach (element_children($vars['apps']) as $app_name) {
      $app = $vars['apps'][$app_name];
      if (!empty($app['package'])) {
        foreach (explode(',', $app['package']) as $package) {
          $packages[trim($package)][$app_name] = $app['name'];
        }
      }
      else {
        $other[$app_name] = $app['name'];
      }
    }
    ksort($packages);
    if (!empty($other)) {
      $packages[t('Other')] = $other;
    }
    // Until issue @https://drupal.org/node/1099132 is fixed, we need to
    // manually load js file and add classes to element
    $render['app_groups']['#attached']['js'][] = "misc/collapse.js";
    $render['app_groups']['#attached']['js'][] = "misc/form.js";
    if (variable_get('apps_grouping_vertical', TRUE)) {
      $render['app_groups'] = array(
        '#type' => 'vertical_tabs',
        '#weight' => 99,
      );
    }
    foreach ($packages as $key => $apps) {
      $items = array();
      foreach ($apps as $id => $app) {
        $vars['apps'][$id]['#printed'] = FALSE;
        $items[] = drupal_render($vars['apps'][$id]);
      }
      $render['app_groups'][$key] = array(
        '#type' => 'fieldset',
        '#title' => $key,
        '#group' => 'app_groups',
        '#children' => theme('item_list', array('items' => $items)),
        '#attributes' => array('class' => array('collapsible')),
      );
    }
    return drupal_render($render);
  }
  else {
    $items = array();
    foreach ($vars['apps'] as $id => $app) {
      if (!preg_match("/^#/", $id)) {
        $items[] = drupal_render($app);
      }
    }
    return theme('item_list', array('items' => $items));
  }
}


/**
 * Implements hook_preprocess_apps_app_teaser().
 */
function apps_preprocess_apps_app_teaser(&$vars) {
  apps_include('pages');
  $link = apps_app_page_path($vars['app']);
  $vars['name'] = l($vars['app']['name'], $link);
  if (!empty($vars['app']['logo'])) {
    $vars['app']['logo']['style_name']= 'apps_logo';
    $vars['logo'] = l(theme('image_style', $vars['app']['logo']), $link, array('html' => TRUE));
  }
  else {
    $vars['logo'] = FALSE;
  }
  $status = $vars['app']['status'];
  $vars['status'] = $status === APPS_ENABLED ?
    'enabled' :
    (($status === APPS_DISABLED) ?
      'disabled' :
      (($status === APPS_INCOMPATIBLE) ?
        'incompatible' :
        'available'
      )
    );

  //add rating information for theming
  $vars['app']['teaser'] = TRUE;

  if (variable_get('apps_allow_voting', FALSE)) {
    $vars['rating'] = theme('apps_voting_widget', $vars['app']);
  }

  //action link
  $vars['config'] = apps_app_access($vars['app'], 'configure') ? l(t('Config'), apps_app_page_path($vars['app'], 'configure')) : '';
  $vars['action'] = l(t('Details'), $link);
  $vars['update'] = apps_app_access($vars['app'], 'update') ? l(t('Update'), apps_app_page_path($vars['app'], 'update')) : '';

  if ($vars['app']['installed_version'] && $vars['app']['version'] != $vars['app']['installed_version']) {
    $vars['classes_array'][] = ' apps-update-needed-teaser';
  }
}

/**
 * Implements hook_preprocess_apps_app_page().
 */
function apps_preprocess_apps_app_page(&$vars) {
  // First do everything we do in the teaser.
  drupal_add_css(drupal_get_path('module', 'apps') . '/theme/css/apps.css');
  apps_preprocess_apps_app_teaser($vars);

  // We need some special stuff for the logo here.
  if (!empty($vars['app']['logo']) && $vars['app']['logo']) {
    $vars['app']['logo']['style_name']= 'apps_logo_small';
    $vars['logo'] = theme('image_style', $vars['app']['logo']);
  }


  if (isset($vars['app']['screenshots'])) {
    $vars['screenshot'] = '';
    foreach ($vars['app']['screenshots'] as $screenshot) {
      $screenshot['style_name'] = 'apps_screenshot';
      $vars['screenshot'] .= l(theme('image_style', $screenshot), file_create_url($screenshot['uri']), array('html' => TRUE, 'attributes' => array('class' => 'colorbox')));
    }
  }
  else {
    $vars['screenshot'] = FALSE;
  }

  $vars['description'] = $vars['app']['description'];
  $vars['name'] = $vars['app']['name'];
  $vars['author'] = l($vars['app']['author'], $vars['app']['author_url']);
  $vars['version'] = $vars['app']['version'];
  if ($vars['app']['installed_version'] && $vars['app']['version'] != $vars['app']['installed_version']) {
    $vars['version'] .= ' <span class="apps-update-needed">' . t('Installed: @installed_version', array('@installed_version' => $vars['app']['installed_version'])) . '</span>';
  }

  $conflicts_enabled = array();
  if ($conflicts = apps_app_find_conflicts($vars['app'])) {
    $vars['conflicts_title'] = t('Conflicts');
    $conflicts = array();
    foreach (apps_app_find_conflicts($vars['app']) as $conflict) {
      if ($conflict_app = apps_app_load($conflict['server'], $conflict['name'])) {
        $enabled = $conflict_app['status'] == APPS_ENABLED;
        $conflicts[] = l($conflict_app['name'] . ($enabled ? ' (enabled)' : ''), 'admin/apps/' . $conflict['server'] . '/' . $conflict['name']);
        if ($enabled) {
          $conflicts_enabled[] = $conflict_app['name'];
        }
      }
    }
    if ($conflicts) {
      $vars['conflicts'] = implode(', ', $conflicts);
    }
  }

  if ($vars['app']['status'] === APPS_INCOMPATIBLE) {
    $incompatible_deps = array();
    $incompatible_message = '';
    foreach ($vars['app']['dependencies'] as $dep) {
      if ($dep['status'] === APPS_INCOMPATIBLE) {
        $incompatible_deps[] = "{$dep['version']['name']} {$dep['version']['original_version']}";
      }
    }
    if (!empty($incompatible_deps)) {
      $incompatible_message = t("Incompatible - requires @deps.", array('@deps' => implode(", ", $incompatible_deps)));
    }
    else {
      //this should never run
      $incompatible_message = t('Incompatible with current install.');
    }
    if ($conflicts_enabled) {
      $incompatible_message = ($incompatible_message ? $incompatible_message . ' ' : '') . t('Conflicts with enabled @apps', array('@apps' => implode(", ", $conflicts_enabled)));
    }
    $vars['status'] = $incompatible_message;
    $vars['status_title'] = t('Status');
  }

  //Title texts for App Detail Page
  $vars['author_title'] = t('Author');
  $vars['version_title'] = t('Version');
  $vars['description_title'] = t('Description');

  $vars['app']['teaser'] = FALSE;

  if (variable_get('apps_allow_voting', FALSE)) {
    $vars['rating_title'] = t('Customer Rating');
    //Override the rating key with the full widget
    $vars['rating_caption'] = t('Average rating for this version:');
    $vars['rating'] = theme('apps_voting_widget', $vars['app']);
  }

  $vars['parent_apps'] = array();
  $vars['parent_apps_title'] = t('Depends on');
  if (!empty($vars['app']['parent_apps'])) {
    $apps = apps_apps($vars['app']['server']);
    foreach ($vars['app']['parent_apps'] as $parent_app) {
      if (!empty($apps[$parent_app])) {
        $vars['parent_apps'][] = l($apps[$parent_app]['name'], apps_app_page_path($apps[$parent_app]));
      }
    }
  }
}

/**
 * Implements hook_preprocess_apps_app_featured().
 */
function apps_preprocess_apps_app_featured(&$vars) {
  //first do everything we do in the teaser
  apps_preprocess_apps_app_teaser($vars);
  if ($vars['app']['screenshots'][0]) {
    $vars['app']['screenshots'][0]['style_name'] = 'apps_featured_screenshot';
    $vars['screenshot'] = theme('image_style', $vars['app']['screenshots'][0]);
  }
  $vars['description'] = $vars['app']['description'];

  if (variable_get('apps_allow_voting', FALSE)) {
    $vars['rating'] = theme('apps_voting_widget', $vars['app']);
  }

  //action link
  $link = apps_app_page_path($vars['app']);
  $vars['action'] = l(t('free'), $link);  //The text and link for the action button
}

/**
 * Implements hook_preprocess_apps_install_page().
 */
function apps_preprocess_apps_install_page(&$vars) {
  drupal_add_css(drupal_get_path('module', 'apps') . '/theme/css/apps.css');
  if (isset($vars['content']['featured_app'])) {
    $vars['content']['featured_app']['#theme'] = 'apps_app_featured';
  }
}

/**
 * Implements hook_preprocess_apps_manage_page().
 */
function apps_preprocess_apps_manage_page(&$vars) {
  drupal_add_css(drupal_get_path('module', 'apps') . '/theme/css/apps.css');
}

/**
 * Implements hook_preprocess_apps_update_page().
 */
function apps_preprocess_apps_update_page(&$vars) {
  drupal_add_css(drupal_get_path('module', 'apps') . '/theme/css/apps.css');
}

/**
 * Implements hook_preprocess_apps_update_page().
 */
function apps_preprocess_apps_catalog_page(&$vars) {
  $vars['title'] = $vars['server']['title'];
  $vars['apps_render'] = array();
  foreach ($vars['apps'] as $machine_name => $info) {
    $vars['apps_render'][$info['name']] = array(
      'description' => check_plain($info['description']),
      'conflicts' => array(),
      'name' => check_plain($info['name']),
    );
    if ($conflicts = apps_app_find_conflicts($info)) {
      foreach ($conflicts as $conflict) {
        if ($conflict['server'] == $vars['server']['name']) {
          $vars['apps_render'][$info['name']]['conflicts'][] = check_plain($vars['apps'][$conflict['name']]['name']);
        }
      }
    }
  }
  ksort($vars['apps_render']);
}
