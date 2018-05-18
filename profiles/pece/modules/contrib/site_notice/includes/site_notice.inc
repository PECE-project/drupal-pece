<?php
/**
 * @file
 * Custom module functionality.
 */
/**
 * Check to see if a notice with this name exists.
 */
function site_notice_name_exists($name) {
  return SiteNoticeController::exists($name);
}

/**
 * API function to enable a notice with proper validation and messages.  Use
 * this function as a callback for user facing calls.
 *
 * Wrapper for site_notice_update_status().
 */
function site_notice_enable_notice(SiteNoticeEntity $notice, $force = FALSE) {
  $args = array('%name' => $notice->title);
  $pos  = variable_get('site_notice_default_position', SiteNoticeEntity::TOP);

  // Access check
  if ($force || site_notice_access('edit', $notice)) {
    if ($notice->status) {
      drupal_set_message(t('Site notice %name is already enabled.', array('%name' => $notice->title)), 'warning');
    }
    else {
      if (site_notice_update_status($notice, $pos)) {
        // Provide a hook for other modules.
        module_invoke_all('site_notice_enable', $notice);

        drupal_set_message(t('Notice %name has been enabled.', $args));
      }
      else {
        drupal_set_message(t('Error enabling notice %name.', $args), 'error');
      }
    }
  }
  else {
    drupal_set_message(t('You do not have privelages to enable the site notice %name.', array('%name' => $notice->title)), 'error');
  }

  drupal_goto(drupal_get_destination());
}

/**
 * API function to disable a notice with proper validation and messages.  Use
 * this function as a callback for user facing calls.
 *
 * Wrapper for site_notice_update_status().
 */
function site_notice_disable_notice(SiteNoticeEntity $notice, $force = FALSE) {
  $args = array('%name' => $notice->title);

  // Access check
  if ($force || site_notice_access('edit', $notice)) {
    if (!$notice->status) {
      drupal_set_message(t('Site notice %name is already disabled.', $args), 'warning');
    }
    else {
      if (site_notice_update_status($notice, 0)) {
        // Provide a hook for other modules.
        module_invoke_all('site_notice_disable', $notice);

        drupal_set_message(t('Notice %name has been disabled.', $args));
      }
      else {
        drupal_set_message(t('Error disabling notice %name.', $args), 'error');
      }
    }
  }
  else {
    drupal_set_message(t('You do not have privelages to disable the site notice %name.', $args), 'error');
  }

  drupal_goto(drupal_get_destination());
}

/**
 * API call to directly change the status of a notice.  Only use this if you
 * have already checked for permission.
 *
 * @see site_notice_enable()
 * @see site_notice_disable()
 */
function site_notice_update_status(SiteNoticeEntity $notice, $status) {
  $notice->status = (int) $status;
  return $notice->save();
}

/**
 * Dismiss a notice.  Flag that a user has dismissed a notice, either in the
 * session or in their user data settings.
 */
function site_notice_dismiss_notice(SiteNoticeEntity $notice) {
  $account = $GLOBALS['user'];
  $dtype   = $notice->settings['behavior']['dismiss'];
  $ajax    = isset($_POST['ajax']) && $_POST['ajax'] == TRUE;

  // Identify the type of dismissal allowed
  switch ($dtype) {
    case SiteNoticeEntity::DISMISS_SESS:
      // Set the session variable
      $_SESSION['site_notice']['dismiss'][$notice->dismissalID] = TRUE;
      break;

    case SiteNoticeEntity::DISMISS_PERM:
      // Use flood control for one year as the permanent dismissal.
      // Log them by IP, then also by UID if they are logged in, in case their
      // IP changes.
      flood_register_event($notice->dismissalID, SITE_NOTICE_PERMANENT_DISMISSAL_TIMEOUT);
      if (user_is_logged_in()) {
        flood_register_event($notice->dismissalID, SITE_NOTICE_PERMANENT_DISMISSAL_TIMEOUT, $account->uid);
      }
      break;

    case SiteNoticeEntity::DISMISS_NONE:
      // Um, nondismissable.  What are you doing here?
      break;
  }

  if ($ajax) {
    return drupal_json_output(TRUE);
  }
  else {
    drupal_goto(drupal_get_destination());
  }
}

/**
 * Filter notices.
 *
 * @param $statuses
 *   Array of notice statuses to load by.
 *
 * @return $notices
 *   Array of notices that passed the filters.
 */
function site_notice_filter_notices($statuses = array()) {
  $return = array();

  // If no status was supplied, load them all.
  if (empty($statuses)) {
    $statuses = array(
      SiteNoticeEntity::TOP,
      SiteNoticeEntity::BOTTOM,
      SiteNoticeEntity::BLOCK,
    );
  }

  $notices = array();
  foreach ($statuses as $status) {
    $notices += site_notice_load_multiple(FALSE, array('status' => $status));
  }

  // Run the notices through the filters.
  foreach ($notices as $notice) {
    if (site_notice_passed_filters($notice)) {
      $return[$notice->status][$notice->snid] = $notice;
    }
  }

  return $return;
}

/**
 * Validate a single notice against the filters.
 */
function site_notice_passed_filters($notice, $is_block = FALSE) {
  $account = $GLOBALS['user'];

  // Determine whether we need to evaluate this instance as a block instance
  // or a regular top/bottom instance.
  $eval_as_block = ($notice->block == SiteNoticeEntity::BLOCK_EXPOSE && $is_block);

  // Ensure the notice is enabled.
  if ($notice->status == SiteNoticeEntity::DISABLED) {
    return FALSE;
  }

  // Check for session dismissal.
  if ($notice->settings['behavior']['dismiss'] == SiteNoticeEntity::DISMISS_SESS && isset($_SESSION['site_notice']['dismiss'][$notice->dismissalID])) {
    return FALSE;
  }

  // Check for permanent dismissal.
  if (!flood_is_allowed($notice->dismissalID, 1, SITE_NOTICE_PERMANENT_DISMISSAL_TIMEOUT)) {
    return FALSE;
  }

  // If the user is logged in, look for the UID to be set as well.
  if (user_is_logged_in() && !flood_is_allowed($notice->dismissalID, 1, SITE_NOTICE_PERMANENT_DISMISSAL_TIMEOUT, $account->uid)) {
    return FALSE;
  }

  // Check for path and role filters if not a block notice.
  if (!$eval_as_block && (!_site_notice_filter_path($notice) || !_site_notice_filter_role($notice))) {
    return FALSE;
  }

  return TRUE;
}

/**
 * Helper to determine if a notice passes the path filter.
 */
function _site_notice_filter_path($notice) {
  $s = $notice->settings['path_filter'];

  $pages_match = drupal_match_path($_GET['q'], $s['value']);

  // Check whether the page filter is inclusionary or exclusionary
  if ($s['status'] == SiteNoticeEntity::FILTER_INCLUDE && !$pages_match) {
    return FALSE;
  }
  elseif ($s['status'] == SiteNoticeEntity::FILTER_EXCLUDE && $pages_match) {
    return FALSE;
  }

  return TRUE;
}

/**
 * Helper to determine if a notice passes the role filter.
 */
function _site_notice_filter_role($notice) {
  global $user;
  $s = $notice->settings['role_filter'];

  // Get an array of roles checked in the notice and assigned to the active user.
  $matching_roles = array();
  foreach ($s['value'] as $rid => $active) {
    if ($active && isset($user->roles[$rid])) {
      $matching_roles[$rid] = $user->roles[$rid];
    }
  }

  // Check whether the role filter is inclusionary or exclusionary
  if ($s['status'] == SiteNoticeEntity::FILTER_INCLUDE && empty($matching_roles)) {
    return FALSE;
  }
  elseif ($s['status'] == SiteNoticeEntity::FILTER_EXCLUDE && !empty($matching_roles)) {
    return FALSE;
  }

  return TRUE;
}
