/**
 * @file
 * Custom scripts for theme.
 */
(function ($) {
  Drupal.behaviors.artifactsAccordion = {
    attach: function (context, settings) {
      var $context = $(context);

      var $items = $context.find('.dashboard-add-content-link').text().contain('artifact').closest('li');
    }
  }
})(jQuery);
