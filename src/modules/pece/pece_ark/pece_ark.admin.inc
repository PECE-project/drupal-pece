<?php

/**
 * Provides form to define settings.
 *
 * Settings which must be set include:
 *  - Naming Assigning Authority Number
 *  - Content types
 *  - Fields
 */
function pece_ark_settings($form, &$form_state) {

  $form['ark_naan'] = array(
    '#type' => 'textfield',
    '#title' => t('Name Assigning Authority Number'),
    '#description' => t('Before your ARK identifiers can be shared publicly, a NAAN must be provided to you by the <a href="http://www.cdlib.org/">California Digital Library</a>. See <a href="https://wiki.ucop.edu/display/Curation/ARK#ARK-NAAN:theNameAssigningAuthorityNumber">the ARK wiki for more information</a>. Use "pending" here to test your site before you have a number.'),
    '#default_value' => variable_get('ark_naan', 'pending'),
    '#size' => 10,
    '#required' => TRUE,
  );

  $form['ark_name_prefix'] = array(
    '#type' => 'textfield',
    '#title' => t('Prefix for ARK names'),
    '#description' => t('Every name assigning authority must have a namespace management strategy. A time-honored technique is to hierarchically partition a namespace into subnamespaces using prefixes that guarantee non-collision of names in different partition. This practice is strongly encouraged for all NAAs, especially when subnamespace management will be delegated to other departments, units, or projects within an organization.'),
    '#default_value' => variable_get('ark_name_prefix', pece_ark_default_prefix()),
    '#size' => 10,
  );

  $form['ark_ezid_user'] = array(
    '#type' => 'textfield',
    '#title' => t('Username for the University of California Digital Library'),
    '#description' => t('Username provided by University of California EZID to use the API system'),
    '#default_value' => variable_get('ark_ezid_user'),
    '#size' => 30,
  );

  $form['ark_ezid_password'] = array(
    '#type' => 'password',
    '#title' => t('Password for the University of California Digital Library'),
    '#description' => t('Password provided by University of California EZID to use the API system'),
    '#default_value' => variable_get('ark_ezid_password'),
    '#size' => 30,
  );

  $form['ark_remote_server_address'] = array(
    '#type' => 'textfield',
    '#title' => t('Remote ARK server address. Normally the server address for the University of California Digital Library'),
    '#description' => t('Server address for the University of California EZID to use the API system'),
    '#default_value' => variable_get('ark_remote_server_address', ARK_DEFAULT_REMOTE_SERVER_ADDRESS),
    '#size' => 90,
  );

  $form['ark_remote_identifier_site_address'] = array(
    '#type' => 'textfield',
    '#title' => t('Remote Identifier Site Address. By default "https://n2t.net/"'),
    '#description' => t('Remote Identifier Site Address. The remote Identifiear as URL will composed by this server url + the Remote Ark Name value. Ex: https://n2t.net/ark:/99999/fk4pecetest15'),
    '#default_value' => variable_get('ark_remote_identifier_site_address', ARK_DEFAULT_REMOTE_IDENTIFIER_SITE_ADDRESS),
    '#size' => 90,
  );

  $node_types = pece_ark_all_available_node_types();
  $form['ark_node_types'] = array(
    '#type' => 'checkboxes',
    '#multiple' => TRUE,
    '#title' => t('Content types'),
    '#description' => t('Select the content types in which every piece of content should receive Archival Resource Key identifiers.'),
    '#options' => $node_types,
    '#default_value' => variable_get('ark_node_types', ''),
  );

  $form['fields_explanation'] = array(
    '#markup' => '<p>' . t('Select the fields to use for Who (a textfield) and When (a datefield) for each resource/content type. (What is always matched to the content title.)') . '</p>',
  );

  foreach ($node_types as $type_machine_name => $type_human) {
    $who = 'ark_' . $type_machine_name . '_who';

    $form['fs-' . $type_machine_name] = array(
      '#type' => 'fieldset',
      '#title' => $type_human,
    );
    $form['fs-' . $type_machine_name][$who] = array(
      '#type' => 'select',
      '#title' => t('Who'),
      '#options' => pece_ark_fields_by_type_by_bundle('node', $type_machine_name, 'text'),
      '#description' => t('The @entity_type @bundle needs a @field_type field to be used. If no other option being choose, the @bundle Author will be used.',
        array('@entity_type' => 'node', '@bundle' => $type_machine_name, '@field_type' => 'text')),
      '#default_value' => variable_get($who, ARK_SELECT_DEFAULT_WHO_OPTION_VALUE),
    );

    $compositeWhoFields = pece_ark_check_if_composite_who_fields_exists_in_content_type($type_machine_name);
    if ($compositeWhoFields) {
      $composite_who_options = array();
      foreach ($compositeWhoFields as $compositeWhoField) {
        $composite_who_options[$compositeWhoField] = $compositeWhoField;
      }

      $composite_who = 'ark_' . $type_machine_name . '_composite_who';
      $default_value = variable_get($composite_who);
      $checked_all = (count(array_unique(array_values($default_value))) == 1) ? array('checked' => 'checked') : array();

      $form['fs-' . $type_machine_name][$composite_who] = array(
        '#title' => t('Use fields bellow as a composite field for WHO'),
        '#type' => 'checkboxes',
        '#description' => t('Choose composite WHO fields.'),
        '#options' => $composite_who_options,
        '#default_value' => $default_value,
        '#attributes' => $checked_all,
        '#tree' => TRUE,
        '#states' => array(
          'visible' => array(
            'select[name="' .$who. '"]' => array('value' => 'use_composite_who'),
          ),
        ),
      );
    }

    $when = 'ark_' . $type_machine_name . '_when';
    $form['fs-' . $type_machine_name][$when] = array(
      '#type' => 'select',
      '#title' => t('When'),
      '#options' => pece_ark_fields_by_type_by_bundle('node', $type_machine_name, 'date'),
      '#description' => t('The @entity_type @bundle needs a @field_type field to be used. If no other option being choose, the @bundle creation date will be used.',
        array('@entity_type' => 'node', '@bundle' => $type_machine_name, '@field_type' => 'date')),
      '#default_value' => variable_get($when, ARK_SELECT_DEFAULT_WHEN_OPTION_VALUE),
    );

  }

  $form['#validate'][] = 'pece_ark_settings_validate';

  return system_settings_form($form);
}

/**
 * Form validation logic for the contact form.
 */
function pece_ark_settings_validate($form, &$form_state) {
  if (!pece_ark_naan_format_valid($form_state['values']['ark_naan'])) {
    form_set_error('ark_naan', t('NAAN must be a number, or, if you do not yet have one, test the site using "pending".'));
  }
  if (!$form_state['values']['ark_node_types']) {
    form_set_error('ark_node_types', t('You must select at least one content type to use as a resource.'));
  }
  else {
    foreach ($form_state['values']['ark_node_types'] as $type_machine_name => $type_human) {
      if (!$form_state['values']['ark_' . $type_machine_name . '_who']) {
        form_set_error('ark_' . $type_machine_name . '_who', t('There must be a text field on the selected %type_human content type used for "Who".', array('%type_human' => $type_human)));
      }
      if (!$form_state['values']['ark_' . $type_machine_name . '_when']) {
        form_set_error('ark_' . $type_machine_name . '_when', t('There must be a date field on the selected %type_human content type used for "When".', array('%type_human' => $type_human)));
      }
    }
  }
}

/**
 * Returns all available node types defined on the site.
 */
function pece_ark_all_available_node_types() {
  return _node_types_build()->names;
}

function pece_ark_check_if_composite_who_fields_exists_in_content_type($bundle_name = NULL, array $fields = null) {
  $entity_type = 'node';
  $result = NULL;

  $composite_who_fields = variable_get('ark_composite_who_field') ? array_map('trim', explode(',', variable_get('ark_composite_who_field'))) : ARK_COMPOSITE_WHO_FIELD;
  // exit(var_dump($composite_who_fields));

  $fields = (!is_null($fields) && is_array($fields) && count($fields)) ? $fields : $composite_who_fields;
  if (isset($bundle_name)) {
    $fields_list = field_info_instances($entity_type, $bundle_name);
    if ($fields_list) {
      $fields_name = array_keys($fields_list);
      $array_comparison = array_intersect($fields_name, $fields);
      $result = (count($array_comparison)) ? $array_comparison : false;
    }
    return $result;
  }
}

/**
 * Helper function to return all fields of one type on one bundle.
 */
function pece_ark_fields_by_type_by_bundle($entity_type, $bundle, $field_type) {
  $result_fields = array();
  $fields = field_info_field_map();
  foreach ($fields as $field => $info) {
    if ($info['type'] == $field_type &&
        in_array($entity_type, array_keys($info['bundles'])) &&
        in_array($bundle, $info['bundles'][$entity_type])) {
      $result_fields[$field] = $field;
    }
  }

  if($field_type == 'date') {
    $result_fields[ARK_SELECT_DEFAULT_WHEN_OPTION_VALUE] = t('Default value');
  }

  if($field_type == 'text') {
    $result_fields[ARK_SELECT_DEFAULT_WHO_OPTION_VALUE] = t('Default value');

    if (pece_ark_check_if_composite_who_fields_exists_in_content_type($bundle)) {
      $result_fields['use_composite_who'] = t('Use a composite WHO field with the fields bellow.');
    }
  }

  if (!$result_fields) {
    $result_fields[''] = t('The @entity_type @bundle needs a @field_type field to be used.',
        array('@entity_type' => $entity_type, '@bundle' => $bundle, '@field_type' => $field_type));
  }

  return $result_fields;
}

/**
 * Provide a default ARK prefix (random, as recommended by ARK).
 */
function pece_ark_default_prefix() {
  return ARK_DEFAULT_PRE_PREFIX . substr(str_shuffle('bcdfghjklmnpqrstvwxyz123456789'), 0, 4);
}
