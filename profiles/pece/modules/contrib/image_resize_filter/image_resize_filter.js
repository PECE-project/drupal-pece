/**
 * @file
 * Small enhancement for configuring the options of the Image Resize Filter.
 */

/**
 * Show the link class option if the "Link to the original" option is checked.
 */
(function($){$().ready(function(){
  $('.image-resize-filter-link-options input.form-checkbox').change(function() {
    if (this.checked) {
      $('span.image-resize-filter-rel').css('display', 'inline');
      $('span.image-resize-filter-class').css('display', 'inline');
    }
    else {
      $('span.image-resize-filter-rel').css('display', 'none');
      $('span.image-resize-filter-class').css('display', 'none');
    }
  });

  if ($('.image-resize-filter-link-options input').is('[checked]') == false) {
    $('span.image-resize-filter-rel').css('display', 'none');
    $('span.image-resize-filter-class').css('display', 'none');
  }
});})(jQuery);
