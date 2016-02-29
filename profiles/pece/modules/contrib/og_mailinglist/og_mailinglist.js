(function ($) {
  $(document).ready(function() {
    $(".toggle-quoted-text").click( function() {
      if ($(this).next().css('display') == "block") {
        $(this).text(Drupal.t('- Show quoted text -'));
      }
      else {
        $(this).text(Drupal.t('- Hide quoted text -'));
      }
      $(this).next().toggle('fast');
    });
  });
})(jQuery);
