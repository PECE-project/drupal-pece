/**
 * @file
 * Custom scripts for Dashboard Menu.
 */
(function ($) {
  Drupal.behaviors.artifactsAccordion = {
    attach: function (context, settings) {
      var $context = $(context);
      var $items = $context.find('.dashboard-artifact-item').parent();
      var $submenu = $context.find('.dashboard-artifact-submenu ul');
      var $toggleButton = $context.find('.dashboard-artifact-toggle');

      // Creates submenu only in the first load.
      $('.pane-pece-dashboard-dashboard-add-content').once('dashboard-submenu', createSubmenu);


      // Event listeners
      // @TODO: find a better way to prevent duplicated listener to $toggleButton.
      $toggleButton.off('click');
      $toggleButton.on('click', toggle);


      // Methods
      function toggle(event) {
        event.preventDefault();

        if ($(this).hasClass('opened')) {
          hide();
        } else {
          show();
        }
      }

      function show() {
        $submenu.slideDown(400);
        $toggleButton.addClass('opened');
      }

      function hide() {
        $submenu.slideUp(400);
        $toggleButton.removeClass('opened');
      }

      function createSubmenu() {
        $items.wrapAll('<li class="dashboard-artifact-submenu"><ul></ul></li>');
        $submenu = $('.dashboard-artifact-submenu').find('ul');

        $submenu.parent().prepend('<a class="dashboard-artifact-toggle" href="#">Artifacts</a>');
        $toggleButton = $('.dashboard-artifact-toggle');
      }
    }
  }
})(jQuery);
