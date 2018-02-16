/**
 * @file
 * Javascript behaviors for the Encrypt module.
 */

(function ($) {

  Drupal.behaviors.encryptFieldsetSummaries = {
    attach: function (context) {
      // Provide the vertical tab summaries.
      $('fieldset#edit-method-settings', context).drupalSetSummary(function(context) {
        var vals = [];
        var label = $('#edit-encrypt-encryption-method input:checked', context).next('label');
        if (label.text()) {
          vals.push(Drupal.checkPlain(label.text()));
        }
        else {
          vals.push(Drupal.t('No method chosen'))
        }
        return vals.join(', ');
      });
      $('fieldset#edit-provider-settings', context).drupalSetSummary(function(context) {
        var vals = [];
        var label = $('#edit-encrypt-key-provider input:checked', context).next('label');
        if (label.text()) {
          vals.push(Drupal.checkPlain(label.text()));
        }
        else {
          vals.push(Drupal.t('No provider chosen'))
        }
        return vals.join(', ');
      });
    }
  };

})(jQuery);
