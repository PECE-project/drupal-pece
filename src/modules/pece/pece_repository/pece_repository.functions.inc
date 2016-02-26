<?php
/**
 * Creates default menu item for PECE Repository module.
 */
function pece_repository_set_menu_items() {
  $items = array(
    'Collaborate' => array(
      'link_path' => drupal_get_normal_path('repo/groups'),
      'link_title' => t('Collaborate'),
      'weight' => 2,
      'menu_name' => 'main-menu',
      'mlid' => NULL,
    ),
    'Analyze' => array(
      'link_path' => drupal_get_normal_path('repo/artifacts'),
      'link_title' => t('Analyze'),
      'weight' => 3,
      'menu_name' => 'main-menu',
      'mlid' => NULL,
    ),
    'Discover' => array(
      'link_path' => drupal_get_normal_path('repo'),
      'link_title' => t('Discover'),
      'weight' => 4,
      'menu_name' => 'main-menu',
      'mlid' => NULL,
    )
  );
  foreach ($items as $title => $item) {
    $query = db_select('menu_links')
      ->fields('menu_links')
      ->condition('link_title', t($title))
      ->execute();
    $result = $query->fetchObject();

    if (empty($result)) {
      menu_link_save($item);
      menu_cache_clear_all();
    }
  }


}
