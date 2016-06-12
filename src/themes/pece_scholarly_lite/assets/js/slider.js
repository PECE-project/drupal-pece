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
      $(selector, context).slick($.extend(true, {}, defaults, config)).each(function () {
        var $slider = $(this);
        if (config.sameHeight) $slider.on('setPosition', sameHeight);
      });
    });
  }
};

function sameHeight() {
  $(this).find('.slick-slide')
    .height('auto')
    .css('height', $('.slick-track', this).height() + 'px');
}

})(window, document, jQuery);
