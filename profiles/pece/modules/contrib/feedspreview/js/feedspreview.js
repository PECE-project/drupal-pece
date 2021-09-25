/**
 * @file
 * Javascript for previous/next record.
 */
(function ($) {

  /**
   * Process controls.
   */
  Drupal.behaviors.feedsPreviewControls = {
    attach: function (context) {

      // Process previous link.
      $('.feeds-preview-controls-previous:not(.feeds-preview-controls-previous-processed)', context).addClass('feeds-preview-controls-previous-processed').each(function() {
        var previewID = $(this).attr('id').replace('feeds-preview-controls-previous-', '');
        $(this).click(function() {
          Drupal.feedsPreview.prev({ "previewID": previewID });
          return false;
        });

        $(document).keydown(function(element) {
          if (element.which == 37) {
            Drupal.feedsPreview.prev({ "previewID": previewID });
          }
        });
      });

      // Process next link.
      $('.feeds-preview-controls-next:not(.feeds-preview-controls-next-processed)', context).addClass('feeds-preview-controls-next-processed').each(function() {
        var previewID = $(this).attr('id').replace('feeds-preview-controls-next-', '');
        $(this).click(function() {
          Drupal.feedsPreview.next({ "previewID": previewID });
          return false;
        });

        $(document).keydown(function(element) {
          if (element.which == 39) {
            Drupal.feedsPreview.next({ "previewID": previewID });
          }
        });
      });
    }
  };

  /**
   * Collapse content.
   */
  Drupal.behaviors.feedsPreviewCollapseLongContent = {
    attach: function (context) {
      // Add "Read more" links for every text that is too long.
      $('.feeds-preview-long-content:not(.feeds-preview-long-content-processed)', context).addClass('feeds-preview-long-content-processed').each(function() {

        var current = $(this);

        // Create more link.
        var link = document.createElement('a');
        $(link).attr('href', '#')
        $(link).append(Drupal.t('Read more'));
        $(this).after(link);

        $(link).click(function() {
          Drupal.feedsPreview.toggle(this, current);
          return false;
        });
      });
    }
  };

  /**
   * Feeds Preview object.
   */
  Drupal.feedsPreview = Drupal.feedsPreview || {};

  /**
   * Toggler.
   *
   * Toggles collapsed/non-collapsed texts.
   *
   * @todo add slide effect?
   */
  Drupal.feedsPreview.toggle = function (trigger, element, event) {
    if ($(element).hasClass('collapsed')) {
      $(element).removeClass('collapsed');
      $(trigger).contents().remove();
      $(trigger).append(Drupal.t('Close'));
    }
    else {
      $(element).addClass('collapsed');
      $(trigger).contents().remove();
      $(trigger).append(Drupal.t('Read more'));
    }
  };

  /**
   * Go to a particular item.
   */
  Drupal.feedsPreview.goTo = function (itemNum, options) {
    // Remove active class from items.
    $('.feeds-preview-table-' + options.previewID).removeClass('active');

    // Add active class to active item.
    $('#feeds-preview-table-item-' + options.previewID + '-' + itemNum).addClass('active');

    $('#feeds-preview-result-summary-current-' + options.previewID).text(itemNum + 1);

    Drupal.settings.feedsPreview[options.previewID].activeItem = itemNum;
  };

  /**
   * Shows previous item.
   */
  Drupal.feedsPreview.prev = function (options) {
    // Get the current active item.
    var itemNum = Drupal.settings.feedsPreview[options.previewID].activeItem;

    // If we are on the first item then show the last item.
    // Otherwise show the previous item.
    if (itemNum == 0) {
      itemNum = $('.feeds-preview-table-' + options.previewID).length - 1;
    }
    else {
      itemNum--;
    }

    this.goTo(itemNum, options);
  };

  /**
   * Shows next item.
   */
  Drupal.feedsPreview.next = function (options) {
    // Get the current active item.
    var itemNum = Drupal.settings.feedsPreview[options.previewID].activeItem;
    var total = $('.feeds-preview-table-' + options.previewID).length;

    // If we are on the last item then activate the first item.
    // Otherwise activate the next item.
    itemNum++;
    if (itemNum == total) {
      itemNum = 0;
    }

    this.goTo(itemNum, options);
  };

})(jQuery);
