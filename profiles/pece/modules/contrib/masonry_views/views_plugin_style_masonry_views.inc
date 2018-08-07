<?php
/**
 * @file
 * Contains the Masonry style plugin.
 */

class views_plugin_style_masonry_views extends views_plugin_style {

  /**
   * Set default options.
   */
  function option_definition() {
    $options = parent::option_definition();

    // Get default options
    $default_options = masonry_default_options();

    // Set default values for Masonry
    foreach ($default_options as $option => $default_value) {
      $options[$option] = array(
        'default' => $default_value,
      );
      if (is_int($default_value)) {
        $options[$option]['bool'] = TRUE;
      }
    }

    return $options;
  }

  /**
   * Render the given style.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // Add Masonry options to views form
    $form['masonry'] = array(
      '#type' => 'fieldset',
      '#title' => t('Masonry'),
    );
    if (masonry_installed()) {
      masonry_add_options_to_form($form, $this->options);

      // Display each option within the Masonry fieldset
      foreach (masonry_default_options() as $option => $default_value) {
        $form[$option]['#fieldset'] = 'masonry';
      }

      // Views doesn't use FAPI states, so set dependencies instead
      $form['masonry_animated']['#dependency'] = array(
        'edit-style-options-masonry-resizable' => array(1),
      );
      $form['masonry_animation_duration']['#dependency'] = array(
        'edit-style-options-masonry-animated' => array(1),
      );
    }
    else {
      // Disable Masonry as plugin is not installed
      $form['masonry_disabled'] = array(
        '#markup' => t('These options have been disabled as the jQuery Masonry plugin is not installed.'),
        '#fieldset' => 'masonry',
      );
    }
  }

}

