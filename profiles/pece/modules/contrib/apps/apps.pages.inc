<?php
/**
 * @file
 * The page callbacks for the Apps module.
 */

/**
 * Title for the App Server
 */
function apps_server_title($server) {
  return t("@title Apps", array('@title' => $server['title']));
}

/**
 * Title for the app detail page
 */
function apps_app_title($app) {
  return t("@title Details", array('@title' => $app['name']));
}

/**
 * Verify's token or presents a confirm form.
 */
function apps_display_confirm_form($question, $unique) {
  // Can't easily pass query args to batch, so allow if install next is set to
  // current page, as we set that.
  if ((isset($_SESSION['apps_install_next']) && $_SESSION['apps_install_next']  == $_GET['q'])
    || (isset($_REQUEST['token']) && drupal_valid_token($_REQUEST['token'], $unique))) {
    return FALSE;
  }
  else {
    $path = array($_GET['q'], array('query' => array('token' => drupal_get_token($unique))));
    return drupal_get_form('apps_confirm_form', $question, $path);
  }
}

/**
 * Confirms the user wants to do the action.
 */
function apps_confirm_form($form, $form_state, $question, $path) {
  $form['#redirect_path'] = $path;
  return confirm_form($form, $question, 'admin/apps', t('This action can be undone.'));
}

/**
 * Redirects user to same path but with token.
 */
function apps_confirm_form_submit($form, &$form_state) {
  $form_state['redirect'] = $form['#redirect_path'];
}

/**
 * Callback for the market page
 *
 * If there is only one server, go directly to it. Otherwise, list 'em.
 */
function apps_market_page() {
  apps_include('manifest');
  $servers = apps_servers();

  // If there is only one, go directly to it
  if (isset($servers) && count($servers) === 1) {
    return drupal_goto('admin/apps/' . key($servers));
  }

  foreach ($servers as &$server) {
    $server['#theme'] = 'apps_server_item';
  }
  return theme('apps_market_page', array('servers' => $servers));
}

/**
 * Callback list off all apps
 */
function apps_install_page($server_name) {
  apps_include('manifest');
  $element = array(
    '#theme' => 'apps_install_page',
  );
  //find all apps
  try {
    $apps = apps_apps($server_name, array(), TRUE);
    if (!empty($apps)) {
      $element['apps'] = $apps;
      $featured_apps = apps_apps($server_name , array('featured' => TRUE)) ;
      if (!empty($featured_apps)) {
        $element['featured_app'] = array_pop($featured_apps);
      }
    }
  }
  catch (Exception $e) {
    drupal_set_message(t("There was the following error: @msg", array('@msg' => $e->getMessage())), 'warning');
  }
  return $element;
}

/**
 * Callback for listing of installed apps
 */
function apps_manage_page($server) {
  apps_include('manifest');
  $element = array(
    '#theme' => 'apps_manage_page',
  );
  // find all installed apps
  try {
    $apps = apps_apps($server, array("installed" => TRUE), TRUE);
    $element['apps'] = $apps;
  }
  catch (Exception $e) {
    drupal_set_message(t("There was the following error: @error", array('@error' => $e->getMessage())), 'warning');
  }
  return $element;
}

/**
 * Callback for listing of installed apps that have available updates
 */
function apps_update_page($server) {
  apps_include('manifest');
  $element = array(
     '#theme'=> 'apps_update_page',
   );
  // find all installed apps
  try {
    $apps = apps_apps($server, array("upgradeable" => TRUE), TRUE);
    $element['apps'] = $apps;
  }
  catch (Exception $e) {
    drupal_set_message(t("There was the following error - @error", array('@error' => $e->getMessage())), 'warning');
  }
  return $element;
}

/**
 * Callpage for apps catelog page, an .md formatted app listing.
 */
function apps_catalog_page($server) {
  apps_include('manifest');
  drupal_add_http_header('Content-Type', 'text/x-markdown');
  $render = array(
    '#theme' => 'apps_catalog_page',
    '#apps' => apps_apps($server, array(), FALSE),
    '#server' => $server,
  );
  print drupal_render($render);
}

/**
 * Callback for app config page
 */
function apps_app_config_page($app) {
  apps_include('manifest');
  $element = array();
  if (apps_app_callback($app, "demo content enable callback")) {
    $element['demo'] = drupal_get_form('apps_demo_content_form', $app);
  }

  // Check for a status table
  if ($data_callback = apps_app_callback($app, "status callback")) {
    $data = $data_callback();
    $header = isset($data['header']) ? $data['header'] : NULL;
    $items = isset($data['items']) ? $data['items'] : array();
    $element['status'] = array(
      '#type' => 'fieldset',
      '#title' => t('Status'),
      'table' => apps_app_status_report($items, $header),
    );
  }
  if ($form = apps_app_callback($app, "configure form")) {
    $element['config'] =  drupal_get_form($form);
  }
  if (!empty($app['permissions'])) {
    if (user_access('administer permissions')) {
      $element['permissions'] = drupal_get_form('apps_admin_permissions', $app);
    }
    else {
      $element['permissions']['#markup'] = t('This app has permissions that can be customized but you currently do not have permission to configure them. Please contact an administrator if this is in error.');
    }
  }
  return $element;
}

/**
 * Copy of user_admin_permissions() but for specific permissions.
 */
function apps_admin_permissions($form, $form_state, $app) {
  $form['#app'] = $app;
  $form['#theme'] = 'user_admin_permissions';
  // Retrieve role names for columns.
  $role_names = user_roles();
  // Fetch permissions for all roles or the one selected role.
  $role_permissions = user_role_permissions($role_names);

  // Store $role_names for use when saving the data.
  $form['role_names'] = array(
    '#type' => 'value',
    '#value' => $role_names,
  );
  $permissions = module_invoke_all('permission');
  $hide_descriptions = system_admin_compact_mode();
  $options = array();

  foreach ($app['permissions'] as $perm => $default_roles) {
    if (!empty($permissions[$perm])) {
      $perm_item = $permissions[$perm];
      // Fill in default values for the permission.
      $perm_item += array(
        'description' => '',
        'restrict access' => FALSE,
        'warning' => !empty($perm_item['restrict access']) ? t('Warning: Give to trusted roles only; this permission has security implications.') : '',
      );
      $options[$perm] = '';
      $form['permission'][$perm] = array(
        '#type' => 'item',
        '#markup' => $perm_item['title'],
        '#description' => theme('user_permission_description', array('permission_item' => $perm_item, 'hide' => $hide_descriptions)),
      );
      foreach ($role_names as $rid => $name) {
        // Builds arrays for checked boxes for each role
        if (isset($role_permissions[$rid][$perm])) {
          $status[$rid][] = $perm;
        }
      }
    }
  }

  // Have to build checkboxes here after checkbox arrays are built
  foreach ($role_names as $rid => $name) {
    $form['checkboxes'][$rid] = array(
      '#type' => 'checkboxes',
      '#options' => $options,
      '#default_value' => isset($status[$rid]) ? $status[$rid] : array(),
      '#attributes' => array('class' => array('rid-' . $rid)),
    );
    $form['role_names'][$rid] = array(
      '#markup' => check_plain($name),
      '#tree' => TRUE,
    );
  }

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save permissions'),
    '#submit' => array(
      'user_admin_permissions_submit',
    ),
  );
  $form['actions']['revert'] = array(
    '#type' => 'submit',
    '#value' => t('Revert to defaults'),
    '#submit' => array(
      'apps_admin_permissions_revert_submit',
    ),
  );
  $form['#attached']['js'][] = drupal_get_path('module', 'user') . '/user.permissions.js';

  return $form;
}

/**
 * Reverts the permission to default.
 */
function apps_admin_permissions_revert_submit($form, &$form_state) {
  apps_app_configure_permissions($form['#app']);
  drupal_set_message(t('The permissions have been reverted.'));
}

/**
 * Callback for the app detail page
 */
function apps_app_details_page($app) {
  $app['#theme'] = 'apps_app_page';
  return $app;
}

/**
 * Callback for app install
 * TODO: check to see the app is install able and then install
 * TODO: should goto config page but pass on the current destination
 * NOTE: it is expected that this page would be called with a drupal desination set
 */
function apps_app_install($app) {
  $token_name = 'install-' . $app['machine_name'];
  if ($confirm_form = apps_display_confirm_form(t('Are you sure you want to install @name?', array('@name' => $app['name'])), $token_name)) {
    return $confirm_form;
  }
  apps_include('installer');
  require_once DRUPAL_ROOT . '/includes/authorize.inc';
  $action = arg(5);
  switch ($action) {
    case 'install':
      $_SESSION['apps_install_next'] = apps_app_page_path($app, 'enable');
      $install = apps_install_downloads();
      // Error encountered during install.
      if ($install === FALSE) {
        drupal_goto(apps_app_page_path($app));
      }
      else {
        return $install;
      }
    default:
      // Clear cache so downloads new files.
      apps_clear_update_disk_cache();
      // Adds an extra path element to avoid an endless loop. If we check for
      // install at arg(4) we are usually there. So here we add an install at
      // arg(5) and that will get caught in the case above ^-^
      $_SESSION['apps_install_next'] = apps_app_page_path($app, 'install/install');
      apps_download_apps($app);
      break;
  }
}

/**
 * Callback for the enable action
 *
 * Enables the app and got to config page if it exists
 */
function apps_app_enable($app) {
  $token_name = 'enable-' . $app['machine_name'];
  if ($confirm_form = apps_display_confirm_form(t('Are you sure you want to enable @name?', array('@name' => $app['name'])), $token_name)) {
    return $confirm_form;
  }
  $next = apps_app_page_path($app);
  if ($app['status'] === APPS_DISABLED) {
    $success = module_enable(array($app['machine_name']), TRUE);
    if ($success) {
      drupal_flush_all_caches();
      drupal_set_message(t("Enabled @name app", array('@name' => $app['name'])));
      if (!$app['disabled'] && ($cb = apps_app_callback($app, "post install callback"))) {
        $cb($app);
      }
      if (apps_app_access('administer apps', $app, 'configure')) {
        $next = apps_app_page_path($app, 'configure');
      }
    }
    else {
      drupal_set_message(t("@name App Not Enabled", array('@name' => $app['name'])));
    }
  }
  elseif ($app['status'] === APPS_ENABLED) {
    drupal_set_message(t("@name App already Enabled", array('@name' => $app['name'])), 'warning');
  }
  elseif ($app['status'] === APPS_INCOMPATIBLE) {
    $incompatible = array();
    foreach ($app['dependencies'] as $depedency_name => $depedency) {
      if ($depedency['incompatible']) {
        $incompatible[] = $depedency_name;
      }
    }
    drupal_set_message(t("@name App not compatible (incompatible dependencies: @dependencies)", array('@name' => $app['name'], '@dependencies' => implode(', ', $incompatible))), 'error');
  }
  elseif ($app['status'] === APPS_INSTALLABLE) {
    $missing = array();
    foreach ($app['dependencies'] as $depedency_name => $depedency) {
      if (empty($depedency['installed'])) {
        $missing[] = $depedency_name;
      }
    }
    drupal_set_message(t("@name App has missing depedencies (missing depedencies: @dependencies)", array('@name' => $app['name'], '@dependencies' => implode(', ', $missing))), 'error');
  }
  unset($_SESSION['apps_install_next']);
  drupal_goto($next);
}

/**
 * Callback for app disable
 */
function apps_app_disable($app) {
  $token_name = 'disable-' . $app['machine_name'];
  if ($confirm_form = apps_display_confirm_form(t('Are you sure you want to disable @name?', array('@name' => $app['name'])), $token_name)) {
    return $confirm_form;
  }
  // Force the user to disable demo content before disabling the app
  if (($is_cb = apps_app_callback($app, "demo content enabled callback")) &&
    $is_cb($app)) {
    $next = apps_app_page_path($app, 'configure');
    drupal_set_message(t("Please disable demo content before disabling the app"));
    drupal_goto($next);
  }

  module_disable(array($app['machine_name']));
  drupal_flush_all_caches();
  drupal_set_message(t("Disabled @name app", array('@name' => $app['name'])));
  $next = apps_app_page_path($app);
  drupal_goto($next);
}

/**
 * Callback for app uninstall
 */
function apps_app_uninstall($app) {
  $token_name = 'uninstall-' . $app['machine_name'];
  if ($confirm_form = apps_display_confirm_form(t('Are you sure you want to uninstall @name?', array('@name' => $app['name'])), $token_name)) {
    return $confirm_form;
  }
  require_once DRUPAL_ROOT . '/includes/install.inc';
  $uninstall[] = $app['machine_name'];
  if (isset($app['demo content module']) && $app['demo content module']) {
    array_unshift($uninstall, $app['demo content module']);
  }

  if (drupal_uninstall_modules($uninstall)) {
    drupal_flush_all_caches();
    drupal_set_message(t("Uninstalled @name app", array('@name' => $app['name'])));
  }
  else {
    drupal_set_message(t("Uninstalling @name app failed. Please ensure all modules that depend on this module are also uninstalled", array('@name' => $app['name'])));
   }
  $next = apps_app_page_path($app);
  drupal_goto($next);
}


/**
 * Callback for app update.
 */
function apps_app_update($app) {
  $token_name = 'update-' . $app['machine_name'];
  if ($confirm_form = apps_display_confirm_form(t('Are you sure you want to update @name?', array('@name' => $app['name'])), $token_name)) {
    return $confirm_form;
  }
  // Redownload apps then run any updates.
  apps_include('installer');
  require_once DRUPAL_ROOT . '/includes/authorize.inc';
  $action = arg(5);
  switch ($action) {
    case 'updatedb';
      drupal_set_message($_SESSION['authorize_results']['page_message']['message'], $_SESSION['authorize_results']['page_message']['type']);
      unset($_SESSION['apps_install_next']);
      drupal_goto(apps_app_page_path($app));
      break;
    case 'update':
      $_SESSION['apps_install_next'] = apps_app_page_path($app, 'update/updatedb');
      return apps_install_downloads();
    default:
      // Need to clear update cache or it'll reuse all downloads.
      apps_clear_update_disk_cache();
      // Adds an extra path element to avoid an endless loop. If we check for
      // install at arg(4) we are usually there. So here we add an install at
      // arg(5) and that will get caught in the case above ^-^
      $_SESSION['apps_install_next'] = apps_app_page_path($app, 'update/update');
      apps_download_apps($app);
      break;
  }
}

/**
 * Admin settings form for Apps.
 */
function apps_settings_form() {
  $form = array();
  $form['apps_offline_mode'] = array(
    '#title' => t('Apps Offline Mode'),
    '#description' => t('Does not try to make external requests to app servers. Assumes all apps are already locally stored.'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('apps_offline_mode', FALSE),
  );
  $form['apps_enable_dev_console'] = array(
    '#title' => t('Enable Development Console'),
    '#description' => t('Allows local Apps to be displayed in a development app server.'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('apps_enable_dev_console', FALSE),
  );
  $form['apps_allow_voting'] = array(
    '#title' => t('Allow Voting'),
    '#description' => t('Allow users who can install apps to also rate them.  Requires that the appserver is running the appserver module.'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('apps_allow_voting', FALSE),
  );
  $form['apps_install_path'] = array(
    '#title' => t('Apps Install Path'),
    '#description' => t('For best practice, you can change the path to sites/all/modules/contrib.'),
    '#type' => 'textfield',
    '#default_value' => variable_get('apps_install_path', APPS_INSTALL_PATH),
  );
  $form['apps_grouping_mode'] = array(
    '#title' => t('Allow Apps Grouping'),
    '#description' => t('Allow grouping of Apps according to packages (as defined in app information via "package" key.)'),
    '#type' => 'checkbox',
    '#default_value'=> variable_get('apps_grouping_mode', FALSE),
  );
  $form['apps_grouping_vertical'] = array(
    '#title' => t('Use vertical tabs for Apps Grouping'),
    '#description' => t('Put the groupings into vertical tabs instead of collapsible fieldsets.'),
    '#type' => 'checkbox',
    '#default_value'=> variable_get('apps_grouping_vertical', TRUE),
  );

  $form = system_settings_form($form);
  $form['#submit'][] = 'apps_settings_form_submit';
  return $form;
}

/**
 * Once the settings are saved, flush all caches. This will trigger the
 * Apps dev server to appear in the Apps console.
 */
function apps_settings_form_submit() {
  drupal_flush_all_caches();
}


/**
 * apps_app_status_report()
 *
 * @PARAM items: an array of items to display the keys of which should be the
 * keys of the $header param or use the default.
 * The default are severity, title, description and action.  Severity is expected to be
 * an int in (REQUIREMENT_INFO, REQUIREMENT_OK, REQUIREMENT_WARNING, REQUIREMENT_ERROR)
 * @PARAM header: an array of header titles, the keys of which should match the keys in $items
 * there is a default for this value
 *
 * @RETURN: a render array for the status report table
 */
function apps_app_status_report($items, $header = NULL) {
  if (!isset($header)) {
    $header = array(
      'severity' => 'Status',
      'title' => 'Title',
      'description' => 'Description',
      'action' => 'Action',
    );
  }
  $rows = array();
  $severities = array(
    REQUIREMENT_INFO => array(
      'title' => t('Info'),
      'class' => 'info',
      'image' => array('#theme' => "image", "#path" => "misc/message-24-info.png", "#alt" => "Info"),
    ),
    REQUIREMENT_OK => array(
      'title' => t('OK'),
      'class' => 'ok',
      'image' => array('#theme' => "image", "#path" => "misc/message-24-ok.png", "#alt" => "Ok"),
    ),
    REQUIREMENT_WARNING => array(
      'title' => t('Warning'),
      'class' => 'warning',
      'image' => array('#theme' => "image", "#path" => "misc/message-24-warning.png", "#alt" => "Warning"),
    ),
    REQUIREMENT_ERROR => array(
      'title' => t('Error'),
      'class' => 'error',
      'image' => array('#theme' => "image", "#path" => "misc/message-24-error.png", "#alt" => "Error"),
    ),
  );
  foreach ($items as $item) {
    $row = array();
    foreach (array_keys($header) as $key) {
      if (isset($item[$key])) {
        if ($key =='severity') {
          $row['data'][] = render($severities[$item[$key]]['image']);
          $row['class'][] = $severities[$item[$key]]['class'];
        }
        elseif ($key == 'action') {
          $row['data'][] = theme('item_list', array("items" => $item[$key]));

        }
        else {
          $row['data'][] = $item[$key];
        }
      }
      else {
          $row['data'][] = '';
      }
    }
    $rows[] = $row;
  }
  return array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
  );
}

/**
 * Provide development information.
 */
function apps_devel_load_array($type, $array) {
  module_load_include('pages.inc', 'devel');
  // Wth krumo, array is fine, but devel_print_object needs an object.
  return devel_load_object($type, has_krumo() ? $array : (object) $array);
}
