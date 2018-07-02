<?php

/**
 * @file
 *
 * "Panel Pages" panels content pane. It shows users with permissions the
 * panel pages on the site, and provides links directly to the "content" tab.
 *
 */

$plugin = array(
  'single' => TRUE,
  'title' => t('Admin - Menus'),
  'defaults' => array('menus' => array()),
  'icon' => 'cog.png',
  'description' => t('Provides links to administer menus.'),
  'category' => t('Dashboard'),
  'edit text' => t('Configure'),
);

/**
 * 'Admin title' callback for the content type.
 */
function total_control_menus_content_type_admin_title($subtype = NULL, $conf = NULL, $context = NULL) {
  return t('Administer Menus');
}

/**
 * 'Admin info' callback for the content type.
 */
function total_control_menus_content_type_admin_info($subtype = NULL, $conf = NULL, $context = NULL) {
  $block = new stdClass();
  $block->title = t('Provides links to administer menus.');

  return $block;
}

/**
 * Run-time rendering of the body of the block.
 */
function total_control_menus_content_type_render($subtype, $conf, $args, &$context) {
  if (!module_exists('menu')) {
    return;
  }
  $items = array();

  $menus = menu_get_menus();
  $options = array('query' => array('destination' => 'admin/dashboard'));
  $header = array(
    array('data' => t('Menu')), 
    array('data' => t('Operations'), 'colspan' => 3));
  $rows = array();

  foreach ($menus as $menu_name => $menu) {
    if (array_key_exists($menu_name, $conf['menus'])) {
      if ($conf['menus'][$menu_name] === $menu_name) {
        $rows[] = array(
          'data' => array(
            t($menu),
            l(t('Configure'), 'admin/structure/menu/manage/' . $menu_name . '/edit', $options),
            l(t('Manage links'), 'admin/structure/menu/manage/' . $menu_name, $options),
            l(t('Add new link'), 'admin/structure/menu/manage/' . $menu_name . '/add', $options),
          ),
        );
      }
    }
  }

  if (empty($rows)) {
    $rows[] = array(
      array(
        'data' => t('There are no menus to display.'),
        'colspan' => 4,
      )
    );
  }

  // Build a link to the menu admin UI.
  $link = '';
  if (user_access('administer menu')) {
    $link = l(t('Menu administration'), 'admin/structure/menu');
  }

  $block = new stdClass();
  $block->title = t('Administer Menus');
  $block->module = t('total_control');
  $block->content = theme('total_control_admin_table', array('header' => $header, 'rows' => $rows, 'link' => $link));

  return $block;

}

/**
 * 'Edit form' callback for the content type.
 */
function total_control_menus_content_type_edit_form($form, &$form_state) {
  if (!module_exists('menu')) {
    return $form;
  }
  $conf = $form_state['conf'];

  $menus = menu_get_menus();
  foreach ($menus as $machine => $name) {
    if (!in_array($machine, array('management', 'user-menu', 'devel'))) {
      $menu_defaults[$machine] = $machine;
    }
  }
  $form['menus'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Show links for the following menus on the dashboard'),
    '#options' => $menus,
    '#default_value' => ($conf['menus'])? $conf['menus'] : $menu_defaults,
  );

  return $form;
}

/**
 * 'Edit form' submit callback for the content type.
 */
function total_control_menus_content_type_edit_form_submit($form, &$form_state) {
  foreach (array_keys($form_state['plugin']['defaults']) as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}
