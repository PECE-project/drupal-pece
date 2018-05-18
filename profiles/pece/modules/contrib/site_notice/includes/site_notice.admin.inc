<?php
/**
 * @file
 * Admin interface for Site Notices.
 *
 * Based on model.admin.inc from Entity Model module.
 */
/**
 * UI controller.
 */
class SiteNoticeUIController extends EntityDefaultUIController {
  /**
   * Overrides hook_menu().
   */
  public function hook_menu() {
    $id_count = count(explode('/', $this->path));
    $wildcard = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : '%' . $this->entityType;
    $modpath = drupal_get_path('module', $this->entityInfo['module']);

    // Base item
    $items[$this->path] = array(
      'title' => 'Site Notices',
      'description' => 'Add edit and update site notices.',
      'page callback' => 'system_admin_menu_block_page',
      'access arguments' => array('access administration pages'),
      'file path' => drupal_get_path('module', 'system'),
      'file' => 'system.admin.inc',
    );

    // Add a notice
    $items[$this->path . '/add'] = array(
      'title' => 'Add a Site Notice',
      'page callback' => 'site_notice_form_wrapper',
      'page arguments' => array(site_notice_create()),
      'access callback' => 'site_notice_access',
      'access arguments' => array('create'),
      'file' => 'includes/site_notice.admin.inc',
      'type' => MENU_NORMAL_ITEM,
      'file path' => $modpath,
    );

    // Loading and editing site notice entities
    $items[$this->path . "/$wildcard"] = array(
      'page callback' => 'site_notice_form_wrapper',
      'page arguments' => array($id_count),
      'access callback' => 'site_notice_access',
      'access arguments' => array('view', $id_count),
      'weight' => 0,
      'file' => 'includes/site_notice.admin.inc',
      'file path' => $modpath,
    );
    $items[$this->path . "/$wildcard" . '/view'] = array(
      'title' => 'View',
      'access callback' => 'site_notice_access',
      'access arguments' => array('view', $id_count),
      'type' => MENU_DEFAULT_LOCAL_TASK,
      'weight' => -10,
    );
    $items[$this->path . "/$wildcard" . '/edit'] = array(
      'title' => 'Edit',
      'type' => MENU_LOCAL_TASK,
      'weight' => -10,
      'access callback' => 'site_notice_access',
      'access arguments' => array('edit', $id_count),
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
    );

    // Delete a notice
    $items[$this->path . "/$wildcard" . '/delete'] = array(
      'title' => 'Delete',
      'page callback' => 'site_notice_delete_form_wrapper',
      'page arguments' => array($id_count),
      'access callback' => 'site_notice_access',
      'access arguments' => array('edit', $id_count),
      'type' => MENU_LOCAL_TASK,
      'weight' => 10,
      'file' => 'includes/site_notice.admin.inc',
      'file path' => $modpath,
    );

    // Enable a notice
    $items[$this->path . "/$wildcard" . '/enable'] = array(
      'title' => 'Enable',
      'page callback' => 'site_notice_enable_notice',
      'page arguments' => array($id_count, TRUE),
      'access callback' => 'site_notice_access',
      'access arguments' => array('edit', $id_count),
      'type' => MENU_LOCAL_TASK,
    );

    // Disable a notice
    $items[$this->path . "/$wildcard" . '/disable'] = array(
      'title' => 'Disable',
      'page callback' => 'site_notice_disable_notice',
      'page arguments' => array($id_count, FALSE),
      'access callback' => 'site_notice_access',
      'access arguments' => array('edit', $id_count),
      'type' => MENU_LOCAL_TASK,
      'context' => MENU_CONTEXT_INLINE,
    );

    // Dismiss a notice
    $items["site-notices/$wildcard/dismiss"] = array(
      'title' => 'Dismiss',
      'page callback' => 'site_notice_dismiss_notice',
      'page arguments' => array(1),
      'access callback' => TRUE,
      'type' => MENU_CALLBACK,
    );

    // Menu item for viewing notices
    $items["site-notices/$wildcard"] = array(
      //'title' => 'Title',
      'title callback' => 'site_notice_page_title',
      'title arguments' => array(1),
      'page callback' => 'site_notice_page_view',
      'page arguments' => array(1),
      'access callback' => 'site_notice_access',
      'access arguments' => array('view', 2),
      'type' => MENU_CALLBACK,
    );

    // Admin pages
    $items['admin/config/administration/site-notice'] = array(
      'title' => 'Site Notice settings',
      'description' => 'Configure site notice settings, behaviors and fields.',
      'page callback' => 'drupal_get_form',
      'page arguments' => array('site_notice_admin_settings'),
      'access arguments' => array('administer site notices'),
      'file' => 'includes/site_notice.admin.inc',
      'file path' => $modpath,
      'weight' => -10,
    );
    $items['admin/config/administration/site-notice/settings'] = array(
      'title' => 'Settings',
      'type' => MENU_DEFAULT_LOCAL_TASK,
      'weight' => -10,
    );

    return $items;
  }

  /**
   * Create the markup for the add Notice Entities page within the class
   * so it can easily be extended/overriden.
   */
  public function addPage() {
    return drupal_get_form('site_notice_edit_form');
  }
}

/**
 * Form callback wrapper: create or edit a notice.
 *
 * @param $site_notice
 *   The site notice object being edited by this form.
 *
 * @see site_notice_edit_form()
 */
function site_notice_form_wrapper($site_notice) {
  // Add the breadcrumb for the form's location.
  site_notice_set_breadcrumb();
  return drupal_get_form('site_notice_edit_form', $site_notice);
}

/**
 * Form callback wrapper: delete a site notice.
 *
 * @param $site_notice
 *   The site notice object being edited by this form.
 *
 * @see site_notice_edit_form()
 */
function site_notice_delete_form_wrapper($site_notice) {
  // Add the breadcrumb for the form's location.
  //site_notice_set_breadcrumb();
  return drupal_get_form('site_notice_delete_form', $site_notice);
}

/**
 * Form callback: create or edit a site notice.
 *
 * @param $site_notice
 *   The site notice object to edit or for a create form an empty site notice
 *   object.
 */
function site_notice_edit_form($form, &$form_state, $site_notice) {
  // Add the default field elements.
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => isset($site_notice->title) ? $site_notice->title : '',
    '#maxlength' => 255,
    '#required' => TRUE,
    '#weight' => -20,
  );
  $form['name'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($site_notice->name) ? $site_notice->name : '',
    '#maxlength' => 32,
    '#machine_name' => array(
      'exists' => 'site_notice_name_exists',
      'source' => array('title'),
    ),
  );

  // Settings
  $form['settings'] = array(
    '#type' => 'vertical_tabs',
    '#tree' => TRUE,
    '#attached' => array(
      'js' => array(drupal_get_path('module', 'site_notice') . '/js/site-notice-settings.js'),
    ),
  );

  // Status
  $form['settings']['status'] = array(
    '#type' => 'fieldset',
    '#title' => t('Status'),
    '#collapsible' => TRUE,
    '#weight' => 1,
  );
  $form['settings']['status']['status'] = array(
    '#type' => 'radios',
    '#title' => t('Status'),
    '#description' => t('Choose the placement of the notice.'),
    '#options' => SiteNoticeEntity::getOptions('status'),
    '#default_value' => (isset($site_notice->status) ? $site_notice->status : SiteNoticeEntity::TOP),
  );

  $form['settings']['status']['block'] = array(
    '#type' => 'checkbox',
    '#title' => t('Expose as Block'),
    '#description' => t('Make this notice available as a block.'),
    '#default_value' => (isset($site_notice->block) ? ($site_notice->block != SiteNoticeEntity::BLOCK_NONE) : 0),
    '#states' => array(
      'invisible' => array(
        ':input[name="settings[status][status]"]' => array('value' => SiteNoticeEntity::DISABLED),
      ),
    ),
  );

  $form['settings']['status']['warning'] = array(
    '#type' => 'item',
    '#title' => t('Note:'),
    '#markup' => t('Site Notice path and role filters DO NOT apply to Site Notice blocks, only the Top and Bottom displays.  Use the default block settings to determine where the Site Notice blocks are placed on your pages.'),
    '#states' => array(
      'visible' => array(
        ':input[name="settings[status][block]"]' => array('checked' => TRUE),
      ),
      'invisible' => array(
        ':input[name="settings[status][status]"]' => array('value' => SiteNoticeEntity::DISABLED),
      ),
    ),
  );

  // Link Text
  $form['settings']['behavior'] = array(
    '#type' => 'fieldset',
    '#title' => t('Behavior'),
    '#collapsible' => TRUE,
    '#weight' => 2,
  );
  $form['settings']['behavior']['dismiss'] = array(
    '#type' => 'radios',
    '#title' => t('Dismissal'),
    '#description' => t('At what level can a user dismiss the notice?') . '<br />' .
                      t('<strong>Dismiss per Session:</strong> The notice may be dismissed for the duration of the user\'s session.') . '<br />' .
                      t('<strong>Dismiss per Notice:</strong> The notice may be dismissed permanently unless it is disabled and re-enabled.') . '<br />' .
                      t('<strong>Non-Dismissable:</strong> The notice cannot be dismissed by the user.') . '<br />',
    '#options' => SiteNoticeEntity::getOptions('dismissal'),
    '#default_value' => (isset($site_notice->settings['behavior']['dismiss']) ? $site_notice->settings['behavior']['dismiss'] : SiteNoticeEntity::DISMISS_SESS),
  );
  $form['settings']['behavior']['dismiss_text'] = array(
    '#type' => 'textfield',
    '#title' => t('Link Text'),
    '#description' => t('Provide the text for the dismissal link.'),
    '#default_value' => (isset($site_notice->settings['behavior']['dismiss_text']) ? $site_notice->settings['behavior']['dismiss_text'] : t('Dismiss')),
    '#states' => array(
      'invisible' => array(
        ':input[name="settings[behavior][dismiss]"]' => array('value' => SiteNoticeEntity::DISMISS_NONE),
      ),
    ),
  );

  // Path filter
  $form['settings']['path_filter'] = array(
    '#type' => 'fieldset',
    '#title' => t('Filter by Path'),
    '#collapsible' => TRUE,
    '#weight' => 3,
  );
  $form['settings']['path_filter']['note'] = array(
    '#type' => 'item',
    '#title' => t('Note:'),
    '#markup' => t('Only applies to Top and Bottom displays.'),
    '#states' => array(
      'visible' => array(
        ':input[name="settings[status][block]"]' => array('checked' => TRUE),
      ),
    ),
  );
  $form['settings']['path_filter']['status'] = array(
    '#type' => 'radios',
    '#title' => t('Include or Exclude Paths'),
    '#options' => array(
      1 => t('Show notice <strong>only</strong> on these paths'),
      0 => t('Show notice on all paths <strong>except</strong> these'),
    ),
    '#default_value' => (isset($site_notice->settings['path_filter']['status']) ? $site_notice->settings['path_filter']['status'] : SiteNoticeEntity::FILTER_EXCLUDE),
  );
  $form['settings']['path_filter']['value'] = array(
    '#type' => 'textarea',
    '#title' => t('Paths'),
    '#description' => t('List paths one per line.'),
    '#rows' => 3,
    '#default_value' => (isset($site_notice->settings['path_filter']['value']) ? $site_notice->settings['path_filter']['value'] : ''),
  );

  // Role Filter
  $form['settings']['role_filter'] = array(
    '#type' => 'fieldset',
    '#title' => t('Filter by Role'),
    '#collapsible' => TRUE,
    '#weight' => 4,
  );
  $form['settings']['role_filter']['note'] = array(
    '#type' => 'item',
    '#title' => t('Note:'),
    '#markup' => t('Only applies to Top and Bottom displays.'),
    '#states' => array(
      'visible' => array(
        ':input[name="settings[status][block]"]' => array('checked' => TRUE),
      ),
    ),
  );
  $form['settings']['role_filter']['status'] = array(
    '#type' => 'radios',
    '#title' => t('Include or Exclude Roles'),
    '#options' => array(
      1 => t('Show notices to <strong>only</strong> these roles'),
      0 => t('Show notices to all roles <strong>except</strong> these'),
    ),
    '#default_value' => (isset($site_notice->settings['role_filter']['status']) ? $site_notice->settings['role_filter']['status'] : SiteNoticeEntity::FILTER_EXCLUDE),
  );
  $form['settings']['role_filter']['value'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Roles'),
    '#description' => t('Select roles to include or exclude.'),
    '#options' => user_roles(),
    '#default_value' => (isset($site_notice->settings['role_filter']['value']) ? $site_notice->settings['role_filter']['value'] : array()),
  );

  // Add the field related form elements.
  $form_state['site_notice'] = $site_notice;
  field_attach_form('site_notice', $site_notice, $form, $form_state);

  $form['actions'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('form-actions')),
    '#weight' => 400,
  );

  // We add the form's #submit array to this button along with the actual submit
  // handler to preserve any submit handlers added by a form callback_wrapper.
  $submit = array();

  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Site Notice'),
    '#submit' => $submit + array('site_notice_edit_form_submit'),
  );

  if (!empty($site_notice->name)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete Site Notice'),
      '#suffix' => l(t('Cancel'), 'admin/content/site-notices'),
      '#submit' => $submit + array('site_notice_form_submit_delete'),
      '#weight' => 45,
    );
  }

  // We append the validate handler to #validate in case a form callback_wrapper
  // is used to add validate handlers earlier.
  $form['#validate'][] = 'site_notice_edit_form_validate';
  return $form;
}

/**
 * Form API validate callback for the site notice form
 */
function site_notice_edit_form_validate(&$form, &$form_state) {
  $site_notice = $form_state['site_notice'];
  $vals = $form_state['values'];

  // Require a dismissal link text if the message is dismissable.
  if ($vals['settings']['behavior']['dismiss'] != SiteNoticeEntity::DISMISS_NONE && !$vals['settings']['behavior']['dismiss_text']) {
    form_set_error('settings][behavior][dismiss_text', t('Text for the dismissal link is required if the notice is dismissable.'));
  }

  // Notify field widgets to validate their data.
  field_attach_form_validate('site_notice', $site_notice, $form, $form_state);
}

/**
 * Form API submit callback for the site notice form.
 *
 * @todo remove hard-coded link
 */
function site_notice_edit_form_submit(&$form, &$form_state) {
  $site_notice = entity_ui_controller('site_notice')->entityFormSubmitBuildEntity($form, $form_state);

  // Add in created and changed times.
  if ($site_notice->is_new = isset($site_notice->is_new) ? $site_notice->is_new : 0) {
    $site_notice->created = time();
  }
  $site_notice->changed = time();

  // Move the Status and Block settings out of the settings and onto the raw object.
  $site_notice->status = $site_notice->settings['status']['status'];
  $site_notice->block  = $site_notice->settings['status']['block'];
  unset($site_notice->settings['status']['status'], $site_notice->settings['status']['block']);

  // Remove unnecessary data
  unset($site_notice->settings['settings__active_tab']);

  // Enable/disable a block based on notice settings.
  db_update('block')
    ->condition('module', 'site_notice')
    ->condition('delta', $site_notice->name)
    ->fields(array('status' => $site_notice->block))
    ->execute();

  // Save and return
  if ($site_notice->save()) {
    drupal_set_message(t('Notice %name saved.', array('%name' => $site_notice->title)));
  }
  else {
    drupal_set_message(t('Error saving notice %name..', array('%name' => $site_notice->title)), 'error');
  }
  $form_state['redirect'] = 'admin/content/site-notices';
}

/**
 * Form API submit callback for the delete button.
 *
 * @todo Remove hard-coded path
 */
function site_notice_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/content/site-notices/' . $form_state['site_notice']->site_notice_id . '/delete';
}

/**
 * Form callback: confirmation form for deleting a site notice.
 *
 * @param $site_notice
 *   The site notice to delete
 *
 * @see confirm_form()
 */
function site_notice_delete_form($form, &$form_state, $site_notice) {
  $form_state['site_notice'] = $site_notice;

  $form['#submit'][] = 'site_notice_delete_form_submit';

  $form = confirm_form($form,
    t('Are you sure you want to delete site notice %name?', array('%name' => $site_notice->title)),
    'admin/content/site-notices',
    '<p>' . t('This action cannot be undone.') . '</p>',
    t('Delete'),
    t('Cancel'),
    'confirm'
  );

  return $form;
}

/**
 * Submit callback for site_notice_delete_form
 */
function site_notice_delete_form_submit($form, &$form_state) {
  $site_notice = $form_state['site_notice'];

  site_notice_delete($site_notice);

  drupal_set_message(t('The site notice %name has been deleted.', array('%name' => $site_notice->title)));
  watchdog('site_notice', 'Deleted site notice %name.', array('%name' => $site_notice->title));

  $form_state['redirect'] = 'admin/content/site-notices';
}

/**
 * Page to add Site notice Entities.
 *
 * @todo Pass this through a proper theme function
 */
function site_notice_add_page() {
  $controller = entity_ui_controller('site_notice');
  return $controller->addPage();
}

/**
 * Sets the breadcrumb for administrative site notice pages.
 */
function site_notice_set_breadcrumb() {
  $breadcrumb = array(
    l(t('Home'), '<front>'),
    l(t('Administration'), 'admin'),
    l(t('Content'), 'admin/content'),
    l(t('Site Notices'), 'admin/content/site-notices'),
  );

  drupal_set_breadcrumb($breadcrumb);
}

/**
 * Admin settings form.
 */
function site_notice_admin_settings($form, &$form_state) {
  $form['site_notice_default_position'] = array(
    '#type' => 'radios',
    '#title' => t('Default Position'),
    '#description' => t('Set the default position for notices when they are enabled.'),
    '#options' => array(
      SiteNoticeEntity::TOP      => t('Page Top'),
      SiteNoticeEntity::BOTTOM   => t('Page Bottom'),
    ),
    '#default_value' => variable_get('site_notice_default_position', SiteNoticeEntity::TOP),
  );

  // Enable ajax dismissal
  $form['site_notice_ajax_dismiss'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable AJAX Dismissal'),
    '#description' => t('Notices may be dismissed without reloading the page.'),
    '#default_value' => variable_get('site_notice_ajax_dismiss', 1),
  );

  // Option to ignore the Redirect form element on the entity edit form.
  if (module_exists('redirect')) {
    $form['site_notice_ignore_redirect'] = array(
      '#type' => 'checkbox',
      '#title' => t('Ignore Redirect'),
      '#description' => t('Remove the Redirect option from the Site Notice edit form.'),
      '#default_value' => variable_get('site_notice_ignore_redirect', 1),
    );
  }

  return system_settings_form($form);
}
