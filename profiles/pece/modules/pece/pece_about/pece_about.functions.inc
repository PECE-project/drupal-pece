<?php

/**
 * Ensures the existance of a about item.
 *
 * @param $name
 *   The kraftwagen itemname to use as unique id.
 *
 * @param $info
 *   Array with data for the item's fields.
 *
 * @return object
 *   An entity object or NULL if not found/not able to create.
 */
function pece_about_ensure_item($name, $info) {
  module_load_include('inc', 'kw_itemnames');

  $item_id = kw_itemnames_name_get_item_id('node', $name);
  $item = empty($item_id) ? null : kw_itemnames_item_load('node', $item_id);

  if (!empty($item)) {
    return $item;
  }

  $item_values = array(
    'title' => $info['title'],
    'type' => 'pece_about_page',
    'uid' => 1,
    'language' => LANGUAGE_NONE,
  );

  if (!empty($info['body'])) {
    $item_values['body'] = array(
      LANGUAGE_NONE => array(
        array(
          'value' => $info['body'],
          'format' => 'panopoly_wysiwyg_text',
        )
      ),
    );
  }

  return kw_itemnames_ensure('node', $name, array(), $item_values);
}

/**
 * Creates default menu item for PECE About module.
 */
function pece_about_set_menu_item() {
  $item = array(
    'link_path' => drupal_get_normal_path('about'),
    'link_title' => t('About'),
    'weight' => 1,
    'menu_name' => 'main-menu',
    'mlid' => NULL,
  );

  $query = db_select('menu_links')
    ->fields('menu_links')
    ->condition('link_title', t('About'))
    ->execute();
  $result = $query->fetchObject();

  if (empty($result)) {
    menu_link_save($item);
    menu_cache_clear_all();
  }
}
