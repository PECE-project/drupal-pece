<?php

/**
 * @file
 * Admin page callbacks for the mimedetect module.
 */

/**
 * Form builder; configure mimedetect settings.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function mimedetect_settings() {
  // Mime detection engines.
  $form['engines'] = array(
    '#type'          => 'fieldset',
    '#title'         => t('MIME detection engines'),
  );

  // PHP Fileinfo.
  $form['engines']['mimedetect_enable_file_info'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('PHP fileinfo'),
    '#default_value' => variable_get('mimedetect_enable_file_info', TRUE),
    '#description'   => t('Use the <a href="@url">PHP file information extension</a>. This is the preferred method.', array('@url' => 'http://php.net/manual/en/book.fileinfo.php')),
  );

  // Disable fileinfo option if extension not present.
  if (!extension_loaded('fileinfo')) {
    $form['engines']['mimedetect_enable_file_info']['#attributes'] = array('disabled' => TRUE);
    $form['engines']['mimedetect_enable_file_info']['#default_value'] = FALSE;
  }

  // UNIX file command.
  $form['engines']['mimedetect_enable_file_binary'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('UNIX file'),
    '#default_value' => variable_get('mimedetect_enable_file_binary', FALSE),
    '#description'   => t('System call to the file command. Used when PHP fileinfo fails or is not available.'),
  );

  $form['engines']['mimedetect_file_binary'] = array(
    '#type'          => 'textfield',
    '#title'         => t("Path to the 'file' command"),
    '#default_value' => variable_get('mimedetect_file_binary', '/usr/bin/file'),
    '#required'      => TRUE,
    '#description'   => t("The path to the executable 'file' binary."),
    '#states'        => array(
      'visible'        => array(
        ':input[name="mimedetect_enable_file_binary"]' => array('checked' => TRUE),
      )
    )
  );

  $form['engines']['mimedetect_enable_file_extension'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('File extension'),
    '#default_value' => TRUE,
    '#attributes'    => array('disabled' => TRUE),
    '#description'   => t('MIME detection based on filename extension. This is the system default method, used as fall back when all others fail or are not available.'),
  );

  // Custom MIME 'magic' file.
  $form['mimedetect_magic'] = array(
    '#type'          => 'textfield',
    '#title'         => t("Custom 'magic' file path"),
    '#default_value' => variable_get('mimedetect_magic', ''),
    '#description'   => t("Used by any magic based engine. Leave blank to rely on system magic file or PHP internal info."),
    '#states'        => array(
      'enabled'        => array(
        array(
          ':input[name="mimedetect_enable_file_info"]' => array('checked' => TRUE),
        ),
        array(
          ':input[name="mimedetect_enable_file_binary"]' => array('checked' => TRUE),
        ),
      )
    )
  );

  return system_settings_form($form);
}

/**
 * Validation handler for the MimeDetect settings form.
 */
function mimedetect_settings_validate($form_id, &$form_state) {
  // Test custom magic file path
  $magic_file = $form_state['values']['mimedetect_magic'];
  if (!empty($magic_file) && !file_exists($magic_file)) {
    form_set_error('mimedetect_magic', t("The path %path does not exist or is not readable by your webserver.", array('%path' => $magic_file)));
    return;
  }

  // Test fileinfo settings.
  if ($form_state['values']['mimedetect_enable_file_info']) {
    if (!extension_loaded('fileinfo') || !@finfo_open(FILEINFO_MIME, $magic_file)) {
      if (!empty($magic_file)) {
        form_set_error('mimedetect_magic', t('Fileinfo cannot load the configured magic file <em>@file</em>. It could be corrupted. Try another magic file or remove your magic file path settings to use defaults.', array('@file' => $magic_file)));
      } else {
        form_set_error('mimedetect_enable_file_info', t('Fileinfo could not load magic information. Check the MAGIC environment variable on your system and that fileinfo PHP extension is properly installed.'));
      }
    }
  }

  // Test file binary settings.
  if ($form_state['values']['mimedetect_enable_file_binary']) {
    if (empty($form_state['values']['mimedetect_file_binary'])) {
      form_set_error('mimedetect_file_binary', t("You must specify the path to the 'file' binary if it is enabled."));
    }

    $filebin = $form_state['values']['mimedetect_file_binary'];

    if (!is_executable($filebin)) {
      if (!file_exists($form_state['values']['mimedetect_file_binary'])) {
        form_set_error('mimedetect_file_binary', t("The path %path does not exist or is not readable by your webserver.", array('%path' => $filebin)));
      }
      else {
        form_set_error('mimedetect_file_binary', t("%path is not executable by your webserver.", array('%path' => $filebin)));
      }
    } else {
      // Execution test.
      $exit_code = 0;
      $empty = NULL;
      exec($filebin . ( !empty($magic_file)? ' --magic-file=' . escapeshellarg($magic_file) : '' ) . ' --list', $empty, $exit_code);
      if ($exit_code !== 0) {
        if (!empty($magic_file)) {
          form_set_error('mimedetect_enable_file_binary', t('File command execution failed with exit code <em>@code</em>. Could not load the magic file <em>@file</em>.', array('@code' => $exit_code, '@file' => $magic_file)));
        } else {
          form_set_error('mimedetect_enable_file_binary', t('File command execution failed with exit code <em>@code</em>.', array('@code' => $exit_code)));
        }
      }
    }
  }

  if (!$form_state['values']['mimedetect_enable_file_info'] && !$form_state['values']['mimedetect_enable_file_binary']) {
    drupal_set_message(t("MimeDetect is using the browser supplied filename for file extension lookups. It is strongly recommended that you install and configure the PHP Fileinfo Extension or the UNIX 'file' command to provide more accurate sever-side mime type detection."), 'warning');
  }
}
