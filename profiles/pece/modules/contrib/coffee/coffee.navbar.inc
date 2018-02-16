<?php

/**
 * @file
 * Navbar hooks implemented by the coffee module.
 */

/**
 * Implements hook_navbar().
 */
function coffee_navbar() {
  $items = array();

  if (user_access('access coffee')) {
    $items['coffee'] = array(
      '#type' => 'navbar_item',
      '#weight' => 200,
      'tab' => array(
        '#type' => 'link',
        '#title' => t('Go to'),
        '#href' => '<front>',
        '#options' => array(
          'attributes' => array(
            'title' => t('Use alt+d to start Coffee and search for a page to go to.'),
            'class' => array('navbar-icon', 'navbar-icon-coffee',),
          ),
        ),
      ),
    );
  }

  return $items;
}
