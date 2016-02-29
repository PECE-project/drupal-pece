(function($) {
  Drupal.behaviors.tvi_initialize = {
    attach: function(context, settings) {
      //--------------------------------------------------------------------------
      // Properties

      var current_display = $('#tvi-display-selector', context).val();
      var all_displays = $('#tvi-display-selector', context).children('option');

      //--------------------------------------------------------------------------
      // Handlers

      var set_active_option = function() {
        $('#tvi-display-selector', context).val(current_display);
      }

      //--------------------------------------------------------------------------

      var view_change_handler = function() {
        var view_name = $('#tvi-view-selector', context).val();

        if (!view_name) {
          view_name = $('#tvi-view-selector option:first', context).val();
          $('#tvi-view-selector', context).val(view_name);
        }

        // Load new view displays.
        var ds = $('#tvi-display-selector', context).html('');
        all_displays.each(function(i,item) {
          if ($(item).attr('value').indexOf(view_name + ':') == 0) {
            ds.append($(item));
          }
        });
        ds.val($('[selected]', ds).val());
      }

      //--------------------------------------------------------------------------
      // Start

      // Javascript is enabled.
      $('.javascript-warning', context).hide();

      // Reload displays when views are changed.
      $('#tvi-view-selector', context).change(view_change_handler);
      view_change_handler();
    }
  };
})(jQuery);
