<?php
/**
 * @file
 * panopoly_test.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function panopoly_test_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'date_popup_authored_enabled_panopoly_test_landing_page';
  $strongarm->value = 1;
  $export['date_popup_authored_enabled_panopoly_test_landing_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'date_popup_authored_format_panopoly_test_landing_page';
  $strongarm->value = 'm/d/Y - H:i';
  $export['date_popup_authored_format_panopoly_test_landing_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'date_popup_authored_year_range_panopoly_test_landing_page';
  $strongarm->value = '3';
  $export['date_popup_authored_year_range_panopoly_test_landing_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__panopoly_test_page';
  $strongarm->value = array(
    'view_modes' => array(),
    'extra_fields' => array(
      'form' => array(
        'metatags' => array(
          'weight' => '4',
        ),
        'title' => array(
          'weight' => '0',
        ),
        'path' => array(
          'weight' => '5',
        ),
        'redirect' => array(
          'weight' => '6',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__panopoly_test_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__panopoly_test_page_simple';
  $strongarm->value = array(
    'view_modes' => array(),
    'extra_fields' => array(
      'form' => array(),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__panopoly_test_page_simple'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_panopoly_test_landing_page';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_panopoly_test_landing_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_panopoly_test_page';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_panopoly_test_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_panopoly_test_page_simple';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_panopoly_test_page_simple'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_panopoly_test_landing_page';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_panopoly_test_landing_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_panopoly_test_page';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_panopoly_test_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_panopoly_test_page_simple';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_panopoly_test_page_simple'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_panopoly_test_landing_page';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_panopoly_test_landing_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_panopoly_test_page';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_panopoly_test_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_panopoly_test_page_simple';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_panopoly_test_page_simple'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_panopoly_test_landing_page';
  $strongarm->value = '0';
  $export['node_preview_panopoly_test_landing_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_panopoly_test_page';
  $strongarm->value = '1';
  $export['node_preview_panopoly_test_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_panopoly_test_page_simple';
  $strongarm->value = '0';
  $export['node_preview_panopoly_test_page_simple'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_panopoly_test_landing_page';
  $strongarm->value = 0;
  $export['node_submitted_panopoly_test_landing_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_panopoly_test_page';
  $strongarm->value = 1;
  $export['node_submitted_panopoly_test_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_panopoly_test_page_simple';
  $strongarm->value = 1;
  $export['node_submitted_panopoly_test_page_simple'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_defaults_node_panopoly_test_landing_page';
  $strongarm->value = array(
    'status' => 1,
    'view modes' => array(
      'page_manager' => array(
        'status' => 1,
        'default' => 1,
        'choice' => 0,
      ),
      'default' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
      'full' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
      'teaser' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
      'rss' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
      'search_index' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
      'search_result' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
      'featured' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
      'token' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
    ),
  );
  $export['panelizer_defaults_node_panopoly_test_landing_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_defaults_node_panopoly_test_page';
  $strongarm->value = array(
    'status' => 1,
    'view modes' => array(
      'page_manager' => array(
        'status' => 1,
        'default' => 1,
        'choice' => 1,
      ),
      'default' => array(
        'status' => 1,
        'default' => 1,
        'choice' => 0,
      ),
      'teaser' => array(
        'status' => 1,
        'default' => 1,
        'choice' => 0,
      ),
      'featured' => array(
        'status' => 1,
        'default' => 1,
        'choice' => 0,
      ),
    ),
  );
  $export['panelizer_defaults_node_panopoly_test_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_node:panopoly_test_landing_page_allowed_layouts';
  $strongarm->value = 'O:22:"panels_allowed_layouts":4:{s:9:"allow_new";b:1;s:11:"module_name";s:41:"panelizer_node:panopoly_test_landing_page";s:23:"allowed_layout_settings";a:71:{s:8:"flexible";b:1;s:17:"threecol_33_34_33";b:1;s:6:"onecol";b:1;s:13:"twocol_bricks";b:1;s:6:"twocol";b:1;s:25:"threecol_25_50_25_stacked";b:1;s:25:"threecol_33_34_33_stacked";b:1;s:17:"threecol_25_50_25";b:1;s:14:"twocol_stacked";b:1;s:7:"moscone";b:1;s:5:"selby";b:1;s:4:"webb";b:1;s:7:"brenham";b:1;s:9:"sanderson";b:1;s:4:"pond";b:1;s:5:"sutro";b:1;s:6:"boxton";b:1;s:16:"bartlett_flipped";b:1;s:4:"burr";b:1;s:5:"geary";b:1;s:6:"taylor";b:1;s:6:"phelan";b:1;s:12:"sutro_double";b:1;s:6:"bryant";b:1;s:15:"moscone_flipped";b:1;s:15:"brenham_flipped";b:1;s:14:"taylor_flipped";b:1;s:8:"mccoppin";b:1;s:17:"sanderson_flipped";b:1;s:15:"hewston_flipped";b:1;s:7:"hewston";b:1;s:6:"whelan";b:1;s:6:"harris";b:1;s:12:"webb_flipped";b:1;s:13:"selby_flipped";b:1;s:5:"rolph";b:1;s:12:"burr_flipped";b:1;s:22:"bryant_flipped_flipped";b:1;s:5:"brown";b:1;s:8:"bartlett";b:1;s:12:"radix_phelan";b:1;s:20:"radix_taylor_flipped";b:1;s:13:"radix_moscone";b:1;s:23:"radix_sanderson_flipped";b:1;s:21:"radix_hewston_flipped";b:1;s:12:"radix_taylor";b:1;s:14:"radix_bartlett";b:1;s:12:"radix_whelan";b:1;s:12:"radix_boxton";b:1;s:19:"radix_selby_flipped";b:1;s:15:"radix_sanderson";b:1;s:11:"radix_sutro";b:1;s:20:"radix_bryant_flipped";b:1;s:18:"radix_sutro_double";b:1;s:13:"radix_brenham";b:1;s:10:"radix_burr";b:1;s:18:"radix_webb_flipped";b:1;s:18:"radix_burr_flipped";b:1;s:13:"radix_hewston";b:1;s:11:"radix_selby";b:1;s:21:"radix_brenham_flipped";b:1;s:21:"radix_moscone_flipped";b:1;s:10:"radix_webb";b:1;s:12:"radix_harris";b:1;s:10:"radix_pond";b:1;s:11:"radix_brown";b:1;s:11:"radix_geary";b:1;s:12:"radix_bryant";b:1;s:14:"radix_mccoppin";b:1;s:11:"radix_rolph";b:1;s:22:"radix_bartlett_flipped";b:1;}s:10:"form_state";N;}';
  $export['panelizer_node:panopoly_test_landing_page_allowed_layouts'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_node:panopoly_test_landing_page_allowed_layouts_default';
  $strongarm->value = 1;
  $export['panelizer_node:panopoly_test_landing_page_allowed_layouts_default'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_node:panopoly_test_landing_page_allowed_types_default';
  $strongarm->value = 1;
  $export['panelizer_node:panopoly_test_landing_page_allowed_types_default'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_node:panopoly_test_landing_page_default';
  $strongarm->value = array(
    'entity_form_field' => 'entity_form_field',
    'token' => 'token',
    'block' => 'block',
    'entity_field' => 'entity_field',
    'entity_field_extra' => 'entity_field_extra',
    'custom' => 'custom',
    'entity_view' => 'entity_view',
    'fieldable_panels_pane' => 'fieldable_panels_pane',
    'menu_tree' => 'menu_tree',
    'views_panes' => 'views_panes',
    'other' => 'other',
  );
  $export['panelizer_node:panopoly_test_landing_page_default'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_node:panopoly_test_page:page_manager_selection';
  $strongarm->value = 'node:panopoly_test_page:default';
  $export['panelizer_node:panopoly_test_page:page_manager_selection'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_node:panopoly_test_page_allowed_layouts_default';
  $strongarm->value = 1;
  $export['panelizer_node:panopoly_test_page_allowed_layouts_default'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_node:panopoly_test_page_allowed_types_default';
  $strongarm->value = 1;
  $export['panelizer_node:panopoly_test_page_allowed_types_default'] = $strongarm;

  return $export;
}
