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


// AJAX listeners.
// ---------------

$(document).on('ajaxSuccess', handleAjaxSuccess);

/**
 * Listen to any ajax completition to update layout when needed.
 */
function handleAjaxSuccess(e, res, req, commands) {
  // Do not handle non-Drupal ajax request.
  if (!res.responseText || res.responseText.indexOf('[{"command"') !== 0) return;

  var operations = {
    'edit': req.url.match(/^\/panels\/ajax\/ipe\/edit-pane/),
    'add': req.url.match(/^\/panels\/ajax\/ipe\/add-pane/)
  };

  var operation = Object.keys(operations).filter(function (type) {
    return operations[type];
  })[0];

  var ajaxListener = ajaxListeners[operation];

  // Find if any operation was found.
  if (ajaxListener) {
    var ipeWrapperSelector = commands.reduce(function (prev, command) {
      return prev || (command.command === 'changed' ? command.selector : null);
    }, null);

    if (ipeWrapperSelector) {
      var $container = $(ipeWrapperSelector).find('.panels-ipe-sort-container');
      var configSelector = Object.keys(Drupal.settings.packery || {}).filter(function (selector) {
        return $container.is(selector)
      })[0];
      var config = Drupal.settings.packery && Drupal.settings.packery[configSelector]

      // Safe exit.
      if ($container.length === 0 || !config) return;

      ajaxListener($container, config, commands);
    }
  }
}

var ajaxListeners = {
  'edit': function ($container, config, commands) {
    var instance = $container.data('packery');
    var itemSelector = commands.reduce(function (prev, command) {
      return prev || (command.command === 'insert' && command.method === 'replaceWith' ? command.selector : null);
    }, null)

    var item = instance.items.find(function (item) {
      return jQuery(item.element).is(itemSelector)
    });

    var replacement = $container.find(itemSelector).get(0)

    // Safe exit.
    if (!item || !replacement) return false;

    var classes = $(item.element).attr('class');

    item.element = replacement;
    item.moveTo(item.rect.x, item.rect.y)

    $(item.element)
      .addClass(classes)
      .each(attachItemBehaviors($container));
  },
  'add': function ($container) {
    var instance = $container.data('packery');

    var $packeryItems = $($container.packery('getItemElements'));
    var $allItems = $container.find(instance.options.itemSelector);
    var $newItems = $allItems.filter(function () {
      return !$packeryItems.filter(this).length
    });

    $container.packery('prepended', $newItems);
    $newItems.each(attachItemBehaviors($container));
  }
}

})(window, document, jQuery);
