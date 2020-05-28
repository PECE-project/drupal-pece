(function ($) {
  "use strict";

  var $window = $(window);

  var vis_index = 0;

  /**
   * Insert a views infinite scroll view into the document after AJAX.
   *
   * @param {object} $new_view The new view coming from the server.
   */
  $.fn.infiniteScrollInsertView = function ($new_view) {
    var $existing_view = this;
    var $existing_content = $existing_view.find('> .view-content').last().children();
    $new_view.find('> .view-content').last().first().prepend($existing_content);
    $existing_view.replaceWith($new_view);
    $(document).trigger('infiniteScrollComplete', [$new_view, $existing_content]);
  };

  /**
   * Handle the automatic paging based on the scroll amount.
   */
  Drupal.behaviors.views_infinite_scroll_automatic = {
    attach : function(context, settings) {

      var settings = settings.views_infinite_scroll;
      var loadingImg = '<div class="views_infinite_scroll-ajax-loader"><img src="' + settings.img_path + '" alt="loading..."/></div>';

      $('.pager--infinite-scroll.pager--infinite-scroll-auto', context).once().each(function() {
        var $pager = $(this);
        $pager.find('.pager__item').hide();
        if ($pager.find('.pager__item a').length) {
          $pager.append(loadingImg);
        }
        $window.bind('scroll.views_infinite_scroll_' + vis_index, function() {
          if (window.innerHeight + window.pageYOffset > $pager.offset().top - settings.scroll_threshold) {
            $pager.find('.pager__item a').click();
            $window.unbind('scroll.views_infinite_scroll_' + vis_index);
          }
        });
        vis_index++;
      });

    }
  };

})(jQuery);
