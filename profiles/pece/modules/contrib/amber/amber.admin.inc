<?php
/**
 * @file
 * Admin functionality
 */

/**
 * Amber configuration settings form
 */
function amber_config_form($form, &$form_state) {
  $form['amber_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Amber'),
    '#default_value' => variable_get('amber_enabled', 1),
    '#description' => t('Enable all functionality, including the preservation of new snapshots and notifications to site visitors. Disabling this will not remove existing snapshots.'),
  );
  $form['amber_cache'] = array(
    '#type' => 'fieldset',
    '#title' => t('Storage Settings'),
    '#description' => t("Control how Amber stores snapshots"),
  );
  $form['amber_cache']['amber_backend'] = array(
    '#type' => 'select',
    '#title' => t('Backend to use for storing snapshots'),
    '#options' => array_merge(
      array(
          AMBER_BACKEND_LOCAL => t('Local'),
          AMBER_BACKEND_PERMA => t('Perma.cc'),
          AMBER_BACKEND_INTERNET_ARCHIVE => t('Internet Archive')
        ),
        (version_compare(PHP_VERSION, "5.5") >= 0) ? array(AMBER_BACKEND_AMAZON_S3 => t('Amazon Web Services S3')) : array()
      ),
    '#default_value' => variable_get('amber_backend', 0),
    '#description' => t('Amber can store snapshots locally, in your website\'s storage space. If you prefer, you can store snapshots in an alternative backend. At this time, Amber is compatible with the following services: <a href="https://perma.cc/" target="_blank">Perma.cc</a>, the <a href="https://archive.org" target="_blank">Internet Archive</a>, and <a href="https://aws.amazon.com/s3/">Amazon S3</a>.'),
  );

  $form['amber_cache']['amber_alternate_backends'] = array(
    '#type' => 'select',
    '#title' => t('Alternate backend(s) to use for storing snapshots'),
    '#options' => array(
          AMBER_BACKEND_PERMA => t('Perma.cc'),
          AMBER_BACKEND_INTERNET_ARCHIVE => t('Internet Archive'),
      ),
    '#multiple' => TRUE,
    '#default_value' => variable_get('amber_alternate_backends', 0),
    '#description' => t('Preserve snapshots in multiple storage locations by selecting one or more alternates above. Amber will show your visitors only the storage location selected in the dropdown menu.'),
  );

  /* Settings for Local storage strategy */
  $form['amber_cache']['local'] = array(
    '#type' => 'fieldset',
    '#title' => t('Setttings for Local Storage'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    // '#states' => array(
    //   'visible' => array(
    //     ':input[name="amber_backend"]' => array('value' => AMBER_BACKEND_LOCAL),
    //   ),
    //  ),
  );

  $form['amber_cache']['local']['amber_max_file'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum file size (kB)'),
    '#size' => 10,
    '#default_value' => variable_get('amber_max_file', '1000'),
    '#description' => t('Amber will store snapshots up to a specified size. Links to pages that exceed this size will not be preserved.'),
  );

  $form['amber_cache']['local']['amber_max_disk'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum disk usage (MB)'),
    '#size' => 10,
    '#default_value' => variable_get('amber_max_disk', '1000'),
    '#description' => t('The maximum amount of disk space to be used for all preserved content. If this disk space usage is exceeded, old snapshots will be removed.'),
  );

  $form['amber_cache']['local']['amber_storage_location'] = array(
    '#type' => 'textfield',
    '#title' => t('Storage location'),
    '#default_value' => variable_get('amber_storage_location', 'amber'),
    '#description' => t('Path to the location where snapshots are stored on disk, relative to the Drupal private files directory.'),
  );

  $form['amber_cache']['local']['advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['amber_cache']['local']['advanced']['amber_update_strategy'] = array(
    '#type' => 'select',
    '#title' => t('Update strategy for snapshots'),
    '#options' => array(
      0 => t('Update snapshots periodically'),
      1 => t('Do not update snapshots'),
    ),
    '#default_value' => variable_get('amber_update_strategy', 0),
    '#description' => t('Select "Do not update" if you want to preserve links at the time the content is published. Otherwise, link storage will be periodically updated.'),
  );

  /* Settings for Perma storage strategy */
  $form['amber_cache']['perma'] = array(
    '#type' => 'fieldset',
    '#title' => t('Setttings for Perma.cc Storage'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    // '#states' => array(
    //   'visible' => array(
    //     ':input[name="amber_backend"]' => array('value' => AMBER_BACKEND_PERMA),
    //   ),
    //  ),
  );

  $form['amber_cache']['perma']['amber_perma_apikey'] = array(
    '#type' => 'textfield',
    '#title' => t('Perma API Key'),
    '#size' => 50,
    '#default_value' => variable_get('amber_perma_apikey', ''),
    '#description' => t('Generate an API key in your Perma.cc Dashboard under Settings > Tools'),
  );

  $form['amber_cache']['perma']['advanced_perma'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#states' => array(
      'visible' => array(
         ':input[name="amber_backend"]' => array('value' => "Never displayed"),
      ),
    ),
  );

  $form['amber_cache']['perma']['advanced_perma']['amber_perma_server_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Perma URL'),
    '#size' => 30,
    '#default_value' => variable_get('amber_perma_server_url', 'http://perma.cc'),
    '#description' => t('This should not need to be changed.'),
  );

  $form['amber_cache']['perma']['advanced_perma']['amber_perma_server_api_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Perma API URL'),
    '#size' => 30,
    '#default_value' => variable_get('amber_perma_server_api_url', 'http://api.perma.cc'),
    '#description' => t('This should not need to be changed.'),
  );

  /* Settings for AWS S3 storage strategy */
  $form['amber_cache']['aws'] = array(
    '#type' => 'fieldset',
    '#title' => t('Setttings for Amazon Web Services S3 Storage'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    // '#states' => array(
    //   'visible' => array(
    //     ':input[name="amber_backend"]' => array('value' => AMBER_BACKEND_AMAZON_S3),
    //   ),
    //  ),
  );

  $form['amber_cache']['aws']['amber_aws_access_key'] = array(
    '#type' => 'textfield',
    '#title' => t('AWS Access Key'),
    '#size' => 50,
    '#default_value' => variable_get('amber_aws_access_key', ''),
    '#description' => t('Visit <a href="http://docs.aws.amazon.com/general/latest/gr/managing-aws-access-keys.html" target="_blank">Managing Access Keys for your AWS Account</a> for instructions to generate an access key.'),
  );

  $form['amber_cache']['aws']['amber_aws_secret_key'] = array(
    '#type' => 'textfield',
    '#title' => t('AWS Secret Access Key'),
    '#size' => 50,
    '#default_value' => variable_get('amber_aws_secret_key', ''),
    '#description' => t('Visit <a href="http://docs.aws.amazon.com/general/latest/gr/managing-aws-access-keys.html" target="_blank">Managing Access Keys for your AWS Account</a> for instructions to generate a secret access key.'),
  );

  $form['amber_cache']['aws']['amber_aws_bucket'] = array(
    '#type' => 'textfield',
    '#title' => t('S3 Bucket'),
    '#size' => 50,
    '#default_value' => variable_get('amber_aws_bucket', ''),
    '#description' => t('Name of the bucket where snapshots will be stored'),
  );

  $form['amber_cache']['aws']['advanced_aws'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['amber_cache']['aws']['advanced_aws']['amber_aws_region'] = array(
    '#type' => 'textfield',
    '#title' => t('S3 Region'),
    '#size' => 30,
    '#default_value' => variable_get('amber_aws_region', 'us-east-1'),
    '#description' => t('Your snapshots will be stored in this <a href="http://docs.aws.amazon.com/general/latest/gr/rande.html#s3_region" target="_blank">S3 region</a>. Unless you are an advanced user, do not modify this setting'),
  );


  global $base_url;
  $form['amber_cache']['advanced']['amber_excluded_sites'] = array(
    '#type' => 'textarea',
    '#title' => t('Excluded URL patterns'),
    '#default_value' => variable_get('amber_excluded_sites', parse_url($base_url, PHP_URL_HOST)),
    '#description' => t('A list of URL patterns, one per line. Amber will not preserve any link that matches one of these patterns. Regular expressions may be used.'),
  );

  $form['amber_cache']['advanced']['amber_excluded_formats'] = array(
    '#type' => 'textarea',
    '#title' => t('Excluded file formats'),
    '#default_value' => variable_get('amber_excluded_formats', ''),
    '#description' => t('A list of of MIME types, one per line. Amber will not preserve any link containing an excluded MIME type.'),
  );

  $form['amber_delivery'] = array(
    '#type' => 'fieldset',
    '#title' => t('Amber Delivery'),
    '#description' => t("Settings that control the user experience"),
  );

  $form['amber_delivery']['amber_available_action'] = array(
    '#type' => 'select',
    '#title' => t('Available links'),
    '#options' => array(
      AMBER_ACTION_NONE => t('None'),
      AMBER_ACTION_HOVER => t('Hover'),
      AMBER_ACTION_POPUP => t('Link to pop-up'),
    ),
    '#default_value' => variable_get('amber_available_action', 0),
    '#description' => t('How a visitor to your site will experience links to pages that are currently available.'),
  );

  $form['amber_delivery']['amber_available_action_hover'] = array(
    '#type' => 'textfield',
    '#title' => t('Hover delay (seconds)'),
    '#size' => 2,
    '#default_value' => variable_get('amber_available_action_hover', 2),
    '#description' => t('Delay before "Site Available" notification appears to a visitor on your site.'),
    '#states' => array(
      'visible' => array(
        ':input[name="amber_available_action"]' => array('value' => '1'),
      ),
    ),
  );

  $form['amber_delivery']['amber_unavailable_action'] = array(
    '#type' => 'select',
    '#title' => t('Unavailable links'),
    '#options' => array(
      AMBER_ACTION_NONE => t('None'),
      AMBER_ACTION_HOVER => t('Hover'),
      AMBER_ACTION_POPUP => t('Link to pop-up'),
      AMBER_ACTION_CACHE => t('Link directly to snapshots'),
    ),
    '#default_value' => variable_get('amber_unavailable_action', 1),
    '#description' => t('How a visitor to your site will experience links to pages that are currently unavailable.'),
  );

  $form['amber_delivery']['amber_unavailable_action_hover'] = array(
    '#type' => 'textfield',
    '#title' => t('Hover delay (seconds)'),
    '#size' => 2,
    '#default_value' => variable_get('amber_unavailable_action_hover', 2),
    '#description' => t('Delay before "Site Unvailable" notification appears to a visitor on your site.'),
    '#states' => array(
      'visible' => array(
        ':input[name="amber_unavailable_action"]' => array('value' => '1'),
      ),
    ),
  );

  $form['amber_country'] = array(
    '#type' => 'fieldset',
    '#title' => t('Activity for a specific country'),
    '#description' => t("Customize the user experience for visitors from a specific country"),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['amber_country']['amber_country_id'] = array(
    '#type' => 'select',
    '#title' => t('Country'),
    '#options' => array("" => "") + _amber_get_countries(),
    '#default_value' => variable_get('amber_country_id', ""),
    '#description' => t('Visitors to your website with browser IP addresses originating in this country will experience specified behavior.'),
  );

  $form['amber_country']['amber_country_available_action'] = array(
    '#type' => 'select',
    '#title' => t('Available sites'),
    '#options' => array(
      AMBER_ACTION_NONE => t('None'),
      AMBER_ACTION_HOVER => t('Hover'),
      AMBER_ACTION_POPUP => t('Link to pop-up'),
    ),
    '#default_value' => variable_get('amber_country_available_action', 0),
    '#description' => t('How links that are available will appear to visitors to your site.'),
    '#states' => array(
      'visible' => array(
        ':input[name="amber_country_id"]' => array('!value' => ''),
      ),
    ),
  );

  $form['amber_country']['amber_country_available_action_hover'] = array(
    '#type' => 'textfield',
    '#title' => t('Hover delay (seconds)'),
    '#size' => 2,
    '#default_value' => variable_get('amber_country_available_action_hover', 2),
    '#description' => t('Delay a visitor to your site will experience before notification appears.'),
    '#states' => array(
      'visible' => array(
        ':input[name="amber_country_id"]' => array('!value' => ''),
        ':input[name="amber_country_available_action"]' => array('value' => '1'),
      ),
    ),
  );

  $form['amber_country']['amber_country_unavailable_action'] = array(
    '#type' => 'select',
    '#title' => t('Unavailable sites'),
    '#options' => array(
      AMBER_ACTION_NONE => t('None'),
      AMBER_ACTION_HOVER => t('Hover'),
      AMBER_ACTION_POPUP => t('Link to pop-up'),
      AMBER_ACTION_CACHE => t('Link directly to snapshot'),
    ),
    '#default_value' => variable_get('amber_country_unavailable_action', 1),
    '#description' => t('How links that are available will appear to visitors to your site.'),
    '#states' => array(
      'visible' => array(
        ':input[name="amber_country_id"]' => array('!value' => ''),
      ),
    ),
  );

  $form['amber_country']['amber_country_unavailable_action_hover'] = array(
    '#type' => 'textfield',
    '#title' => t('Hover delay (seconds)'),
    '#size' => 2,
    '#default_value' => variable_get('amber_country_unavailable_action_hover', 2),
    '#description' => t('Delay a visitor to your site will experience before notification appears.'),
    '#states' => array(
      'visible' => array(
        ':input[name="amber_country_id"]' => array('!value' => ''),
        ':input[name="amber_country_unavailable_action"]' => array('value' => '1'),
      ),
    ),
  );


  $form['amber_services'] = array(
    '#type' => 'fieldset',
    '#title' => t('Optional Functionality'),
    '#description' => t("Connect to academic efforts to retrieve more accurate data and additional snapshots"),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  /* Do not display options to enable NetClerk functionality unless a particular
     Drupal variable is set. It will be unset by default on install */
  if (variable_get('amber_enable_netclerk', 0)) {

    $form['amber_services']['amber_external_availability'] = array(
      '#type' => 'select',
      '#title' => t('Use a third-party database to check site availability'),
      '#options' => array(
        AMBER_EXTERNAL_AVAILABILITY_NONE => t('Do not use an external service'),
        AMBER_EXTERNAL_AVAILABILITY_NETCLERK => t('Use NetClerk'),
      ),
      '#default_value' => variable_get('amber_external_availability', AMBER_EXTERNAL_AVAILABILITY_NONE),
      '#description' => t('Optional: Use site accessibility data from the Berkman Center for Internet & Society at Harvard University'),
    );

    $form['amber_services']['amber_report_availability'] = array(
      '#type' => 'select',
      '#title' => t('Inform a third-party database of site availability'),
      '#options' => array(
        AMBER_REPORT_AVAILABILITY_NONE => t('Do not report site availability to an external service'),
        AMBER_REPORT_AVAILABILITY_NETCLERK => t('Use NetClerk'),
      ),
      '#default_value' => variable_get('amber_report_availability', AMBER_REPORT_AVAILABILITY_NONE),
      '#description' => t('Optional: Contribute site accessibility data for research as part of the Berkman Center for Internet & Society at Harvard University'),
    );
  }

  $form['amber_services']['amber_timegate'] = array(
    '#type' => 'textfield',
    '#title' => t('Check a TimeGate server for additional snapshots'),
    '#default_value' => variable_get('amber_timegate', "http://timetravel.mementoweb.org/timegate"),
    '#description' => t('Optional: Request additional snapshots from the Internet Archive, the Library of Congress web archive, archive.today, and more.'),
  );



  $form = system_settings_form($form);
  $form['#submit'][] = 'amber_settings_submit';
  $form['#validate'][] = 'amber_settings_validate';

  return $form;
}

/* Ensure that the user does not enter invalid regular expressions for excluded sites */
function amber_settings_validate($form, &$form_state) {
  $excluded_sites = explode(PHP_EOL, $form_state['values']['amber_excluded_sites']);
  foreach ($excluded_sites as $site) {
    $blacklistitem = preg_replace("/https?:\\/\\//i", "", trim($site));
    if ($blacklistitem) {
      $blacklistitem = str_replace("@", "\@", $blacklistitem);
      $blacklistitem = '@' . $blacklistitem . '@';

      /* Hide warning messages from preg_match() that can be generated by
         invalid user-entered regular expressions. */
      $default_error_logging_level = error_reporting();
      error_reporting(E_ALL ^ E_WARNING);
      $match_result = preg_match($blacklistitem, "foobar");
      error_reporting($default_error_logging_level);

      if ($match_result === FALSE) {
        form_set_error("amber_excluded_sites", "The regular expression '${site}' is not valid");
      }
    }
  }

  if (($form_state['values']['amber_backend'] == AMBER_BACKEND_LOCAL)) {
    if (empty(variable_get('file_private_path', ''))) {
      form_set_error('amber_backend', t("The Drupal <a href='@url'>Private file system path</a> must be set to use the local storage method.", array('@url' => url('admin/config/media/file-system'))));
    }
  }

  if (($form_state['values']['amber_backend'] == AMBER_BACKEND_PERMA) ||
      (array_key_exists(AMBER_BACKEND_PERMA, $form_state['values']['amber_alternate_backends']))) {
    foreach (array('amber_perma_apikey', 'amber_perma_server_url', 'amber_perma_server_api_url') as $field) {
      if (empty($form_state['values'][$field])) {
        form_set_error($field, t("Required if using the Perma storage engine"));
      }
    }
  }

  if (($form_state['values']['amber_backend'] == AMBER_BACKEND_AMAZON_S3) ||
      (array_key_exists(AMBER_BACKEND_AMAZON_S3, $form_state['values']['amber_alternate_backends']))) {
    $aws_missing_field = FALSE;
    foreach (array('amber_aws_access_key', 'amber_aws_secret_key', 'amber_aws_bucket', 'amber_aws_region') as $field) {
      if (empty($form_state['values'][$field])) {
        form_set_error($field, t("Required if using the Amazon S3 storage engine"));
        $aws_missing_field = TRUE;
      }
    }
    if (!$aws_missing_field) {
      /* Validate the AWS settings.  Duplicates some of the logic in amber_get_storage_by_id() to achieve this */
      $library = libraries_load('aws');
      if (!$library || !$library['loaded']) {
        $library_info = libraries_info('aws');
          form_set_error('amber_backend', "The AWS PHP library is required to use the AWS S3 backend,
            but is not available.
            <a href='${library_info['download url']}'>Download</a> the library and unpack the zip file and
            install into sites/all/libraries/aws.");
      }
      else {
        try {
          /* The $storage value is unused because we're just checking to see if the authorization
             against AWS is successful */
          $storage = new AmazonS3Storage(array(
              'access_key' => $form_state['values']['amber_aws_access_key'],
              'secret_key' => $form_state['values']['amber_aws_secret_key'],
              'bucket' => $form_state['values']['amber_aws_bucket'],
              'region' => $form_state['values']['amber_aws_region'],
            ));
        } catch (\Aws\S3\Exception\S3Exception $e) {
          foreach (array('amber_aws_access_key', 'amber_aws_secret_key', 'amber_aws_bucket', 'amber_aws_region') as $field) {
            form_set_error($field);
          }
          drupal_set_message(t("There is a problem with the provided Amazon
            configuration. Check that the access key and secret key are correct,
            and that they provide write access to the selected bucket. Ensure that
            your bucket name is unique - it cannot have the same name as any other
            bucket in S3."), 'error');
        }
      }
    }
  }
}

/* Custom submit handler to flush filter cache after the settings are updated */
function amber_settings_submit($form, &$form_state) {
  cache_clear_all('*', 'cache_filter', TRUE);
  cache_clear_all('*', 'cache_field', TRUE);
}

/**
 * Get a list of countries for the configuration settings
 */
function _amber_get_countries() {
  if (function_exists("country_get_list")) {
    $countries = country_get_list(); // From Locale module
  }
  else {
    $countries = array(
      'AD' => t('Andorra'),
      'AE' => t('United Arab Emirates'),
      'AF' => t('Afghanistan'),
      'AG' => t('Antigua and Barbuda'),
      'AI' => t('Anguilla'),
      'AL' => t('Albania'),
      'AM' => t('Armenia'),
      'AN' => t('Netherlands Antilles'),
      'AO' => t('Angola'),
      'AQ' => t('Antarctica'),
      'AR' => t('Argentina'),
      'AS' => t('American Samoa'),
      'AT' => t('Austria'),
      'AU' => t('Australia'),
      'AW' => t('Aruba'),
      'AX' => t('Aland Islands'),
      'AZ' => t('Azerbaijan'),
      'BA' => t('Bosnia and Herzegovina'),
      'BB' => t('Barbados'),
      'BD' => t('Bangladesh'),
      'BE' => t('Belgium'),
      'BF' => t('Burkina Faso'),
      'BG' => t('Bulgaria'),
      'BH' => t('Bahrain'),
      'BI' => t('Burundi'),
      'BJ' => t('Benin'),
      'BL' => t('Saint Barthélemy'),
      'BM' => t('Bermuda'),
      'BN' => t('Brunei'),
      'BO' => t('Bolivia'),
      'BR' => t('Brazil'),
      'BS' => t('Bahamas'),
      'BT' => t('Bhutan'),
      'BV' => t('Bouvet Island'),
      'BW' => t('Botswana'),
      'BY' => t('Belarus'),
      'BZ' => t('Belize'),
      'CA' => t('Canada'),
      'CC' => t('Cocos (Keeling) Islands'),
      'CD' => t('Congo (Kinshasa)'),
      'CF' => t('Central African Republic'),
      'CG' => t('Congo (Brazzaville)'),
      'CH' => t('Switzerland'),
      'CI' => t('Ivory Coast'),
      'CK' => t('Cook Islands'),
      'CL' => t('Chile'),
      'CM' => t('Cameroon'),
      'CN' => t('China'),
      'CO' => t('Colombia'),
      'CR' => t('Costa Rica'),
      'CU' => t('Cuba'),
      'CW' => t('Curaçao'),
      'CV' => t('Cape Verde'),
      'CX' => t('Christmas Island'),
      'CY' => t('Cyprus'),
      'CZ' => t('Czech Republic'),
      'DE' => t('Germany'),
      'DJ' => t('Djibouti'),
      'DK' => t('Denmark'),
      'DM' => t('Dominica'),
      'DO' => t('Dominican Republic'),
      'DZ' => t('Algeria'),
      'EC' => t('Ecuador'),
      'EE' => t('Estonia'),
      'EG' => t('Egypt'),
      'EH' => t('Western Sahara'),
      'ER' => t('Eritrea'),
      'ES' => t('Spain'),
      'ET' => t('Ethiopia'),
      'FI' => t('Finland'),
      'FJ' => t('Fiji'),
      'FK' => t('Falkland Islands'),
      'FM' => t('Micronesia'),
      'FO' => t('Faroe Islands'),
      'FR' => t('France'),
      'GA' => t('Gabon'),
      'GB' => t('United Kingdom'),
      'GD' => t('Grenada'),
      'GE' => t('Georgia'),
      'GF' => t('French Guiana'),
      'GG' => t('Guernsey'),
      'GH' => t('Ghana'),
      'GI' => t('Gibraltar'),
      'GL' => t('Greenland'),
      'GM' => t('Gambia'),
      'GN' => t('Guinea'),
      'GP' => t('Guadeloupe'),
      'GQ' => t('Equatorial Guinea'),
      'GR' => t('Greece'),
      'GS' => t('South Georgia and the South Sandwich Islands'),
      'GT' => t('Guatemala'),
      'GU' => t('Guam'),
      'GW' => t('Guinea-Bissau'),
      'GY' => t('Guyana'),
      'HK' => t('Hong Kong S.A.R., China'),
      'HM' => t('Heard Island and McDonald Islands'),
      'HN' => t('Honduras'),
      'HR' => t('Croatia'),
      'HT' => t('Haiti'),
      'HU' => t('Hungary'),
      'ID' => t('Indonesia'),
      'IE' => t('Ireland'),
      'IL' => t('Israel'),
      'IM' => t('Isle of Man'),
      'IN' => t('India'),
      'IO' => t('British Indian Ocean Territory'),
      'IQ' => t('Iraq'),
      'IR' => t('Iran'),
      'IS' => t('Iceland'),
      'IT' => t('Italy'),
      'JE' => t('Jersey'),
      'JM' => t('Jamaica'),
      'JO' => t('Jordan'),
      'JP' => t('Japan'),
      'KE' => t('Kenya'),
      'KG' => t('Kyrgyzstan'),
      'KH' => t('Cambodia'),
      'KI' => t('Kiribati'),
      'KM' => t('Comoros'),
      'KN' => t('Saint Kitts and Nevis'),
      'KP' => t('North Korea'),
      'KR' => t('South Korea'),
      'KW' => t('Kuwait'),
      'KY' => t('Cayman Islands'),
      'KZ' => t('Kazakhstan'),
      'LA' => t('Laos'),
      'LB' => t('Lebanon'),
      'LC' => t('Saint Lucia'),
      'LI' => t('Liechtenstein'),
      'LK' => t('Sri Lanka'),
      'LR' => t('Liberia'),
      'LS' => t('Lesotho'),
      'LT' => t('Lithuania'),
      'LU' => t('Luxembourg'),
      'LV' => t('Latvia'),
      'LY' => t('Libya'),
      'MA' => t('Morocco'),
      'MC' => t('Monaco'),
      'MD' => t('Moldova'),
      'ME' => t('Montenegro'),
      'MF' => t('Saint Martin (French part)'),
      'MG' => t('Madagascar'),
      'MH' => t('Marshall Islands'),
      'MK' => t('Macedonia'),
      'ML' => t('Mali'),
      'MM' => t('Myanmar'),
      'MN' => t('Mongolia'),
      'MO' => t('Macao S.A.R., China'),
      'MP' => t('Northern Mariana Islands'),
      'MQ' => t('Martinique'),
      'MR' => t('Mauritania'),
      'MS' => t('Montserrat'),
      'MT' => t('Malta'),
      'MU' => t('Mauritius'),
      'MV' => t('Maldives'),
      'MW' => t('Malawi'),
      'MX' => t('Mexico'),
      'MY' => t('Malaysia'),
      'MZ' => t('Mozambique'),
      'NA' => t('Namibia'),
      'NC' => t('New Caledonia'),
      'NE' => t('Niger'),
      'NF' => t('Norfolk Island'),
      'NG' => t('Nigeria'),
      'NI' => t('Nicaragua'),
      'NL' => t('Netherlands'),
      'NO' => t('Norway'),
      'NP' => t('Nepal'),
      'NR' => t('Nauru'),
      'NU' => t('Niue'),
      'NZ' => t('New Zealand'),
      'OM' => t('Oman'),
      'PA' => t('Panama'),
      'PE' => t('Peru'),
      'PF' => t('French Polynesia'),
      'PG' => t('Papua New Guinea'),
      'PH' => t('Philippines'),
      'PK' => t('Pakistan'),
      'PL' => t('Poland'),
      'PM' => t('Saint Pierre and Miquelon'),
      'PN' => t('Pitcairn'),
      'PR' => t('Puerto Rico'),
      'PS' => t('Palestinian Territory'),
      'PT' => t('Portugal'),
      'PW' => t('Palau'),
      'PY' => t('Paraguay'),
      'QA' => t('Qatar'),
      'RE' => t('Reunion'),
      'RO' => t('Romania'),
      'RS' => t('Serbia'),
      'RU' => t('Russia'),
      'RW' => t('Rwanda'),
      'SA' => t('Saudi Arabia'),
      'SB' => t('Solomon Islands'),
      'SC' => t('Seychelles'),
      'SD' => t('Sudan'),
      'SE' => t('Sweden'),
      'SG' => t('Singapore'),
      'SH' => t('Saint Helena'),
      'SI' => t('Slovenia'),
      'SJ' => t('Svalbard and Jan Mayen'),
      'SK' => t('Slovakia'),
      'SL' => t('Sierra Leone'),
      'SM' => t('San Marino'),
      'SN' => t('Senegal'),
      'SO' => t('Somalia'),
      'SR' => t('Suriname'),
      'ST' => t('Sao Tome and Principe'),
      'SV' => t('El Salvador'),
      'SY' => t('Syria'),
      'SZ' => t('Swaziland'),
      'TC' => t('Turks and Caicos Islands'),
      'TD' => t('Chad'),
      'TF' => t('French Southern Territories'),
      'TG' => t('Togo'),
      'TH' => t('Thailand'),
      'TJ' => t('Tajikistan'),
      'TK' => t('Tokelau'),
      'TL' => t('Timor-Leste'),
      'TM' => t('Turkmenistan'),
      'TN' => t('Tunisia'),
      'TO' => t('Tonga'),
      'TR' => t('Turkey'),
      'TT' => t('Trinidad and Tobago'),
      'TV' => t('Tuvalu'),
      'TW' => t('Taiwan'),
      'TZ' => t('Tanzania'),
      'UA' => t('Ukraine'),
      'UG' => t('Uganda'),
      'UM' => t('United States Minor Outlying Islands'),
      'US' => t('United States'),
      'UY' => t('Uruguay'),
      'UZ' => t('Uzbekistan'),
      'VA' => t('Vatican'),
      'VC' => t('Saint Vincent and the Grenadines'),
      'VE' => t('Venezuela'),
      'VG' => t('British Virgin Islands'),
      'VI' => t('U.S. Virgin Islands'),
      'VN' => t('Vietnam'),
      'VU' => t('Vanuatu'),
      'WF' => t('Wallis and Futuna'),
      'WS' => t('Samoa'),
      'YE' => t('Yemen'),
      'YT' => t('Mayotte'),
      'ZA' => t('South Africa'),
      'ZM' => t('Zambia'),
      'ZW' => t('Zimbabwe'),
    );
    natcasesort($countries);

  }
  return $countries;
}


