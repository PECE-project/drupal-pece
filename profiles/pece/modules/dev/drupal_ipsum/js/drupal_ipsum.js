// Drupal Ipsum generation form results

(function($){
  Drupal.behaviors.drupal_ipsum = {
    attach: function(context, settings) {
      var $link = $('a.drupal_ipsum_select', context);

      if ($link.length) {
        $link.click(function(){

          var $text = $('div.drupal_ipsum_text', context),
          $textarea = $('textarea.drupal_ipsum_textarea', context);

          if ($text.is(':visible')) {
            $text.hide();
            $textarea.show().get(0).select();
            $(this).text(Drupal.t('Select none'));
          } else {
            $text.show();
            $textarea.hide()
            $(this).text(Drupal.t('Select all'));
          }
        });
      }
    }
  }
}(jQuery));