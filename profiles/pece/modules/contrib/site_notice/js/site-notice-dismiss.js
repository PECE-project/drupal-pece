/**
 * @file
 * Ajax callbacks for notice dismissal.
 */
(function ($) {
  Drupal.behaviors.siteNoticeDismiss = {
    links: [],
    attach: function (context) {
      // Get the dismissal links.
      this.links = $("a[ajax='site-notice-dismiss']", context);

      // Kick out if there are no links.
      if (this.links.length == 0) {
        return;
      }

      // Bind the action.
      this.links.bind('click', function() {
        var link    = $(this);
        var href    = link.attr('href');
        var notice  = link.closest("*[ajax='site-notice']");
        var wrapper = link.closest("*[ajax='site-notices']");

        // If there is only one notice in the wrapper, act on the wrapper, not
        // on the individual notice so we remove the entire element.
        if ($("*[ajax='site-notice']", wrapper).length == 1) {
          notice = wrapper;
        }

        $.ajax({
          url: href,
          type: 'POST',
          dataType: 'json',
          data: {ajax: true},
          beforeSend: function() {
            link.fadeTo('fast', 0.5);
          },
          success: function(res) {
            if (res == true) {
              notice.slideUp('fast', function() {
                $(this).remove();
              });
            }
            else {
              location.href = href;
            }
          },
          error: function(a,b,c) {
            // Manually send the request by going to the page
            location.href = href;
          },
        });

        return false;
      });
    }
  }
})(jQuery);
