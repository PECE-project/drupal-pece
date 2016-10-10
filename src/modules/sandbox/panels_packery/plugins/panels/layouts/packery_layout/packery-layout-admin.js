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
    var instance = $container.data('packery');
    var $items = $($container.packery('getItemElements'));
    var $form = $('#panels-ipe-edit-control-form');

    // Attach draggable events.
    $items.each(function (i, item) {
      $container.packery('bindDraggabillyEvents', new Draggabilly(item, {
        handle: '.panel-pane'
      }));
    });

    $items.resizable({
      containment: 'parent',
      grid: instance.columnWidth,
      handles: 'e,w',
      resize: function(event, ui) {
        $container.packery('fit', event.target, ui.position.left, ui.position.top);
      },
      stop: function(event, ui) {
        $container.packery('shiftLayout');
      }
    });

    $container
      .on('dragItemPositioned resizestop', reorder)
      .on('dragItemPositioned resizestop', save(ipe));
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
 * After modiying, save position and size of each item.
 *
 * @TODO: find 'name' inside ipe instance form.
 */
function save(ipe) {
  var $form = ipe.container.find('form');
  var $input = $form.find('[name="packery_items"]');

  if (!$input.length) {
    var $input = $('<input type="hidden" name="packery_items" value="{}" />').appendTo($form);
  }

  return function () {
    $input.val(JSON.stringify($(this).packery('getItemsInfo')))
  };
}


// Custom Packery.prototype methods.
// ---------------------------------

/**
 * Get JSON positioning data from items.
 */
Packery.prototype.getItemsInfo = function () {
  var instance = this

  return this.items.reduce(function (result, item) {
    var uuid = $(item.element).find('[data-pane-uuid]').data('pane-uuid') || null;

    return $.extend(result, uuid ? {
      [uuid]: {
        position: Math.round(item.position.x / instance.columnWidth),
        size: Math.round(item.rect.width / instance.columnWidth)
      }
    } : {});
  }, {});
};

})(window, document, jQuery);
