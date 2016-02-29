(function ($, undefined) {

Drupal.behaviors.peceAjaxViewsAutocomplete = {
  attach: function (context, settings) {
    var $context = $(context);

    $.each(settings.views && settings.views.ajaxViews || {}, function (key, conf) {
      if (!conf.view_dom_id) return;

      var selector = '.view-dom-id-' + conf.view_dom_id.replace(/_/g, '-');
      var $view = $context.is(selector) ? $context : $context.find(selector);
      var $input = $view.find('input.form-autocomplete');
      var $submit = $view.find('input[type=submit], button[type=submit]').eq(0);

      $input.on('autocompleteSelect', function () {
        $submit.trigger('click');
      });
    });
  }
};

})(jQuery);
