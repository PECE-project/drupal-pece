/**
 * @file
 * Masonry script.
 */

(function($) {

Drupal.behaviors.masonry = {
  attach: function(context, settings) {

    // Iterate through all Masonry instances
    $.each(Drupal.settings.masonry, function (container, settings) {
      // Set container
      var $container = $(container);

      // Set options
      var $options = new Object();
      if (settings.item_selector) {
        $options.itemSelector = settings.item_selector;
      }
      if (settings.column_width) {
        if (settings.column_width_units == 'px') {
          $options.columnWidth = parseInt(settings.column_width);
        }
        else if (settings.column_width_units == '%') {
          $options.columnWidth = ($container.width() * (settings.column_width / 100)) - settings.gutter_width ;
        }
        else {
          $options.columnWidth = settings.column_width;
      }
        }
      if (settings.stamp) {
        $options.stamp = settings.stamp;
      }
      $options.gutter = settings.gutter_width;
      $options.isResizeBound = settings.resizable;
      $options.isFitWidth = settings.fit_width;
      if (settings.rtl) {
        $options.isOriginLeft = false;
      }
      if (settings.animated) {
        $options.transitionDuration = settings.animation_duration + 'ms';
      }
      else {
        $options.transitionDuration = 0;
      }

      // Apply Masonry to container
      if (settings.images_first) {
        $container.imagesLoaded(function () {
          if ($container.hasClass('masonry-processed')) {
            $container.masonry('reloadItems').masonry('layout');
          }
          else {
            $container.once('masonry').masonry($options);
          }
        });
      }
      else {
        if ($container.hasClass('masonry-processed')) {
          $container.masonry('reloadItems').masonry('layout');
        }
        else {
          $container.once('masonry').masonry($options);
        }
      }
    });
  }
};
})(jQuery);
