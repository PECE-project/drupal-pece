(function ($) {

  // Drupal Ipsum settings summary.
  Drupal.behaviors.drupal_ipsumFieldsetSummeries = {
    attach: function (context) {
      $('fieldset.drupal_ipsum-form', context).drupalSetSummary(function (context) {
        // If we add more settings we will have to refactor this.
        if ($('.form-checkbox', context).is(':checked')) {
          return Drupal.t('Drupal Ipsum is enabled.');
        }
        else {
          return Drupal.t('Drupal Ipsum is disabled.');
        }
      });
    }
  }
})(jQuery);