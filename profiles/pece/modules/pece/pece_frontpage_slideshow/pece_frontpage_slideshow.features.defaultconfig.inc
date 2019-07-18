<?php

/**
 * @file
 * pece_frontpage_slideshow.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function pece_frontpage_slideshow_defaultconfig_features() {
  return array(
    'pece_frontpage_slideshow' => array(
      'field_default_fields' => 'field_default_fields',
      'strongarm' => 'strongarm',
      'user_default_permissions' => 'user_default_permissions',
      'views_default_views' => 'views_default_views',
    ),
  );
}

/**
 * Implements hook_defaultconfig_field_default_fields().
 */
function pece_frontpage_slideshow_defaultconfig_field_default_fields() {
  $fields = array();

  // Exported field: 'comment-comment_node_frontpage_image_slideshow-comment_body'.
  $fields['comment-comment_node_frontpage_image_slideshow-comment_body'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(
        0 => 'comment',
      ),
      'field_name' => 'comment_body',
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => 0,
      'module' => 'text',
      'settings' => array(),
      'translatable' => 0,
      'type' => 'text_long',
    ),
    'field_instance' => array(
      'bundle' => 'comment_node_frontpage_image_slideshow',
      'default_value' => NULL,
      'deleted' => 0,
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'comment',
      'field_name' => 'comment_body',
      'label' => 'Comment',
      'required' => TRUE,
      'settings' => array(
        'text_processing' => 1,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'text',
        'settings' => array(
          'rows' => 5,
        ),
        'type' => 'text_textarea',
        'weight' => 0,
      ),
    ),
  );

  // Exported field: 'node-frontpage_image_slideshow-field_pece_slideshow_image'.
  $fields['node-frontpage_image_slideshow-field_pece_slideshow_image'] = array(
    'field_config' => array(
      'active' => 1,
      'cardinality' => 1,
      'deleted' => 0,
      'entity_types' => array(),
      'field_name' => 'field_pece_slideshow_image',
      'foreign keys' => array(
        'fid' => array(
          'columns' => array(
            'fid' => 'fid',
          ),
          'table' => 'file_managed',
        ),
      ),
      'indexes' => array(
        'fid' => array(
          0 => 'fid',
        ),
      ),
      'locked' => 0,
      'module' => 'image',
      'settings' => array(
        'default_image' => 0,
        'profile2_private' => FALSE,
        'uri_scheme' => 'public',
      ),
      'translatable' => 0,
      'type' => 'image',
    ),
    'field_instance' => array(
      'bundle' => 'frontpage_image_slideshow',
      'deleted' => 0,
      'description' => '',
      'display' => array(
        'card' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
        'default' => array(
          'label' => 'hidden',
          'module' => 'image',
          'settings' => array(
            'image_link' => '',
            'image_style' => 'pece_frontpage_image_style',
          ),
          'type' => 'image',
          'weight' => 0,
        ),
        'featured' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
        'free_panel' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
        'highlighted' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
        'meta_content' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
        'mini_teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
        'most_recent' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'node',
      'fences_wrapper' => 'div_div_div',
      'field_name' => 'field_pece_slideshow_image',
      'label' => 'Image',
      'required' => 1,
      'settings' => array(
        'alt_field' => 1,
        'default_image' => 0,
        'file_directory' => 'slideshow',
        'file_extensions' => 'png gif jpg jpeg',
        'max_filesize' => '',
        'max_resolution' => '1920x460',
        'min_resolution' => '960x230',
        'title_field' => 1,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'image',
        'settings' => array(
          'manualcrop_crop_info' => 1,
          'manualcrop_default_crop_area' => 1,
          'manualcrop_enable' => 0,
          'manualcrop_inline_crop' => 0,
          'manualcrop_instant_crop' => 0,
          'manualcrop_instant_preview' => 1,
          'manualcrop_keyboard' => 1,
          'manualcrop_maximize_default_crop_area' => 0,
          'manualcrop_require_cropping' => array(),
          'manualcrop_styles_list' => array(),
          'manualcrop_styles_mode' => 'include',
          'manualcrop_thumblist' => 0,
          'preview_image_style' => 'thumbnail',
          'progress_indicator' => 'throbber',
        ),
        'type' => 'image_image',
        'weight' => 3,
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Comment');
  t('Image');

  return $fields;
}

/**
 * Implements hook_defaultconfig_strongarm().
 */
function pece_frontpage_slideshow_defaultconfig_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'additional_settings__active_tab_frontpage_image_slideshow';
  $strongarm->value = 'edit-menu';
  $export['additional_settings__active_tab_frontpage_image_slideshow'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'bundle_inherit_frontpage_image_slideshow';
  $strongarm->value = array(
    0 => 'entity_type',
    1 => 'parent_type',
    2 => 'mode',
  );
  $export['bundle_inherit_frontpage_image_slideshow'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_frontpage_image_slideshow';
  $strongarm->value = 0;
  $export['comment_anonymous_frontpage_image_slideshow'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_frontpage_image_slideshow';
  $strongarm->value = 0;
  $export['comment_default_mode_frontpage_image_slideshow'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_frontpage_image_slideshow';
  $strongarm->value = '50';
  $export['comment_default_per_page_frontpage_image_slideshow'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_frontpage_image_slideshow';
  $strongarm->value = 0;
  $export['comment_form_location_frontpage_image_slideshow'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_frontpage_image_slideshow';
  $strongarm->value = '1';
  $export['comment_frontpage_image_slideshow'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_frontpage_image_slideshow';
  $strongarm->value = '0';
  $export['comment_preview_frontpage_image_slideshow'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_frontpage_image_slideshow';
  $strongarm->value = 0;
  $export['comment_subject_field_frontpage_image_slideshow'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'date_popup_authored_enabled_frontpage_image_slideshow';
  $strongarm->value = 0;
  $export['date_popup_authored_enabled_frontpage_image_slideshow'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'date_popup_authored_format_frontpage_image_slideshow';
  $strongarm->value = 'm/d/Y - H:i';
  $export['date_popup_authored_format_frontpage_image_slideshow'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'date_popup_authored_year_range_frontpage_image_slideshow';
  $strongarm->value = '3';
  $export['date_popup_authored_year_range_frontpage_image_slideshow'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_enable_revisions_page_node_frontpage_image_slideshow';
  $strongarm->value = 1;
  $export['diff_enable_revisions_page_node_frontpage_image_slideshow'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_show_preview_changes_node_frontpage_image_slideshow';
  $strongarm->value = 1;
  $export['diff_show_preview_changes_node_frontpage_image_slideshow'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_view_mode_preview_node_frontpage_image_slideshow';
  $strongarm->value = 'full';
  $export['diff_view_mode_preview_node_frontpage_image_slideshow'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__frontpage_image_slideshow';
  $strongarm->value = array(
    'view_modes' => array(
      'teaser' => array(
        'custom_settings' => TRUE,
      ),
      'featured' => array(
        'custom_settings' => TRUE,
      ),
      'mini_teaser' => array(
        'custom_settings' => TRUE,
      ),
      'most_recent' => array(
        'custom_settings' => TRUE,
      ),
      'full' => array(
        'custom_settings' => FALSE,
      ),
      'rss' => array(
        'custom_settings' => FALSE,
      ),
      'search_index' => array(
        'custom_settings' => FALSE,
      ),
      'search_result' => array(
        'custom_settings' => FALSE,
      ),
      'diff_standard' => array(
        'custom_settings' => FALSE,
      ),
      'token' => array(
        'custom_settings' => FALSE,
      ),
    ),
    'extra_fields' => array(
      'form' => array(
        'locations' => array(
          'weight' => '30',
        ),
        'title' => array(
          'weight' => '-5',
        ),
        'path' => array(
          'weight' => '30',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__frontpage_image_slideshow'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_frontpage_image_slideshow';
  $strongarm->value = '0';
  $export['language_content_type_frontpage_image_slideshow'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_frontpage_image_slideshow';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_frontpage_image_slideshow'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_frontpage_image_slideshow';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_frontpage_image_slideshow'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_frontpage_image_slideshow';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_frontpage_image_slideshow'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_frontpage_image_slideshow';
  $strongarm->value = '0';
  $export['node_preview_frontpage_image_slideshow'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_frontpage_image_slideshow';
  $strongarm->value = 0;
  $export['node_submitted_frontpage_image_slideshow'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'panelizer_defaults_node_frontpage_image_slideshow';
  $strongarm->value = array(
    'status' => 1,
    'view modes' => array(
      'page_manager' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
      'default' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
      'teaser' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
      'featured' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
      'mini_teaser' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
      'most_recent' => array(
        'status' => 0,
        'default' => 0,
        'choice' => 0,
      ),
    ),
  );
  $export['panelizer_defaults_node_frontpage_image_slideshow'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'save_continue_frontpage_image_slideshow';
  $strongarm->value = 'Save and add fields';
  $export['save_continue_frontpage_image_slideshow'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'site_frontpage';
  $strongarm->value = 'home';
  $export['site_frontpage'] = $strongarm;

  return $export;
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function pece_frontpage_slideshow_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer panelizer node frontpage_image_slideshow breadcrumbs'.
  $permissions['administer panelizer node frontpage_image_slideshow breadcrumbs'] = array(
    'name' => 'administer panelizer node frontpage_image_slideshow breadcrumbs',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node frontpage_image_slideshow content'.
  $permissions['administer panelizer node frontpage_image_slideshow content'] = array(
    'name' => 'administer panelizer node frontpage_image_slideshow content',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node frontpage_image_slideshow context'.
  $permissions['administer panelizer node frontpage_image_slideshow context'] = array(
    'name' => 'administer panelizer node frontpage_image_slideshow context',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node frontpage_image_slideshow defaults'.
  $permissions['administer panelizer node frontpage_image_slideshow defaults'] = array(
    'name' => 'administer panelizer node frontpage_image_slideshow defaults',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node frontpage_image_slideshow layout'.
  $permissions['administer panelizer node frontpage_image_slideshow layout'] = array(
    'name' => 'administer panelizer node frontpage_image_slideshow layout',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node frontpage_image_slideshow overview'.
  $permissions['administer panelizer node frontpage_image_slideshow overview'] = array(
    'name' => 'administer panelizer node frontpage_image_slideshow overview',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'administer panelizer node frontpage_image_slideshow settings'.
  $permissions['administer panelizer node frontpage_image_slideshow settings'] = array(
    'name' => 'administer panelizer node frontpage_image_slideshow settings',
    'roles' => array(),
    'module' => 'panelizer',
  );

  // Exported permission: 'create frontpage_image_slideshow content'.
  $permissions['create frontpage_image_slideshow content'] = array(
    'name' => 'create frontpage_image_slideshow content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any frontpage_image_slideshow content'.
  $permissions['delete any frontpage_image_slideshow content'] = array(
    'name' => 'delete any frontpage_image_slideshow content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own frontpage_image_slideshow content'.
  $permissions['delete own frontpage_image_slideshow content'] = array(
    'name' => 'delete own frontpage_image_slideshow content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any frontpage_image_slideshow content'.
  $permissions['edit any frontpage_image_slideshow content'] = array(
    'name' => 'edit any frontpage_image_slideshow content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own frontpage_image_slideshow content'.
  $permissions['edit own frontpage_image_slideshow content'] = array(
    'name' => 'edit own frontpage_image_slideshow content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'set frontpage_image_slideshow published on date'.
  $permissions['set frontpage_image_slideshow published on date'] = array(
    'name' => 'set frontpage_image_slideshow published on date',
    'roles' => array(),
    'module' => 'publication_date',
  );

  return $permissions;
}

/**
 * Implements hook_defaultconfig_views_default_views().
 */
function pece_frontpage_slideshow_defaultconfig_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'frontpage_image_slider';
  $view->description = '';
  $view->tag = 'PECE';
  $view->base_table = 'node';
  $view->human_name = 'PECE Frontpage Image Slider';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '8';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Image */
  $handler->display->display_options['fields']['field_pece_slideshow_image']['id'] = 'field_pece_slideshow_image';
  $handler->display->display_options['fields']['field_pece_slideshow_image']['table'] = 'field_data_field_pece_slideshow_image';
  $handler->display->display_options['fields']['field_pece_slideshow_image']['field'] = 'field_pece_slideshow_image';
  $handler->display->display_options['fields']['field_pece_slideshow_image']['label'] = '';
  $handler->display->display_options['fields']['field_pece_slideshow_image']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_pece_slideshow_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_pece_slideshow_image']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_pece_slideshow_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_pece_slideshow_image']['settings'] = array(
    'image_style' => 'pece_frontpage_image_style',
    'image_link' => '',
  );
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'frontpage_image_slideshow' => 'frontpage_image_slideshow',
  );

  /* Display: Content pane */
  $handler = $view->new_display('panel_pane', 'Content pane', 'panel_pane_1');

  /* Display: Frontpage slideshow short */
  $handler = $view->new_display('panel_pane', 'Frontpage slideshow short', 'slideshow_front_short');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Image link */
  $handler->display->display_options['fields']['field_pece_slideshow_img_link_1']['id'] = 'field_pece_slideshow_img_link_1';
  $handler->display->display_options['fields']['field_pece_slideshow_img_link_1']['table'] = 'field_data_field_pece_slideshow_img_link';
  $handler->display->display_options['fields']['field_pece_slideshow_img_link_1']['field'] = 'field_pece_slideshow_img_link';
  $handler->display->display_options['fields']['field_pece_slideshow_img_link_1']['label'] = '';
  $handler->display->display_options['fields']['field_pece_slideshow_img_link_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_pece_slideshow_img_link_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_pece_slideshow_img_link_1']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_pece_slideshow_img_link_1']['type'] = 'link_absolute';
  /* Field: Content: Image */
  $handler->display->display_options['fields']['field_pece_slideshow_image']['id'] = 'field_pece_slideshow_image';
  $handler->display->display_options['fields']['field_pece_slideshow_image']['table'] = 'field_data_field_pece_slideshow_image';
  $handler->display->display_options['fields']['field_pece_slideshow_image']['field'] = 'field_pece_slideshow_image';
  $handler->display->display_options['fields']['field_pece_slideshow_image']['label'] = '';
  $handler->display->display_options['fields']['field_pece_slideshow_image']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_pece_slideshow_image']['alter']['path'] = '[field_pece_slideshow_img_link_1]';
  $handler->display->display_options['fields']['field_pece_slideshow_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_pece_slideshow_image']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_pece_slideshow_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_pece_slideshow_image']['settings'] = array(
    'image_style' => 'pece_frontpage_image_short',
    'image_link' => '',
  );
  /* Field: Content: Image link */
  $handler->display->display_options['fields']['field_pece_slideshow_img_link']['id'] = 'field_pece_slideshow_img_link';
  $handler->display->display_options['fields']['field_pece_slideshow_img_link']['table'] = 'field_data_field_pece_slideshow_img_link';
  $handler->display->display_options['fields']['field_pece_slideshow_img_link']['field'] = 'field_pece_slideshow_img_link';
  $handler->display->display_options['fields']['field_pece_slideshow_img_link']['label'] = '';
  $handler->display->display_options['fields']['field_pece_slideshow_img_link']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_pece_slideshow_img_link']['element_wrapper_type'] = 'div';
  $handler->display->display_options['fields']['field_pece_slideshow_img_link']['element_wrapper_class'] = 'slideshow-image-link';
  $handler->display->display_options['fields']['field_pece_slideshow_img_link']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_pece_slideshow_img_link']['field_api_classes'] = TRUE;
  $translatables['frontpage_image_slider'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Content pane'),
    t('View panes'),
    t('Frontpage slideshow short'),
  );
  $export['frontpage_image_slider'] = $view;

  return $export;
}
