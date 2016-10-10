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
        $containers.packery('shiftLayout');
      }, 100)
    });
  }
};

/**
 * Packery initializer factory.
 */
function initializePackeryAdmin(config) {
  var ipe = Drupal.PanelsIPE.editors[config.IPECacheKeys];

  return function () {
    var $container = $(this);
    var $items = $container.find(config.itemSelector);
    var $form = $('#panels-ipe-edit-control-form');

    $items.each(function (i, item) {
      $container.packery('bindDraggabillyEvents', new Draggabilly(item));
    });

    if (!$form.find('[name="packery_positions"]').length) {
      $form.append('<input type="hidden" name="packery_positions" value="{}" />')
    }

    $container
      .on('dragItemPositioned', reorder)
      .on('dragItemPositioned', savePosition(ipe));
  };
}

/**
 * After dragging, make sure to reflect order in the DOM.
 */
function reorder() {
  var $container = $(this)
  $container.packery('getItemElements').forEach(function (item) {
    $container.append(item)
  });
}

/**
 * After dragging, save position of each item.
 */
function savePosition(ipe) {
  return function () {
    $('[name="packery_positions"]').val(JSON.stringify($(this).packery('getShiftPositions')))
  };
}


// Custom Packery.prototype methods.
// ---------------------------------

/**
 * Get JSON positioning data from items.
 */
Packery.prototype.getShiftPositions = function () {
  var instance = this

  return this.items.reduce(function (result, item) {
    var uuid = $(item.element).find('[data-pane-uuid]').data('pane-uuid') || null;

    return $.extend(result, uuid ? {
      [uuid]: item.position.x / instance.columnWidth
    } : {});
  }, {});
};

})(window, document, jQuery);
