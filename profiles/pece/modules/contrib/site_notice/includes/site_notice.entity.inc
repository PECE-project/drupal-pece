<?php
/**
 * @file
 * Entity API
 */
/**
 * Create a site notice object.
 */
function site_notice_create($values = array()) {
  return entity_create('site_notice', $values);
}

/**
 * Load a site notice.
 */
function site_notice_load($snid, $reset = FALSE) {
  $notices = site_notice_load_multiple(array($snid), array(), $reset);
  return reset($notices);
}

/**
 * Load a site notice by name.
 */
function site_notice_load_by_name($name, $reset = FALSE) {
  $notices = site_notice_load_multiple(FALSE, array('name' => $name), $reset);
  return reset($notices);
}

/**
 * Load multiple notices based on certain conditions.
 */
function site_notice_load_multiple($snids = array(), $conditions = array(), $reset = FALSE) {
  // Convert any machine name snids to the actual integer snid.
  if (is_array($snids)) {
    foreach ($snids as &$snid) {
      if (!is_numeric($snid)) {
        $snid = db_select('site_notice', 'sn')->fields('sn', array('snid'))->condition('sn.name', $snid)->execute()->fetchField();
      }
    }
  }

  return entity_load('site_notice', $snids, $conditions, $reset);
}

/**
* Save site notice.
*/
function site_notice_save($notice) {
  entity_save('site_notice', $notice);
}

/**
* Delete single site notice.
*/
function site_notice_delete($notice) {
  entity_delete('site_notice', entity_id('site_notice', $notice));
}

/**
* Delete multiple site notices.
*/
function site_notice_delete_multiple($notice) {
  entity_delete_multiple('site_notice', $notice);
}

/**
 * Sets up content to show an individual notice
 * @todo - get rid of drupal_set_title();
 */
function site_notice_page_view($notice, $view_mode = 'full') {
  $controller = entity_get_controller('site_notice');
  $content = $controller->view(array($notice->snid => $notice));
  drupal_set_title($notice->title);
  return $content;
}

/*******************************************************************************
 * Entity and Controller
 ******************************************************************************/
/**
 * Site Notice class.
 */
class SiteNoticeEntity extends Entity {
  const DISABLED = 0;
  const TOP      = 1;
  const BOTTOM   = 2;

  const BLOCK_NONE   = 0;
  const BLOCK_EXPOSE = 1;

  const DISMISS_NONE = 0;
  const DISMISS_PERM = 1;
  const DISMISS_SESS = 2;

  const FILTER_EXCLUDE = 0;
  const FILTER_INCLUDE = 1;

  protected function defaultLabel() {
    return $this->title;
  }
  protected function defaultUri() {
    return array('path' => 'site-notices/' . $this->identifier());
  }

  /**
   * Translate a constant value to text.
   */
  public static function getOptions($type, $value = NULL) {
    $values['status'] = array(
      SiteNoticeEntity::DISABLED => t('Disabled'),
      SiteNoticeEntity::TOP      => t('Top'),
      SiteNoticeEntity::BOTTOM   => t('Bottom'),
    );

    $values['dismissal'] = array(
      SiteNoticeEntity::DISMISS_SESS => t('Dismiss per Session'),
      SiteNoticeEntity::DISMISS_PERM => t('Dismiss Permanently'),
      SiteNoticeEntity::DISMISS_NONE => t('Non-Dismissable'),
    );

    return (is_null($value) ? $values[$type] : (isset($values[$type][$value]) ? $values[$type][$value] : ''));
  }

  /**
   * Save the entity
   */
  public function save() {
    $this->changed = REQUEST_TIME;

    // Serialize the settings
    $this->settings = serialize($this->settings);

    // Generate the instance Id if new or newly enabled
    if ((isset($this->is_new) && $this->is_new) || ($this->old_notice->status == self::DISABLED && $this->status >= self::DISABLED)) {
      $this->instance = md5($this->changed . $this->name);
    }

    return parent::save();
  }
}

/**
 * Site Notice Controller
 */
class SiteNoticeController extends EntityAPIController {
  /**
   * Create a new notice.
   */
  public function create(array $values = array()) {
    global $user;
    $values += array(
      'title'    => '',
      'created'  => REQUEST_TIME,
      'changed'  => REQUEST_TIME,
      'uid'      => $user->uid,
      'language' => language_default('language'),
    );
    return parent::create($values);
  }

  /**
   * Verify the existence of a notice by name.
   */
  public static function exists($name) {
    $select = db_select('site_notice', 'sn')->fields('sn')->condition('sn.name', $name);
    return (bool) $select->execute()->rowCount();
  }

  /**
   * Overriding the buildContent function to add entity specific fields
   */
  public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array()) {
    $content = parent::buildContent($entity, $view_mode, $langcode, $content);
    $ajax = variable_get('site_notice_ajax_dismiss', 1);

    // Add dismissal links.
    $content['links'] = array(
      '#theme' => 'links__site_notice',
      '#pre_render' => array('drupal_pre_render_links'),
    );

    switch ($entity->settings['behavior']['dismiss']) {
      case SiteNoticeEntity::DISMISS_SESS:
      case SiteNoticeEntity::DISMISS_PERM:
        $content['links']['#links']['dismiss'] = array(
          'href' => "site-notices/{$entity->name}/dismiss",
          'title' => filter_xss($entity->settings['behavior']['dismiss_text']),
          'query' => drupal_get_destination(),
        );

        // Add the AJAX parameters
        if ($ajax) {
          $content['#attached']['js'][] = drupal_get_path('module', 'site_notice') . '/js/site-notice-dismiss.js';
          $content['links']['#links']['dismiss']['attributes']['ajax'] = array('site-notice-dismiss');
        }
        break;
    }

    // Add contextual links.
    $content['#contextual_links'] = array(
      'site_notice' => array(
        'admin/content/site-notices',
        array($entity->snid),
      ),
    );

    return $content;
  }

  // Load the entity
  public function load($ids = array(), $conditions = array()) {
    $notices = parent::load($ids, $conditions);

    foreach ($notices as $notice) {
      // Unserialize the settings
      if (is_string($notice->settings)) {
        $notice->settings = unserialize($notice->settings);
      }

      // Generate a standard dismissal ID
      $notice->dismissalID = "site-notice-{$notice->instance}";

      // Create a clone of the original for reference on save.
      $notice->old_notice = clone($notice);
    }

    return $notices;
  }
}

