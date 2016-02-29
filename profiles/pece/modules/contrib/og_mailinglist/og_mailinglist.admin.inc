<?php
/**
 * @file
 *  Admin interface for OG Mailinglist module.
 */

require_once 'og_mailinglist_common.inc';

/**
 * Admin settings form for email settings
 */
function og_mailinglist_email_settings() {
  $form['subscription'] = array(
    '#type' => 'fieldset',
    '#title' => t('Email subscription'),
  );
  $form['subscription']['og_mailinglist_default_group_subscription_type'] = array(
    '#title' => t('Default group email subscription type'),
    '#type' => 'select',
    '#default_value' => variable_get('og_mailinglist_default_group_subscription_type', 'email'),
    '#options' => array(
      'email' => t('Email'),
      'digest email' => t('Digest email'),
      'no email' => t('No email'),
    ),
    '#description' => t('Choose the default email subscription for users joining a new group. "Email" means the user will receive an email for each new post. "No email" means the user will recieve no emails except for discussion threads they participate in. "Digest" is the same as "No email" except the user will also receive digest emails. (Users can change this later at http://example.com/user/%user/og_mailinglist)'),
  );

  $form['limits'] = array(
    '#type' => 'fieldset',
    '#title' => t('Email limits'),
  );
  $form['limits']['og_mailinglist_max_message_size'] = array(
    '#title' => t('Maximum message body size (excluding attachments)'),
    '#type' => 'textfield',
    '#default_value' => variable_get('og_mailinglist_max_message_size', '100'),
    '#description' => t('Any messages over this size will be rejected.  Set to 0 for unlimited.'),
    '#size' => 10,
    '#maxlength' => 10,
    '#field_suffix' => t('KiB'),
    '#element_validate' => array('_og_mailinglist_element_validate_unsigned_integer'),
  );
  $form['limits']['og_mailinglist_max_posts_per_hour'] = array(
    '#title' => t('Maximum posts per hour'),
    '#type' => 'textfield',
    '#default_value' => variable_get('og_mailinglist_max_posts_per_hour', '20'),
    '#description' => t('The maximum number of messages a user is able to post per hour by email.  Set to 0 for unlimited.'),
    '#size' => 10,
    '#maxlength' => 10,
    '#element_validate' => array('_og_mailinglist_element_validate_unsigned_integer'),
  );

  $form['headers'] = array(
    '#type' => 'fieldset',
    '#title' => t('Email headers'),
  );
  $form['headers']['og_mailinglist_reply_to_group'] = array(
    '#title' => t('Add a Reply-To header to outgoing group emails'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('og_mailinglist_reply_to_group', '0'),
    '#description' => t('Set an explicit reply-to header. See <a href="@link">a discussion</a> for pros and cons on this setting.', array('@link' => 'http://wiki.list.org/pages/viewpage.action?pageId=4030691')),
  );
  $form['headers']['og_mailinglist_thread_comments'] = array(
    '#title' => t('Thread comments using In-Reply-To header'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('og_mailinglist_thread_comments', '0'),
    '#description' => t('New comments will be threaded on save. Existing comments will not be affected.'),
  );
  $form['headers']['og_mailinglist_new_thread_from_subject'] = array(
    '#title' => t('Create a new node if the subject has been changed'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('og_mailinglist_new_thread_from_subject', TRUE),
    '#description' => t('Create a new node if the subject of the email has been changed, even if it was a reply to an existing thread.'),
  );

  $form['signatures'] = array(
    '#type' => 'fieldset',
    '#title' => t('User signature'),
  );
  $form['signatures']['og_mailinglist_add_signatures'] = array(
    '#title' => t('Add user signatures to nodes and comments created on the site'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('og_mailinglist_add_signatures', '1'),
    '#description' => t('Add a user\'s signature if they have one.'),
  );
  return system_settings_form($form);
}

/**
 * Admin settings form for OGM content types
 */
function og_mailinglist_content_types_settings($form, &$form_state) {
  $default_content_type = variable_get('og_mailinglist_default_content_type', 'none^set');
  $node_types = array('none^set' => t('- None -'));
  foreach (node_type_get_names() as $type => $name) {
    if (og_is_group_content_type('node', $type)) {
      $node_types[$type] = $name;
    }
  }
  $form['content_defaults'] = array(
    '#type' => 'fieldset',
    '#title' => t('Content defaults'),
  );
  $form['content_defaults']['og_mailinglist_default_content_type'] = array(
    '#title' => t('Default content type'),
    '#type' => 'select',
    '#default_value' => $default_content_type,
    '#options' => $node_types,
    '#description' => t('Choose the default content type to be created from new emails.'),
    '#ajax' => array(
      'event' => 'change',
      'callback' => 'og_mailinglist_admin_dropdown_content_fields',
      'wrapper' => 'content-fields-wrapper',
    ),
  );

  $form['og_mailinglist_fields']['wrapper'] = array(
    '#prefix' => '<div id="content-fields-wrapper">',
    '#suffix' => '</div>',
  );

  $node_file_fields = array('no^field' => t('- None -'));
  $node_image_fields = array('no^field' => t('- None -'));
  $content_type = isset($form_state['values']['og_mailinglist_default_content_type']) ? $form_state['values']['og_mailinglist_default_content_type'] : $default_content_type;
  if ($content_type != 'none^set') {
    $fields_info = field_info_instances('node', $default_content_type);
    foreach ($fields_info  as $field_name => $value) {
      $field_info = field_info_field($field_name);
      $type = $field_info['type'];
      if ($type == 'file') {
        $node_file_fields[$field_name] = $value['field_name'];
      }
      elseif ($type == 'image') {
        $node_image_fields[$field_name] = $value['field_name'];
      }
    }
  }

  $comment_file_fields = count($node_file_fields) > 1 ? array('no^field' => t('- None -'), 'attach^to^node' => t('- Attach to node -')) : array('no^field' => t('- None -'));
  $comment_image_fields = count($node_image_fields) > 1 ? array('no^field' => t('- None -'), 'attach^to^node' => t('- Attach to node -')) : array('no^field' => t('- None -'));
  if ($content_type != 'none^set') {
    $fields_info = field_info_instances('comment', 'comment_node_' . $default_content_type);
    foreach ($fields_info  as $field_name => $value) {
      $field_info = field_info_field($field_name);
      $type = $field_info['type'];
      if ($type == 'file') {
        $comment_file_fields[$field_name] = $value['field_name'];
      }
      elseif ($type == 'image') {
        $comment_image_fields[$field_name] = $value['field_name'];
      }
    }
  }

  $form['og_mailinglist_fields']['wrapper']['og_mailinglist_node_file_field'] = array(
    '#title' => t('Field for files in node'),
    '#description' => t('Field where incoming files will be stored. Will be used for images too when image field is not set.'),
    '#type' => 'select',
    '#options' => $node_file_fields,
    '#default_value' => variable_get('og_mailinglist_node_file_field', ''),
  );
  $form['og_mailinglist_fields']['wrapper']['og_mailinglist_node_image_field'] = array(
    '#title' => t('Field for images in node'),
    '#type' => 'select',
    '#options' => $node_image_fields,
    '#default_value' => variable_get('og_mailinglist_node_image_field', ''),
  );
  $form['og_mailinglist_fields']['wrapper']['og_mailinglist_comment_file_field'] = array(
    '#title' => t('Field for files in comment/reply'),
    '#description' => t('Field where incoming files for email replies will be stored. Will be used for images too when image field is not set.'),
    '#type' => 'select',
    '#options' => $comment_file_fields,
    '#default_value' => variable_get('og_mailinglist_comment_file_field', ''),
  );
  $form['og_mailinglist_fields']['wrapper']['og_mailinglist_comment_image_field'] = array(
    '#title' => t('Field for images in comment/reply'),
    '#type' => 'select',
    '#options' => $comment_image_fields,
    '#default_value' => variable_get('og_mailinglist_comment_image_field', ''),
  );

  $filter_list = array();
  foreach (filter_formats() as $machine_name => $filter) {
    $filter_list[$machine_name] = $filter->name;
  }
  $form['content_defaults']['og_mailinglist_default_filter_format'] = array(
    '#title' => t('Default filter format'),
    '#type' => 'select',
    '#default_value' => variable_get('og_mailinglist_default_filter_format', 'plain_text'),
    '#options' => $filter_list,
    '#description' => t('Choose the default filter format to be used on new nodes which are sent from email.'),
  );

  $form['excluded_content_types'] = array(
    '#type' => 'fieldset',
    '#title' => t('Excluded content types'),
  );
  $form['excluded_content_types']['og_mailinglist_exclude_content_types'] = array(
    '#title' => t('Exclude the following content types'),
    '#type' => 'select',
    '#multiple' => TRUE,
    '#default_value' => variable_get('og_mailinglist_exclude_content_types', array()),
    '#options' => $node_types,
    '#description' => t('Do not send emails on creation of these content types.'),
  );

  return system_settings_form($form);
}

/**
 * Function for AJAX request on admin/config/group/mailinglist/content_types
 */
function og_mailinglist_admin_dropdown_content_fields($form, $form_state) {
  // Return the dropdown list including the wrapper.
  return $form['og_mailinglist_fields']['wrapper'];
}

/**
 * Admin settings form for digest emails.
 */
function og_mailinglist_digest_settings() {
  $digest_days = variable_get('og_mailinglist_digest_interval_days', 1);
  $digest_hour = variable_get('og_mailinglist_digest_hour', 17);
  $next_digest = variable_get('og_mailinglist_digest_runtime',
    mktime($digest_hour, 0, 0));
  variable_set('og_mailinglist_digest_runtime', $next_digest);

  $form['digest'] = array(
    '#type' => 'fieldset',
    '#title' => t('Digest email settings'),
  );
  $form['digest']['og_mailinglist_digest_interval_days'] = array(
    '#title' => t('Digest interval'),
    '#type' => 'textfield',
    '#default_value' => $digest_days,
    '#size' => 5,
    '#maxlength' => 3,
    '#required' => TRUE,
    '#description' => t('Choose how often the digest will be sent. Value is in days. Defaults to 1.'),
    '#element_validate' => array('element_validate_integer_positive'),
  );
  $form['digest']['og_mailinglist_digest_hour'] = array(
    '#title' => t('Digest hour'),
    '#type' => 'textfield',
    '#size' => 5,
    '#maxlength' => 2,
    '#required' => TRUE,
    '#default_value' => $digest_hour,
    '#description' => t('The digest email will be sent after this hour. Defaults to 17.'),
    '#element_validate' => array('_og_mailinglist_element_validate_unsigned_integer'),
  );
  $form['digest']['next_digest_run'] = array(
    '#title' => t('Next digest run'),
    '#type' => 'item',
    '#description' => t('Next digest is scheduled to @datestring. Please keep in mind that the digest mail will be sent on the next cron run after this date, so it also depends on cron settings.',
      array('@datestring' => format_date($next_digest))),
  );
  return system_settings_form($form);
}

/**
 * Validate admin digest emails settings form.
 */
function og_mailinglist_digest_settings_validate($form, &$form_state) {
  $hour = $form_state['values']['og_mailinglist_digest_hour'];
  if ($hour > 23) {
    form_set_error('og_mailinglist_digest_hour',
      t('Digest hour must be an integer between 0 and 23.'));
  }
}

/**
 * Admin settings form for configuration
 */
function og_mailinglist_config_settings() {
  $form['server'] = array(
    '#type' => 'fieldset',
    '#title' => t('Server settings'),
  );
  $form['server']['og_mailinglist_server_string'] = array(
    '#title' => t('Domain name'),
    '#type' => 'textfield',
    '#default_value' => og_mailinglist_server(),
    '#description' => t('Domain name for incoming/outgoing emails, e.g. example.com.'),
  );
  $form['server']['og_mailinglist_address_open'] = array(
    '#title' => t('Accept emails sent to @ogm address', array('@ogm' => $GLOBALS['base_url'] . '/og_mailinglist')),
    '#type' => 'checkbox',
    '#default_value' => variable_get('og_mailinglist_address_open', '1'),
    '#description' => t('If this is unchecked, then @ogm address does not accept incoming emails. This might be useful to block all incoming emails in case of emergency or when you use direct posting method.', array('@ogm' => $GLOBALS['base_url'] . '/og_mailinglist')),
  );
  // Save an incoming key by default.
  if ((variable_get('og_mailinglist_incoming_key', '')) == '') {
    variable_set('og_mailinglist_incoming_key',   md5(rand()));
  }
  $form['server']['og_mailinglist_incoming_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Message validation string'),
    '#default_value' => variable_get('og_mailinglist_incoming_key', md5(rand())),
    '#required' => TRUE,
    '#description' => t('This string will be used to validate incoming messages.  It can be anything, but must be used on both sides of the transfer. For more see the INSTALL.txt for your Mail Transfer Agent.'),
  );
  $form['debugging'] = array(
    '#type' => 'fieldset',
    '#title' => t('Debugging'),
  );
  $form['debugging']['og_mailinglist_test_email_addresses'] = array(
    '#title' => t('List of email addresses to recieve all email'),
    '#type' => 'textfield',
    '#default_value' => variable_get('og_mailinglist_test_email_addresses', ''),
    '#description' => t('For testing / monitoring purposes, add a comma separated list of email addresses to receive all emails sent by OG Mailinglist.'),
  );
  return system_settings_form($form);
}

/**
 * Build subscription admin for each user.
 */
function og_mailinglist_subscriptions_settings_form($form, $form_state, $account = NULL) {
  global $user;

  // $uid is of the user we are trying to see/change.
  $uid = $user->uid;
  if (is_object($account)) {
    $uid = $account->uid;
  }

  $result = db_query('SELECT m.nid as gid, m.subscription_type, n.title
          FROM {og_mailinglist_group_subscription} m, {node} n
          WHERE m.nid = n.nid
          AND m.uid = :uid
          ORDER BY n.title', array(':uid' => $uid));

  $subscription_options = array(
    'email' => t('Email'),
    'digest email' => t('Digest email'),
    'no email' => t('No email'),
  );
  $form = array();

  $form['uid'] = array(
    '#type' => 'value',
    '#value' => $uid,
  );

  foreach ($result as $group) {
    $form[$group->gid] = array(
      '#type' => 'fieldset',
      '#title' => l($group->title, "node/" . $group->gid),
      '#tree' => TRUE,
    );
    $form[$group->gid]['subscription-type'] = array(
      '#type' => 'select',
      '#default_value' => $group->subscription_type,
      '#title' => t("Email Settings"),
      '#options' => $subscription_options,
    );
    if (og_user_access('node', $group->gid, 'unsubscribe', $user)) {
      $form[$group->gid]['leave-group'] = array(
        '#type' => 'checkbox',
        '#title' => t('Leave the @name group',
          array('@name' => $group->title)),
      );
    }
  }
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Settings'),
  );

  return $form;
}

function _og_mailinglist_element_validate_unsigned_integer($element, &$form_state) {
  if ($element['#value'] != 0) {
    element_validate_integer_positive($element, $form_state);
  }
}
