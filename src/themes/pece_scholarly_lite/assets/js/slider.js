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
  arrows: true,
  dots: true,
  speed: 700
};

Drupal.behaviors.peceSlider = {
  attach: function (context, settings) {
    $.each(settings.peceSlider || {}, function (selector, config) {
      $(selector, context)
        .filter(':not(.slick-initialized)')
        .slick($.extend(true, {}, defaults, config))
        .on('setPosition', sameHeight);
    });
  }
};

function sameHeight() {
  var $slick = $(this);
  var $slides = $slick.find('.slick-slide');
  var instance = $slick.slick('getSlick');
  var sameHeight = instance.activeBreakpoint && instance.breakpointSettings[instance.activeBreakpoint].sameHeight || instance.options.sameHeight;

  $slides.height('auto');

  if (sameHeight) {
    $slides.height('auto').css('height', $slick.find('.slick-track').height() + 'px');
  }
}

})(window, document, jQuery);
