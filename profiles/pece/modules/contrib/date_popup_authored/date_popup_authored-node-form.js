(function ($) {

Drupal.behaviors.datePopupAuthoredFieldsetSummaries = {
  attach: function (context) {
    // Provide the vertical tab summaries.
    $('fieldset#edit-date-popup-authored', context).drupalSetSummary(function(context) {
      var vals = [];
      if ($('#edit-date-popup-authored-enabled', context).is(':checked')) {
        vals.unshift(Drupal.t('Enabled'));

        // Date format.
        var format = $('.form-item-date-popup-authored-format select option:selected', context).text();
        vals.push(Drupal.t('Date format: @format', {'@format': format}));

        // Date range.
        var range = $('#edit-date-popup-authored-year-range', context).val();
        vals.push(Drupal.t('Display &#x00B1;@range years', {'@range': range}));
      }
      else {
        vals.unshift(Drupal.t('Disabled'));
      }
      return vals.join(', ');
    });
  }
};

})(jQuery);