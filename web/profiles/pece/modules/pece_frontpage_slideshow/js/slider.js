jQuery('.frontpage-slideshow-view-wrapper .view-content').addClass('owl-carousel').addClass('owl-theme');

jQuery(document).ready(function () {
  jQuery(".owl-carousel").owlCarousel({
    items: 1,
    nav: true,
    loop: true,
    margin: 20,
    dots: false,
  });
});
