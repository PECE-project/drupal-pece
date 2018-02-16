(function ($) {
  Drupal.behaviors.entityconnect = {
    'attach': function(context) {
      ref_field_buttons = {};

      // Treatments for each widget type.
      // Autocomplete widget.
      $(".entityconnect-add.autocomplete", context).each(function() {
        $(this).insertAfter($(this).siblings('.form-type-textfield').children("input").first());
        $(this).insertAfter($(this).siblings('.form-type-select').children("select").first());
      });
      $(".entityconnect-edit.autocomplete", context).each(function() {
        $(this).insertAfter($(this).siblings('.form-type-textfield').children("input").first());
        $(this).insertAfter($(this).siblings('.form-type-select').children("select").first());
      });

      // Autocomplete tags style widget.
      $(".entityconnect-add.textfield", context).each(function() {
        $(this).insertAfter($(this).siblings('.form-type-textfield').children("input").first());
      });
      $(".entityconnect-edit.textfield", context).each(function() {
        $(this).insertAfter($(this).siblings('.form-type-textfield').children("input").first());
      });

      // Select widget.
      $(".entityconnect-add.select", context).each(function() {
        var $form_type_select = $(this).siblings(".form-type-select");
        if ($(this).hasClass('multiple-selection')) {
          $(this).insertAfter($form_type_select.find("label").first());
          $('<div class="clearfix"></div>').insertAfter(this);
        }
        else {
          $(this).insertAfter($form_type_select.children("select"));
        }
      });
      $(".entityconnect-edit.select.single-value", context).each(function() {
        var $form_type_select = $(this).siblings(".form-type-select");
        if ($(this).hasClass('multiple-selection')) {
          $(this).insertAfter($form_type_select.find("label").first());
          $('<div class="clearfix"></div>').insertAfter(this);
        }
        else {
          $(this).insertAfter($form_type_select.children("select"));
        }
      });

      // Radios widget.
      $(".entityconnect-add.radios", context).each(function() {
        $(this).insertAfter($(this).siblings("div.form-type-radios").find("label").first());
      });
      $(".entityconnect-edit.radios", context).each(function() {
        $(this).insertAfter($(this).siblings("div.form-type-radios").find("label").first());
      });

      // Checkboxes widget.
      $(".entityconnect-add.checkboxes", context).each(function() {
        $(this).insertAfter($(this).siblings("div.form-type-checkboxes").find("label").first());
      });
      $(".entityconnect-edit.checkboxes", context).each(function() {
        $(this).insertAfter($(this).siblings("div.form-type-checkboxes").find("label").first());
      });

      // Edit button control.
      $(".entityconnect-edit input").click(function() {

        var wrapper = $(this).parents(".entityconnect-edit"),
            text = $(wrapper).siblings("[type='text']"),
            radio = $(wrapper).siblings("[type='radio']"),
            checkbox = $(wrapper).siblings("[type='checkbox']"),
            select = $(wrapper).siblings("select");

        if(text.length == 0) {
          text = $(wrapper).siblings().find("[type='text']");
        }
        if(radio.length == 0) {
          radio = $(wrapper).siblings().find("[type='radio']:checked");
        }
        if(checkbox.length == 0) {
          checkbox = $(wrapper).siblings().find("[type='checkbox']:checked");
        }
        if(select.length == 0) {
          select = $(wrapper).siblings().find("select:checked");
        }

        if($.trim($(text).val()) == ''
            && ($.trim($(radio).val()) == '' || $.trim($(radio).val()) == '_none')
            && ($.trim($(select).val()) == '' || $.trim($(select).val()) == '_none')
            && $.trim($(checkbox).val()) == '') {
          return false;
        }
        return true;
      });
    }
  };
})(jQuery);
