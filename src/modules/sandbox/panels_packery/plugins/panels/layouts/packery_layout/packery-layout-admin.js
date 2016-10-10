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

$(document).on('ajaxSuccess', handleAjaxSuccess);

/**
 * Packery initializer factory.
 */
function initializePackeryAdmin(config) {
  var ipe = Drupal.PanelsIPE.editors[config.IPECacheKeys];

  return function () {
    var $container = $(this);
    var $items = $($container.packery('getItemElements'));

    // Attach items behavior.
    $items.each(attachItemBehaviors($container))

    $container
      .on('sortremove', refreshLayout)
      .on('dragItemPositioned resizestop', reorder)
      .on('dragItemPositioned resizestop', save(ipe));
  };
}

/**
 * Refresh layout.
 */
function refreshLayout() {
  $(this).packery('shiftLayout');
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

/**
 * Attach behaviors to a single item.
 */
function attachItemBehaviors($container) {
  var instance = $container.data('packery');

  return function () {
    var item = this;
    var $item = $(item);

    // Attach draggable events.
    $container.packery('bindDraggabillyEvents', new Draggabilly(item, {
      handle: '.panel-pane'
    }));

    $item.resizable({
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
  }
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

/**
 * Listen to any ajax completition to update layout when needed.
 */
function handleAjaxSuccess(e, res, req, commands) {
  // Do not handle non-Drupal ajax request.
  if (!res.responseText || res.responseText.indexOf('[{"command"') !== 0) return;

  var isAddingPane = commands.map(commandName).indexOf('insertNewPane') !== -1;

  // Do not handle non pane adding ajax requests.
  if (!isAddingPane) return;

  commands.forEach(function (command) {
    if (command.command === 'changed') {
      // Refresh packery layout.
      var $container = $(command.selector).find('.panels-ipe-sort-container');
      var instance = $container.data('packery');
      var $packeryItems = $($container.packery('getItemElements'));
      var $allItems = $container.find(instance.options.itemSelector);

      var $newItems = $allItems.filter(function () {
        return !$packeryItems.filter(this).length
      });

      $container.packery('prepended', $newItems);
      $newItems.each(attachItemBehaviors($container));
    }
  });
}

function commandName(command) {
  return command.command
}

})(window, document, jQuery);
