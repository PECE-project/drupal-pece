(function ($) {

  $(document).ready(function () {
    $('.view-id-frontpage_image_slider').cycle({
      fx: 'scrollLeft',
      fit: 0,
      width: '100%',
      slideExpr: '.view-content div img'
    });
  });

})(jQuery);
