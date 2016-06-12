/**
 * @file
 * Custom scripts for theme.
 */

(function (window, document, $, undefined) {

// @ref: http://kenwheeler.github.io/slick/
var defaults = {
  adaptiveHeight: true,
  autoplay: true,
  autoplaySpeed: 5000,
  arrows: false,
  speed: 700
};

Drupal.behaviors.peceSlider = {
  attach: function (context, settings) {
    $.each(settings.peceSlider || {}, function (selector, config) {
      $(selector, context).slick($.extend(true, {}, defaults, config));
    });
  }
};

})(window, document, jQuery);
