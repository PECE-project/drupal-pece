/**
 * @file
 * Custom scripts for theme.
 */

(function (window, document, $, undefined) {

$(document).on('opening', '[data-remodal-id]', function (e) {
  var $modal = $(this);
  var $sliders = $modal.find('.slick-slider');

  // Handle full-modal sliders.
  if ($modal.is('.slick-slider')) $sliders = $sliders.add($modal);

  $sliders.each(function () {
    var $slider = $(this)
    var Slick = $slider.slick('getSlick');
    var options = Slick && Slick.options;
    if (options) $slider.slick('unslick').slick(options);
  });
});

})(window, document, jQuery);
