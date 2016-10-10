/**
 * @file
 * Custom scripts for theme.
 */

(function (window, document, $, undefined) {

Drupal.behaviors.panelsPackery = {
  attach: function (context, settings) {
    $.each(settings.packery || {}, function (selector, config) {
      $(selector, context).each(initializePackery(config));
    });
  }
};

/**
 * Packery initializer factory.
 */
function initializePackery(config) {
  return function () {
    var $container = $(this);
    var $items = $container.find(config.itemSelector)

    var columnWidth = $items.toArray().reduce(function (prev, item) {
      return Math.min(prev, $(item).outerWidth());
    }, Infinity)

    if (!$container.data('packery')) {
      $container.packery({
        itemSelector: config.itemSelector,
        columnWidth: columnWidth,
        initLayout: !config.items
      });

      if (config.items) {
        $container.packery('applySavedLayout', config.items);
      }
    }
  };
}


// Custom Packery.prototype methods.
// ---------------------------------

Packery.prototype.applySavedLayout = function (items, attr) {
  var instance = this;
  var $container = $(instance.element)

  this._resetLayout();

  this.items = this.items.map(function (item) {
    var $element = $(item.element)
    var uuid = $element
      .filter('[data-pane-uuid]')
      .add($element.find('[data-pane-uuid]'))
      .attr('data-pane-uuid');

    // Safe guard.
    if (!uuid || !items[uuid]) return item;

    item.rect.x = items[uuid].position * instance.columnWidth;
    item.rect.width = items[uuid].size * instance.columnWidth;

    $element.addClass('size-' + items[uuid].size)

    return item;
  });

  this.shiftLayout();
};

})(window, document, jQuery);
