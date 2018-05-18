(function ($) {
  /**
   * Provide the summary information for the site notice settings vertical tabs.
   */
  Drupal.behaviors.siteNoticeSettingsSummary = {
    attach: function (context) {
      // The drupalSetSummary method required for this behavior is not available
      // on the Blocks administration page, so we need to make sure this
      // behavior is processed only if drupalSetSummary is defined.
      if (typeof jQuery.fn.drupalSetSummary == 'undefined') {
        return;
      }

      // Notice Status
      $('fieldset#edit-settings-status', context).drupalSetSummary(function (context) {
        var $ret = '';
        var $method = $('input[name="settings[status][status]"]:checked', context);
        var $block  = $('input[name="settings[status][block]"]:checked', context);

        switch ($method.val()) {
          case "0":
            $ret += Drupal.t('Disabled');
            break;

          case "1":
            $ret += Drupal.t('Top');
            break;

          case "2":
            $ret += Drupal.t('Bottom');
            break;
        }

        if ($block.is(':checked')) {
          $ret += Drupal.t(', w/block');
        }

        return $ret;
      });

      // Behavior
      $('fieldset#edit-settings-behavior', context).drupalSetSummary(function (context) {
        var $ret = '';
        var $method = $('input[name="settings[behavior][dismiss]"]:checked', context);

        switch ($method.val()) {
          case "0":
            $ret += Drupal.t('Non-Dismissable');
            break;

          case "1":
            $ret += Drupal.t('Dismissable Permanently');
            break;

          case "2":
            $ret += Drupal.t('Dismissable per Session');
            break;
        }

        return $ret;
      });

      // Path filter
      $('fieldset#edit-settings-path_filter', context).drupalSetSummary(function (context) {
        var $ret = '';
        var $method = $('input[name="settings[path_filter][status]"]:checked', context);
        var $list = $('textarea[name="settings[path_filter][value]"]', context).val();

        $ret += ($method.val() == 1 ? Drupal.t('Include: ') : Drupal.t('Exclude: '));
        $ret += ($list.length > 0 ? $list.replace(/\n/g, ', ') : Drupal.t('None'));

        return $ret;
      });

      // Role filter
      $('fieldset#edit-settings-role_filter', context).drupalSetSummary(function (context) {
        var $ret = '';
        var $roles = [];
        var $method = $('input[name="settings[role_filter][status]"]:checked', context);

        $ret += ($method.val() == 1 ? Drupal.t('Include: ') : Drupal.t('Exclude: '));

        $('.form-checkboxes input:checkbox', context).each(function() {
          if ($(this).is(':checked')) {
            $roles.push($(this).next('label').text().replace(/\ +$/g, ''));
          }
        });

        $ret += ($roles.length > 0 ? $roles.join(', ') : Drupal.t('None'));

        return $ret;
      });
    }
  }
})(jQuery);
