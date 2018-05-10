<?php

namespace Drupal\pece_groups;

/**
 * Contains the tools needed to bypass a form's
 * validation system and required fields.
 */
class FormBypasser {

  /**
   * Removes any validations in a form.
   */
  public static function RemoveFormValidations(&$form, $form_id) {
    if(isset($form['#validate']) || isset($form['actions']['submit']['#validate'])) {
      unset($form['#validate']);
      unset($form['actions']['submit']['#validate']);
    }
  }

  /**
   * Removes any required fields in a form.
   */
  public static function RemoveRequiredFields(&$form, $form_id) {
    // Remove required in all fields.
    static::RemoveRequiredFieldsInternal($form);
  }

  /**
   * Removes nested required fields in a form.
   */
  private static function RemoveRequiredFieldsInternal(&$form, array $parent_key = array()) {
    if (!is_array($form)) {
      return array();
    }
    $removed = array();
    foreach ($form as $key => &$value) {
      $key_chain = $parent_key;
      $key_chain[] = $key;
      if (is_array($form[$key])) {
        if (!empty($form[$key]['#required'])) {
          if (isset($form[$key]['#type'])) {
            unset($form[$key]['#required']);
            $removed[implode(':', $key_chain)] = $form[$key];
          }
        }
      }
      $removed = array_merge($removed, self::RemoveRequiredFieldsInternal($form[$key], $key_chain));
    }
    return $removed;
  }
}
