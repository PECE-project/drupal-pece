/**
 * @file
 * Custom scripts for theme.
 */

(function (window, document, $, undefined) {

Drupal.behaviors.panelsPackeryAdmin = {
  attach: function (context, settings) {
    $.each(settings.packery || {}, function (selector, config) {
      // Disable IPE dragging.
      Drupal.PanelsIPE.editors[config.IPECacheKeys].sortableOptions.cancel = '*';

      var $ipeContainer = $(config.IPEContainer, context);
      var $containers = $(selector, context);
      var isEditing = $ipeContainer.hasClass('panels-ipe-editing');

      if (isEditing) {
        $containers.each(initializePackeryAdmin(config));
        $containers.find('.panels-ipe-handlebar-wrapper .panels-ipe-linkbar a').on('mousedown', function (e) {
          e.stopPropagation();
        })
      }

      // Refresh often to avoid broken layouts.
      setTimeout(function () {
        $containers.packery();
      }, 100)
    });
  }
};

/**
 * Packery initializer factory.
 */
function initializePackeryAdmin(config) {
  return function () {
    var $container = $(this);
    var $items = $container.find(config.itemSelector);

    $items.each(function(i, item ) {
      $container.packery('bindDraggabillyEvents', new Draggabilly(item));
    });

    $container.on('dragItemPositioned', reorder);
  };
}

/**
 * After reordering, make sure to reflect order in the DOM.
 */
function reorder() {
  var $container = $(this)
  $container.packery('getItemElements').forEach(function (item) {
    $container.append(item)
  });
}

})(window, document, jQuery);
