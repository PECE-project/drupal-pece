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

    if (!$container.data('packery')) {
      $container.packery({
        itemSelector: config.itemSelector,
        columnWidth: config.itemSelector,
        initLayout: !config.positions
      });

      if (config.positions) {
        $container.packery('applySavedLayout', config.positions);
      }
    }
  };
}


// Custom Packery.prototype methods.
// ---------------------------------

Packery.prototype.applySavedLayout = function (positions, attr) {
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
    if (!uuid || !positions[uuid]) return item;

    item.rect.x = positions[uuid] * instance.columnWidth;

    return item;
  });

  this.shiftLayout();
};

})(window, document, jQuery);
