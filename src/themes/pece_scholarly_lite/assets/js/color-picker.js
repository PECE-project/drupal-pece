/**
 * @file
 * Javascript for Farbtastic colorfield widget.
 */

/**
 * Provides a farbtastic colorpicker for the widget.
 */
(function ($) {
  Drupal.behaviors.colorfield = {
    attach: function (context) {
      // Display the current value as background if the field has one.
      $(".pece-field-colorpicker", context)
      .each(function () {
        $(this).css('background-color', $(this).val());
      })
      .focus(function () {
        var edit_field = this;
        var picker = $(this).closest('div').parent().find(".pece-colorpicker");

        // Hide all color pickers except this one.
        $(".pece-colorpicker").hide();
        $(picker).show();

        var updateBackground = function () {
          // Catch errors caused by invalid hex codes.
          var unpacked = farb.unpack(this.value);
          if (!unpacked) {
            return;
          }
          // If a valid color, set background/foreground colors.
          $(this).css({
            backgroundColor: this.value,
            'color': farb.RGBToHSL(unpacked)[2] > 0.5 ? '#000' : '#fff'
          });
        }

        var updatePicker = function () {
          farb.setColor(this.value);
        }

        // Adjust the background color on keyup and onload.
        $(edit_field)
            .unbind('keyup.colorfield')
            .bind('keyup.colorfield', updateBackground)
            .bind('keyup.colorfield', updatePicker);

        // Attach Farbtastic.
        var farb = $.farbtastic(picker);
        farb.setColor(edit_field.value);
        farb.linkTo(function (color) {
          edit_field.value = color;
          updateBackground.apply(edit_field);
        });
      })
      .focusout(function () {
        $(".pece-colorpicker").hide();
      });
    }
  }
})(jQuery);
