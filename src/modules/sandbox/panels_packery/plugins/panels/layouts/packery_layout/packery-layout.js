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

    var columnWidth = $container.width() / 12;

    if (!$container.data('packery')) {
      // Default items to a third of container.
      if (!config.items) {
        $items.width(columnWidth * 4);
      }

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

/**
 * Custom Packery method to apply saved layout.
 */
Packery.prototype.applySavedLayout = function (items) {
  var instance = this;
  var $container = $(instance.element);
  var defaultItem = { position: 0, size: 4 };

  this._resetLayout();

  this.items = this.items.map(function (item) {
    var $element = $(item.element)
    var uuid = $element
      .filter('[data-pane-uuid]')
      .add($element.find('[data-pane-uuid]'))
      .attr('data-pane-uuid');

    var itemConfig = items[uuid] || defaultItem

    item.rect.x = itemConfig.position * instance.columnWidth;
    item.rect.width = itemConfig.size * instance.columnWidth;

    $element.addClass('col-md-' + itemConfig.size)

    return item;
  });

  this.shiftLayout();
};

})(window, document, jQuery);
